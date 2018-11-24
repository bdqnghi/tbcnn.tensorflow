//============================================================================
// Name        : radix-sort.cpp
// Author      : Alex Kaiser
// Date        :
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

void
RadixSort::sort(int A[], int size)
{
  /*
     Complete this function with the implementation of radix sort
     algorithm.
  */
for(int i = 0; i < size; i++)
	A[i] += 32767;

 int i, j, m;

int *C = new int[10];
int *B = new int[size];
for (m = 0; m < 10; m++) {
	for (i = 0; i < 10; i++) C[i] = 0;
	for (j = 0; j < size; j++) C[(A[j]/(int)pow(10, m))%10]++;
	for (i = 1; i < 10; i++) C[i] += C[i-1];
	for (j = size-1; j >= 0; j--) {
		int digit = ((A[j]/(int)pow(10, m))%10);
		i = C[digit] - 1;
		C[digit]--;
		B[i] = A[j];
	}
for (j = 0; j < size; j++) A[j] = B[j];
//for (i = 0; i < size; i++) cout << A[i];
}
delete [] B; delete [] C; 

for(int i = 0; i <= size; i++)
	A[i] -= 32767;
}
