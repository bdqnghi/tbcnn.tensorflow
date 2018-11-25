

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
