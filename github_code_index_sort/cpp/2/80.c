//
// Created by kamil on 21.03.18.
//

#ifndef HYBRIDSORT_MERGESORT_H
#define HYBRIDSORT_MERGESORT_H

#include <iostream>
#include "ISortable.h"
#include "IPreparable.h"

template <class T>
class Mergesort : public ISortable, public IPreparable {
public:
    Mergesort() : tab(nullptr), temp(nullptr) {}
    ~Mergesort() { delete[] tab, temp; }

    // virtuals methods
    void sort();
    std::string name() { return "mergesort"; }
    void clear();
    void prepare(int) {}
    void prepare(int data[], int data_size);

    // methods
    void swap(T& v1, T& v2);
    void merge(T array[],T temp[], T first, T last);
    void mergesort(T data[], T temp[],T first, T last);

private:
    T data_size;
    T *tab;
    T *temp;
};

template <class T>
inline void Mergesort<T>::sort() {
    mergesort(tab, temp, 0, data_size);
}

template <class T>
inline void Mergesort<T>::clear() {
    delete tab;
    this->tab = nullptr;
    this->data_size = 0;
}

template <class T>
inline void Mergesort<T>::prepare(int data[], int data_size) {
    if (tab != nullptr) return;

    this->data_size = data_size;
    tab = new int[data_size];
    temp = new int[data_size];

    for (auto i=0; i<data_size; i++) {
        tab[i] = data[i];
    }
}

/*///////////////////////////
// IMPLEMENTACJA ALGORYTMU //
///////////////////////////*/

template<class T>
inline void Mergesort<T>::swap(T& v1, T& v2)
{
    T tmp = v2;
    v2 = v1;
    v1 = tmp;
}

template <typename T>
inline void Mergesort<T>::merge(T array[],T temp[], T first, T last) {
    T mid = (first+last)/2;
    T i1 = 0, i2 = first, i3 = mid+1;

    temp [last-first+1];
    while (i2 <= mid && i3 <= last) { // dopóki prawa i lewa podtablica zawieraja elementy
        if (array[i2] < array[i3]) {
            temp[i1++] = array[i2++];
        } else {
            temp[i1++] = array[i3++];
        }
    }

    while (i2 <= mid) {
        temp[i1++] = array[i2++];
    }

    while (i3 <= last) {
        temp[i1++] = array[i3++];
    }

    for (i1 = 0, i2 = first ; i2 <= last; array[i2++] = temp[i1++]);
}

template <typename T>
inline void Mergesort<T>:: mergesort(T data[], T temp[],T first, T last) {
    if (first < last) {
        T mid = (first+last)/2 ;
        mergesort(data, temp,first, mid);
        mergesort(data,temp, mid+1, last);
        merge(data,temp,first, last);
    }
}

#endif //HYBRIDSORT_MERGESORT_H
