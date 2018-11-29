//============================================================================
// Name        : insertion-sort.cpp
// Author      :
// Date        :
// Copyright   :
// Description : Implementation of insertion sort in C++
//============================================================================

#include "sort.h"

void InsertionSort::sort(int A[], int size)
{
	for(int k=1; k<size; k++) {
		int tmp=A[k];
		int j;
		for(j = k; j>0 && (num_cmps++, tmp<A[j-1]); j--) {
			A[j] = A[j-1];
		}
		A[j] = tmp;
	}

}
