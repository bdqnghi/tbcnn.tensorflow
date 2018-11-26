//
// Created by Саид on 10.06.16.
//

#ifndef HEAPSORT_HEAPSORT_H
#define HEAPSORT_HEAPSORT_H

#include <iostream>

template <class T>
class HeapSort {
public:
    static void sort(T *data, int n);
private:
    static void heapMake(T *heap, int n);
    static void heapPop(T *heap, int n);
};

template <class T>
void HeapSort<T>::sort(T *data, int n) {
    heapMake(data - 1, n);
    for (int i = 0; i < n; ++i) {
        heapPop(data - 1, n - i);
    }
}

template <class T>
void HeapSort<T>::heapMake(T *heap, int n) {
    for (int i = n / 2; i >= 1; --i) {
        for (int j = i; j <= n / 2;) {
            int k = j * 2;

            if (k + 1 <= n && heap[k] < heap[k+1]) {
                ++k;
            }
            if (heap[j] < heap[k]) {
                std::swap(heap[k], heap[j]);
                j = k;
            } else {
                break;
            }
        }
    }
}

template <class T>
void HeapSort<T>::heapPop(T *heap, int n) {
    std::swap(heap[n], heap[1]);
    for (int i = 1; 2 * i < n;) {
        i *= 2;
        if (i + 1 < n && heap[i] < heap[i + 1]) {
            i ++;
        }
        if (heap[i / 2] < heap[i]) {
            std::swap(heap[i / 2], heap[i]);
        }
    }
}


#endif //HEAPSORT_HEAPSORT_H
