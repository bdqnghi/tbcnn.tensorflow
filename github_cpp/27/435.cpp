/*
Jessica Fang, Justin Gonzalez, Juan Pablo Zambrano
CSCE 221-512
Radix Sort
*/

#include "sort.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
const int base = 10;

int Digit(int k, int num)
{
	int r;
	r = num/(int)pow(base, k);
	return r % base;
}

void RadixSort::sort(int A[], int size)
{	
	int d=0;
	int largest=0;
	int smallest=0;
	
	for(int i = 0; i < size; ++i)
		if(smallest > A[i])
			smallest = A[i];
	
	bool neg = false;
	if(smallest < 0)
	{
		neg = true;
		for(int i = 0; i < size; ++i)
			A[i] = A[i] - smallest;
	}
	
	for(int i = 0; i < size; ++i)
		if(largest < A[i])	
			largest = A[i];	
			
	for(; largest>0; largest/=10)
		d++;
	
	int i, j, m;
	int* C = new int[base];
	int* B = new int[size];
	
	for (m = 0; m < d; m++)
	{
		for (i = 0; i < base; i++)  C[i] = 0;
		for (j = 0; j < size; j++)  C[Digit(m, A[j])]++;
		for (i = 1; i < base; i++)	C[i] += C[i-1];
		for (j = size-1; j >= 0; j--)
		{
			i = C[Digit(m, A[j])]-- -1;
			B[i] = A[j];
		}
	
		for (j = 0; j < size; j++)  A[j] = B[j];
	}
	
	if(neg == true)
	{	
		for(int i = 0; i < size; ++i)
			A[i] = A[i] + smallest;
	}
	
	delete[] B;
	delete[] C;
}