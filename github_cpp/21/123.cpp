#include <iostream>
#include <algorithm>
#include "SortTestHelper.h"
#include "SelectionSort.h"
#include "InsertionSort.h"

using namespace std;



template<typename T>
void selectionSort(T arr[], int n){

    int left = 0, right = n - 1;
    while(left < right){
        int minIndex = left;
        int maxIndex = right;

        
        if(arr[minIndex] > arr[maxIndex])
            swap(arr[minIndex], arr[maxIndex]);

        for(int i = left + 1 ; i < right; i ++)
            if(arr[i] < arr[minIndex])
                minIndex = i;
            else if(arr[i] > arr[maxIndex])
                maxIndex = i;

        swap(arr[left], arr[minIndex]);
        swap(arr[right], arr[maxIndex]);

        left ++;
        right --;
    }

    return;
}

int main() {

    int n = 40000;
    
    
    cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;
    int *arr1 = SortTestHelper::generateRandomArray(n,0,n);
    int *arr2 = SortTestHelper::copyIntArray(arr1, n);
    int *arr3 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Insertion Sort", insertionSort,arr1,n);
    SortTestHelper::testSort("Selection Sort", selectionSort,arr2,n);
    SortTestHelper::testSort("Selection Sort 2", selectionSort,arr3,n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

    cout<<endl;


    
    cout<<"Test for more ordered random array, size = "<<n<<", random range [0, 3]"<<endl;
    arr1 = SortTestHelper::generateRandomArray(n,0,3);
    arr2 = SortTestHelper::copyIntArray(arr1, n);
    arr3 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Insertion Sort", insertionSort,arr1,n);
    SortTestHelper::testSort("Selection Sort", selectionSort,arr2,n);
    SortTestHelper::testSort("Selection Sort 2", selectionSort,arr3,n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

    cout<<endl;


    
    int swapTimes = 100;
    cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;
    arr1 = SortTestHelper::generateNearlyOrderedArray(n,swapTimes);
    arr2 = SortTestHelper::copyIntArray(arr1, n);
    arr3 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Insertion Sort", insertionSort,arr1,n);
    SortTestHelper::testSort("Selection Sort", selectionSort,arr2,n);
    SortTestHelper::testSort("Selection Sort 2", selectionSort,arr3,n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

    return 0;
}