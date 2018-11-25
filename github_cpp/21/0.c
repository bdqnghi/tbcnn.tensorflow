







#include "selectionSort.hpp"
void selectionSort(int arr[], int length){
    for(int i=0; i!=length-1; i++){
        int pos=smallestValue(arr, length, i);
        swap(arr[pos], arr[i]);
    }
    
}

void swap(int& num1, int& num2){
    int temp=num1;
    num1=num2;
    num2=temp;
}

int smallestValue(int arr[], int length, int start){
    int temp= arr[start];
    int pos=start;
    for(int i=start; i!=length; i++){
        if(arr[i]<temp){
            temp=arr[i];
            pos=i;
        }
    }
    return pos;
}
