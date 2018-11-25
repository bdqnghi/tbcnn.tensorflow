//============================================================================
// Name        : bubble-sort.cpp
// Author      :
// Date        :
// Copyright   :
// Description : Implementation of bubble sort in C++
//============================================================================

#include "sort.h"
void BubbleSort::sort(int A[], int size)			// main entry point
{
	/* Complete this function with the implementation of bubble sort algorithm
		 Record number of comparisons in variable num_cmps of class Sort
	*/
	for (int k=1;k<size;k++){
		bool stop = true;
		for (int i=0; i <size-k; i++) {
			num_cmps++;
			if(A[i+1]<A[i]) {
				int tmp=A[i]; // swap A[j] and A[j+1]
				A[i]=A[i+1];
				A[i+1]=tmp;
				stop=false;
			}
		}
		if (stop) break; // stop sorting
	}
}
