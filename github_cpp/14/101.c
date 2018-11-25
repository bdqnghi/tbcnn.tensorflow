







#include "sort.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
const int base = 10;

int digit(int k, int num) {
    int r;
    r = num/(int) std::pow(base, k); 
    return (r % base)+9;
}

void
RadixSort::sort(int A[], int size)
{
  
    
    int max = 0;
    for (int i=0; i<size; i++) {
        max = (abs(A[i]) > abs(max))? A[i]: max;
    }
    
    
    int digits = 0;
    
    while (max) {
        max /= 10;
        digits++;
    }
    
    int i, j, m;
    int *C  = new int[base+9];
    int *B = new int[size];
    for (m=0; m<digits; m++) {
        for (i=0; i<base+9; i++) C[i] = 0;
        for (j=0; j<size; j++) C[digit(m,A[j])]++;
        for (i=1; i<base+9; i++) C[i] += C[i-1];
        for (j = size-1; j >= 0; j--) {
            i = --C[digit(m, A[j])];
            B[i] = A[j];
        } 
        for (j = 0; j < size; j++) A[j] = B[j];
    }
    delete [] B; delete [] C;


}
