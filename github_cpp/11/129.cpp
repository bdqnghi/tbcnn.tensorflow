

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




void MaxHeapify(int A[], int n, int i) {
    int largest = i; 
    int l = 2*i + 1; 
    int r = 2*i + 2; 

    
    if (l < n && A[l] > A[largest])
        largest = l;

    
    if (r < n && A[r] > A[largest])
        largest = r;

    
    if (largest != i) {
        swap(A[i], A[largest]);

        
        MaxHeapify(A, n, largest);
    }
}

void HeapSort(int A[], int n) {
    
    
    for (int i = n / 2 - 1; i >= 0; i--)
        MaxHeapify(A, n, i);

    
    for (int i=n-1; i>=0; i--) {
        
        swap(A[0], A[i]);

        
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
