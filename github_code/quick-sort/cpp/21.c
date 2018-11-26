/*
 * Quick Sort
 *
 */

#include <iostream>

using namespace std;

void swap(int *xp, int *yp);
void printArray(int arr[], int size);

int partition (int arr[], int l, int h) {
    int pivot = arr[h];
    int i = l - 1;
    for (int j = l; j <= h-1; ++j) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[h]);
    return(i+1);
}

void QuickSort(int arr[], int l, int h) {
    if (l < h) {
        int p = partition(arr, l, h);
        QuickSort(arr, l, p - 1);
        QuickSort(arr, p + 1, h);
    }
}

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void printArray(int arr[], int size) {
    for (int i=0; i < size; i++)
        cout<<" "<<arr[i];
    cout<<endl;
}

int main(int argc, char const *argv[]) {
    int arr[] = {3,1,5,2,75,7,4,12,35,54,1,256,24,5736453,1,7};
    int n = sizeof(arr) / sizeof(arr[0]);
    QuickSort(arr, 0, n-1);
    cout<<"Quick Sort => ";
    printArray(arr, n);
    return 0;
}
