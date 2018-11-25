







#include "sort.h"

void 
BubbleSort::sort(int A[], int size)			
{
  
	for (int i = 0; i < size; i++) {
  		for (int j = 1; j < size - i; j++) {
  			if (num_cmps++, A[j-1] > A[j]) {
				int temp_var = A[j];
				A[j] = A[j-1];
				A[j-1] = temp_var;  		
  			}
  		}
  	}
}
