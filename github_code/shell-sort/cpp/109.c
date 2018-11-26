//============================================================================
// Name        : shell-sort.cpp
// Author      : Daniel Jaeger
// Date        : 9/20/2016
// Copyright   : 
// Description : Implementation of shell sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

inline int ShellSort::next_space(int space)
{
  //std::clog << "BEFORE" << std::endl;
  if (space == 2) {
    //std::clog << "INSIDE" << std::endl;
    num_cmps++;
    return 1;
  }
  else return (int) (space/2.2);
}

void ShellSort::sort(int A[], int size)
{
  int space = size/2;
  for (; space > 0; space = next_space(space)) {
    for (int i = space; i < size; i++) {
      int temp = A[i];
      int j = i;
      while (j >= space && (num_cmps++, temp < A[j-space])) {
        A[j] = A[j-space];
        j -= space;
      }
      A[j] = temp;
    }
  }
}