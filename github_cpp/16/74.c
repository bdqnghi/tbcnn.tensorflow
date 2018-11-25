







#include "sort.h"
#include <iostream>

void
ShellSort::sort(int A[], int size)
{
  
	num_cmps = 0;
	int gap = size/2;
    
	while(gap > 0)
	{
		for(int i = gap; i < size; i++)
		{
			int tmp = A[i];
			int j = i;
			
            while(j >= gap && tmp < A[j-gap])
			{
				A[j] = A[j-gap];
				j -= gap;
                num_cmps++;
			}
			A[j] = tmp;
		}
		if(gap == 2) gap = 1;
		else gap = (int) (gap/2.2);
	}
    
    Sort::getNumCmps();
}