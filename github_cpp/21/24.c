







#include "sort.h"
#include <iostream>


void
SelectionSort::sort(int A[], int size){
		int i, k, index, tmp;
		for (k = 0; k < size - 1; k++) {
			int index = k;
			for (i = k + 1; i < size; i++) {
				if (A[i] < A[index]) {
					
					
					index = i;
				} 
				num_cmps++;
			}
			if (index != k) {
				int tmp = A[k]; 
				A[k] = A[index]; 
				A[index] = tmp;
				num_cmps++;
			}
		}
}
