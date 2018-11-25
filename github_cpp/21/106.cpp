







#include "sort.h"
#include <iostream>

void SelectionSort::sort(int A[], int size) { 
	int i, j,counter(0),Min;

	for( i = 0; i < (size-1); i++) {
		Min = i; 

		for (j = (i+1); j < size; j++) {
	
			if(counter++,A[j] < A[Min]) { Min = j; } 
		}

	if(Min != i) { 

		
		
		int temp = A[i];
			A[i] = A[Min];
			A[Min] = temp;
			
		} } 

	num_cmps = counter;

}  