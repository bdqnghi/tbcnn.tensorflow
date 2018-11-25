

#include "sort.h"

void swap(std::vector<int> &array, int first, int second)
{
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}

int bubble(std::vector<int> &list, int size_unsorted)
{
    int last_element_swapped = 1;
    for (int i = 1; i < size_unsorted; ++i) {
        if (list[i - 1] > list[i]) {
            swap(list, i - 1, i);
            last_element_swapped = i;
        }
    }
    return last_element_swapped;
}

std::vector<int> sort(std::vector<int> list)
{
    int len = list.size();
    while (len > 1) {
        len = bubble(list, len);
    }
    return list;
}


