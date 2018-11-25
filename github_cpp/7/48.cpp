#include <iostream>

void mergeSort(int [], int, int);
void quickSort(int [], int, int);

int main() {
  int arr[] = {5, 1, 6, 2, 7, 1, 8, 2, 9, 2};

  mergeSort(arr, 0, 9);
  for (int i:arr) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  int arr2[] = {5, 1, 6, 2, 7, 1, 8, 2, 9, 2};

  quickSort(arr2, 0, 9);
  for (int i:arr2) {
    std::cout << i << " ";
  }
  return 0;
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}



void merge(int arr[], int start, int middle, int end) {
  int index1, index2, indexMerge;
  int size1 = middle - start + 1;
  int size2 = end - middle;

  int lArray[size1], rArray[size2];

  for (index1 = 0; index1 < size1; index1++)
    lArray[index1] = arr[start + index1];
  for (index2 = 0; index2 < size2; index2++)
    rArray[index2] = arr[(middle + 1) + index2];

  index1 = 0;
  index2 = 0;
  indexMerge = start;

  while (index1 < size1 && index2 < size2) {
    if (lArray[index1] <= rArray[index2]) {
      arr[indexMerge] = lArray[index1];
      index1++;
    } else {
      arr[indexMerge] = rArray[index2];
      index2++;
    }
    indexMerge++;
  }

  while (index1 < size1) {
    arr[indexMerge] = lArray[index1];
    index1++;
    indexMerge++;
  }

  while (index2 < size2) {
    arr[indexMerge] = rArray[index2];
    index2++;
    indexMerge++;
  }
}



void mergeSort(int arr[], int start, int end) {
  if (start < end) {
    int middle = start + (end - start) / 2;

    mergeSort(arr, start, middle);
    mergeSort(arr, middle + 1, end);

    merge(arr, start, middle, end);
  }
}




int partition(int arr[], int start, int end) {
  int pivot = arr[start + (end - start) / 2];
  int leftI = start - 1;
  int rightI = end + 1;
  while (leftI <= rightI) {
    while (arr[++leftI] < pivot);
    while (arr[--rightI] > pivot);
    if (leftI >= rightI)break;
    swap(&arr[leftI], &arr[rightI]);
  }
  return rightI;
}



void quickSort(int arr[], int start, int end) {
  if (end <= start) return;

  int part = partition(arr, start, end);
  quickSort(arr, start, part);
  quickSort(arr, part + 1, end);
}