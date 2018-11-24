//============================================================================
// Name        : bubble-sort.cpp
// Author      : 
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
  //for(int i=0; i<2; ++i) {
	resetNumCmps();
  //if(i==0) {
	  for(int i=1; i < size; i++) {
		  bool cont = false;
		  for(int j=0; j < size-i; j++) {
			  if((num_cmps++, A[j+1] < A[j])) {
				//swap(A[j+1], A[j]);
				int tmp = A[j];
				A[j] = A[j+1];
				A[j+1] = tmp;
				cont = true;
			  }
		  }
		  if (!cont) break;
	  }
  }
  
/*   if(i==1) {
	  for(int i=1; i < size; i++) {
		  bool cont = false;
		  for(int j=0; j < size-i; j++) {
			  if(A[j+1] < A[j]) {
				//swap(A[j+1], A[j]);
				int tmp = A[j];
				A[j] = A[j+1];
				A[j+1] = tmp;
				cont = true;
				num_cmps++;
			  }
		  }
		  if (!cont) break;
	  }
  }  */
  
//}
