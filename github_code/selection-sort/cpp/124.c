//============================================================================
// Name        : selection-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of selection sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

void
SelectionSort::sort(int A[], int size)				// main entry point
{
  resetNumCmps();   //reset the number of comparisons for other algorithms

  for(int i=0; i < size-1; i++){
    int position = i;
    int temp = i;
    for(int k=i+1; k<size;k++){           //Iterate through the array
      if(++num_cmps,A[k]<A[position])     //Count the first comparison
        position = k;                   //Assigne new position to variable k
    } 
      temp = A[i];                //Save old value to temp
      A[i] = A[position];         //Changing of A[i] and A[index]
      A[position] = temp;         
  }

}
