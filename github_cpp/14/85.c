






#include "sort.h"

 

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


void countSort(int* arr, int n, int digit)
{
    int output[n]; 
    int i, placeCount[10] = {0};
 
    
    for (i = 0; i < n; i++)
        placeCount[ (arr[i]/digit)%10 ]++;
 
    
    for (i = 1; i < 10; i++)
        placeCount[i] += placeCount[i - 1];
 
    
    for (i = n - 1; i >= 0; i--)
    {
        output[placeCount[ (arr[i]/digit)%10 ] - 1] = arr[i];
        placeCount[ (arr[i]/digit)%10 ]--;
    }
 
    
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}


void RadixSort::sort(int* arr, int n)
{
    
    checkNeg(arr, n);
    
    int max = getMax(arr, n);
 
    
    for (int digit = 1; max/digit > 0; digit *= 10)
        countSort(arr, n, digit);
}