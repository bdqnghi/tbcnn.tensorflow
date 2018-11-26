//============================================================================
// Name        : radix-sort.cpp
// Author      : Oneal Abdulrahim
// Date        : 19 September 2016
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include <cmath>

/// Find minimum
/**
Located the minimum value of the given array. This will be useful to use
with radix sort, because if we have negative indices, we must account for it.
@param A	The array to be traversed
@param size	The size of the array A
@return min	The minimum value within A*/
int get_minimum(int A[], int size) {
	int min = A[0];
	
	for (int i = 1; i < size; ++i) {
		if (min > A[i]) {
			min = A[i];
		}
	}
	
	return min;
}

///Find maximum
/**
Located the maximum value of the given array.
@param A	The array to be traversed
@param size	The size of the array A
@return min	The maximum value within A*/
int get_maximum(int A[], int size) {
	int max = A[0];
	for (int i = 1; i < size; ++i) {
		if (A[i] > max) {
            max = A[i];
		}
	}
	
	return max;
}

/// Shift indices
/**
Shifts every integer in the array by the value of the given integer
@param A	The array to be shifted
@param size	The size of the array A
@param value	The amount to shift by */
void shift_array(int A[], int size, int value) {
	for (int i = 0; i < size; ++i) {
		A[i] += value;
	}
}

/**
▒▒▒▒▒▒▄▄██████▄
▒▒▒▒▒▒▒▒▒▒▄▄████████████▄
▒▒▒▒▒▒▄▄██████████████████
▒▒▒▄████▀▀▀██▀██▌███▀▀▀████
▒▒▐▀████▌▀██▌▀▐█▌████▌█████▌
▒▒█▒▒▀██▀▀▐█▐█▌█▌▀▀██▌██████
▒▒█▒▒▒▒████████████████████▌
▒▒▒▌▒▒▒▒█████░░░░░░░██████▀
▒▒▒▀▄▓▓▓▒███░░░░░░█████▀▀
▒▒▒▒▀░▓▓▒▐█████████▀▀▒
▒▒▒▒▒░░▒▒▐█████▀▀▒▒▒▒▒▒
▒▒░░░░░▀▀▀▀▀▀▒▒▒▒▒▒▒▒▒
▒▒▒░░░░░░░░▒▒
*/
//http://www.geeksforgeeks.org/radix-sort/
void
RadixSort::sort(int A[], int size) {
	bool is_negative = false;
	int minimum = get_minimum(A, size);
	
	// see if we must account for negative numbers
	if (minimum < 0) {
		shift_array(A, size, abs(minimum));
		is_negative = true;
	}
	
	// find the maximum index, so that we know to what order of digits
	// we need to search for (what decimal place past ones place)
	int maximum = get_maximum(A, size);
	
	// we essentially perform a counting sort for every digit place
	// on each loop iteration, the order of magnitude increases by 1
	// and goes up based on the max
	for (int order = 1; maximum / order > 0; order *= 10) {
		
		// begin counting sort
		int result[size];
		int bucket[10] = {0}; // there are only 10 digits (0 --> 9)
		
		// count the number of occurrences of each digit, place in bucket
		for (int i = 0; i < size; ++i) {
			bucket[(A[i] / order) % 10]++;
		}
		
		// ensure that the bucket values contain the position of the digit
		// which are less than or equal to the index value_comp
		for (int i = 1; i < 10; ++i) {
			bucket[i] += bucket[i - 1];
		}
		
		// use the bucketed values to create the resultant array, sorted
		// by the value of the digit at the respective order
		for (int i = size - 1; i >= 0; --i) {
			result[bucket[(A[i] / order) % 10] - 1] = A[i];
			bucket[(A[i] / order) % 10]--; // decrement once used
		}
		
		// finally, our resulting array must be copied to Abdulrahim
		for (int i = 0; i < size; ++i) {
			A[i] = result[i];
		}
	}
	
	// re-shift array properly if we shifted before
	if (is_negative) {
		shift_array(A, size, minimum);
	}
}

