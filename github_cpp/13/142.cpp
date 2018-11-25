







#include "sort.h"

void 
BubbleSort::sort(int A[], int size)			
{
  
  
	resetNumCmps();
  
	  for(int i=1; i < size; i++) {
		  bool cont = false;
		  for(int j=0; j < size-i; j++) {
			  if((num_cmps++, A[j+1] < A[j])) {
				
				int tmp = A[j];
				A[j] = A[j+1];
				A[j+1] = tmp;
				cont = true;
			  }
		  }
		  if (!cont) break;
	  }
  }
  

  

