//
// Created by guoliang on 2018/9/29.
//
#include <iostream>
#include "SortTestHelper.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "BubbleSort.h"
#include "ShellSort.h"

using namespace std;

int main() {

    cout << "================= Test Totaly Random Arry =================" << endl;
    int n = 10000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
    int *arr2 = SortTestHelper::copyIntArray(arr, n);
    int *arr3 = SortTestHelper::copyIntArray(arr, n);
    int *arr4 = SortTestHelper::copyIntArray(arr, n);
    int *arr5 = SortTestHelper::copyIntArray(arr, n);
    int *arr6 = SortTestHelper::copyIntArray(arr, n);
    int *arr7 = SortTestHelper::copyIntArray(arr, n);
//    SelectionSort::selectionSort(arr, n);
//    SortTestHelper::printArr(arr, n);
    SortTestHelper::testSort("Selection Sort", SelectionSort::selectionSort, arr, n);
    SortTestHelper::testSort("Insertion Sort", InsertionSort::insertionSort, arr2, n);
    SortTestHelper::testSort("Bubble Sort 1", BubbleSort::bubbleSort1, arr3, n);
    SortTestHelper::testSort("Bubble Sort 2", BubbleSort::bubbleSort2, arr4, n);
    SortTestHelper::testSort("Bubble Sort 3", BubbleSort::bubbleSort3, arr5, n);
    SortTestHelper::testSort("Shell Sort 1", ShellSort::shellSort1, arr6, n);
    SortTestHelper::testSort("Shell Sort 2", ShellSort::shellSort2, arr7, n);


    cout << "================= Test Nearly Ordered Arry =================" << endl;
    arr = SortTestHelper::generateNearlyOrderedArray(n, 100);
    arr2 = SortTestHelper::copyIntArray(arr, n);
    arr3 = SortTestHelper::copyIntArray(arr, n);
    arr4 = SortTestHelper::copyIntArray(arr, n);
    arr5 = SortTestHelper::copyIntArray(arr, n);
    arr6 = SortTestHelper::copyIntArray(arr, n);
    arr7 = SortTestHelper::copyIntArray(arr, n);
    SortTestHelper::testSort("Selection Sort", SelectionSort::selectionSort, arr, n);
    SortTestHelper::testSort("Insertion Sort", InsertionSort::insertionSort, arr2, n);
    SortTestHelper::testSort("Bubble Sort 1", BubbleSort::bubbleSort1, arr3, n);
    SortTestHelper::testSort("Bubble Sort 2", BubbleSort::bubbleSort2, arr4, n);
    SortTestHelper::testSort("Bubble Sort 3", BubbleSort::bubbleSort3, arr5, n);
    SortTestHelper::testSort("Shell Sort 1", ShellSort::shellSort1, arr6, n);
    SortTestHelper::testSort("Shell Sort 2", ShellSort::shellSort2, arr7, n);
    delete[] arr;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;
    return 0;
}

