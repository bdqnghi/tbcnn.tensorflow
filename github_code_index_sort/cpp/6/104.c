//============================================================================
// Name        : radix-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include <cstring>
#include <algorithm> 



void RadixSort::sort(int A[], int size) 
{
    int B[size]; // second array 
    int k = A[0]; // set k to begining of list
    int exp = 1;

    for(int i = 0; i < size; i++) 
    {
        if(A[i] > k)
            k = A[i];   //determining the K value in the array
    }

    while(k / exp > 0)
    {
        int iBucket[10] = {0}; //fill array with null

        for(int i  = 0; i < size; i++)
        {
            iBucket[(A[i] / exp) % 10]++; //orginizes element into Buckets
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