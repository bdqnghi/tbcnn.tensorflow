#include <bits/stdc++.h>
using namespace std;

void combinesort(int arr[],int start, int end)
{
	int mid = (start+end)/2;
	int *ar=(int*)malloc((end-start+1) * sizeof(int));
	int i = start;
	int j = mid + 1;
	int k = 0;
	while(i<=mid&&j<=end)
	{
		if(arr[i]>arr[j]) ar[k++]=arr[j++];
		else ar[k++]=arr[i++];
	}
	while(i<=mid) ar[k++]=arr[i++];
	while(j<=end) ar[k++]=arr[j++];
	for(int i = 0; i < end - start + 1; i++) arr[start+i]=ar[i];
}

void mergesort(int arr[],int start, int end)
{
	//cout<<start<<" "<<end<<endl;
	if(start>=end) return;
	mergesort(arr,start,(start+end)/2);
	mergesort(arr,(start+end)/2+1,end);
	combinesort(arr,start,end);
}

int main()
{
	int arr[]={2,1,4,1,5,2,1,4,6,3,4,7,5};
	mergesort(arr,0,12);
	for(int i = 0 ; i< 13;i++) cout<<arr[i]<<" ";
}