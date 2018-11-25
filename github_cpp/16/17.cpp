



#ifndef SHELLSORT_SHELLSORT_H
#define SHELLSORT_SHELLSORT_H

#include "InsertSortMethod.h"

namespace ShellSort {
    int step = 3;

    template<typename T>
    void shellSort(T *arr, int n) {
        
        for (int h = n / step; h > 0; h = h / step) {
            
            for (int i = 0; i < h; ++i) {
                
                for (int j = i; j < n; j = j + h) {
                    
                    T t = arr[j];
                    int insertIndex = j;
                    
                    
                    
                    
                    for (int k = j; k - h >= 0 && t > arr[k - h]; k = k - h) {
                        arr[k] = arr[k - h];
                        insertIndex = k - h;
                    }
                    arr[insertIndex] = t;
                }
            }
        }
    }
}

#endif 
