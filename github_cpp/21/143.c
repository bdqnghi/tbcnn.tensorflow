

#include <stdio.h>

void printArray(int arr[], int n) {
  for(int i = 0; i < n; ++i)
    printf("%d ", arr[i]);
  printf("\n");
}

void selectionSort(int arr[], int n) {
  for(int i = 0; i < n - 1; ++i)  {
    int min = i;
    for(int j = i + 1; j < n; ++j)  {
      if(arr[j] < arr[min])
        min = j;
    }
    if(min != i)  {
      int temp = arr[min];
      arr[min] = arr[i];
      arr[i] = temp;
    }
  }
}

int main()  {
  int arr[] = {64, 34, 25, 12, 22, 11, 90};
  printf("Array is initially:\n");
  printArray(arr, 7);
  printf("After selection sort, array is:\n");
  selectionSort(arr, 7);
  printArray(arr, 7);
  return 0;
}
