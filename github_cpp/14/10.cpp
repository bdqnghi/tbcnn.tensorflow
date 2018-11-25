







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
    
    bool anyNegatives = false;
    for(int i = 0; i<size; ++i) {  
        if(A[i] < 0) {
            anyNegatives = true;
            break;
        }
    }

    
    
    int smallest = getMin(A, size);
    smallest *= -1;
    if(anyNegatives) {
        for(int i = 0; i<size; ++i) {
            A[i] += smallest;
        }
    }

    
    int m = getMax(A, size);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(A, size, exp);

    
    if(anyNegatives) {
        for(int i = 0; i<size; ++i) {
            A[i] -= smallest;
        }
    }

}
