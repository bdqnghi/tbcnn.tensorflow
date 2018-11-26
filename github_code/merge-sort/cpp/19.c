#include <iostream>
#include "SortTestHelper.h"
#include "InsertionSort.h"
#include "ShellSort.h"
#include "MergeSort.h"
#include "QuickSort.h"

using namespace std;

int main() {

    int n = 1000000;

    cout << "======================= Test Random Array =======================" << endl;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
    int *arr1 = SortTestHelper::copyIntArray(arr, n);
    int *arr2 = SortTestHelper::copyIntArray(arr, n);
    int *arr3 = SortTestHelper::copyIntArray(arr, n);
    int *arr4 = SortTestHelper::copyIntArray(arr, n);
    int *arr5 = SortTestHelper::copyIntArray(arr, n);
    int *arr6 = SortTestHelper::copyIntArray(arr, n);
    int *arr7 = SortTestHelper::copyIntArray(arr, n);
    int *arr8 = SortTestHelper::copyIntArray(arr, n);
    int *arr9 = SortTestHelper::copyIntArray(arr, n);
    int *arr10 = SortTestHelper::copyIntArray(arr, n);
    int *arr11 = SortTestHelper::copyIntArray(arr, n);
//    SortTestHelper::testSort("Insertion Sort", InsertionSort::insertionSort, arr1, n);
    SortTestHelper::testSort("Shell Sort", ShellSort::shellSort, arr2, n);
    SortTestHelper::testSort("Merge Sort", MergeSort::mergeSort, arr3, n);
    SortTestHelper::testSort("Merge Sort 2", MergeSort::mergeSort2, arr6, n);
    SortTestHelper::testSort("Merge Sort BU", MergeSort::mergeSortBU, arr4, n);
    SortTestHelper::testSort("Merge Sort BU 2", MergeSort::mergeSortBU2, arr5, n);
    SortTestHelper::testSort("Merge Sort BU 3", MergeSort::mergeSortBU3, arr7, n);
    SortTestHelper::testSort("Quick Sort", QuickSort::quickSort, arr8, n);
    SortTestHelper::testSort("Quick Sort 2", QuickSort::quickSort2, arr9, n);
    SortTestHelper::testSort("Quick Sort 2 Ways", QuickSort::quickSort2Ways, arr10, n);
    SortTestHelper::testSort("Quick Sort 3 Ways", QuickSort::quickSort3Ways, arr11, n);

    cout << "======================= Test Nearly Ordered Array =======================" << endl;
    int swapTimes = 100;
    arr = SortTestHelper::generateNearlyRandomArray(n, swapTimes);
    arr1 = SortTestHelper::copyIntArray(arr, n);
    arr2 = SortTestHelper::copyIntArray(arr, n);
    arr3 = SortTestHelper::copyIntArray(arr, n);
    arr4 = SortTestHelper::copyIntArray(arr, n);
    arr5 = SortTestHelper::copyIntArray(arr, n);
    arr6 = SortTestHelper::copyIntArray(arr, n);
    arr7 = SortTestHelper::copyIntArray(arr, n);
    arr8 = SortTestHelper::copyIntArray(arr, n);
    arr9 = SortTestHelper::copyIntArray(arr, n);
    arr10 = SortTestHelper::copyIntArray(arr, n);
    arr11= SortTestHelper::copyIntArray(arr, n);
    SortTestHelper::testSort("Insertion Sort", InsertionSort::insertionSort, arr1, n);
    SortTestHelper::testSort("Shell Sort", ShellSort::shellSort, arr2, n);
    SortTestHelper::testSort("Merge Sort", MergeSort::mergeSort, arr3, n);
    SortTestHelper::testSort("Merge Sort 2", MergeSort::mergeSort2, arr6, n);
    SortTestHelper::testSort("Merge Sort BU", MergeSort::mergeSortBU, arr4, n);
    SortTestHelper::testSort("Merge Sort BU 2", MergeSort::mergeSortBU2, arr5, n);
    SortTestHelper::testSort("Merge Sort BU 3", MergeSort::mergeSortBU3, arr7, n);
//    SortTestHelper::testSort("Quick Sort", QuickSort::quickSort, arr8, n);
    SortTestHelper::testSort("Quick Sort 2", QuickSort::quickSort2, arr9, n);
    SortTestHelper::testSort("Quick Sort 2 Ways", QuickSort::quickSort2Ways, arr10, n);
    SortTestHelper::testSort("Quick Sort 3 Ways", QuickSort::quickSort3Ways, arr11, n);

    cout << "======================= Test Small Range Array =======================" << endl;
    arr = SortTestHelper::generateRandomArray(n, 0, 10);
    arr1 = SortTestHelper::copyIntArray(arr, n);
    arr2 = SortTestHelper::copyIntArray(arr, n);
    arr3 = SortTestHelper::copyIntArray(arr, n);
    arr4 = SortTestHelper::copyIntArray(arr, n);
    arr5 = SortTestHelper::copyIntArray(arr, n);
    arr6 = SortTestHelper::copyIntArray(arr, n);
    arr7 = SortTestHelper::copyIntArray(arr, n);
    arr8 = SortTestHelper::copyIntArray(arr, n);
    arr9 = SortTestHelper::copyIntArray(arr, n);
    arr10 = SortTestHelper::copyIntArray(arr, n);
    arr11 = SortTestHelper::copyIntArray(arr, n);
//    SortTestHelper::testSort("Insertion Sort", InsertionSort::insertionSort, arr1, n);
    SortTestHelper::testSort("Shell Sort", ShellSort::shellSort, arr2, n);
    SortTestHelper::testSort("Merge Sort", MergeSort::mergeSort, arr3, n);
    SortTestHelper::testSort("Merge Sort 2", MergeSort::mergeSort2, arr6, n);
    SortTestHelper::testSort("Merge Sort BU", MergeSort::mergeSortBU, arr4, n);
    SortTestHelper::testSort("Merge Sort BU 2", MergeSort::mergeSortBU2, arr5, n);
    SortTestHelper::testSort("Merge Sort BU 3", MergeSort::mergeSortBU3, arr7, n);
//    SortTestHelper::testSort("Quick Sort", QuickSort::quickSort, arr8, n);
//    SortTestHelper::testSort("Quick Sort 2", QuickSort::quickSort2, arr9, n);
    SortTestHelper::testSort("Quick Sort 2 ", QuickSort::quickSort2Ways, arr10, n);
    SortTestHelper::testSort("Quick Sort 3 Ways", QuickSort::quickSort3Ways, arr11, n);

    delete[] arr;
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;
    delete[] arr8;
    delete[] arr9;
    delete[] arr10;
    delete[] arr11;
    return 0;
}