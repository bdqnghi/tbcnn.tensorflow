
#include <bits/stdc++.h>
using namespace std;

struct Maxheap{
	int *arr;
	int heapsize;
	};
void swap(int *a,int*b)
{
	int t;
	t=*a;
	*a=*b;
	*b=t;
}
void Maxheapify(struct Maxheap* m,int i)
{
	int largest=i;
	int left=(i<<1)+1;
	int right=(i+1)<<1;													
	if(left < m->heapsize && m->arr[left] > m->arr[largest])
		largest=left;
	if(right < m->heapsize && m->arr[right] > m->arr[largest])
			largest=right;
	if(largest!=i){														
		swap(&m->arr[largest],&m->arr[i]);								
		Maxheapify(m,largest);
	}
}

struct Maxheap*  BuildMaxHeap(int *a,int n)
{
	struct Maxheap* m = (struct Maxheap*)malloc(sizeof(struct Maxheap));
	m->arr	= a;
	m->heapsize=n;
	for(int i=(m->heapsize-2)/2;i>=0;i--)
	{
		Maxheapify(m,i);
	}
	return m;
}

void heapsort(int a[],int n)											
{		
	struct Maxheap* m = BuildMaxHeap(a,n);								
	for(int i=m->heapsize-1;i>=1;i--)									
	{																	
		swap(&m->arr[0],&m->arr[i]);
		m->heapsize--;
		Maxheapify(m,0);
	}
}

int main()
{
	int a[100],i,n;
	cout<<"Enter Size \t";
	cin>>n;
	cout<<"\nEnter The array Elements\n";
	for(i=0;i<n;i++)
	{
		cin>>a[i];
	}
	heapsort(a,n);														
	cout<<"The Sorted Array is : \n";
	for(i=0;i<n;i++)
	{
		cout<<a[i]<<" ";
	}
	
}
