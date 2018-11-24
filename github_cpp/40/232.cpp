/* This program is written to illustrate quick sort for an interger array. The idea behind
quick sort is to find the pivot and organize all the elements which are smaller than the pivot 
to the left and elements which are greater to the right side of it. The time complexity of this 
algorithm is O(nlongn).*/

#include<cstdio>
#include<algorithm>

using namespace std;

void swap(int arr[], int median, int left)
{
	int temp;
	temp = arr[left];
	arr[left] = arr[median];
	arr[median] = temp;
}
int median_of_three(int arr[], int left, int right)
{
	int mid = left+(right-left)/2;
	int val;
	if (arr[mid] <= arr[left] && arr[mid]>=arr[right] )
		val = mid;
	else if (arr[left] >= arr[mid] && arr[left] <= arr[right])
		val = left;
	else
		val = right;
	return val;
}
int partition (int arr[], int left, int right)
{
	int lastmin,current;
	swap(arr, median_of_three(arr,left,right),left);
	for (lastmin = left,current = left+1; current <=right;++current)
	{
		if(arr[current] < arr[left])
			swap(arr,++lastmin, current);

	}
	swap(arr,lastmin,left);
	return lastmin;
}

void quick_sort(int arr[], int left, int right)
{
	if(left<right)
	{
		int p = partition(arr,left,right);
		quick_sort(arr,left,p-1);
		quick_sort(arr, p+1,right);
	}
}


int main()
{
	int n;
	scanf("%d", &n);
	int arr[n];
	for (int i =0;i<n;i++)
	{
		scanf("%d", &arr[i]);
	}

	quick_sort(arr,0,n-1);

	for (int i =0;i<n;i++)
	{
		printf("%d\n", arr[i]);
	}
	return 0;

}