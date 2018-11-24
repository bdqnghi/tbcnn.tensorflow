//============================================================================
// Name        : shell-sort.cpp
// Author      : Alex Kaiser
// Date        :
// Copyright   : 
// Description : Implementation of shell sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

void
ShellSort::sort(int A[], int size)
{
  /* Complete this function with the implementation of shell sort algorithm 
  Record number of comparisons in variable num_cmps of class Sort
  */
  num_cmps = 0;
  for (int k = 1; k < size; k++) {
	bool cont = false;
	for (int j = 0; j < size - k; j++){
		if (A[j+1] < A[j]) {
		int tmp = A[j]; // swap A[j] and A[j+1]
		A[j] = A[j+1];
		A[j+1] = tmp;
		cont = true;
		}
		num_cmps++;
	}
		if (!cont) break; // stop sorting
	}

}
