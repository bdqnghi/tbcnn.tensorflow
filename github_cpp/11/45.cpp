

#include <algorithm>
#include <iostream>

using namespace std;

const int capacity = (int) 1e2;


void maxHeapify(int a[], int n, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    if ((left < n) && (a[left] > a[largest])) {
        largest = left;
    }
    if ((right < n) && (a[right] > a[largest])) {
        largest = right;
    }
    if (largest != i) {
        swap(a[i], a[largest]);
        maxHeapify(a, n, largest);
    }
}


void buildMaxHeap(int a[], int n) {
    
    for (int i = (n - 1) / 2; i > -1; i--) {
        maxHeapify(a, n, i);
    }
}


void heapSort(int a[], int n) {
    
    if (n == 1) return;

    buildMaxHeap(a, n);
    swap(a[0], a[n - 1]);
    n--;
    heapSort(a, n);
}


int main() {
    int a[capacity];
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    heapSort(a, n);
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}
