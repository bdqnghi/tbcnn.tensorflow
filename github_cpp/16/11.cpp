

#include <iostream>

using namespace std;

void printArray(int arr[], int size);

int shellSort(int arr[], int n) {
    
    for (int gap = n/2; gap > 0; gap /= 2) {
        
        
        
        
        for (int i = gap; i < n; i += 1) {
            
            
            int temp = arr[i];

            
            
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            
            arr[j] = temp;
        }
    }
    printArray(arr, n);
}

void printArray(int arr[], int size) {
    for (int i=0; i < size; i++)
        cout<<" "<<arr[i];
    cout<<endl;
}

int main(int argc, char const *argv[]) {
    int arr[] = {3,1,5,2,75,7,4,12,35,54,1,256,24,5736453,1,7};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout<<"Shell Sort => ";
    shellSort(arr, n);
    return 0;
}
