

#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    
    for (int j = low; j <= high-1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[high]);
    return (i+1);
}

void Quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        Quicksort(arr, low, pi-1);
        Quicksort(arr, pi+1, high);
    }
}

int main() {
    int Array[] = {0, 1, 9, 2, 3, 7, 5, 4, 15, 16, 22, 29, 24, 10, 33};
    int arrayLength = sizeof(Array)/sizeof(int);
    int sortedArray[arrayLength-1];
    int low_int = 0;
    int hi_int = Array[arrayLength-1];
    printf("Array created. The array is %d items long.", arrayLength);
    printf("\nWe now need to sort the array.\n");
    
    Quicksort(Array, low_int, arrayLength);
    for (int i=1; i <= arrayLength; i++) {
        sortedArray[i-1] = Array[i];
    }
    printf("Sorted...\n");
    printf("Now, we need to perform a binary search for an integer value. We'll do 15.\n");
    int s_INT = 15; 
    
    
}
