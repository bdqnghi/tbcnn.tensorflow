







#include "sort.h"
#include <iostream>

void
SelectionSort::sort(int A[], int size)				
{
  
  num_cmps = 0;
  for (int k = 0; k < size-1; k++)
  {
	  int index = k;
	  for (int i = k + 1; i < size; i++){
		  if (A[i] < A[index]) index = i;
		  num_cmps++;
	  }
	  int tmp = A[k]; 
	  A[k] = A[index];
	  A[index] = tmp;
  }
}
