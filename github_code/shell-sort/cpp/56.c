#include "ShellSort.h"

#ifndef SHELL_SORT_CPP
#define SHELL_SORT_CPP

template <class T>
ShellSort<T>::ShellSort():
    SortAlgorithm<T>("Shell") {}

template <class T>
ShellSort<T>::~ShellSort() {}

template <class T>
void ShellSort<T>::sort(T* elements, int size) {
    for(int k = size / 2; k > 0; k /= 2) {
        for(int i = k; i < size; i++) {
            T number = elements[i];
            int j;

            for(j = i; j >= k; j -= k) {
                if(number < elements[j - k])
                    elements[j] = elements[j - k];
                else
                    break;
            }

            elements[j] = number;
        }
    }
}

#endif // SHELL_SORT_CPP
