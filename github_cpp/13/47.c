




#ifndef _BUBBLE_HPP_
#define _BUBBLE_HPP_

#include <iostream>
#include <chrono>
#include <cmath>
#include "message.hpp"



template <typename T>
void bubble_sort(T arr[], int size) {
    int i;
    bool flag;
    do {
        flag = false;
        for (i = 0; i < (size - 1); i++) {
            if (arr[i] > arr[i+1]) {
                std::swap(arr[i], arr[i+1]);
                flag = true;
            }
        }
    } while (flag);
}

#endif  
