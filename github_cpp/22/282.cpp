/*
carry out heap sort method
> max-heapify
> build-max-heap
> heap-sort
*/

#include <iostream>
#include <cstdlib>
using namespace std;

int comparisons = 0;

// max heapify procedure
void max_heapify(int arr[], int index, int size) {
    int largest = index;
    int left  = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size & arr[left] > arr[largest]) {
        largest = left;
        comparisons++;
    } else {
        largest = index;
        if (left < size)
            comparisons++;
    }

    if (right < size & arr[right] > arr[largest]) {
        largest = right;
        comparisons++;
    } else {
        largest = index;
        if (right < size)
            comparisons++;
    }

    if (largest != index) {
        // swap arr[largest] with arr[index]
        swap(arr[largest], arr[index]);

        // call heapify recursively at largest
        max_heapify(arr, largest, size);
    }
}

// procedure for build max heap
void build_max_heap(int arr[], int size) {
    for (int i = size/2 - 1; i >= 0; --i) {
        max_heapify(arr, i, size);
    } 
}

// main procedure for heap sort
void heap_sort(int arr[], int size) {
    // build the max heap first
    build_max_heap(arr, size);

    // as soon as a max heap is formed continue with these procedures:
    for (int i = size-1; i >= 0; --i) {
        // exchange root element with last element 
        swap(arr[0], arr[i]);

        // call max_heapify at 0 with size = i
        max_heapify(arr, 0, i); 
    }
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
}

int main () {
    system("clear");

    int arr[] = {12, 3, 45, 6, 78, 9, 1011, 12, 1314, 15};
    int size = sizeof(arr)/sizeof(arr[0]);

    cout << endl << "Unsorted array: ";
    print_array(arr, size);

    heap_sort(arr, size);

    cout << endl << "Sorted array: ";
    print_array(arr, size);
    cout << endl << "Number of comparisons for this procedure: " << comparisons << endl;

    return 0;
}
