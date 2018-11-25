//============================================================================
// Name        : selection-sort.cpp
// Author      :
// Date        :
// Copyright   :
// Description : Implementation of selection sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

void SelectionSort::sort(int A[], int size)
{
	for(int k=0;k<size-1;k++) {
		int ind = k;
		for(int i=k+1;i<size;i++) {
			num_cmps++;
			if(A[i]<A[ind]) {
				ind = i;
			}
		}
		int tmp = A[k]; // swap A[k] and A[index]
		A[k] = A[ind];
		A[ind] = tmp;
	}
}
