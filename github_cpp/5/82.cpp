#include <stdio.h>
#include "insertionsort.hpp"

void printArray(int arr[], size_t len) {
    printf("Array:");
    for (int i = 0; i < len; i++) {
        printf("%d", arr[i]);
    }
    printf("\n");
}


int* insertion_sort (int arr[], size_t len) {
    int outer = 0;
    int inner = 0;
    for (int i = 1; i < len; i++, outer++) {
        for (int j = i; j > 0 && arr[j] < arr[j-1]; j--) {
            int tmp = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = tmp;
            inner++;
        }
    }
    printf("Outer = %d\n", outer);
    printf("Inner = %d\n", inner);
    return arr;
}

