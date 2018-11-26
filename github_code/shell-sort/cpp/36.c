//============================================================================
// Name        : shell-sort.cpp
// Author      : Michael Kosler
// Date        : 02/07/2012
// Copyright   : GPL v3 (http://www.gnu.org/copyleft/gpl.html)
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
	int temp = 0;
	for (int gap = size/2; gap >= 1; gap /= 2)
	{
		for (int i = gap; i < size; i++)
		{
			temp = A[i];
			int j = i;
			for (; (num_cmps++, j >= gap) && (num_cmps++, temp < A[j - gap]); j -= gap)
			{
				A[j] = A[j - gap];
			}
			A[j] = temp;
		}
	}
}
