#ifndef _INDEXER_H
#define _INDEXER_H
#include <pthread.h>
#include "include/const.h"
#include "file-list.h"
#include "hash-list.h"
#include "red-black-tree.h"

typedef struct _INDEXER_BUFFER{
    Hash_list **buffer;
    int end;        // final d'indexacio (se activa con barrera)
    int quantity;   // quantitat pendent d'indexar al buffer
    int iposition;  // posicio del seguent a indexar
    int pposition;  // posicio del seguent procesat
    int length;
}Indexer_buffer;

typedef struct _INDEXER_CONTEXT{
    RBTree *tree;
}Indexer_context;

void *indexador(void *arg);
int init_indexer( int buffersize);

Indexer_buffer *ibuffer;
pthread_mutex_t mutex_shared;
pthread_cond_t cond_indexar;
pthread_cond_t cond_procesar;
#endif 
