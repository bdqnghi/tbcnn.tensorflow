







#include "sort.h"
#include <iostream>

void
ShellSort::sort(int A[], int size)
{
  
  int gap = size/2;
  int next_gap;
  for (; gap > 1; gap = next_gap){
	for (int i = gap; i < size; i++){
		++num_cmps;		
		int tmp = A[i];
		int j = i;
		while (j >= gap && (++num_cmps, tmp < A[j-gap])){	
			A[j] = A[j-gap];
			j -= gap;
		}
		A[j] = tmp;
	}
	if (gap == 2) next_gap = 1;
	else next_gap = gap/2.2;
  }
}
