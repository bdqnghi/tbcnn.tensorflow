//============================================================================
// Name        : shell-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of shell sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

void ShellSort::sort(int A[], int size) 
{ 
	int gaps[8] = {701,301,132,57,23,10,4,1};
	int i, j, gap_number, currentGap, temp,counter(0);

	for(gap_number = 0; gap_number < 8; gap_number++) 
	{ 
		currentGap = gaps[gap_number];
			
			for (i = currentGap; i < size; i++) 
			{ 
				temp = A[i];

				for(j = i; (counter++,j >= currentGap) && (counter++,A[j-currentGap] > temp); j -= currentGap) 
				{	 
					A[j] = A[j - currentGap];
				} 
					
				A[j] = temp; 
			} 
	} 
	num_cmps = counter;
} 
