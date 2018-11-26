//
//  counting.cpp
//  Sorting
//
//  Created by Aviral Aggarwal on 09/07/17.
//  Copyright © 2017 Aviral Aggarwal. All rights reserved.
//

#include <iostream>
using namespace std;

void swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void printArray(int arr[],int size)
{
    for(int i=0;i<size;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}
int getMax(int arr[],int size)
{
    int max = arr[0];
    for(int i=0;i<size;i++)
    {
        if(max<arr[i])
            max = arr[i];
    }
    return max;
}

void countSort(int arr[], int n, int exp)
{
    int output[n]; // output array
    int i, count[10] = {0};
    
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[ (arr[i]/exp)%10 ]++;
    
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }
    
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
void newCountSort(int arr[],int n,int exp){
    
    int range[10] = {0};
    int newArr[n];
    
    for(int i=0;i<n;i++)
    {
        range[((arr[i]/exp)%10)]++;
    }
    for(int i=1;i<10;i++)
    {
        range[i] += range[i-1];
    }
    
    for(int i=n-1;i>=0;i--)
    {
        newArr[range[((arr[i]/exp)%10)]-1] = arr[i];
        range[((arr[i]/exp)%10)]--;
    }
    for(int i=0;i<n;i++)
    {
        arr[i] = newArr[i];
    }
}
// The main function to that sorts arr[] of size n using
// Radix Sort
void radixsort(int arr[], int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);
    
    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m/exp > 0; exp *= 10)
        newCountSort(arr, n, exp);
}





int main(int argc, const char * argv[]) {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int size = (sizeof(arr)/sizeof(arr[0]));
    radixsort(arr, size);
    printArray(arr, size);
    
    return 0;
}
