#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <stdexcept>
#include <exception>
using namespace std;




#ifndef CACHE_LRU_H
#define CACHE_LRU_H

class cacheNode
{
    public:
        cacheNode *next, *prev;
        int key;
        int data;
        cacheNode(int key=-1, int data=-1, cacheNode *next=NULL,
                cacheNode *prev=NULL);
};

cacheNode::cacheNode(int key, int data, cacheNode *next, cacheNode *prev)
{
    this->key=key;
    this->data=data;
    this->next=next;
    this->prev=prev;
}

class cacheQueue {
    public:
        int qMaxSize, qCount;
        cacheNode *qFront, *qRear;

        cacheQueue(int qMaxSize)
        {
            this->qMaxSize = qMaxSize;
            qCount = 0;
            qFront = NULL;
            qRear = NULL;
        }

        virtual ~cacheQueue()=0;
};

cacheQueue::~cacheQueue()
{
    cacheNode *tmp = qFront;

    while (tmp != NULL)
        delete tmp;
}

class cacheHeap
{
    public:
        int hCapacity;
        cacheNode **heapArr;
        cacheHeap(int hCapacity);

        virtual ~cacheHeap()=0;
};

cacheHeap::~cacheHeap()
{
    delete [] heapArr;
}

cacheHeap::cacheHeap(int hCapacity): hCapacity(hCapacity)
{
    if (hCapacity < 1)
        throw std::invalid_argument("\nHeap Capacity should be at least 1\n");

    heapArr = new cacheNode*[hCapacity]();
}


class cache: private cacheQueue, private cacheHeap
{
    private:
        pthread_mutex_t lock;
        inline bool isCacheHit(int key);
        int cacheMiss(int key);
        int cacheHit(int key);
        int enQueue(cacheNode *n);
        cacheNode *deQueue(void);
    public:
        cache(int heapCapacity, int cacheSize);
        ~cache();
        int refereCache(int key);
};

cache::cache(int heapCapacity, int cacheSize): cacheQueue(cacheSize),
    cacheHeap(heapCapacity)
{
    if (heapCapacity < 1 || cacheSize < 1)
        throw std::invalid_argument("\nCache size/Heap \
                Capacity should be at least 1\n");

    pthread_mutex_init(&lock, NULL);
}

cache::~cache()
{
    pthread_mutex_destroy(&lock);
}

cacheNode *cache::deQueue()
{
    cacheNode *n = qRear;
    if (n != NULL)
    {
        heapArr[qRear->key] = NULL;
        qRear = qRear->prev;
        if (NULL != qRear)
            qRear->next = NULL;
        else
            qFront = NULL;

        qCount--;
    }
    return n;
}

int cache::enQueue(cacheNode *n)
{
    n->next = qFront;
    if (qFront != NULL)
        qFront->prev = n;
    else
        qRear = n;

    n->prev = NULL;
    qFront = n;
    heapArr[n->key] = n;
    qCount++;
    return 0;
}

int cache::cacheMiss(int key)
{
    cacheNode *n;
    if (qCount >= qMaxSize)
        n = deQueue();
    else
        n = new cacheNode(key, random());

    enQueue(n);
    return n->data;
}

int cache::cacheHit(int key)
{
    cacheNode *n = heapArr[key];

    if (n == qFront)
        return n->data;

    if (n == qRear) {
        qRear = n->prev;
        qRear->next = NULL;
    } else {
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }

    n->prev = NULL;
    n->next = qFront;
    qFront->prev = n;
    qFront = n;
    return n->data;
}

inline bool cache::isCacheHit(int key) {
    return heapArr[key] == NULL ? false : true;
}

int cache::refereCache(int key) {
    int ret;

    pthread_mutex_lock(&lock);
    if (key > hCapacity) {
        pthread_mutex_unlock(&lock);
        printf("\nKey %d out of heap capacity %d\n", key, hCapacity);
        return -1;
    }

    ret = isCacheHit(key) ?  cacheHit(key) : cacheMiss(key);

    pthread_mutex_unlock(&lock);
    return ret;
}

#endif
