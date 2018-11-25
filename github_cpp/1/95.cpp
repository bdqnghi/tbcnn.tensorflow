

#ident "$Id$"


#ident "Copyright (c) 2006, 2015, Percona and/or its affiliates. All rights reserved."

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "portability/toku_assert.h"
#include "portability/memory.h"

#include "ft/ft-internal.h"
#include "ft/serialize/ft_node-serialize.h"
#include "loader/dbufio.h"
#include "loader/loader-internal.h"

toku_instr_key *bfs_mutex_key;
toku_instr_key *bfs_cond_key;
toku_instr_key *io_thread_key;

struct dbufio_file {
    
    int fd;

    
    size_t offset_in_buf;
    toku_off_t  offset_in_uncompressed_file;

    
    struct dbufio_file *next;
    bool   second_buf_ready; 

    
    char *buf[2];
    size_t n_in_buf[2];
    int    error_code[2]; 

    bool io_done;
};



struct dbufio_fileset {
    
    
    
    
    
    toku_mutex_t mutex;
    toku_cond_t  cond;
    int N; 
    int n_not_done; 
    struct dbufio_file *files;     
    struct dbufio_file *head, *tail; 
    size_t bufsize; 

    bool panic;
    bool compressed;
    int  panic_errno;
    toku_pthread_t iothread;
};


static void enq (DBUFIO_FILESET bfs, struct dbufio_file *f) {
    if (bfs->tail==NULL) {
	bfs->head = f;
    } else {
	bfs->tail->next = f;
    }
    bfs->tail = f;
    f->next = NULL;
}

static void panic (DBUFIO_FILESET bfs, int r) {
    if (bfs->panic) return;
    bfs->panic_errno = r; 
    bfs->panic = true;
    return;
}

static bool paniced (DBUFIO_FILESET bfs) {
    return bfs->panic;
}

static ssize_t dbf_read_some_compressed(struct dbufio_file *dbf, char *buf, size_t bufsize) {
    ssize_t ret;
    invariant(bufsize >= MAX_UNCOMPRESSED_BUF);
    unsigned char *raw_block = NULL;

    

    
    
    
    ssize_t readcode;
    const uint32_t header_size = sizeof(uint32_t);
    char header[header_size];

    readcode = toku_os_read(dbf->fd, &header, header_size);
    if (readcode < 0) {
        ret = -1;
        goto exit;
    }
    if (readcode == 0) {
        ret = 0;
        goto exit;
    }
    if (readcode < header_size) {
        errno = TOKUDB_NO_DATA;
        ret = -1;
        goto exit;
    }
    uint32_t total_size;
    {
        uint32_t *p = (uint32_t *) &header[0];
        total_size = toku_dtoh32(p[0]);
    }
    if (total_size == 0 || total_size > (1<<30)) {
        errno = toku_db_badformat(); 
        ret = -1;
        goto exit;
    }

    
    MALLOC_N(total_size, raw_block);
    if (raw_block == nullptr) {
        errno = ENOMEM;
        ret = -1;
        goto exit;
    }
    readcode = toku_os_read(dbf->fd, raw_block, total_size);
    if (readcode < 0) {
        ret = -1;
        goto exit;
    }
    if (readcode < total_size) {
        errno = TOKUDB_NO_DATA;
        ret = -1;
        goto exit;
    }

    struct sub_block sub_block[max_sub_blocks];
    uint32_t *sub_block_header;
    sub_block_header = (uint32_t *) &raw_block[0];
    int32_t n_sub_blocks;
    n_sub_blocks = toku_dtoh32(sub_block_header[0]);
    sub_block_header++;
    size_t size_subblock_header;
    size_subblock_header = sub_block_header_size(n_sub_blocks);
    if (n_sub_blocks == 0 || n_sub_blocks > max_sub_blocks || size_subblock_header > total_size) {
        errno = toku_db_badformat(); 
        ret = -1;
        goto exit;
    }
    for (int i = 0; i < n_sub_blocks; i++) {
        sub_block_init(&sub_block[i]);
        sub_block[i].compressed_size = toku_dtoh32(sub_block_header[0]);
        sub_block[i].uncompressed_size = toku_dtoh32(sub_block_header[1]);
        sub_block[i].xsum = toku_dtoh32(sub_block_header[2]);
        sub_block_header += 3;
    }

    
    size_t total_compressed_size;
    total_compressed_size = 0;
    for (int i = 0; i < n_sub_blocks; i++) {
        uint32_t compressed_size = sub_block[i].compressed_size;
        if (compressed_size<=0   || compressed_size>(1<<30)) { 
            errno = toku_db_badformat(); 
            ret = -1;
            goto exit;
        }

        uint32_t uncompressed_size = sub_block[i].uncompressed_size;
        if (uncompressed_size<=0 || uncompressed_size>(1<<30)) { 
            errno = toku_db_badformat(); 
            ret = -1;
            goto exit;
        }
        total_compressed_size += compressed_size;
    }
    if (total_size != total_compressed_size + size_subblock_header) {
        errno = toku_db_badformat(); 
        ret = -1;
        goto exit;
    }

    
    size_t uncompressed_size;
    uncompressed_size = get_sum_uncompressed_size(n_sub_blocks, sub_block);
    if (uncompressed_size > bufsize || uncompressed_size > MAX_UNCOMPRESSED_BUF) {
        errno = toku_db_badformat(); 
        ret = -1;
        goto exit;
    }

    unsigned char *uncompressed_data;
    uncompressed_data = (unsigned char *)buf;

    
    unsigned char *compressed_data;
    compressed_data = raw_block + size_subblock_header;

    
    {
        int r;
        r = decompress_all_sub_blocks(n_sub_blocks, sub_block, compressed_data, uncompressed_data, get_num_cores(), get_ft_pool());
        if (r != 0) {
            fprintf(stderr, "%s:%d loader failed %d at %p size %" PRIu32"\n", __FUNCTION__, __LINE__, r, raw_block, total_size);
            dump_bad_block(raw_block, total_size);
            errno = r;
            ret = -1;
            goto exit;
        }
    }
    ret = uncompressed_size;
exit:
    if (raw_block) {
        toku_free(raw_block);
    }
    return ret;
}

