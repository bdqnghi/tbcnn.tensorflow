//selection sort
#include <iostream>

using namespace std;

void swap(int from ,int to , int arr[])
{
	arr[from] = arr[from] + arr[to];
	arr[to] =arr[from] -arr[to];
	arr[from] = arr[from] -arr[to];
}

void sort(int arr[] ,int size ,int k)
{
	for(int i=0; i<k ;i++)
	{
		int min = arr[i];
		int idx = i;
		for(int j=i+1 ;j<size ;j++)
		{
			if(arr[j] < min)
			{
				min =arr[j];
				idx =j;
			}
		}
		if(idx != i)
			swap(i,idx,arr);
	}
}

int main(int argc ,char **argv)
{
	int arr[6] = {8,5,7,1,9,3};
	int order = 5;
	int size = sizeof(arr)/sizeof(arr[0]);
	sort(arr,size ,order);
	for(int i =0 ;i<size ;i++)
			cout<<arr[i]<<", ";
		cout<<endl;
	cout<<"kth order of "<<order<<" is "<<arr[order-1]<<endl;
	return 0;
}