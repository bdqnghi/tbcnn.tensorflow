//============================================================================
// Name        : shell-sort.cpp
// Author      : Alan Villarreal, Christopher Spear, Sidian Wu
// Date        : 02/14/13
// Copyright   : what
// Description : Implementation of shell sort in C++
//============================================================================

#include "sort.h"
#include <iostream>


inline int next_gap(int gap)
	{ if (gap ==2) return 1;else return (int) (gap/2.2); }
void ShellSort::sort(int A[], int size)
{
	for (int gap = size/2; gap > 0; gap = next_gap(gap)) 
	{
		for (int i = gap; i <size; i++)
		{
			int tmp = A[i];
			int j = i;
			for( ; j>=gap && (num_cmps++,tmp < A[j-gap]);j-=gap)
				A[j] = A[j-gap];
			A[j] = tmp;
		}
	}


  /* Complete this function with the implementation of shell sort algorithm 
  Record number of comparisons in variable num_cmps of class Sort
  */
}
