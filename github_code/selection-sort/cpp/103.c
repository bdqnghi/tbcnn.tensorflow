//  "Copyright [2017] <MGTU IU8-33>"
//  SELECTION.HPP

/*!
    \file
    \brief selection_sort
    \details В данном файле реализован шаблонный алгоритм неустойчивой сортировки SELECTION.
    \author Овчаров Анисим
    \date 14/12/2017
*/

#ifndef _SELECTION_HPP_
#define _SELECTION_HPP_

#include <iostream>
#include <chrono>
#include "message.hpp"

/*!
Функция selection_sort.
Сортирует массив алгоритмом неустойчивой сортировки SELECTION.

\param[in] arr[] - Массив, который необходимо отсортировать.
\param[in] size - Размер передаваемого массива.
\snippet selection.cpp selection_sort_example
*/

template <typename T>
void selection_sort(T arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[min] > arr[j]) {
                min = j;
            }
        }
        std::swap(arr[min], arr[i]); //  В случае 1 2 3 |4| 5 меняем 4 саму с собой
    }
}

#endif  // _SELECTION_HPP_
