#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <stdexcept>
#include <exception>
#include <vector>
#include <list>
using namespace std;
// g++ -lpthread -Wall main.cpp -o lru
// g++ -std=c++11 -lpthread -Wall main.cpp -o lru

#ifndef CACHE_LRU_H
#define CACHE_LRU_H

class cache {
    private:
        pthread_mutex_t lock;
        // hash/heap
        vector <list <pair <unsigned long,unsigned long>>::iterator> heapArr;
        unsigned long heapSize;

        // queue/fifo
        list <pair <unsigned long,unsigned long>> cQueue;
        unsigned long cacheSize;

        inline int cacheMiss(unsigned long key);
        inline int cacheHit(unsigned long key);

    public:
        int refereCache(unsigned long);
        cache(int heapSize, int cacheSize);
        ~cache();
};

cache::cache(int heapSize, int cacheSize) {
    if (heapSize < 1 || cacheSize < 1) {
        throw std::invalid_argument("\nCache size/Heap \
                Capacity should be at least 1\n");
    }

    this->heapSize = heapSize;
    this->cacheSize = cacheSize;
    heapArr.resize(heapSize);
    pthread_mutex_init(&lock, NULL);
}

cache::~cache()
{
    pthread_mutex_destroy(&lock);
}

inline int cache::cacheMiss(unsigned long key) {
    if (cQueue.size() >= cacheSize) {
        list<pair<unsigned long, unsigned long>>::iterator it = cQueue.end();
        it--;
        heapArr[(*it).first] = list <pair<unsigned long, unsigned long>>::iterator();
        cQueue.pop_back();
    }

    try {
        cQueue.push_front(std::make_pair(key, key+1));
    } catch (...) {
        throw std::invalid_argument("\nenQueue Operation failure<push_front>");
    }

    heapArr[key] = cQueue.begin();
    return (*heapArr[key]).second;
}

inline int cache::cacheHit(unsigned long key) {
    try {
        cQueue.splice(cQueue.begin(), cQueue, heapArr[key]);
    } catch (...) {
        throw std::invalid_argument("\nenQueue Operation failure<splice>");
    }
    return (*heapArr[key]).second;
}

int cache::refereCache(unsigned long key) {
    int ret = 0;
    list <pair<unsigned long, int>>::iterator it;

    if (key > heapSize) {
        throw std::invalid_argument("\nReference Key \
                out of range.\n");
    }

    pthread_mutex_lock(&lock);
    try {
        if ( heapArr[key] != list <pair<unsigned long, unsigned long>>::iterator()) {
            ret = cacheHit(key);
        } else {
            ret = cacheMiss(key);
        }
    } catch(...) {
        pthread_mutex_unlock(&lock);
        throw std::invalid_argument("\nrefer cache failure.");
    }

    pthread_mutex_unlock(&lock);
    return ret;
}

#endif
