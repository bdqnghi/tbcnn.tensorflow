#ifndef QUICKSORTER_H
#define QUICKSORTER_H

#include "../../lang/Lang.h"

namespace ycg {

class QuickSorter {
public:
	template <class T>
    void operator() (T *array, int size);
    template <class T, class Comparator>
    void operator() (T *array, int size, Comparator cmp);
protected:
    template <class T>
    void quickSort(T *array, int left, int right);
    template <class T, class Comparator>
    void quickSort(T *array, int left, int right, Comparator cmp);
    template <class T>
    int partition(T *array, int left, int right);
    template <class T, class Comparator>
    int partition(T *array, int left, int right, Comparator cmp);
    template <class T>
    void insertionSort(T *array, int left, int right);
    template <class T, class Comparator>
    void insertionSort(T *array, int left, int right, Comparator cmp);
    template <class T>
    void compareExchange(T &a, T &b) {
    	if (b < a) {
    		exchange(a, b);
    	}
    }
    template <class T, class Comparator>
    void compareExchange(T &a, T &b, Comparator cmp) {
        if (cmp(b, a) < 0) {
            exchange(a, b);
        }
    }
    template <class T>
    void exchange(T &a, T &b) {
       swap(a, b);
    }
protected:
    static const int MIN_SEG = 16;
};

template <class T>
void QuickSorter::operator () (T *array, int size) {
	quickSort(array, 0, size-1);
    insertionSort(array, 0, size-1);
}

template <class T, class Comparator>
void QuickSorter::operator () (T *array, int size, Comparator cmp) {
    quickSort(array, 0, size-1, cmp);
    insertionSort(array, 0, size-1, cmp);
}

template <class T>
void QuickSorter::quickSort(T *array, int left, int right) {
    if(right - left < MIN_SEG) return;
    exchange(array[(left+right)/2], array[left+1]);
    compareExchange(array[left], array[left+1]);
    compareExchange(array[left], array[right]);
    compareExchange(array[left+1], array[right]);
    int mid = partition(array, left+1, right-1);
    quickSort(array, left, mid-1);
    quickSort(array, mid+1, right);
}

template <class T, class Comparator>
void QuickSorter::quickSort(T *array, int left, int right, Comparator cmp) {
    if(right - left < MIN_SEG) return;
    exchange(array[(left+right)/2], array[left+1]);
    compareExchange(array[left], array[left+1], cmp);
    compareExchange(array[left], array[right], cmp);
    compareExchange(array[left+1], array[right], cmp);
    int mid = partition(array, left+1, right-1, cmp);
    quickSort(array, left, mid-1, cmp);
    quickSort(array, mid+1, right, cmp);
}

template <class T>
int QuickSorter::partition(T *array, int left, int right) {
    T key = array[left];
    int i = left, j = right;
    while (i < j) {
        while (i < j && key < array[j]) --j;
        if (i < j) {
            array[i] = array[j];
            ++i;
        }
        while (i < j && array[i] < key) ++i;
        if (i < j) {
            array[j] = array[i];
            --j;
        }
    }
    array[i] = key;
    return i;
}

template <class T, class Comparator>
int QuickSorter::partition(T *array, int left, int right, Comparator cmp) {
    T key = array[left];
    int i = left, j = right;
    while (i < j) {
        while (i < j && cmp(key, array[j]) < 0) --j;
        if (i < j) {
            array[i] = array[j];
            ++i;
        }
        while (i < j && cmp(array[i], key) < 0) ++i;
        if (i < j) {
            array[j] = array[i];
            --j;
        }
    }
    array[i] = key;
    return i;
}

template <class T>
void QuickSorter::insertionSort(T *array, int left, int right) {
    for(int j = left + 1; j <= right; ++j) {
        int i = j - 1;
        T key = array[j];
        while(i >= left && key < array[i]) {
            array[i+1] = array[i];
            --i;
        }
        array[i+1] = key;
    }
}

template <class T, class Comparator>
void QuickSorter::insertionSort(T *array, int left, int right, Comparator cmp) {
    for(int j = left + 1; j <= right; ++j) {
        int i = j - 1;
        T key = array[j];
        while(i >= left && cmp(key, array[i]) < 0) {
            array[i+1] = array[i];
            --i;
        }
        array[i+1] = key;
    }
}

} //~ namespace ycg

#endif // QUICKSORTER_H
