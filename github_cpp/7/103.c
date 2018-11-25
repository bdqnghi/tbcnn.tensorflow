#include "MergeSort.h"

#ifndef MERGE_SORT_CPP
#define MERGE_SORT_CPP

template <class T>
MergeSort<T>::MergeSort():
    SortAlgorithm<T>("Merge") {}

template <class T>
MergeSort<T>::~MergeSort() {}

template <class T>
void MergeSort<T>::sort(T* elements, int size) {
    T* array = new T[size];

    for(int i = 0; i < size; i++)
        array[i] = elements[i];

    this->sort(array, elements, 0, size - 1);
    delete array;
}


template <class T>
void MergeSort<T>::sort(T* elements, T* result, int from, int to) {
    if(to <= from)
        return;

    int firstFrom = from;
    int firstTo = (from + to) / 2;
    int secondFrom = firstTo + 1;
    int secondTo = to;

    sort(elements, result, firstFrom, firstTo);
    sort(elements, result, secondFrom, secondTo);
    merge(elements, result, firstFrom, firstTo, secondFrom, secondTo);

    for(int i = from; i <= to; i++)
        elements[i] = result[i];
}

template <class T>
void MergeSort<T>::merge(T* elements, T* result, int firstFrom, int firstTo, int secondFrom, int secondTo) {
    int firstIndex = firstFrom;
    int secondIndex = secondFrom;

    for(int i = firstFrom; i <= secondTo; i++) {
        if(firstIndex > firstTo) {
            result[i] = elements[secondIndex];
            secondIndex++;
        } else if(secondIndex > secondTo) {
            result[i] = elements[firstIndex];
            firstIndex++;
        } else {
            T first = elements[firstIndex];
            T second = elements[secondIndex];

            if(first < second) {
                result[i] = first;
                firstIndex++;
            } else {
                result[i] = second;
                secondIndex++;
            }
        }
    }
}

#endif 
