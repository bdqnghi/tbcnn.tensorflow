
#include <bits/stdc++.h>
using namespace std;
int parent(int i)
{
	return i/2;
}
int left(int i)
{
	return 2*i+1;
}
int right(int i)
{
	return ((2*i)+2);
}

void max_heapify(int a[],int n, int i)
{
	int temp;
	int largest;
	
	int l=2*i+1;
	int r=2*i+2;
	if (l<n&&a[l]>a[i])
	{
		largest = l;
	}
	else largest = i;
	if (r<n&&a[r]>a[largest])
	{
		largest=r;
	}
	if (largest!=i)
	{
		temp=a[i];
		a[i]=a[largest];
		a[largest]=temp;
			max_heapify(a,n, largest);

	}
}
void build_max_heap(int a[],int n)
{
	
	for (int i = n/2-1; i>=0 ; --i)
	{
		max_heapify(a,n,i);
	}
}
void heapsort(int a[], int n)
{
	build_max_heap(a, n);
	int temp;
	
	for (int i = n-1; i>=0; --i)
	{
		temp=a[0];
		a[0]=a[i];
		a[i]=temp;
		
		max_heapify(a,i,0);
	}
}
int main()
{
	ios_base::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin>>n;
	int a[n];
	for (int i = 0; i < n; ++i)
	{
		cin>>a[i];
	}
	heapsort(a,n);
	for (int i = 0; i < n; ++i)
	{
		cout<<a[i];
	}
	return 0;
}