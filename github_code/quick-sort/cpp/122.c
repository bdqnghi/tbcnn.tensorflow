#include <iostream>
#include <algorithm>
#include "MergeSort.h"
#include "QuickSort.h"
#include "QuickSort2.h"
#include "SortTestHelper.h"

using namespace std;

//对arr[l,r]进行快速排序
//将arr[l,r]分为<v,==v,>v
//之后对<v,>v两部分继续递归进行三路快排
template<typename T>
void __quickSort3Ways(T arr[], int l, int r) {
//    if (l >= r) {
//        return;
//    }
    if (r - l <= 15) {
        InsertionSort(arr, l, r);
        return;
    }

    //对arr[l,r]进行partition操作
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    T v = arr[l];
    //arr[l+1,lt]<v,arr[gt,r]>v,arr[lt+1,i]==v
    int lt = l;
    int gt = r + 1;
    int i = l + 1;
    while (i < gt) {
        if (arr[i] < v) {
            swap(arr[i], arr[lt + 1]);
            lt++;
            i++;
        } else if (arr[i] > v) {
            swap(arr[i], arr[gt - 1]);
            gt--;
        } else {
            i++;
        }
    }
    swap(arr[l], arr[lt]);

    __quickSort3Ways(arr, l, lt - 1);
    __quickSort3Ways(arr, gt, r);
}

template<typename T>
void quickSort3Ways(T arr[], int n) {
    srand(time(NULL));
    __quickSort3Ways(arr, 0, n - 1);
}

int main() {
    int n = 1000000;
    int *arr1 = SortTestHelper::generateRandomArray(n, 0, n);
    int *arr2 = SortTestHelper::copyIntArray(arr1, n);
    int *arr3 = SortTestHelper::copyIntArray(arr1, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort 2", quickSort2, arr2, n);
    SortTestHelper::testSort("Quick Sort 3", quickSort3Ways, arr3, n);
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    cout << endl;

    int swapTimes = 100;
    arr1 = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
    arr2 = SortTestHelper::copyIntArray(arr1, n);
    arr3 = SortTestHelper::copyIntArray(arr1, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort 2", quickSort2, arr2, n);
    SortTestHelper::testSort("Quick Sort 3", quickSort3Ways, arr3, n);
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    cout << endl;

    arr1 = SortTestHelper::generateRandomArray(n, 0, 10);
    arr2 = SortTestHelper::copyIntArray(arr1, n);
    arr3 = SortTestHelper::copyIntArray(arr1, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort 2", quickSort2, arr2, n);
    SortTestHelper::testSort("Quick Sort 3", quickSort3Ways, arr3, n);
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    return 0;
}