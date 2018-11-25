

#include <iostream>
#include <vector>


void heapify(std::vector<int> &arr, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}


void heapify2(std::vector<int> &arr, int n, int i) {
    while (i < n) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int min = i;
        if (l < n && arr[l] < arr[min]) {
            min = l;
        }
        if (r < n && arr[r] < arr[min]) {
            min = r;
        }
        if (min != i) {
            std::swap(arr[min], arr[i]);
            i = min;
        }
        else {
            break;
        }
    }
}


void heapSort(std::vector<int> &arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify2(arr, n, i);
 
    for (int i=n-1; i>=0; i--) {
        std::swap(arr[0], arr[i]);
        heapify2(arr, i, 0);
    }
}

void printArray(std::vector<int> &arr) {
    int n = arr.size();
    for (int i=0; i<n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int a[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(a)/sizeof(a[0]);
    std::vector<int> arr(a,a+n);
    heapSort(arr);
    printArray(arr);

    return 0;
}
