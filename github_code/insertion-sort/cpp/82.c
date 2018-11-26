#include <stdio.h>
#include "insertionsort.hpp"

void printArray(int arr[], size_t len) {
    printf("Array:");
    for (int i = 0; i < len; i++) {
        printf("%d", arr[i]);
    }
    printf("\n");
}

/*
 * Say we have an array like this:
 *     i = 1
 * {2, 4, 1, 5, 3}
 *        j = 1
 *    {2, 4, 1, 5, 3} compare 4 < 2, j = 0;
 *
 *        i = 2 
 * {2, 4, 1, 5, 3}
 *           j = 2
 *    {2, 4, 1, 5, 3} compare 1 < 4, 
 *    {2, 1, 4, 5, 3} swap, j = 1
 *        j = 1
 *    {2, 1, 4, 5, 3} compare 1 < 2
 *    {1, 2, 4, 5, 3} swap, j = 0;
 *
 *           i = 3
 * {1, 2, 4, 5, 3} 
 *              j = 3
 *    {1, 2, 4, 5, 3} compare 5 < 4 
 *           j = 2
 *    {1, 2, 4, 5, 3} compare 4 < 2 
 *        j = 1
 *    {1, 2, 4, 5, 3} compare 2 < 1 
 *              i = 4
 * {1, 2, 4, 5, 3} 
 *                 j = 4
 *    {1, 2, 4, 5, 3}  compare 3 < 5
 *    {1, 2, 4, 3, 5}  swap, j = 3
 *              j = 3
 *    {1, 2, 4, 3, 5}  compare 3 < 4
 *    {1, 2, 3, 4, 5}  swap, j = 2
 *           j = 2
 *    {1, 2, 3, 4, 5}  compare 3 < 2
 *        j = 1
 *    {1, 2, 3, 4, 5}  compare 2 < 1
 */
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

