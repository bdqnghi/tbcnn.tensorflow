//============================================================================
// Name        : radix-sort.cpp
// Author      : Shaeeta Sharar
// Date        :
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include "math.h"

using namespace std;

const int base = 10;
int digit(int k, int num)
{
	int r;
	r = num/(int)pow(static_cast<double>(base),k);
	return r%base;
}

void RadixSort::sort(int A[], int size)
{
	int i, j, m;
	
	int* tempC = new int [base];
	int* tempB = new int[size];
	
	for (m = 0; m<d; m++)
	{
		for(i = 0; i<base; i++)
		{
			tempC[i] =0;
		}
		for (j = 0; j<size; j++)
		{
			tempC[digit(m,A[j])]++;
		}
		for(i = 1; i<base; i++)
		{
			tempC[i] += tempC[i-1];
		}
		for (j = size-1; j >=0; j--)
		{
			i = --tempC[digit(m, A[j])];
			tempB[i] = A[j];
		}
		
		for(j=0; j<size; j++)
		{
			A[j] = tempB[j];
		}
	}
	delete [] tempB;
	delete [] tempC;
 
}
