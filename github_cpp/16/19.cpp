







#include "sort.h"
#include <iostream>



inline int next_gap(int gap)
{
	if (gap == 2) 
		return 1;
	else 
		return (int) (gap/2.2);
}

void ShellSort::sort(int A[], int n)
{
  
	int gap = n/2;
	for (; gap > 0; gap = next_gap(gap)) 
	{
		for (int i = gap; i < n; i++)
		{
			int tmp = A[i];
			int j = i;
			num_cmps++;
			while (j >= gap && tmp < A[j-gap]) 
			{
				A[j] = A[j-gap];
				j -= gap;
			}
			A[j] = tmp;
		}
	}

}
