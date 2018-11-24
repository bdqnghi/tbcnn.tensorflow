/*
 * Bubble Sort
 *
 */

#include <iostream>

using namespace std;

void swap(int *xp, int *yp);
void printArray(int arr[], int size);

int bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; ++i)
        for (int j = 0; j < n-i-1; ++j)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
    printArray(arr, n);
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
    cout<<"Bubble Sort => ";
    bubbleSort(arr, n);
    return 0;
}
