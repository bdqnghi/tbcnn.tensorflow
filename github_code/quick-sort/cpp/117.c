//
//  quick-sort.cpp
//  sort-algorithm
//
//  Created by Meilei Jiang on 10/4/15.
//  Copyright © 2015 Meilei Jiang. All rights reserved.
//

#include "quick-sort.hpp"

void quick_sort(int* A, int low, int high)
{
    if (low < high) {
        int pivot;
        pivot = partition(A, low, high);
        quick_sort(A, low, pivot-1);
        quick_sort(A, pivot + 1, high);
    }
}

int partition(int* A, int low, int high)
{
    int x,i,temp;
    x = A[high]; // select the last number of A as pivot
    i = low - 1;
    
    for (int j = low; j <= high-1; j++) {
        if (A[j] <= x) {
            i++;
            temp = A[j];
            A[j] = A[i];
            A[i] = temp;
        }
    }
    temp = A[i+1];
    A[i+1] = x;
    A[high] = temp;
    return i+1;
}