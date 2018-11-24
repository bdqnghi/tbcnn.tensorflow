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
#define BASE 10

int Digit(int k, int num)
{
	int r;
	r=num/(int)(pow(BASE,k));
	return r%BASE;
}

void RadixSort::sort(int A[], int size)
{
	int d=0;	//to store the # of digits in the largest number
	int largest=0;
	for(int i=0; i<size; ++i)	//finds the largest number
		if(largest<A[i])	//checks if current # is larger than previous largest
			largest=A[i];	//assigns largest found number to largest
			
	for(; largest>0; largest/=10)	//counts the number of digits in the largest number
		d++;
	
	int i, j, m;
	int *C, *B; // temporary storage
		C=(int*) malloc(BASE*sizeof(int));
		B=(int*) malloc(size*sizeof(int));
		for (m=0; m<d; m++)
		{
			for (i=0; i<BASE; i++)
				C[i]=0;
			for (j=0; j<size; j++)
				C[Digit(m, A[j])]++;
			for (i=1; i<BASE; i++)
				C[i]+=C[i-1];
			for (j=size-1; j>=0; j--)
			{
				i=C[Digit(m, A[j])]-- -1;
				B[i]=A[j];
			}
	/* Copy B -> A*/
			for (j = 0; j < size; j++)
				A[j] = B[j];
		}
		free(B);
		free(C);
}
