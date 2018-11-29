//============================================================================
// Name        : selection-sort.cpp
// Author      : Grant Hruzek
// Date        : 2/8/2017
// Copyright   : Grant Hruzek ©
// Description : Implementation of selection sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

void
SelectionSort::sort(int A[], int size)				// main entry point
{
  for (int i = 0; i < size - 1; ++i) {
		int index = i; 
		int temp = 0;
		for (int k = i + 1; k < size; ++k) {
			++num_cmps;
			if (A[k] < A[index]) {
				index = k;
			}
		}
		// Swap
		temp = A[i];
		A[i] = A[index];
		A[index] = temp;
	}
}
