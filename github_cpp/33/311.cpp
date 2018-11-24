//============================================================================
// Name        : shell-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of shell sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include "math.h"

void ShellSort::sort(int A[], int size)
{
 	for(int k = 2; k < size; k *= 2) {
		int gap = floor(size/k);
		for(int i = gap; i < size; i += 1) {
			int temp = A[i];
			int j;
			for(j = i; j >= gap and (num_cmps++, A[j - gap] > temp); j -= gap) {
				A[j] = A[j - gap];
			}
			A[j] = temp;
		}
	}
}
