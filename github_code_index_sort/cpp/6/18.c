//============================================================================
// Name        : radix-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

  void RadixSort::sort(int A[], int size) 
{ 
	int i, m(A[0]),B[size+1], exp(1),counter(0);
	
	for(i = 0; i < size; i++) 
	{ 

		if(counter++,A[i] > m) { m = A[i]; } 
	}
	
	while (counter++, (m / exp) > 0) 
	{
		int bucket[10] =
		{  0 };
	
		for ( i = 0; i < size; i++) 
		
			bucket[A[i] / exp % 10]++;
		
		for (i = 1; i < 10; i++)
		
			bucket[i] += bucket[i - 1];
		
		for (i = size - 1; i >= 0; i--)
			 
			B[--bucket[A[i] / exp % 10]] = A[i];
		
		for (i = 0; i < size; i++) 
		
		A[i] = B[i];
		
		exp *= 10; 
	}
	num_cmps = counter;
} 

