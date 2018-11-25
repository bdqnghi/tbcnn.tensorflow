#include <algorithm>
#include <iostream>
using namespace std;
void displayArray(int[], int);
void inputArray(int[], int);
void bubbleSort(int[], int);
void selectionSort(int[], int);
void insertIntoSortedArray(int[], int, int);
void QuickSort(int input[], int l, int r);
int binarySearch(int a[], int begin, int end, int search);
void quickSort2(int a[],int start,int end);
int partitionArray(int a[], int start, int end);
static int numOfPasses = 0;
int main(){
    int array[10];
    cout << "Enter data into array" << endl;
    inputArray(array, 10);
    displayArray(array, 10);
    cout << "Sorting..." <<endl;
    quickSort2(array, 0, 10);
    displayArray(array, 10);


}
void selectionSort(int a[], int size){
    for (int startIndex = 0; startIndex < size; ++startIndex)
    {
        
        int smallestIndex = startIndex;
        
        
        for (int currentIndex = startIndex + 1; currentIndex < size; ++currentIndex)
        {
            
            if (a[currentIndex] < a[smallestIndex])
                
                smallestIndex = currentIndex;
        }
        
        int temp;
        temp = a[startIndex];
        a[startIndex] = a[smallestIndex];
        a[smallestIndex] = temp; 
    }

}
void displayArray(int a[], int size){
    for (int i = 0; i < size; i++){
        cout << a[i] <<  " ";
    }
    cout << endl;
}
void inputArray(int a[], int size){
    for (int i = 0; i < size; i++){
        cin >> a[i];
    }
}
void bubbleSort(int a[], int size){
    for (int n=0; n <size; n++){
        for (int i=0; i <size; i++){
            if(a[i]> a[i+1]){
                int temp=a[i];
                a[i]=a[i+1];
                a[i+1]=temp;
            }
        }
    }
}
void insertIntoSortedArray(int a[], int size, int num){
    int location = size;
    for(int i=0; i < size; i++){
        if (a[i] < num && a[i+1] >= num ){
            location = i+1;
        }
    }
    int temp;
    int count;
    for (int n = size; n > location; n--){
        
            a[n] = a[n-1];
        
    }
    a[location]=num;
}
void QuickSort(int input[], int l, int r)
{
    unsigned int i = l + 1, j;
    unsigned int pivot = input[l];
    if (l + 1 < r) {
        for (j = l + 1; j < r; j++) {
            if (input[j] < pivot) {
                std::swap(input[j], input[i]);
                i++;
            }
        }
        swap(input[i - 1], input[l]);

        QuickSort(input, l, i);
        QuickSort(input, i, r);
    }
}
int binarySearch(int a[], int begin, int end, int search){
    int midpoint = (begin+end)/2;
    if (a[midpoint] > search){
        return binarySearch(a, begin, midpoint, search);
    }
    if (a[midpoint] < search){
        return binarySearch(a, midpoint, end, search);
    }
    if (a[midpoint] == search){
        return midpoint;
    }
}
void quickSort2(int a[],int start,int end){
    if (start < end){
        int partitionIndex = partitionArray(a, start, end);
        quickSort2(a, start, partitionIndex-1);
        quickSort2(a, partitionIndex+1, end);
        
    }
    else{
    }
}
int partitionArray(int a[], int start, int end){

    numOfPasses ++;
    int pivot = a[end];
    int pIndex = start;
    int temp;
    for (int i = start; i < end; i++){
        if (a[i] <= pivot){
            temp = a[pIndex];
            a[pIndex] = a[i];
            a[i] = temp;
            pIndex++;
        }
    }
    temp = a[pIndex];
    a[pIndex] = a[end];
    a[end] = temp; 
    displayArray(a, 10);
    return pIndex;
}