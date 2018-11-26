#include<iostream>

using namespace std;

void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

void heapify(int arr[],int n,int i)
{
    int largest=i;
    int l=2*i+1;
    int r=2*i+2;

    if(l<n && arr[l]>arr[largest])
        largest=l;
    if(r<n && arr[r]>arr[largest])
        largest=r;

    if(largest!=i)
    {
        swap(&arr[largest],&arr[i]);
        heapify(arr,n,largest);
    }
}

void heapsort(int arr[],int n)
{
    for(int i=(n/2)-1 ; i>=0 ; i--)
        heapify(arr,n,i);
    for(int i=n-1 ; i>=0 ; i--)
    {
        swap(&arr[0],&arr[i]);
        heapify(arr,i,0);
    }
}

void display(int arr[],int n)
{
    for(int i=0 ; i<n ; i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

int main()
{
    int arr[30],n;
    cout<<"Enter no. of elements: ";
    cin>>n;
    cout<<"Enter elements: ";
    for(int i=0 ; i<n ; i++)
        cin>>arr[i];
    heapsort(arr,n);
    cout<<"After applying HeapSort: ";
    display(arr,n);
    return 0;
}
