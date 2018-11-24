//============================================================================
// Name        : shell-sort.cpp
// Author      : Garret Sifuentez
// Date        :9/14/16
// Copyright   : 
// Description : Implementation of shell sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

void
ShellSort::sort(int A[], int size) {
  int gap;
  int temp;

    for (gap = size/2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            for (int j=i-gap; j>=0; j-=gap) {
				num_cmps++;
				if(A[j] > A[j+gap]) {
						temp = A[j];
						A[j] = A[j+gap];
						A[j+gap] = temp;
				} else break;
            }
		}
	}
}
