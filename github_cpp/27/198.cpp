//============================================================================
// Name        : radix-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include "string.h"
#include <cmath>

/* int digit(double k, int num)
{ 
	double base=10.0;
	int base1=10;
	int r;
	r = num/(int)pow(base, k); // integer division
	return r % base1;
}

void
RadixSort::sort(int A[], int size)
{
  // Complete this function with the implementation of radix sort
  // algorithm.
	int i, j, m;
	int d=10;
	int base=10;
	// temporary storage
	int *C = new int[base];
	int *B = new int[size];
	for (m = 0; m < d; m++) {
		for (i = 0; i < base; i++) C[i] = 0;
		for (j = 0; j < size; j++) C[digit(m, A[j])]++;
		for (i = 1; i < base; i++) C[i] += C[i-1];
		for (j = size-1; j >= 0; j--) {
			i = C[digit(m, A[j])]--;
			B[i] = A[j];
		} // copy B -> A
		for (j = 0; j < size; j++) A[j] = B[j];
	}
	delete [] B; delete [] C;
}
 */

 // A utility function to get maximum value in arr[]
int getMax(int A[], int size)
{
    int mx = A[0];
    for (int i = 1; i < size; i++)
        if (A[i] > mx)
            mx = A[i];
    return mx;
}
 
// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(int A[], int size, int exp)
{
    int output[size]; // output array
    int i, count[10] = {0};
 
    // Store count of occurrences in count[]
    for (i = 0; i < size; i++)
        count[ (A[i]/exp)%10 ]++;
 
    // Change count[i] so that count[i] now contains actual position of
    // this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    // Build the output array
    for (i = size - 1; i >= 0; i--)
    {
        output[count[ (A[i]/exp)%10 ] - 1] = A[i];
        count[ (A[i]/exp)%10 ]--;
    }
 
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to curent digit
    for (i = 0; i < size; i++)
        A[i] = output[i];
}
 
// The main function to that sorts arr[] of size n using Radix Sort
void
RadixSort::sort(int A[], int size)
{
    // Find the maximum number to know number of digits
    int m = getMax(A, size);
 
    // Do counting sort for every digit. Note that instead of passing digit
    // number, exp is passed. exp is 10^i where i is current digit number
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(A, size, exp);
}