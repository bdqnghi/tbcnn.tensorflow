//============================================================================
// Name        : shell-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of shell sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
inline int next_gap(int gap)
{
	if (gap == 2) return 1;
	else return (int)(gap / 2.2);
}

void
ShellSort::sort(int A[], int size)
{
	num_cmps = 0;
	int gap = size / 2;
	for (; gap > 0; gap = next_gap(gap))
	{
		for (int i = gap; i < size; ++i)
		{
			int temp = A[i];
			int j = i;
			while (num_cmps++, j >= gap && temp < A[j - gap])
			{
				A[j] = A[j - gap];
				j -= gap;
			}
			A[j] = temp;
		}
	}
}
