//============================================================================
// Name        : selection-sort.cpp
// Author      : Jacob Rodgers
// Date        : 9/19/16
// Copyright   : 
// Description : Implementation of selection sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
//using namespace std;

void
SelectionSort::sort(int A[], int size){
		int i, k, index, tmp;
		for (k = 0; k < size - 1; k++) {
			int index = k;
			for (i = k + 1; i < size; i++) {
				if (A[i] < A[index]) {
					//std::clog << A[i] << " < " << A[index] << std::endl;
					//std::clog << A[i] << " & " << A[index] << std::endl;
					index = i;
				} //else {std::clog << A[i] << " >= " << A[index] << std::endl;}
				num_cmps++;
			}
			if (index != k) {
				int tmp = A[k]; // swap A[k] and A[index]
				A[k] = A[index]; // k first index
				A[index] = tmp;
				num_cmps++;
			}
		}
}
