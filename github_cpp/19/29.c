#include <iostream>

template <typename T>
inline void         
swap(T& a, T& b)
{
    if (a != b) {  
        T tmp = a;
        a = b;
        b = tmp;
    }
}

template <typename T>
void
qsort_r(T arr[], int begin, int end, bool is_ascending=true)
{
    if (arr == NULL || begin >= end - 1) {   
        return;
    }
    
    swap(arr[(begin + end - 1) / 2], arr[end - 1]);

    int pivot = end - 1;      
    int last_left = begin - 1;   

    for (int i = begin; i < end - 1; ++i) {
        if ((is_ascending && arr[i] < arr[pivot]) ||
            (!is_ascending && arr[i] > arr[pivot])) {
            swap(arr[i], arr[++last_left]);
        }
    }
    swap(arr[pivot], arr[++last_left]);

    qsort_r(arr, begin, last_left, is_ascending);
    qsort_r(arr, last_left + 1, end, is_ascending);
}
