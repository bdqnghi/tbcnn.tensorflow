
#include <iostream>
using namespace std;
int count=0;


void heapify(int arr[], int n, int i)
{
    int largest = i;  
    int l = 2*i + 1;  
    int r = 2*i + 2;  
 
    
    if (l < n && arr[l] > arr[largest])
        largest = l;
        count++;
    
    if (r < n && arr[r] > arr[largest])
        largest = r;
        count++;
    
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
 
        
        heapify(arr, n, largest);
    }
}
 

void heapSort(int arr[], int n)
{
    
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    
    for (int i=n-1; i>=0; i--)
    {
        
        swap(arr[0], arr[i]);
 
        
        heapify(arr, i, 0);
    }
}
 

int main()
{
    int arr[] = {2,2,3,8,10,7};
    int n = sizeof(arr)/sizeof(arr[0]);
    
  	cout << "Initially array is \n";
    for (int i=0; i<n; ++i)
        cout << arr[i] << " ";
        
    heapSort(arr, n);
 
    cout << "\nSorted array is \n";
    for (int i=0; i<n; ++i)
        cout << arr[i] << " ";
        
    cout << "\nno of comparisons:"<<count;
}