static ssize_t dbf_read_compressed(struct dbufio_file *dbf, char *buf, size_t bufsize) {
    invariant(bufsize >= MAX_UNCOMPRESSED_BUF);
    size_t count = 0;

    while (count + MAX_UNCOMPRESSED_BUF <= bufsize) {
        ssize_t readcode = dbf_read_some_compressed(dbf, buf + count, bufsize - count);
        if (readcode < 0) {
            return readcode;
        }
        count += readcode;
        if (readcode == 0) {
            break;
        }
    }
    return count;
}

static void* io_thread (void *v)

{
    DBUFIO_FILESET bfs = (DBUFIO_FILESET)v;
    toku_mutex_lock(&bfs->mutex);
    
    while (1) {
        if (paniced(bfs)) {
            toku_mutex_unlock(&bfs->mutex);  
            toku_instr_delete_current_thread();
            return toku_pthread_done(nullptr);
        }
        
        if (bfs->n_not_done == 0) {
            
            
            
            toku_mutex_unlock(&bfs->mutex);
            toku_instr_delete_current_thread();
            return toku_pthread_done(nullptr);
        }

        struct dbufio_file *dbf = bfs->head;
        if (dbf == NULL) {
            
            
            toku_cond_wait(&bfs->cond, &bfs->mutex);
            if (paniced(bfs)) {
                toku_mutex_unlock(&bfs->mutex);  
                toku_instr_delete_current_thread();
                return toku_pthread_done(nullptr);
            }
            
        } else {
            
            
            assert(dbf->second_buf_ready == false);
            assert(!dbf->io_done);
            bfs->head = dbf->next;
            if (bfs->head == NULL)
                bfs->tail = NULL;

            
            
            
            toku_mutex_unlock(&bfs->mutex);
	    
	    {
		ssize_t readcode;
                if (bfs->compressed) {
                    readcode = dbf_read_compressed(dbf, dbf->buf[1], bfs->bufsize);
                }
                else {
                    readcode = toku_os_read(dbf->fd, dbf->buf[1], bfs->bufsize);
                }
		
		if (readcode==-1) {
		    
                    int the_errno = get_error_errno();
                    fprintf(stderr, "%s:%d dbf=%p fd=%d errno=%d\n", __FILE__, __LINE__, dbf, dbf->fd, the_errno);
		    dbf->error_code[1] = the_errno;
		    dbf->n_in_buf[1] = 0;
		} else if (readcode==0) {
		    
		    dbf->error_code[1] = EOF;
		    dbf->n_in_buf[1] = 0;
		    dbf->io_done = true;
		    
		} else {
		    dbf->error_code[1] = 0;
		    dbf->n_in_buf[1] = readcode;
		}

		
		{
            toku_mutex_lock(&bfs->mutex);
            if (paniced(bfs)) {
                toku_mutex_unlock(&bfs->mutex);  
                toku_instr_delete_current_thread();
                return toku_pthread_done(nullptr);
            }
        }
        
        
        if (readcode<=0) {
		    bfs->n_not_done--;
		}
		
		dbf->second_buf_ready = true;
                toku_cond_broadcast(&bfs->cond);
		
		
	    }
	}
    }
}

