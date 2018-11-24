/*
 * Heap Sort
 *
 */

#include <iostream>

using namespace std;

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void printArray(int A[], int size) {
    for (int i=0; i < size; i++)
        cout<<" "<<A[i];
    cout<<endl;
}

// To heapify a subtree rooted with node i which is
// an index in A[]. n is size of heap
// Works in a bottom up manner.
void MaxHeapify(int A[], int n, int i) {
    int largest = i; // Initialize largest as root
    int l = 2*i + 1; // left = 2*i + 1
    int r = 2*i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && A[l] > A[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && A[r] > A[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(A[i], A[largest]);

        // Recursively heapify the affected sub-tree
        MaxHeapify(A, n, largest);
    }
}

void HeapSort(int A[], int n) {
    // Build heap (rearrange array)
    // elements fron A[(n/2+1)...n] are all leaf nodes
    for (int i = n / 2 - 1; i >= 0; i--)
        MaxHeapify(A, n, i);

    // One by one extract an element from heap
    for (int i=n-1; i>=0; i--) {
        // Move current root to end
        swap(A[0], A[i]);

        // call max heapify on the reduced heap
        MaxHeapify(A, i, 0);
    }
}

int main() {
    int A[] = {3,1,5,2,75,7,4,12,35,54,1,256,24,5736453,1,7};
    int n1 = sizeof(A) / sizeof(A[0]);
    cout<<"Heap Sort => ";
    HeapSort(A, n1);
    printArray(A, n1);
    return 0;
}
