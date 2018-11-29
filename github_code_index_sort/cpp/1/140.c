//============================================================================
// Name        : insertion-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of insertion sort in C++
//============================================================================

#include "sort.h"
void
InsertionSort::sort(int A[], int size)				// main entry point
{
	num_cmps = 0;
	int i, j ,tmp;
	for (i = 1; i < size; i++) {
		j = i;
		while (++num_cmps,j > 0 && A[j - 1] > A[j]) {
		tmp = A[j];
		A[j] = A[j - 1];
		A[j - 1] = tmp;
		j--;
		}
	}


}
