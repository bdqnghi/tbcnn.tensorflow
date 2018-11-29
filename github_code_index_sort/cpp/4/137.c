#include <iostream>

int getLeftIndex(int index) {
    return (index * 2 + 1);
}
int getRightIndex(int index) {
    return (index + 1) * 2;
}
int getParentIndex(int index) {
    return (index - 1) / 2;
}
void swap(int A[], int index1, int index2){
    int t = A[index1];
    A[index1] = A[index2];
    A[index2] = t;
}
void maxHeapify(int A[], int n, int index) {
    int left = getLeftIndex(index);
    int right = getRightIndex(index);
    int maxIndex = index;

    if(left < n && A[maxIndex] < A[left]) maxIndex = left;
    if(right < n && A[maxIndex] < A[right]) maxIndex = right;

    if(maxIndex != index) {
        int t = A[maxIndex];
        A[maxIndex] = A[index];
        A[index] = t;
        
        maxHeapify(A, n, maxIndex);
    }
}
/* 非递归实现
void maxHeapify(int A[], int n, int index) {
    
    while(true) {
        int left = getLeftIndex(index);
        int right = getRightIndex(index);
        int maxIndex = index;

        if(left < n && A[maxIndex] < A[left]) maxIndex = left;
        if(right < n && A[maxIndex] < A[right]) maxIndex = right;

        if(maxIndex == index) break;

        swap(A, maxIndex, index);

        index = maxIndex;
    }
}
*/

void buildMaxHeap(int A[], int n) {
    int index = getParentIndex(n-1);
    for(int i = index; i >= 0; i--) {
        maxHeapify(A, n, i); 
    }
}

void heapSort(int A[], int n) {
    buildMaxHeap(A, n);
    int size = n;
    for(int i = size - 1; i > 0; i--) {
        swap(A, 0, i);
        size --;
        maxHeapify(A, size, 0);
    }
}


void printArr(int A[], int n) {
    for(int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}
int main() {

    int A[] = {3, 2, 4, 14, 7, 6, 9};
    int n = sizeof(A) / sizeof(int);
    printArr(A, n);
    heapSort(A, n);
    printArr(A, n);
    
    return 0;
}

