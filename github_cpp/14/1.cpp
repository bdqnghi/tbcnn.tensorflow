



#include "I_RadixSort.h"
#include "inktomi++.h"          

#undef NEW
#define NEW(x) x


struct RadixElem
{
  RadixElem *next;
};

class RadixSortImpl
{
public:
  RadixSortImpl(int elem_size, int n_elems);
   ~RadixSortImpl();

  
  void init();

  
  void add(char *elembytes);

  
  void sort();

  
  void iterStart();
  
  
  int iter(char *elemdata);

  
  void dumpBuckets();
private:
  void moveToTemp(RadixElem *);
  void moveToMain(RadixElem *);
  int elemHashToBucket(RadixElem *);

  
  RadixElem **m_bucket_head;
  RadixElem **m_bucket_tail;

  
  RadixElem **m_temp_head;
  RadixElem **m_temp_tail;

  
  RadixElem *m_freelist;
  
  RadixElem *m_data;

  
  int m_elem_size;
  
  int m_nbuckets;
  
  int m_nelems;
  
  int m_curradix;

  
  RadixElem *m_iter;
  int m_iter_bucket;
};

#define bucketptr(_b,_i) (RadixElem **)((char *)_b + sizeof(RadixElem) *_i)
#define data_next(_d) (((RadixElem *)_d)->next)
#define data_set_next(_d,_v) (((RadixElem *)_d)->next = _v)


#define data_elem(_base,_idx,_elsize) (RadixElem *)(_idx == 0 ? NULL : ((char *)_base + _idx * _elsize))
#define data_to_elemidx(_base,_data,_elsize) (((char *)_data - (char *)_base) / _elsize)

#define data_to_elemdata(_d) (((unsigned char *)_d) + sizeof(RadixElem))

#define data_setdata(_d,elemdata,elemsize) memcpy(data_to_elemdata(_d),elemdata,elemsize)


#define elem_to_radixval(_e,_pos) (* ((unsigned char *)_e + _pos))


#define NBUCKETS 256
#define MAXRADIXPOS(elemsize) (elemsize-1)


RadixSort::RadixSort(int elem_size, int n_elems)
  :
m_impl(NULL)
{
  m_impl = NEW(new RadixSortImpl(elem_size, n_elems));
}

RadixSort::~RadixSort()
{
  delete m_impl;
}

RadixSortImpl::RadixSortImpl(int elem_size, int n_elems)
  :
m_bucket_head(NULL)
  ,
m_bucket_tail(NULL)
  ,
m_temp_head(NULL)
  ,
m_temp_tail(NULL)
  ,
m_freelist(NULL)
  ,
m_data(NULL)
  ,
m_elem_size(0)
  ,
m_nbuckets(NBUCKETS)
  ,
m_nelems(n_elems)
  ,
m_curradix(0)
  ,
m_iter(NULL)
  ,
m_iter_bucket(0)
{
  m_elem_size = elem_size + sizeof(RadixElem);

  m_data = (RadixElem *) xmalloc(m_elem_size * m_nelems);

  m_bucket_head = (RadixElem **) xmalloc(m_nbuckets * sizeof(RadixElem *));
  m_bucket_tail = (RadixElem **) xmalloc(m_nbuckets * sizeof(RadixElem *));

  m_temp_head = (RadixElem **) xmalloc(m_nbuckets * sizeof(RadixElem *));
  m_temp_tail = (RadixElem **) xmalloc(m_nbuckets * sizeof(RadixElem *));

  init();
}

RadixSortImpl::~RadixSortImpl()
{
  if (m_data)
    xfree(m_data);

  if (m_bucket_head)
    xfree(m_bucket_head);
  if (m_bucket_tail)
    xfree(m_bucket_tail);

  if (m_temp_head)
    xfree(m_temp_head);
  if (m_temp_tail)
    xfree(m_temp_tail);
}

void
RadixSort::init()
{
  m_impl->init();
}

void
RadixSortImpl::init()
{
  
  m_curradix = MAXRADIXPOS(m_elem_size - sizeof(RadixElem));

  
  int i;
  for (i = 0; i < m_nbuckets; i++) {
    m_bucket_head[i] = NULL;
    m_bucket_tail[i] = NULL;
    m_temp_head[i] = NULL;
    m_temp_tail[i] = NULL;
  }

  
  m_freelist = data_elem(m_data, 1, m_elem_size);

  RadixElem *e = m_freelist;
  
  for (i = 2; i < m_nelems; i++) {
    data_set_next(e, data_elem(m_data, i, m_elem_size));
    e = data_elem(m_data, i, m_elem_size);
  }
}

void
RadixSort::iterStart()
{
  m_impl->iterStart();
}

