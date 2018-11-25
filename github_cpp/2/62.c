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



#ifndef CACHE_LRU_H
#define CACHE_LRU_H



template <typename K, typename V>
class cache {
    private:
        pthread_mutex_t lock;
        
        vector <typename list <pair <K,V>>::iterator> heapArr;
        K heapSize;

        
        list <pair <K,V>> cQueue;
        K cacheSize;

        inline V cacheMiss(K);
        inline V cacheHit(K);

    public:
        V refereCache(K);
        cache(K, K);
        ~cache();
};

template <typename K, typename V>
cache<K,V>::cache(K hSize, K cSize) {
    if (hSize < 1 || cSize < 1) {
        throw std::invalid_argument("\nCache size/Heap \
                Capacity should be at least 1\n");
    }

    this->heapSize = hSize;
    this->cacheSize = cSize;
    heapArr.resize(hSize);
    pthread_mutex_init(&lock, NULL);
}

template <typename K, typename V>
cache<K,V>::~cache()
{
    pthread_mutex_destroy(&lock);
}

template <typename K, typename V>
inline V cache<K,V>::cacheMiss(K  key) {
    if (cQueue.size() >= cacheSize) {
        typename list <pair <K,V>>::iterator it = cQueue.end();
        it--;
        heapArr[(*it).first] = typename list <pair<K, V>>::iterator();
        cQueue.pop_back();
    }

    try {
        cQueue.push_front(std::make_pair(key, to_string(key+1)));
    } catch (...) {
        throw std::invalid_argument("\nenQueue Operation failure<push_front>");
    }

    heapArr[key] = cQueue.begin();
    return (*heapArr[key]).second;
}

template <typename K, typename V>
inline V cache<K,V>::cacheHit(K key) {
    try {
        cQueue.splice(cQueue.begin(), cQueue, heapArr[key]);
    } catch (...) {
        throw std::invalid_argument("\nenQueue Operation failure<splice>");
    }
    return (*heapArr[key]).second;
}

template <typename K, typename V>
V cache<K,V>::refereCache(K key) {
    V ret;
    typename list <pair<K, K>>::iterator it;

    if (key > heapSize) {
        throw std::invalid_argument("\nReference Key \
                out of range.\n");
    }

    pthread_mutex_lock(&lock);
    try {
        if ( heapArr[key] != typename list <pair<K, V>>::iterator()) {
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
