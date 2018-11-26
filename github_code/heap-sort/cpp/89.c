//
// Created by kamil on 21.03.18.
//

#ifndef HYBRIDSORT_HEAPSORT_H
#define HYBRIDSORT_HEAPSORT_H

#include <iostream>
#include "ISortable.h"

template <class T>
class Heapsort : public ISortable, public IPreparable {
public:
    Heapsort() : tab(nullptr) {}
    ~Heapsort() { delete tab; }

    // virutal methods
    void sort();
    void clear();
    void prepare(int) {}
    void prepare(int data[], int data_size);
    std::string name() { return "heapsort"; }

    // methods
    void swap(T& v1, T& v2);
    void heapsort(T data[], T data_size);
    void heapify(T data[], T i, T data_size);

private:
    T data_size;
    T *tab;
};

template <class T>
inline void Heapsort<T>::sort() {
    heapsort(tab, data_size);
}

template <class T>
inline void Heapsort<T>::clear() {
    delete tab;
    tab = nullptr;
    this->data_size = 0;
}

template <class T>
inline void Heapsort<T>::prepare(int data[], int data_size) {
    if (tab != nullptr) return;

    this->data_size = data_size;
    tab = new int[data_size];

    for (auto i=0; i<data_size; i++) {
        tab[i] = data[i];
    }
}

/*///////////////////////////
// IMPLEMENTACJA ALGORYTMU //
///////////////////////////*/

template<typename T>
inline void Heapsort<T>::swap(T& v1, T& v2) {
    T tmp = v2;
    v2 = v1;
    v1 = tmp;
}

template<typename T>
inline void Heapsort<T>::heapify(T data[], T i, T size) {               // kopcuje,dzieli na poddrzewa z wezlami i
    T root = i;
    T left = 2*i ;
    T right = 2*i + 1;

    if(left < size && data[left] > data[root])
        root = left;
    if(right < size && data[right] > data[root])
        root = right;
    if(root != i){
        swap(data[i],data[root]);
        heapify(data, root, size);
    }
}
template<class T>
inline void Heapsort<T>::heapsort(T data[], T size) {
    T i, min = 0;
    for(i = size/2 - 1; i>=0; i--)               // utworzenie sterty
        heapify(data,i,size);

    for(i = size-1; i>=0; i--){                 // wyciaganie jeden po drugim elementu ze sterty
        swap(data[min],data[i]);                // przesuniecie największego el,korzenia do data[i]
        heapify(data,min,i);                    // przywrocenie sterty, zmniejszenie o najwiekszy el
    }
}

#endif //HYBRIDSORT_HEAPSORT_H
