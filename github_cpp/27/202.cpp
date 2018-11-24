//============================================================================
// Name        : radix-sort.cpp
// Author      : All
// Date        :
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

int getMax(int A[], int size)
{
    int max = A[0];
    for (int i = 1; i < size; i++)
        if (A[i] > max)
            max = A[i];
    return max;
}

int getMin(int A[], int size) {
    int min = A[0];
    for(int i = 1; i<size; ++i) {
        if(A[i]<min) {
            min = A[i];
        }
    }
    return min;
}

void countSort(int A[], int size, int exp)
{
    int output[size];
    int i, count[10] = {0};
    for (i = 0; i < size; i++)
        count[(A[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (i = size - 1; i >= 0; i--)
    {
        output[count[(A[i] / exp) % 10] - 1] = A[i];
        count[(A[i] / exp) % 10]--;
    }
    for (i = 0; i < size; i++)
        A[i] = output[i];
}

void
RadixSort::sort(int A[], int size)
{   
    //check to see if there are any negative numbers in the input
    bool anyNegatives = false;
    for(int i = 0; i<size; ++i) {  
        if(A[i] < 0) {
            anyNegatives = true;
            break;
        }
    }

    //if there are any negative numbers, shift the input up by the smallest
    //this will make all numbers in input >= 0
    int smallest = getMin(A, size);
    smallest *= -1;
    if(anyNegatives) {
        for(int i = 0; i<size; ++i) {
            A[i] += smallest;
        }
    }

    //sort the non-negative numbers
    int m = getMax(A, size);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(A, size, exp);

    //shift the array back down
    if(anyNegatives) {
        for(int i = 0; i<size; ++i) {
            A[i] -= smallest;
        }
    }

}
