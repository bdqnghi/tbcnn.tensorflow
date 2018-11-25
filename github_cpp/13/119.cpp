//============================================================================
// Name        : bubble-sort.cpp
// Author      : Todd Christian
// Date        : February 10, 2016
// Copyright   : http://mycodinglab.com/bubble-sort-algorithm/ and the slides
// Description : Implementation of bubble sort in C++
//============================================================================

#include "sort.h"

void 
BubbleSort::sort(int A[], int size)
{		// main entry point
	bool not_sorted = true;
	int j=0;
	int temp; 
	
	while (not_sorted)  
	{
		not_sorted = false; 
		j++;
		for (int i = 0; i < size - j; i++) 
		{
			++num_cmps;
			if (A[i] > A[1+i]) 
			{
				++num_cmps;
				temp = A[i];
				A[i] = A[1+i];
				A[1+i] = temp;
				not_sorted = true;
			}
		}
	}
}