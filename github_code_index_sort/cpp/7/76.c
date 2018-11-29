//============================================================================
// Name        : shell-sort.cpp
// Author      : Nick Kopan
// Date        : 2/16/17
// Copyright   : Nick Kopan ©
// Description : Implementation of shell sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

int next_gap(int gap) { 
if (gap == 2) 
	return 1; 
else return 
	(int) (gap/2.2); 
}

void
ShellSort::sort(int A[], int size)
{
  for(int gap = size/2; gap > 0; gap = next_gap(gap)) {
		for(int i = gap; i < size; ++i) {
			int temp = A[i];
			int j = i;
			if(temp >= A[j-gap])
				++num_cmps;
			for(; j >= gap && temp < A[j-gap]; j-= gap){
				++num_cmps;	
				A[j] = A[j-gap];
			}
			A[j] = temp;
		}
	}
}



















