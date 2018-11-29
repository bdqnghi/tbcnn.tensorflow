/*
 * mergesort.cpp
 *
 *  Created on: Dec 19, 2017
 *      Author: mpiec
 */

#include <insertionsort/insertionsort.h>
#include <stddef.h>
#include <cstring>

#include <stdio.h>

namespace Insertionsort {
template <class T>
bool
Insertionsort<T>::sort(T* buffer, int size) {
    if(NULL == buffer)
        return false;

    for ( int i = 1; i < size; i++) {
        int key = buffer[i];
        int j = i - 1;

        while(j>=0 && buffer[j] > key) {
            buffer[j+1] = buffer[j];
            j = j - 1;
            buffer[j+1] = key;
        }
    }
}

template <class T>
Insertionsort<T>::Insertionsort(){

}

template <class T>
Insertionsort<T>::~Insertionsort(){

}

template class Insertionsort<int>;
template class Insertionsort<float>;
template class Insertionsort<unsigned int>;
}
