










#include "sort.h"
void InsertionSort::sort(int A[], int size)				
{
    int j;
    int temp;
    for (int i = 0; i<size; i++) {
        j = i;
        num_cmps++;
        while (j>0 && A[j] < A[j-1]) {
            temp = A[j];
            num_cmps++;
            A[j] = A[j-1];
            A[j-1] = temp;
            j--;
        }
    }
}
