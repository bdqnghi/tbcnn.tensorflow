/*******************************************************************************

Merge sort
==========

Ref - http://quiz.geeksforgeeks.org/merge-sort/

--------------------------------------------------------------------------------

Problem
=======
Classic old merge sort.

--------------------------------------------------------------------------------

Time Complexity
===============
O(nlogn)

--------------------------------------------------------------------------------

Output
======
Array is initially:
64 34 25 12 22 11 90
After merge sort, array is:
11 12 22 25 34 64 90

*******************************************************************************/

#include <stdio.h>

void printArray(int arr[], int n) {
  for(int i = 0; i < n; ++i)
    printf("%d ", arr[i]);
  printf("\n");
}

void merge(int arr[], int l, int m, int r) {
  int n1 = m - l + 1;
  int n2 = r - m;

  int L[n1], R[n2];

  for (int i = 0; i < n1; i++) {
    L[i] = arr[l + i];
  }
  for (int i = 0; i < n2; i++) {
    R[i] = arr[m + i + 1];
  }

  int i = 0, j = 0, k = l;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i++];
    }
    else  {
      arr[k] = R[j++];
    }
    k++;
  }

  while (i < n1) {
    arr[k++] = L[i++];
  }
  while (j < n2) {
    arr[k++] = R[j++];
  }
}

void mergeSort(int arr[], int l, int r) {
  if (l < r) {
    int m = (l + r)/2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    merge(arr, l, m, r);
  }
}

int main()  {
  int arr[] = {64, 34, 25, 12, 22, 11, 90};
  printf("Array is initially:\n");
  printArray(arr, 7);
  printf("After merge sort, array is:\n");
  mergeSort(arr, 0, 6);
  printArray(arr, 7);
  return 0;
}
