/*
 * Insertion Sort
 *
 */

#include <iostream>

using namespace std;

void printArray(int arr[], int size);

int insertionSort(int arr[], int n) {
    for (int j = 1; j < n; ++j) {
        int key = arr[j];
        int i = j-1;
        while (i >= 0 && arr[i] > key) {

            arr[i+1] = arr[i];
            cout<<"In while loop with i = "<<i<<endl;
            printArray(arr, n);
            i--;
        }
        arr[i+1] = key;
        cout<<"In for loop with j = "<<j<<endl;
        printArray(arr, n);
    }
}

void printArray(int arr[], int size) {
    for (int i=0; i < size; i++)
        cout<<" "<<arr[i];
    cout<<endl;
}

int main(int argc, char const *argv[]) {
    int arr[] = {5,2,4,6,1,3};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout<<"Insertion Sort => "<<endl;
    printArray(arr, n);
    insertionSort(arr, n);
    return 0;
}
