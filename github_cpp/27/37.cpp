//============================================================================
// Name        : radix-sort.cpp
// Author      : Leilani Horlander-Cruz
// Date        : 02/19/17
// Copyright   : 2017
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include <math.h>
#define BASE 10

using namespace std;

int Digit(int p, int num)
{
	int r;
	r = num/(int)(pow(BASE,p));
	return r%BASE;
}

void RadixSort::sort(int A[], int size)
{
	int digits = 0; //# of digits in largest number
	int large = 0;
	for(int i = 0; i < size; i++) //finds largest number
	{
		if(large < A[i])
			large=A[i];
	}
	for(; large>0; large/=10) //counts # of digits in largest number
		digits++;
	int i, j, m;
	int *C, *B; //temp storage
	C = (int*) malloc(BASE*sizeof(int));
	B = (int*) malloc(size*sizeof(int));
	for (m=0; m < digits; m++)
	{
		for (i = 0; i < BASE; i++)
			C[i] = 0;
		for (j = 0; j < size; j++)
			C[Digit(m,A[j])]++;
		for (i = 1; i < BASE; i++)
			C[i]+=C[i-1];
		for (j = size-1; j >= 0; j--)
		{
			i = C[Digit(m,A[j])]-- -1;
			B[i] = A[j];
		}
		for (j = 0; j < size; j++)
			A[j] = B[j];
	}
	free(B);
	free(C);
}
