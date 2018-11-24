//============================================================================
// Name        : radix-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include<iostream>
using namespace std;

int getMax(int arr[], int n)
{
    int mx = arr[0];

    for (int i = 1; i < n; i++){
        if (arr[i] > mx)
            mx = arr[i];
	}
    return mx;
}
int getMin(int arr[], int n){
	int mn = arr[0];
    for (int i = 1; i < n; i++){
		if (arr[i] < mn)
			mn = arr[i];
	}
	if (mn < 0){
		int min = 0- mn;
		for(int i=0; i<n; i++){
			arr[i] = arr[i] + min;
		}
	}
    return mn;
}
void countSort(int arr[], int n, int exp)
{
    int output[n]; // output array
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[ (arr[i]/exp)%10 ]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    for (i = n - 1; i >= 0; i--)
    {
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void RadixSort::sort(int A[], int size)
{
    int m = getMax(A, size);
    int mn = getMin(A, size);
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(A, size, exp);
	
	if(mn<0){
		for(int i=0; i<size; i++){
			A[i] = A[i] + mn;
		}
	}
	
}
