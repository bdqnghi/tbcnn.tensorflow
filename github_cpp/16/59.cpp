//============================================================================
// Name        : shell-sort.cpp
// Author      : Fang Wang	
// Date        : 02-11-2017
// Copyright   : 
// Description : Implementation of shell sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

inline int ShellSort::next_gap(int gap)
{
	if (num_cmps++,gap==2) return 1;
	else return (int) (gap/2.2);
}

void
ShellSort::sort(int A[], int size)
{
  /* Complete this function with the implementation of shell sort algorithm 
  Record number of comparisons in variable num_cmps of class Sort
  */
	int gap=size/2;
	for (;gap>0;gap=next_gap(gap))
	{
		for (int i=gap;i<size;i++)
		{
			int tmp=A[i];
			int j=i;
			while(j>=gap &&(num_cmps++,tmp<A[j-gap]))
			{
				A[j]=A[j-gap];
				j-=gap;
			}
			A[j]=tmp;
		}

	}
}
