#include <iostream>

template <typename T>
void
bubble_sort(T list[], const int& size, bool is_ascending=true)
{
    if (list == NULL || size <= 1) {
        return;
    }
    int pass = 1;
    while (true) {
        bool swapped = false;    
        for (int i = 0; i < size - pass; ++i) {
            if ((is_ascending && list[i] > list[i + 1]) ||
                (!is_ascending && list[i] < list[i + 1])) {
                T tmp = list[i];
                list[i] = list[i + 1];
                list[i + 1] = tmp;
                swapped = true;
            }
        }
        ++pass;
        if (!swapped) {
            break;
        }
    }
}

            
