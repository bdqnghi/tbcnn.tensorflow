//============================================================================
// Name        : selection-sort.cpp
// Author      : Todd Christian
// Date        : February 10, 2016
// Copyright   : http://mathbits.com/MathBits/CompSci/Arrays/Selection.htm and http://cforbeginners.com/ssort.html and the lecture slides
// Description : Implementation of selection sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

void
SelectionSort::sort(int A[], int size)				// main entry point
{
	int min,t;

	for (int i=0; i < size-1; i++)
	{
		++num_cmps;
		min = i;
		for (int j=i+1; j < size; j++)
		{
			++num_cmps;
			if (A[j] < A[min])
			{
				++num_cmps;
				min=j;
			}
		}
		if (min != i)
		{
			++num_cmps;
			t = A[i];
			A[i] = A[min];
			A[min] = t;
		}
	}
}