//============================================================================
// Name        : insertion-sort.cpp
// Author      : Nathan Lee
// Date        : 21 September 2014
// Copyright   : 
// Description : Implementation of insertion sort in C++
//============================================================================

#include "sort.h"

void
InsertionSort::sort(int A[], int size)				// main entry point
{
  /* Complete this function with the implementation of insertion sort algorithm 
  Record number of comparisons in variable num_cmps of class Sort
  */
	int temp_var;
	for (int i = 1; i < size; i++) {
		//int j = i;
		for (int j = i; j > 0 && (num_cmps++, A[j - 1] > A[j]); j--) {
			temp_var = A[j];
			A[j] = A[j - 1];
			A[j - 1] = temp_var;
		}
		/*while (j > 0 && (num_cmps++, A[j - 1] > A[j])) {
			temp_var = A[j];
			A[j] = A[j - 1];
			A[j - 1] = temp_var;
			j--;
		}*/
	}
}
