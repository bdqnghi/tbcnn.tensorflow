//============================================================================
// Name        : radix-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include <cmath>

void
RadixSort::sort(int A[], int size)
{
	/*
	  Complete this function with the implementation of radix sort
	  algorithm.
	*/
	
	/* find max */
	int max_number = A[0];
	for (int i = 0; i < size;i++) {
		if (A[i] > max_number)
			max_number = A[i];
	}
    //
    for (int base = 1; max_number/base > 0; base *= 10){//
        int sorted_array[size]; // sorted_array array
        int i, count[10] = {0};
        
        // Store count of occurrences in count[]
        for (i = 0; i < size; i++)
            count[ (A[i]/base)%10 ]++;
        
        // Change count[i] so that count[i] now contains actual position of
        // this digit in sorted_array[]
        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];
        
        // Build the sorted_array array
        for (i = size - 1; i >= 0; i--)
        {
            sorted_array[count[ (A[i]/base)%10 ] - 1] = A[i];
            count[ (A[i]/base)%10 ]--;
        }
        
        // Copy the sorted_array to A[], so that A[] now
        // contains sorted numbers according to curent digit
        for (i = 0; i < size; i++)
            A[i] = sorted_array[i];
    }
	
}
