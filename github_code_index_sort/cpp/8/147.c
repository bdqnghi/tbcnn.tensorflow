#include "QuickSort.h"

#ifndef QUICK_SORT_CPP
#define QUICK_SORT_CPP

template <class T>
QuickSort<T>::QuickSort():
    SortAlgorithm<T>("Quick") {}

template <class T>
QuickSort<T>::~QuickSort() {}

template <class T>
void QuickSort<T>::sort(T* elements, int size) {
    sort(elements, 0, size - 1);
}

template <class T>
void QuickSort<T>::sort(T* elements, int from, int to) {
    int index = partition(elements, from, to);

    if (from < index - 1)
          sort(elements, from, index - 1);
    if (index < to)
          sort(elements, index, to);
}

template <class T>
int QuickSort<T>::partition(T* elements, int from, int to) {
    int centerIndex = (from + to) / 2;
    T center = elements[centerIndex];

    while (from <= to) {
          while (elements[from] < center)
                from++;
          while (elements[to] > center)
                to--;
          if (from <= to) {
                this->swap(elements, from, to);
                from++;
                to--;
          }
    }

    return from;
}

#endif // QUICK_SORT_CPP
