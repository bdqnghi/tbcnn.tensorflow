//============================================================================
// Name        : insertion-sort.cpp
// Author      : Todd Christian
// Date        : February 10, 2016
// Copyright   : http://www.ee.ryerson.ca/~courses/coe428/sorting/insertionsort.html and http://cforbeginners.com/insertionsort.html and her lecture slides
// Description : Implementation of insertion sort in C++
//============================================================================

#include "sort.h"

void
InsertionSort::sort(int A[], int size)				// main entry point
{
	int i;
	int pos;
	int key;

    for(i = 1; i < size; ++i)
    {
		++num_cmps;
        key = A[i];
        for (pos = i - 1; pos >= 0 && A[pos] > key; --pos)
		{
			++num_cmps;
			++num_cmps;
            A[1+pos] = A[pos];
		}
        A[1+pos] = key;
    }
}