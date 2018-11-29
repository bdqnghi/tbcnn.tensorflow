#include <iostream>
#include <cmath>
#include "MergeSort.h"

using namespace std;


MergeSort::MergeSort()
{
    list = new int[0];
    len = 0;
}


MergeSort::MergeSort (const int* t, int length)
{
    if (t) {
        len = length;
        list = new int[len];
        for (int i = 0; i < length; i++)
            list[i] = t[i];
    }
    else {
        list = new int[0];
        len = 0;
    }
}


MergeSort::~MergeSort()
{
    delete[] list;
}


ostream& 
operator<< (ostream& os, const MergeSort& ms)
{
    if (ms.len >= 1)
        os << ms.list[0];

    for (int i = 1; i < ms.len; i++)
        os << ", " << ms.list[i];

    os << endl;
    return os;
}


int& 
MergeSort::operator[] (const int index)
{
    return list[index];
}


int& 
MergeSort::length (void)
{
    return len;
}


void
print_arr(int *l, int len)
{
    for (int i = 0; i < len; i++)
        cout << l[i] << " ";
    cout << endl;
}


void
MergeSort::merge (int *subarr1, int subarr1_len, 
                  int *subarr2, int subarr2_len, 
                  int *arr)
{
    for (int i = 0, i1 = 0, i2 = 0; i1 < subarr1_len || i2 < subarr2_len; i++) {
        if (i1 < subarr1_len && i2 < subarr2_len)
            arr[i] = 
                (subarr1[i1] <= subarr2[i2]) ? subarr1[i1++] : subarr2[i2++];
        else if (i1 < subarr1_len)
            arr[i] = subarr1[i1++];
        else if (i2 < subarr2_len)
            arr[i] = subarr2[i2++];
    }
}


int *
MergeSort::_mergesort (int *arr, int arrlen)
{
    if (arrlen <= 1)
        return arr;

    int middle = arrlen / 2;
    int *left = arr;
    int *right = arr + middle;

    left = _mergesort(left, middle);
    right = _mergesort(right, arrlen - middle);

    /* copy subarrays into local arrays for merge */
    int l[middle];
    int r[arrlen - middle];
    for (int i = 0; i < middle; i++, left++)
        l[i] = *left;
    for (int i = 0; i < arrlen - middle; i++, right++)
        r[i] = *right;

    merge(l, middle, r, arrlen - middle, arr);
    return arr;
}


void
MergeSort::mergesort ()
{
    _mergesort( list, len );
}
