//============================================================================
// Name        : bubble-sort.cpp
// Author      : Lysander Gutierrez
// Date        :
// Copyright   : 
// Description : Implementation of bubble sort in C++
//============================================================================

#include "sort.h"

void 
BubbleSort::sort(int A[], int size)			// main entry point
{
  /* Complete this function with the implementation of bubble sort algorithm 
     Record number of comparisons in variable num_cmps of class Sort
  */
    for(int iter=1; iter<size; iter++)
 {
	 bool IsSorted=false; 
	 for(int q=0; q<size-iter; q++)
	 {
		 if(A[q]>A[q+1])
		 {
			 num_cmps++;
			 int holder=A[q];
			 A[q]=A[q+1];
			 A[q+1]=holder;
			 IsSorted=true; 
		 }
		 if(!IsSorted)
		 {
			 num_cmps++;
			 IsSorted=true;
		 }
		 
	 }
 }
  

}
