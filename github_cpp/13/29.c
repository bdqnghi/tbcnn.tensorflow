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
