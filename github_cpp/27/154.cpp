//============================================================================
// Name        : radix-sort.cpp
// Author      : Jaiden Gerig
// Date        : 2/5/14
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include <math.h>
void

RadixSort::sort(int A[], int size)
{
num_cmps = 0;
int i;

  // find the max number in the given list.
  // to be used in loop termination part.
  int maxNumber = A[0];
  for (i = 1; i < size; i++)
  {
    if (A[i] > maxNumber)
      maxNumber = A[i];
  }

  // run the loop for each of the decimal places
  int exp = 1;
  int *tmpBuffer = new int[size];
  while (maxNumber / exp > 0)
  {
    int decimalBucket[10] = {  0 };
    // count the occurences in this decimal digit.
    for (i = 0; i < size; i++)
      decimalBucket[A[i] / exp % 10]++;

    // Prepare the position counters to be used for re-ordering the numbers
    // for this decimal place.
    for (i = 1; i < 10; i++)
      decimalBucket[i] += decimalBucket[i - 1];

    // Re order the numbers in the tmpbuffer and later copy back to original buffer.
    for (i = size - 1; i >= 0; i--)
      tmpBuffer[--decimalBucket[A[i] / exp % 10]] = A[i];
    for (i = 0; i < size; i++)
      A[i] = tmpBuffer[i];

    // Move to next decimal place.
    exp *= 10;
  }
	
}

