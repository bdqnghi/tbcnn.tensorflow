//============================================================================
// Name        : selection-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of selection sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

void SelectionSort::sort(int A[], int size)				// main entry point
{
	for (int k = 0; k < size-1; k++)
	{
		int index = k;
		for (int i = k+1; i < size; i++){
			std::cout<<"num_cmps= "<<num_cmps<<std::endl;
			num_cmps++;
			if (A[i] < A[index]) index = i;
		}
		int tmp = A[k]; // swap A[k] and A[index]
		A[k] = A[index];
		A[index] = tmp;
	}
}
