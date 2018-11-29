//
// Created by andy on 18-2-7.
//

#ifndef SELECTIONSORT_SELECTIONSORT_H
#define SELECTIONSORT_SELECTIONSORT_H

#include <iostream>

template<typename T>
void selectionSort(T *arr, int n)
{
    for(int i = 0; i < n - 1; i++ )
    {
        //寻找[i,n)之间的最小值
        int minIndex = i;
        for(int j = i+1; j < n; j++)
        {
            if(arr[j] < arr[minIndex])
                minIndex = j;
        }
        std::swap(arr[i], arr[minIndex]);
    }
}
#endif //SELECTIONSORT_SELECTIONSORT_H
