//============================================================================
// Name        : radix-sort.cpp
// Author      : Clayton Dittman
// Date        : 09/22/2015
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"

 
//get max value in array
int getMax(int* arr, int n)
{
    int maxInt = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > maxInt)
            maxInt = arr[i];
    return maxInt;
}

void checkNeg(int* arr, int n)
{
    int makeZero=0;
    
    for (int i =0; i<n; ++i)
    {
        if (arr[i] < 0 && arr[i] < makeZero) makeZero=arr[i];
    }
    
    if (makeZero < 0)
    {
       for (int i=0; i<n; ++i) arr[i] += abs(makeZero);
    } 
}

//modify counting sort for radix sort by looking at digit
void countSort(int* arr, int n, int digit)
{
    int output[n]; // output array
    int i, placeCount[10] = {0};
 
    // Store placeCount
    for (i = 0; i < n; i++)
        placeCount[ (arr[i]/digit)%10 ]++;
 
    // Change placeCount[i] to contain the position of digit in output[]
    for (i = 1; i < 10; i++)
        placeCount[i] += placeCount[i - 1];
 
    // setup  array
    for (i = n - 1; i >= 0; i--)
    {
        output[placeCount[ (arr[i]/digit)%10 ] - 1] = arr[i];
        placeCount[ (arr[i]/digit)%10 ]--;
    }
 
    // Copy the output array to arr[], to update it with sorted integers according to digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// Uses modified counting sort and getMax to perform radix sort.
void RadixSort::sort(int* arr, int n)
{
    //check for negative number
    checkNeg(arr, n);
    // Find the maximum number
    int max = getMax(arr, n);
 
    // Perform counting sort for every digit.
    for (int digit = 1; max/digit > 0; digit *= 10)
        countSort(arr, n, digit);
}