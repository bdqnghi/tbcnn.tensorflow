







#include "sort.h"
#include <iostream>

#define RANGE 10

void RadixSort::sort(int A[], int size)
{
	int* B = new int[size];
	int digit = 1;

	int max = A[0];
	int min = A[0];
	for(int i = 1; i < size; i++)
	{
		if(A[i] > max) { max = A[i]; }
		if(A[i] < min) { min = A[i]; }
	}

	max -= min;
	for(int i = 0; i < size; i++)
	{
		A[i] -= min;
	}

	while(max / digit > 0)
	{
		int counts[RANGE] = {0};
		for(int i = 0; i < size; i++) {
			counts[(A[i] / digit) % RANGE]++;
		}
		for(int i = 1; i < RANGE; i++) {
			counts[i] += counts[i - 1];
		}
		for(int i = size - 1; i >= 0; i--) {
			B[--counts[(A[i] / digit) % RANGE]] = A[i];
		}
		for(int i = 0; i < size; i++) {
			A[i] = B[i];
		}
		digit *= RANGE;
	}

	for(int i = 0; i < size; i++)
	{
		A[i] += min;
	}

	delete[] B;
}
