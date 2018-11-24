//============================================================================
// Name        : selection-sort.cpp
// Author      : Benjamin Sullivan
// Date        : 
// Copyright   : 
// Description : Implementation of selection sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

void
SelectionSort::sort(int A[], int size){
	for(int k = 0; k < size-1; k++){
		int index = k, tmp;
		for(int i = k+1; i < size; i++) {
			++num_cmps;
			if(A[i] < A[index])
				index = i;
		}
		//Swapping of A[k] and A[index]
			tmp = A[k];
			A[k] = A[index];
			A[index] = tmp;
	}
}
/*Added Algorithm*/
