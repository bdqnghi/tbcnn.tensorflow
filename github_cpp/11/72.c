#include <iostream>
using namespace std;

void heapify(int a[], int n, int i) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    
    int largest = i;
    if (l < n && a[l] > a[largest])
        largest = l;
        
    if (r < n && a[r] > a[largest])
        largest = r;
    
    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n) {
    for (int i = n/2 - 1; i >= 0; i--) 
     heapify(a, n, i);
     
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}


int main() {
    
    int a[] = {10, 6, 7, 12, 2, 45, 8, 90, 55, 120, 32, 1, 1000, -1, 345, -78};
    heapSort(a, 17);

    for (int i = 0; i < 17; i++) {
        cout << a[i] << " ";
    }
    
    return 0;
}