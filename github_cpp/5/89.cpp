







#include "sort.h"

void
InsertionSort::sort(int A[], int size)				
{
  
    resetNumCmps(); 

    for (int k = 1;  k < size ; k ++) {
        int tmp =  A[k];
        int j = k ;
        for (; j > 0 && (num_cmps++,tmp < A[j-1]); j--){
            
            A[j] = A[j-1];
        }
        A[j] = tmp;
    }
}