int create_dbufio_fileset (DBUFIO_FILESET *bfsp, int N, int fds[], size_t bufsize, bool compressed) {
    
    int result = 0;
    DBUFIO_FILESET CALLOC(bfs);
    if (bfs==0) { result = get_error_errno(); }

    bfs->compressed = compressed;

    bool mutex_inited = false, cond_inited = false;
    if (result==0) {
	CALLOC_N(N, bfs->files);
	if (bfs->files==NULL) { result = get_error_errno(); }
	else {
	    for (int i=0; i<N; i++) {
		bfs->files[i].buf[0] = bfs->files[i].buf[1] = NULL;
	    }
	}
    }
    
    if (result == 0) {
        toku_mutex_init(*bfs_mutex_key, &bfs->mutex, nullptr);
        mutex_inited = true;
    }
    if (result == 0) {
        toku_cond_init(*bfs_cond_key, &bfs->cond, nullptr);
        cond_inited = true;
    }
    if (result == 0) {
        bfs->N = N;
        bfs->n_not_done = N;
        bfs->head = bfs->tail = NULL;
        for (int i = 0; i < N; i++) {
            bfs->files[i].fd = fds[i];
            bfs->files[i].offset_in_buf = 0;
            bfs->files[i].offset_in_uncompressed_file = 0;
            bfs->files[i].next = NULL;
            bfs->files[i].second_buf_ready = false;
            for (int j = 0; j < 2; j++) {
                if (result == 0) {
                    MALLOC_N(bufsize, bfs->files[i].buf[j]);
                    if (bfs->files[i].buf[j] == NULL) {
                        result = get_error_errno();
                    }
                }
                bfs->files[i].n_in_buf[j] = 0;
                bfs->files[i].error_code[j] = 0;
            }
            bfs->files[i].io_done = false;
            ssize_t r;
            if (bfs->compressed) {
                r = dbf_read_compressed(&bfs->files[i], bfs->files[i].buf[0], bufsize);
            } else {
		r = toku_os_read(bfs->files[i].fd, bfs->files[i].buf[0], bufsize);
            }
            {
		if (r<0) {
		    result=get_error_errno();
		    break;
                } else if (r==0) {
		    
		    bfs->files[i].io_done = true;
		    bfs->n_not_done--;
		    bfs->files[i].error_code[0] = EOF;
		} else {
		    bfs->files[i].n_in_buf[0] = r;
		    
		    enq(bfs, &bfs->files[i]);
		}
	    }
	}
	bfs->bufsize = bufsize;
	bfs->panic = false;
	bfs->panic_errno = 0;
    }
    
    if (result == 0) {
        result = toku_pthread_create(*io_thread_key,
                                     &bfs->iothread,
                                     nullptr,
                                     io_thread,
                                     static_cast<void *>(bfs));
    }
    if (result == 0) {
        *bfsp = bfs;
        return 0;
    }
    
    
    
    if (bfs) {
	if (bfs->files) {
	    
	    for (int i=0; i<N; i++) {
		for (int j=0; j<2; j++) {
		    if (bfs->files[i].buf[j])
			toku_free(bfs->files[i].buf[j]);
		    bfs->files[i].buf[j]=NULL;
		}
	    }
	    toku_free(bfs->files);
	    bfs->files=NULL;
	}
	if (cond_inited) {
	    toku_cond_destroy(&bfs->cond);  
	}
	if (mutex_inited) {
	    toku_mutex_destroy(&bfs->mutex); 
	}
	toku_free(bfs);
    }
    return result;
}

