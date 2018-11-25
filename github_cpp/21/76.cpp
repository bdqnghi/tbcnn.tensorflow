#include "array.h"
#include <iostream>

using namespace std;

static void SelectionSort(int a[], int len)
{
    for (int i = 0; i < len; i++) {
        int min_index = i;
        for (int j = i; j < len; j++) {
            if (a[j] < a[min_index])
                min_index = j;
        }
        if (min_index != i) {
            int temp = a[i];
            a[i] = a[min_index];
            a[min_index] = temp;
        }
    }
    return;
}

int main()
{
    InitArray(arr, COUNT_MAX);
    cout << "Array:" << endl;
    PrintArray(arr, COUNT_MAX);

    SelectionSort(arr, COUNT_MAX);

    cout << "Array Afer SelectionSort:" << endl;
    PrintArray(arr, COUNT_MAX);

    return 0;
}
