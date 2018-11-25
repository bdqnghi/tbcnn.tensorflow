




#ifndef _SELECTION_HPP_
#define _SELECTION_HPP_

#include <iostream>
#include <chrono>
#include "message.hpp"



template <typename T>
void selection_sort(T arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[min] > arr[j]) {
                min = j;
            }
        }
        std::swap(arr[min], arr[i]); 
    }
}

#endif  
