//============================================================================
// Name        : radix-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include <math.h>

const int base = 10;

int digit(int k, int num)
{ int r;
r = num/(int)pow(base, k); /* integer division */
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
	/* we use counting sort for sorting digits */
	//void radix_sort(int *A, int n, int d)
	 int i, j, m;
	/* temporary storage */
	int *C = new int[base];
	int *B = new int[size];
	int d = getMax(A, size);
	for (m = 0; m < d; m++)
	{
		for (i = 0; i < base; i++) 
			C[i] = 0;
		for (j = 0; j < size; j++)
		{	//std::cout << digit(m, A[j]) << std::endl;
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
		} /* copy B -> A */
			
		for (j = 0; j < size; j++)
		{
			A[j] = B[j];
		}		
	}	
	delete [] B; delete [] C;
}

  /*
     Complete this function with the implementation of radix sort
     algorithm.
  */

/*
int digit(int k, int num)
{ int r;
r = num/(int)pow(base, k); // integer division 
return r % base;
}

int getMax(int arr[], int n)
{
    int max = arr[0];
    int n=0;
	for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
	while(max!=0){
	max=max/10;
	n++;
	}
    return n;
}*/