//============================================================================
// Name        : radix-sort.cpp
// Author      : Peng Li    
// Date        : Sep 24, 2014
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
const int base = 10;

int digit(int k, int num) {
    int r;
    r = num/(int) std::pow(base, k); /* integer division */
    return (r % base)+9;
}

void
RadixSort::sort(int A[], int size)
{
  /*
     Complete this function with the implementation of radix sort
     algorithm.
  */
    // find max number
    int max = 0;
    for (int i=0; i<size; i++) {
        max = (abs(A[i]) > abs(max))? A[i]: max;
    }
    
    // count digits
    int digits = 0;
    //    if (max < 0) digits = 1; // remove this line if '-' counts as a digit
    while (max) {
        max /= 10;
        digits++;
    }
    
    int i, j, m;
    int *C  = new int[base+9];// from -9 to 9
    int *B = new int[size];
    for (m=0; m<digits; m++) {
        for (i=0; i<base+9; i++) C[i] = 0;
        for (j=0; j<size; j++) C[digit(m,A[j])]++;
        for (i=1; i<base+9; i++) C[i] += C[i-1];
        for (j = size-1; j >= 0; j--) {
            i = --C[digit(m, A[j])];
            B[i] = A[j];
        } /* copy B -> A */
        for (j = 0; j < size; j++) A[j] = B[j];
    }
    delete [] B; delete [] C;


}
