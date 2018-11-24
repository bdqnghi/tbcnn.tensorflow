//============================================================================
// Name        : shell-sort.cpp
// Author      : Devin Tuchsen
// Date        : 9 Feb 2013
// Copyright   : © 2013 Devin Tuchsen
// Description : Implementation of shell sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

int next_gap(int gap)
{ if (gap == 2) return 1; else return (int) (gap/2.2); }
void ShellSort::sort(int A[], int size)
{
	for(int gap = size/2; gap > 0; gap = next_gap(gap)) {
		for(int i = gap; i < size; ++i) {
			int temp = A[i];
			int j = i;
			if(temp >= A[j-gap])
				++num_cmps;
			for(; j >= gap && temp < A[j-gap]; j-= gap){
				++num_cmps;	//<-- added to test comparison count
				A[j] = A[j-gap];
			}
			A[j] = temp;
		}
	}
}
