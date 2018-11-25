







#include "sort.h"
#include <iostream>
#include <math.h>
void

RadixSort::sort(int A[], int size)
{
num_cmps = 0;
int i;

  
  
  int maxNumber = A[0];
  for (i = 1; i < size; i++)
  {
    if (A[i] > maxNumber)
      maxNumber = A[i];
  }

  
  int exp = 1;
  int *tmpBuffer = new int[size];
  while (maxNumber / exp > 0)
  {
    int decimalBucket[10] = {  0 };
    
    for (i = 0; i < size; i++)
      decimalBucket[A[i] / exp % 10]++;

    
    
    for (i = 1; i < 10; i++)
      decimalBucket[i] += decimalBucket[i - 1];

    
    for (i = size - 1; i >= 0; i--)
      tmpBuffer[--decimalBucket[A[i] / exp % 10]] = A[i];
    for (i = 0; i < size; i++)
      A[i] = tmpBuffer[i];

    
    exp *= 10;
  }
	
}

