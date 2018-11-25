







#include "sort.h"
#include <iostream>

void
SelectionSort::sort(int A[], int size)				
{
  resetNumCmps();   

  for(int i=0; i < size-1; i++){
    int position = i;
    int temp = i;
    for(int k=i+1; k<size;k++){           
      if(++num_cmps,A[k]<A[position])     
        position = k;                   
    } 
      temp = A[i];                
      A[i] = A[position];         
      A[position] = temp;         
  }

}
