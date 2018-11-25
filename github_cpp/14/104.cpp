







#include "sort.h"
#include <iostream>
#include <cstring>
#include <algorithm> 



void RadixSort::sort(int A[], int size) 
{
    int B[size]; 
    int k = A[0]; 
    int exp = 1;

    for(int i = 0; i < size; i++) 
    {
        if(A[i] > k)
            k = A[i];   
    }

    while(k / exp > 0)
    {
        int iBucket[10] = {0}; 

        for(int i  = 0; i < size; i++)
        {
            iBucket[(A[i] / exp) % 10]++; 
        }

        for(int i = 0; i < 10; i++)
        {
            iBucket[i] += iBucket[i-1];
        }

        for(int i = size - 1; i >= 0; i--)
        {
            B[--iBucket[(A[i] / exp) % 10]] = A[i];
        }

        for(int i = 0; i < size; i++)
        {
            A[i] = B[i];
        }
        exp *= 10;
    }

    
}