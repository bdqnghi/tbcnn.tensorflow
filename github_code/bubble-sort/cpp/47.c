//  "Copyright [2017] <MGTU IU8-33>"
//  BUBBLE.HPP

/*!
    \file
    \brief bubble_sort
    \details В данном заголовочном файле реализован шаблонный алгоритм устойчивой сортировки BUBBLE.
    \author Кошкина Ульяна
    \date 12/12/2017
*/

#ifndef _BUBBLE_HPP_
#define _BUBBLE_HPP_

#include <iostream>
#include <chrono>
#include <cmath>
#include "message.hpp"

/*!
Функция bubble_sort.
Сортирует массив алгоритмом устойчивой сортировки BUBBLE.

\param[in] arr[] - Массив, который необходимо отсортировать.
\param[in] size - Размер передаваемого массива.
\snippet bubble.cpp bubble_sort_example
*/

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

#endif  // _BUBBLE_HPP_
