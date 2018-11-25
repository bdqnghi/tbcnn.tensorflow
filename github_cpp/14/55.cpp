







#include "sort.h"
#include <iostream>
#include <cmath>



int get_minimum(int A[], int size) {
	int min = A[0];
	
	for (int i = 1; i < size; ++i) {
		if (min > A[i]) {
			min = A[i];
		}
	}
	
	return min;
}



int get_maximum(int A[], int size) {
	int max = A[0];
	for (int i = 1; i < size; ++i) {
		if (A[i] > max) {
            max = A[i];
		}
	}
	
	return max;
}



void shift_array(int A[], int size, int value) {
	for (int i = 0; i < size; ++i) {
		A[i] += value;
	}
}



void
RadixSort::sort(int A[], int size) {
	bool is_negative = false;
	int minimum = get_minimum(A, size);
	
	
	if (minimum < 0) {
		shift_array(A, size, abs(minimum));
		is_negative = true;
	}
	
	
	
	int maximum = get_maximum(A, size);
	
	
	
	
	for (int order = 1; maximum / order > 0; order *= 10) {
		
		
		int result[size];
		int bucket[10] = {0}; 
		
		
		for (int i = 0; i < size; ++i) {
			bucket[(A[i] / order) % 10]++;
		}
		
		
		
		for (int i = 1; i < 10; ++i) {
			bucket[i] += bucket[i - 1];
		}
		
		
		
		for (int i = size - 1; i >= 0; --i) {
			result[bucket[(A[i] / order) % 10] - 1] = A[i];
			bucket[(A[i] / order) % 10]--; 
		}
		
		
		for (int i = 0; i < size; ++i) {
			A[i] = result[i];
		}
	}
	
	
	if (is_negative) {
		shift_array(A, size, minimum);
	}
}

