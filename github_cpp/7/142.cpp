



#ifndef CALGS_SORTADVANCE_H
#define CALGS_SORTADVANCE_H

#include <iostream>
#include <algorithm>
#include <ctime>
#include "../SortTestHelper.h"
#include "MergeSort.h"
#include "MergeSortO.h"
#include "MergeSortBU.h"
#include "MergeSortBUO.h"
#include "QuickSort.h"
#include "QuickSort2Ways.h"
#include "QuickSort3Ways.h"

using namespace std;

namespace SortAdvanceMain {

    
    
    int testMain() {

        int n = 1000000;

        
        cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;
        int* arr1 = SortTestHelper::generateRandomArray(n,0,n);
        int* arr2 = SortTestHelper::copyIntArray(arr1,n);
        int* arr3 = SortTestHelper::copyIntArray(arr1,n);
        int* arr4 = SortTestHelper::copyIntArray(arr1,n);
        int* arr5 = SortTestHelper::copyIntArray(arr1,n);
        int* arr6 = SortTestHelper::copyIntArray(arr1,n);
        int* arr7 = SortTestHelper::copyIntArray(arr1,n);

        SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
        SortTestHelper::testSort("Merge Sort BU", mergeSortBU, arr2, n);
        SortTestHelper::testSort("Merge Sort Optimized", mergeSortO, arr3, n);
        SortTestHelper::testSort("Merge Sort BU Optimized", mergeSortBUO, arr4, n);
        SortTestHelper::testSort("Quick Sort", quickSort, arr5, n);
        SortTestHelper::testSort("Quick Sort 2 Ways", quickSort2Ways, arr6, n);
        SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways, arr7, n);

        delete[] arr1;
        delete[] arr2;
        delete[] arr3;
        delete[] arr4;
        delete[] arr5;
        delete[] arr6;
        delete[] arr7;

        cout<<endl;


        
        int swapTimes = 100;
        cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;
        arr1 = SortTestHelper::generateNearlyOrderedArray(n,swapTimes);
        arr2 = SortTestHelper::copyIntArray(arr1, n);
        arr3 = SortTestHelper::copyIntArray(arr1, n);
        arr4 = SortTestHelper::copyIntArray(arr1,n);
        arr5 = SortTestHelper::copyIntArray(arr1,n);
        arr6 = SortTestHelper::copyIntArray(arr1,n);
        arr7 = SortTestHelper::copyIntArray(arr1,n);

        SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
        SortTestHelper::testSort("Merge Sort BU", mergeSortBU, arr2, n);
        SortTestHelper::testSort("Merge Sort Optimized", mergeSortO, arr3, n);
        SortTestHelper::testSort("Merge Sort BU Optimized", mergeSortBUO, arr4, n);
        SortTestHelper::testSort("Quick Sort", quickSort, arr5, n);
        SortTestHelper::testSort("Quick Sort 2 Ways", quickSort2Ways, arr6, n);
        SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways, arr7, n);

        delete[] arr1;
        delete[] arr2;
        delete[] arr3;
        delete[] arr4;
        delete[] arr5;
        delete[] arr6;
        delete[] arr7;

        cout<<endl;


        
        cout<<"Test for random array, size = "<<n<<", random range [0,10]"<<endl;
        arr1 = SortTestHelper::generateRandomArray(n,0,10);
        arr2 = SortTestHelper::copyIntArray(arr1, n);
        arr3 = SortTestHelper::copyIntArray(arr1, n);
        arr4 = SortTestHelper::copyIntArray(arr1,n);
        arr5 = SortTestHelper::copyIntArray(arr1,n);
        arr6 = SortTestHelper::copyIntArray(arr1,n);
        arr7 = SortTestHelper::copyIntArray(arr1,n);

        SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
        SortTestHelper::testSort("Merge Sort BU", mergeSortBU, arr2, n);
        SortTestHelper::testSort("Merge Sort Optimized", mergeSortO, arr3, n);
        SortTestHelper::testSort("Merge Sort BU Optimized", mergeSortBUO, arr4, n);
        
        
        SortTestHelper::testSort("Quick Sort 2 Ways", quickSort2Ways, arr6, n);
        SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways, arr7, n);

        delete[] arr1;
        delete[] arr2;
        delete[] arr3;
        delete[] arr4;
        delete[] arr5;
        delete[] arr6;
        delete[] arr7;

        return 0;
    }
}

#endif 
