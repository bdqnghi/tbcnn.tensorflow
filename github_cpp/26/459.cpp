//============================================================================
// Name        : bubble-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of bubble sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

/*void 
BubbleSort::sort(int A[], int size)			// main entry point
{
  /* Complete this function with the implementation of bubble sort algorithm 
     Record number of comparisons in variable num_cmps of class Sort
  
  
  printf("WESTSANGISAWESOME");
}*/

/*void BubbleSort::sort(int A[], int size) 
{ 
	int counter(0);
	
	
	for(int i = 0; i < size; i++) 
	{ 
		bool swapped = false;
		
		for(int j = 1; j < (size-i); j++) 
		{ 
			if(counter++,A[j-1]>A[j]) 
			{ 
			int temp = A[j-1];
			A[j-1] = A[j];
			A[j] = temp;
			swapped=true;
			
			//swap(A[j-1],A[j]); 
			} 
		} 
	} 
	
	num_cmps = counter;
} */

void BubbleSort::sort(int A[], int size) {
      bool swapped = true;
      int j = 0;
      int tmp;
	  int counter(0);
	  
      while (swapped) {
            swapped = false;
            j++;
            for (int i = 0; i < size - j; i++) {
                  if(counter++,A[i]>A[i+1]) {
                        tmp = A[i];
                        A[i] = A[i + 1];
                        A[i + 1] = tmp;
                        swapped = true;
						
                  }
            }
      }
	  num_cmps = counter;
}


// wwwalgolist.ret ----
