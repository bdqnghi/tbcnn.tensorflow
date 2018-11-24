#include <iostream>
using namespace std;

/*
	This is an implementation of a max heap.
	A Max Heap is one in which the value of each element should be greater than or equal to
	any of its child and smaller than or equal to its parent
*/
/*
	The basic idea is as follows.
	Each nodes has 2 children left and right
	Among the node and the children you find out which is maximum
	if it is the node then lite (else statement)
	if it is one of the children then exchange it with the node
	
	Procede to check the children as the rest will take care of itself

	Also to build a max heap you must start from index N/2 and procede backwards

	It has a complexity of O(log(n))
*/
int* max_heapify(int* arr,int i,int N)
{
	int left=2*(i+1)-1; //the left child
	int right=2*(i+1); //the right child
	int largest=0;
	if(left<N && arr[left]>arr[i])
		largest=left;
	else largest=i;
	if(right<N && arr[right]>arr[largest])
		largest=right;
	if(largest!=i)
	{
		swap(arr[i],arr[largest]);
		max_heapify(arr,largest,N);
	}
	return arr;
}
int* build_max_heap(int* arr,int N)
{
	for(int i=N/2;i>=0;i--)
		max_heapify(arr,i,N);
}
/*
	This is an implementation of a min heap
	You should go about thinking just like a max heap
*/
int* min_heapify(int* arr,int i,int N)
{
	int left=2*(i+1)-1;
	int right=2*(i+1);
	int smallest=0;
	if(left<N && arr[left]<arr[i])
		smallest=left;
	else smallest=i;
	if(right<N && arr[right]<arr[smallest])
		smallest=right;
	if(smallest!=i)
	{
		swap(arr[i],arr[smallest]);
		min_heapify(arr,smallest,N);
	}
}
int* build_minheap(int* arr,int N)
{
	for(int i=N/2;i>=0;i--)
		min_heapify(arr,i,N);
}
int main()
{
	int n;
	cin>>n;
	int arr[n];
	for(int i=0;i<n;i++)
		cin>>arr[i];
	/*int *ans1=build_max_heap(arr,n);
	for(int i=0;i<n;i++)
		cout<<arr[i]<<" ";
	cout<<endl;*/
	int *ans2=build_minheap(arr,n);
	for(int i=0;i<n;i++)
		cout<<arr[i]<<" ";
	cout<<endl;
}
/*
	To insert an element into a heap
		Step1:
			stick the new element at the last level of the heap
		Step2:
			bubble up the new element by exchanging it with its parent until the heap property is restored
*/
/*
	To extract min:
		Delete(extract) the root
		Move the last node to the root
		Bubble down by exchanging it with the child with a lesser value!
		Iterate until you have a heap
	Ex-
	     4
	   4   8
	  9 4   9
	11 13
	     13
	   4    8
	  9 4    9
	11 
	     4
	   13  8
	  9 4   9
	11
	      4
	   4     8
	  9 13     9
	11
	taDAA!
*/