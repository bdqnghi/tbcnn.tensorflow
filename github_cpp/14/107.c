







#include "sort.h"
#include <iostream>
#include <cmath>

void
RadixSort::sort(int A[], int size)
{
	
	
	
	int max_number = A[0];
	for (int i = 0; i < size;i++) {
		if (A[i] > max_number)
			max_number = A[i];
	}
    
    for (int base = 1; max_number/base > 0; base *= 10){
        int sorted_array[size]; 
        int i, count[10] = {0};
        
        
        for (i = 0; i < size; i++)
            count[ (A[i]/base)%10 ]++;
        
        
        
        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];
        
        
        for (i = size - 1; i >= 0; i--)
        {
            sorted_array[count[ (A[i]/base)%10 ] - 1] = A[i];
            count[ (A[i]/base)%10 ]--;
        }
        
        
        
        for (i = 0; i < size; i++)
            A[i] = sorted_array[i];
    }
	
}
