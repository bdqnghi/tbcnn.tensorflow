#include <iostream>
#include <cstring>
using namespace std;


void maxHeapify(int* arr,int i,int n)
{
	int left=2*i+1;
	int right=2*i+2;
	int largest=i;

	if (left<n && arr[largest]<arr[left])
	{
		largest=left;
	}

	if (right<n && arr[largest]<arr[right])
	{
		largest=right;
	}

	if (largest!=i)
	{
		swap(arr[i],arr[largest]);
		maxHeapify(arr,largest,n);
	}
}


void heapSort(int* arr,int n)
{
	for (int i = n/2-1; i>=0; i--)
	{
		 maxHeapify(arr,i,n);
	}

	for (int i = n-1; i>=0 ; i--)
	{
		// cout<<"i "<<i<<endl;
		//swapping with 0 as 0th element contains the max val
		// cout<<arr[0]<<" "<<arr[i]<<endl;
		swap(arr[0],arr[i]);
		// cout<<arr[0]<<" "<<arr[i]<<endl;
		//Call heapify on the reduced length
		maxHeapify(arr,0,i);
	}
}

void printArray(int arr[], int n)
{
    for (int i=0; i<n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

int main()
{

	int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr)/sizeof(arr[0]);
 
    heapSort(arr, n);
 
    cout << "Sorted array is \n";
    printArray(arr, n);
	return 0;
}

