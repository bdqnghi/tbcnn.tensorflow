#include <iostream>

template <typename T>
void
shell_sort(T list[], const int& size, bool is_ascending=true)
{
    if (list == NULL || size <= 1) {
        return;
    }
    int gap = size >> 1;
    while (gap >= 1) {
        for (int i = gap; i < size; i += gap) {
            T tmp = list[i];
            int j;
            for (j = i - gap; j >= 0; j -= gap) {
                if ((is_ascending && tmp < list[j]) ||
                    (!is_ascending && tmp > list[j])) {
                    list[j + gap] = list[j];
                } else {
                    break;
                }
            }
            list[j + gap] = tmp;
        }
        gap >>= 1;
    }
}
