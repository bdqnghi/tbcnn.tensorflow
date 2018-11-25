#include<iostream>
using namespace std;
void swap(int *a,int *p){
int temp;
temp= *a;
*a=*p;
*p=temp;
}
void selectionSort(int arr[], int n)
{
    int i, j, min1;

    for (i = 0; i < n-1; i++)
    {
        min1 = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min1])
            min1 = j;
        swap(&arr[min1], &arr[i]);
    }
}
 void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++){
        cout<<arr[i];
        cout<<"\n";
    }
}

    int main(){
        int n;
        int arr[50];

        cout<<"no.of elements u want to enter \n";
        cin>>n;
        cout<<"enter elements of array \n";
        for(int j=0;j<n;j++){
            cin>>arr[j];

        }
    selectionSort(arr,n);
    printArray(arr,n);
    return 0;
    }
