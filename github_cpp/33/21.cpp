//============================================================================
// Name        : shell-sort.cpp
// Author      : Raymond Zhu & Wesley Ng
// Date        : 9/27/15
// Copyright   : 
// Description : Implementation of shell sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

inline int get_next_gap(int gap)
{
  if (gap ==2) return 1;
  return (int)(gap/2.2);
}

void
ShellSort::sort(int A[], int size)
{
int gap = size/2; 
  for(; gap > 0; gap = get_next_gap(gap))
  {
    for(int i = gap; i < size; i++)
    {
      int temp = A[i];
      int j = i;
      while (j >= gap && temp < A[j - gap])
      {
        A[j] = A[j-gap];
        j = j - gap;
        num_cmps++;
      }
      A[j] = temp;
    }
  }
}

