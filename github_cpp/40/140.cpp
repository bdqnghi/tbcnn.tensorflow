/*******************************************************************************

Quick sort
==========

Ref - http://quiz.geeksforgeeks.org/quick-sort/

--------------------------------------------------------------------------------

Problem
=======
Classic old quick sort.

--------------------------------------------------------------------------------

Time Complexity
===============
O(nlogn)

--------------------------------------------------------------------------------

Output
======
Array is initially:
64 34 25 12 22 11 90
After quick sort, array is:
11 12 22 25 34 64 90

*******************************************************************************/

#include <stdio.h>

void printArray(int arr[], int n) {
  for(int i = 0; i < n; ++i)
    printf("%d ", arr[i]);
  printf("\n");
}

void swap(int *p, int *q) {
  int temp = *p;
  *p = *q;
  *q = temp;
}

int partition(int arr[], int l, int r)  {
  int pivot = arr[r];
  int i = l;
  for (int j = l; j < r; j++) {
    if (arr[j] <= pivot) {
      swap(&arr[i++], &arr[j]);
    }
  }
  swap(&arr[i], &arr[r]);
  return i;
}

void quickSort(int arr[], int l, int r) {
  if (l < r) {
    int p = partition(arr, l, r);

    quickSort(arr, l, p - 1);
    quickSort(arr, p + 1, r);
  }
}

int main()  {
  int arr[] = {64, 34, 25, 12, 22, 11, 90};
  printf("Array is initially:\n");
  printArray(arr, 7);
  printf("After quick sort, array is:\n");
  quickSort(arr, 0, 6);
  printArray(arr, 7);
  return 0;
}
