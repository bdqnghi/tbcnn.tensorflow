#include "array.h"
#include <iostream>

using namespace std;

static void InsertionSort(int a[], int len)
{
    for (int i = 1; i < len; i++) {
        if (a[i - 1] > a[i]) {
            int j = i - 1;
            int temp = a[i];
            while (j >= 0 && a[j] > temp) {
                a[j + 1] = a[j];
                j--;
            }
            a[j + 1] = temp;
        }
    }
    return;
}

int main()
{
    InitArray(arr, COUNT_MAX);
    cout << "Array:" << endl;
    PrintArray(arr, COUNT_MAX);

    InsertionSort(arr, COUNT_MAX);

    cout << "Array Afer InsertionSort:" << endl;
    PrintArray(arr, COUNT_MAX);

    return 0;
}
