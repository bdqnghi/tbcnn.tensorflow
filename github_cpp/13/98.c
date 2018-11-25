//============================================================================
// Name        : bubble-sort.cpp
// Author      : Devin Tuchsen
// Date        : 9 Feb 2013
// Copyright   : © 2013 Devin Tuchsen
// Description : Implementation of bubble sort in C++
//============================================================================

#include "sort.h"

void BubbleSort::sort(int A[], int size)			// main entry point
{
	for(int k = 1; k < size; ++k) {
		bool cont = false;
		for(int j = 0; j < size - k; ++j) {
			++num_cmps;
			if(A[j+1] < A[j]) {
				int temp = A[j];
				A[j] = A[j+1];
				A[j+1] = temp;
				cont = true;
			}
		}
		if(!cont) break;
	}
}
