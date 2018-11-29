#include<iostream>
using namespace std;

class MergeSort{
    int left[];
    int right[];
    int n1;
    int n2;
public:
    MergeSort(int beg,int end,int mid);
    void merge(int arr[],int beg,int end,int mid);    
    void divide(int arr[],int beg,int end,int mid);
    void mergeSort(int arr[],int beg,int end);
    void bubbleSort(int arr[]);
    void printArray(int arr[],int size);
};
MergeSort::MergeSort(int beg,int end,int mid){
    n1 = mid-beg;
    n2 = end-mid;
    left[n1]={0};
    right[n2]={0};
}
void MergeSort::divide(int arr[],int beg,int end,int mid){
    for(int i=0;i<n1;i++){
        left[i] = arr[beg+i];
    }
    for(int j=0;j<n2;j++){
        right[j] = arr[mid+1+j];
    }
    mergeSort(left,beg,n1);
    bubbleSort(right);
}
void MergeSort::merge(int arr[],int beg,int end,int mid){
    int i,j,k;
    i=0;
    j=0;
    k=beg;
    while(i<n1 && j<n2){
        if(left[i] <= right[j]){
            arr[k] = left[i];
            i++;
        }
        else{
            arr[k] = right[j];
            j++;
        }
        k++;
    }
}
void MergeSort::mergeSort(int arr[],int beg,int end){
    int mid = beg + (end-beg)/2;
    mergeSort(arr,beg,mid);
    mergeSort(arr,mid+1,end);
    merge(arr,beg,end,mid);

}
int main(void){
    int arr[] = {12,13,11,5,6,7};
    int arr_size = sizeof(arr)/sizeof(arr[0]);
    int beg = 0;
    int end = arr_size-1;
    int mid = beg+(end-beg)/2;
    MergeSort ms(beg,end,mid);
    ms.divide(arr,beg,end,mid);
    return 0;
}