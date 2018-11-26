/*******************************************************************************

Bubble sort
===========

Ref - http://quiz.geeksforgeeks.org/bubble-sort/

--------------------------------------------------------------------------------

Problem
=======
Classic old bubble sort.

--------------------------------------------------------------------------------

Time Complexity
===============
O(n^2)

--------------------------------------------------------------------------------

Output
======
Array is initially:
64 34 25 12 22 11 90
After bubble sort, array is:
11 12 22 25 34 64 90

*******************************************************************************/

#include <stdio.h>

void printArray(int arr[], int n) {
  for(int i = 0; i < n; ++i)
    printf("%d ", arr[i]);
  printf("\n");
}

void bubbleSort(int arr[], int n) {
  for(int i = n-1; i >= 0; --i) {
    for(int j = 0; j < i; ++j)  {
      if(arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

int main()  {
  int arr[] = {64, 34, 25, 12, 22, 11, 90};
  printf("Array is initially:\n");
  printArray(arr, 7);
  printf("After bubble sort, array is:\n");
  bubbleSort(arr, 7);
  printArray(arr, 7);
  return 0;
}
