/*
 * Selection Sort
 *
 */

#include <iostream>

using namespace std;

void printArray(int arr[], int size);

void swap(int *xp, int *yp);

int SelectionSort(int arr[], int n) {
    int m;
    for (int i = 0; i < n-1; ++i){
        m = i;
        for (int j= i+1; j < n; ++j)
            if (arr[j] < arr[m])
                m = j;
        swap(&arr[m], &arr[i]);
    }
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
    cout<<"Selection Sort => ";
    SelectionSort(arr, n);
    return 0;
}
