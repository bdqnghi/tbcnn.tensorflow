







#include "sort.h"
#include <iostream>
#include <math.h>

const int base = 10;

int digit(int k, int num)
{ int r;
r = num/(int)pow(base, k); 
return r % base;
}

int getMax(int arr[], int n)
{
    int max = arr[0];
    int count=0;
	for (int i = 1; i < n; i++)
        if (arr[i] > max)
    	max = arr[i];
	while(max!=0){
	max=max/10;
	count++;
	}
    return count;
}

void
RadixSort::sort(int* A, int size)
{
	
	
	 int i, j, m;
	
	int *C = new int[base];
	int *B = new int[size];
	int d = getMax(A, size);
	for (m = 0; m < d; m++)
	{
		for (i = 0; i < base; i++) 
			C[i] = 0;
		for (j = 0; j < size; j++)
		{	
			C[digit(m, A[j])]++;
		}
			
		for (i = 1; i < base; i++)
		{
			C[i] += C[i-1];
		}	

		for (j = size-1; j >= 0; j--)
		{
			i = C[digit(m, A[j])]--;
			B[i-1] = A[j];
		} 
			
		for (j = 0; j < size; j++)
		{
			A[j] = B[j];
		}		
	}	
	delete [] B; delete [] C;
}

  

