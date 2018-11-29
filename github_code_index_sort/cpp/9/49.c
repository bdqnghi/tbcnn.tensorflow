//============================================================================
// Name        : selection-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of selection sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

void
SelectionSort::sort(int A[], int size)				// main entry point
{
  /* Complete this function with the implementation of selection sort algorithm 
  Record number of comparisons in variable num_cmps of class Sort
  */
    for (int k = 1; k < size; k++) {
        int tmp = A[k];
        int j = k;
        for (; j > 0 && (num_cmps++, tmp<A[j-1]); j--)
            A[j] = A[j-1];
        A[j] = tmp;
    }
}
