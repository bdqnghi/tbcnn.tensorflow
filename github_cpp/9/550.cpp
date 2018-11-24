//=====================================================================
// Name        : insertion-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Author      : Tate Walker
// Date        : 2-11-17
// Copyright   : Tate Walker
// Description : Implementation of insertion sort in C++
//============================================================================

#include "sort.h"
void InsertionSort::sort(int A[], int size)				// main entry point
{
    int j;
    int temp;
    for (int i = 0; i<size; i++) {
        j = i;
        num_cmps++;
        while (j>0 && A[j] < A[j-1]) {
            temp = A[j];
            num_cmps++;
            A[j] = A[j-1];
            A[j-1] = temp;
            j--;
        }
    }
}
