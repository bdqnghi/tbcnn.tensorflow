//============================================================================
// Name        : bubble-sort.cpp
// Author      : Raymond Zhu & Wesley Ng
// Date        : 9/27/15
// Copyright   : 
// Description : Implementation of bubble sort in C++
//============================================================================

#include "sort.h"

void 
BubbleSort::sort(int A[], int size)			// main entry point
{
  for (int i = 1; (num_cmps++, i < size); i++)
  {
    bool cont = false;
    for(int j = 0; (num_cmps++,j < size - i); j++)
    { 
      if((num_cmps++,A[j + 1] < A[j]))
      {
        int curr = A[j];
        A[j] = A[j + 1];
        A[j+1] = curr;
        cont = true;
      }
    }
	if((num_cmps++,cont == false)) break;
  }
}
