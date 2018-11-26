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
SelectionSort::sort(int A[], int size)		// main entry point
{
	int min_index;						//index of the minimum element
	int temp;

	for (int i = 0; i < size-1; i++)
	{
		min_index = i;
		for (int j = i+1; j < size; j++)//this loop finds the 
											//index of the smallest 
											//element
		{
			if (num_cmps++, A[j] < A[min_index]) { min_index = j; }
		}
	
		if (min_index != i)				//swaps minimum into earliest spot
		{
			temp = A[i];
			A[i] = A[min_index];
			A[min_index] = temp;
		}
	}
}
