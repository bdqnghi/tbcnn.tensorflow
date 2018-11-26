//============================================================================
// Name        : bubble-sort.cpp
// Author      : Nathan Lee
// Date        : 15 September 2014
// Copyright   : 
// Description : Implementation of bubble sort in C++
//============================================================================

#include "sort.h"

void 
BubbleSort::sort(int A[], int size)			// main entry point
{
  /* Complete this function with the implementation of bubble sort algorithm 
     Record number of comparisons in variable num_cmps of class Sort
  */
	for (int i = 0; i < size; i++) {
  		for (int j = 1; j < size - i; j++) {
  			if (num_cmps++, A[j-1] > A[j]) {
				int temp_var = A[j];
				A[j] = A[j-1];
				A[j-1] = temp_var;  		
  			}
  		}
  	}
}
