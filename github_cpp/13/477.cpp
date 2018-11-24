#include <iostream>

template <typename T>
void
merge(T list[], int begin, int mid, int end, bool is_ascending)
{
    T *tmp = new T[end - begin];
    int left = begin;
    int right = mid;
    int index = -1;
    
    while (left < mid && right < end) {
        if ((is_ascending && list[left] < list[right]) ||
            (!is_ascending && list[left] > list[right])) {
            tmp[++index] = list[left];
            ++left;
        } else {
            tmp[++index] = list[right];
            ++right;
        }
    }
    while (left < mid) {
        tmp[++index] = list[left];
        ++left;
    }
    while (right < end) {
        tmp[++index] = list[right];
        ++right;
    }
    for (int i = 0; i <= index; ++i) {
        list[begin + i] = tmp[i];
    }
    delete[] tmp;
}
                      
template <typename T>
void
merge_sort(T list[], int begin, int end, bool is_ascending=true)
{
    if (list == NULL || begin >= end - 1) {
        return;
    }
    int mid = (begin + end) / 2;

    merge_sort(list, begin, mid, is_ascending);
    merge_sort(list, mid, end, is_ascending);
    merge(list, begin, mid, end, is_ascending);
}
