







#include "sort.h"
#include <iostream>





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



