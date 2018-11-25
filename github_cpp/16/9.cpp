







#include "sort.h"
#include <iostream>

void
ShellSort::sort(int A[], int size)
{
  
  num_cmps = 0;
  for (int k = 1; k < size; k++) {
	bool cont = false;
	for (int j = 0; j < size - k; j++){
		if (A[j+1] < A[j]) {
		int tmp = A[j]; 
		A[j] = A[j+1];
		A[j+1] = tmp;
		cont = true;
		}
		num_cmps++;
	}
		if (!cont) break; 
	}

}