void
RadixSortImpl::iterStart()
{
  m_iter_bucket = 0;
  RadixElem *e;
  m_iter = NULL;

  
  while (m_iter_bucket < m_nbuckets) {
    e = m_bucket_head[m_iter_bucket];
    m_iter_bucket++;
    if (e) {
      m_iter = e;
      break;
    }
  }
}

int
RadixSort::iter(char *elemdata)
{
  return m_impl->iter(elemdata);
}

int
RadixSortImpl::iter(char *elemdata)
{
  if (m_iter == NULL) {
    
    while (m_iter_bucket < m_nbuckets) {
      RadixElem *e = m_bucket_head[m_iter_bucket];
      m_iter_bucket++;
      if (e) {
        m_iter = e;
        break;
      }
    }
    if (!m_iter)
      return 0;
  }
  RadixElem *n = data_next(m_iter);
  memcpy(elemdata, data_to_elemdata(m_iter), m_elem_size - sizeof(RadixElem));

  m_iter = n;
  return 1;
}

int
RadixSortImpl::elemHashToBucket(RadixElem * e)
{
  unsigned char *d = data_to_elemdata(e);

  
  int b = elem_to_radixval(d, m_curradix);
  return b;
}

void
RadixSort::sort()
{
  m_impl->sort();
}

void
RadixSortImpl::sort()
{
  if (m_curradix == 3) {
    m_curradix--;
    for (int i = 0; i < m_nbuckets; i++) {
      RadixElem *e = m_bucket_head[i];
      while ((e = m_bucket_head[i])) {
        m_bucket_head[i] = data_next(e);
        data_set_next(e, NULL);
        moveToTemp(e);
      }
      m_bucket_head[i] = m_bucket_tail[i] = NULL;
    }
  }
  if (m_curradix == 2) {
    m_curradix--;
    for (int i = 0; i < m_nbuckets; i++) {
      RadixElem *e = m_temp_head[i];
      while ((e = m_temp_head[i])) {
        m_temp_head[i] = data_next(e);
        data_set_next(e, NULL);
        moveToMain(e);
      }
      m_temp_head[i] = m_temp_tail[i] = NULL;
    }
  }
  if (m_curradix == 1) {
    m_curradix--;
    for (int i = 0; i < m_nbuckets; i++) {
      RadixElem *e = m_bucket_head[i];
      while ((e = m_bucket_head[i])) {
        m_bucket_head[i] = data_next(e);
        data_set_next(e, NULL);
        moveToTemp(e);
      }
      m_bucket_head[i] = m_bucket_tail[i] = NULL;
    }
  }
  int i;
  for (i = 0; i < m_nbuckets; i++) {
    m_bucket_head[i] = m_temp_head[i];
    m_temp_head[i] = NULL;
    m_bucket_tail[i] = m_temp_tail[i];
    m_temp_tail[i] = NULL;
  }

  ink_assert(m_curradix == 0);  
}



void
RadixSortImpl::moveToTemp(RadixElem * e)
{
  int b = elemHashToBucket(e);
  
  if (m_temp_tail[b]) {
    RadixElem *t = m_temp_tail[b];
    data_set_next(t, e);
    m_temp_tail[b] = e;
  } else {
    m_temp_head[b] = m_temp_tail[b] = e;
  }
}



void
RadixSortImpl::moveToMain(RadixElem * e)
{
  int b = elemHashToBucket(e);

  
  if (m_bucket_tail[b]) {
    RadixElem *t = m_bucket_tail[b];
    data_set_next(t, e);
    m_bucket_tail[b] = e;
  } else {
    m_bucket_head[b] = m_bucket_tail[b] = e;
  }
}

void
RadixSort::add(char *elembytes)
{
  m_impl->add(elembytes);
}

void
RadixSortImpl::add(char *elembytes)
{
  
  RadixElem *e = m_freelist;
  ink_assert(e != NULL);        

  RadixElem *n = data_next(e);
  m_freelist = n;
  data_set_next(e, NULL);
  ink_assert(m_elem_size - sizeof(RadixElem) == 4);
  data_setdata(e, elembytes, m_elem_size - sizeof(RadixElem));

  moveToMain(e);
}


void
RadixSort::dumpBuckets()
{
  m_impl->dumpBuckets();
}

void
RadixSortImpl::dumpBuckets()
{
  int i;
  printf("main\n");
  for (i = 0; i < m_nbuckets; i++) {
    printf(" %d: ", i);
    RadixElem *e = m_bucket_head[i];
    while (e) {
      unsigned char *d = data_to_elemdata(e);
      printf("%d, ", *(int *) d);
      e = data_next(e);
    }
    printf("\n");
  }
  printf("temp\n");
  for (i = 0; i < m_nbuckets; i++) {
    printf(" %d: ", i);
    RadixElem *e = m_temp_head[i];
    while (e) {
      unsigned char *d = data_to_elemdata(e);
      printf("%d, ", *(int *) d);
      e = data_next(e);
    }
    printf("\n");
  }
}