int panic_dbufio_fileset(DBUFIO_FILESET bfs, int error) {
    toku_mutex_lock(&bfs->mutex);
    panic(bfs, error);
    toku_cond_broadcast(&bfs->cond);
    toku_mutex_unlock(&bfs->mutex);
    return 0;
}

int destroy_dbufio_fileset (DBUFIO_FILESET bfs) {
    int result = 0;
    {
	void *retval;
	int r = toku_pthread_join(bfs->iothread, &retval);
	assert(r==0);
	assert(retval==NULL);
    }
    {
	toku_mutex_destroy(&bfs->mutex);
    }
    {
	toku_cond_destroy(&bfs->cond);
    }
    if (bfs->files) {
	for (int i=0; i<bfs->N; i++) {
	    for (int j=0; j<2; j++) {
		
		toku_free(bfs->files[i].buf[j]);
	    }
	}
	toku_free(bfs->files);
    }
    toku_free(bfs);
    return result;
}

int dbufio_fileset_read (DBUFIO_FILESET bfs, int filenum, void *buf_v, size_t count, size_t *n_read) {
    char *buf = (char*)buf_v;
    struct dbufio_file *dbf = &bfs->files[filenum];
    if (dbf->error_code[0]!=0) return dbf->error_code[0];
    if (dbf->offset_in_buf + count <= dbf->n_in_buf[0]) {
	
	memcpy(buf, dbf->buf[0]+dbf->offset_in_buf, count);
	dbf->offset_in_buf += count;
	dbf->offset_in_uncompressed_file += count;
	*n_read = count;
	return 0;
    } else if (dbf->n_in_buf[0] > dbf->offset_in_buf) {
	
	size_t this_count = dbf->n_in_buf[0]-dbf->offset_in_buf;
	assert(dbf->offset_in_buf + this_count <= bfs->bufsize);
	memcpy(buf, dbf->buf[0]+dbf->offset_in_buf, this_count);
	dbf->offset_in_buf += this_count;
	dbf->offset_in_uncompressed_file += this_count;
	size_t sub_n_read;
	int r = dbufio_fileset_read(bfs, filenum, buf+this_count, count-this_count, &sub_n_read);
	if (r==0) {
	    *n_read = this_count + sub_n_read;
	    return 0;
	} else {
	    
	    *n_read = this_count;
	    return 0;
	}
    } else {
	
	toku_mutex_lock(&bfs->mutex);
	while (1) {
	    if (dbf->second_buf_ready) {
		dbf->n_in_buf[0] = dbf->n_in_buf[1];
		{
		    char *tmp = dbf->buf[0];
		    dbf->buf[0]      = dbf->buf[1];
		    dbf->buf[1]      = tmp;
		}
		dbf->error_code[0] = dbf->error_code[1];
		dbf->second_buf_ready = false;
		dbf->offset_in_buf = 0;
		if (!dbf->io_done) {
		    
		    
		    enq(bfs, dbf);
		}
		toku_cond_broadcast(&bfs->cond);
		toku_mutex_unlock(&bfs->mutex);
		if (dbf->error_code[0]==0) {
		    assert(dbf->n_in_buf[0]>0);
		    return dbufio_fileset_read(bfs, filenum, buf_v, count, n_read);
		} else {
		    *n_read = 0;
		    return dbf->error_code[0];
		}
	    } else {
		toku_cond_wait(&bfs->cond, &bfs->mutex);
	    }
	}
	assert(0); 
    }
}

void
dbufio_print(DBUFIO_FILESET bfs) {
    fprintf(stderr, "%s:%d bfs=%p", __FILE__, __LINE__, bfs);
    if (bfs->panic)
        fprintf(stderr, " panic=%d", bfs->panic_errno);
    fprintf(stderr, " N=%d %d %" PRIuMAX, bfs->N, bfs->n_not_done, bfs->bufsize);
    for (int i = 0; i < bfs->N; i++) {
        struct dbufio_file *dbf = &bfs->files[i];
        if (dbf->error_code[0] || dbf->error_code[1])
            fprintf(stderr, " %d=[%d,%d]", i, dbf->error_code[0], dbf->error_code[1]);
    }
    fprintf(stderr, "\n");
                
}
