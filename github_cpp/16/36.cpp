







#include "sort.h"
#include <iostream>

void
ShellSort::sort(int A[], int size)
{
  
	int temp = 0;
	for (int gap = size/2; gap >= 1; gap /= 2)
	{
		for (int i = gap; i < size; i++)
		{
			temp = A[i];
			int j = i;
			for (; (num_cmps++, j >= gap) && (num_cmps++, temp < A[j - gap]); j -= gap)
			{
				A[j] = A[j - gap];
			}
			A[j] = temp;
		}
	}
}
