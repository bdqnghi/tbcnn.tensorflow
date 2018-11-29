//
// Created by 72419 on 2018/3/17 0017.
//

#ifndef CPP_QUICKSORT_H
#define CPP_QUICKSORT_H

#include <algorithm>
#include <ctime>


template <typename T>
int __partition(T arr[], int l, int r) {


    std::swap(arr[l], arr[(rand() % (r-l+1)) + l]);

    T v = arr[l];
    int j = l;

    for (int i = l+1; i <= r; i++) {
        if (arr[i] < v) {
            std::swap(arr[++j], arr[i]);
        }
    }
    std::swap(arr[j], arr[l]);
    return j;
}

template <typename T>
void __quickSort(T arr[], int l, int r) {
    if (l >= r)
        return;
    int p = __partition(arr, l, r);
    __quickSort(arr, l, p-1);
    __quickSort(arr, p+1, r);
}

template <typename T>
void quickSort(T arr[], int n) {

    srand(time(NULL));
    __quickSort(arr, 0, n-1);
}

#endif //CPP_QUICKSORT_H
