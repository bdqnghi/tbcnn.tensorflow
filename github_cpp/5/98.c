

#include "sort.h"

void swap(std::vector<int> &array, int first, int second)
{
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}

void insert(std::vector<int> &array, int index)
{
    int elem = array[index];
    
    int i;
    for (i = index; i > 0 && array[i - 1] > elem; --i) {
        array[i] = array[i - 1];
    }
    array[i] = elem;
}

std::vector<int> sort(std::vector<int> list)
{
    int last = list.size() - 1;
    for (int i = 1; i <= last; ++i) {
        insert(list, i);
    }
    return list;
}


