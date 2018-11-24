//============================================================================
// Name        : selection-sort.cpp
// Author      : Raymond Zhu & Wesley Ng
// Date        : 9/27/15
// Copyright   : 
// Description : Implementation of selection sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

void
SelectionSort::sort(int A[], int size)				// main entry point
{
  for(int i = 0; num_cmps++, i < size; i++)
  {
    int curr_index = i;
    for(int j = i + 1;num_cmps++, j < size; j++)
    {
      if (num_cmps++, A[j] < A[curr_index])
        curr_index = j;
      num_cmps++;
    }
    int temp = A[curr_index];
    A[curr_index] = A[i];
    A[i] = temp;
  }    
}


