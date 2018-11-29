#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define N 100
int Heapsize;
void Heapify(int *a,int pos)
{
	int l=2*pos;
	int r=l+1;
	int t=pos;
	if (l<=Heapsize && a[l]>a[t])
		t=l;
	if (r<=Heapsize && a[r]>a[t])
		t=r;
	if (pos != t){
		swap(a[pos],a[t]);
		Heapify(a,t);
	}
}
void BuildHeap(int *a,int n)
{
	for (int i=n/2;i>=1;--i)
		Heapify(a,i);
}
void HeapSort(int *a,int n)
{
	Heapsize=n;
	BuildHeap(a,n);
	for (int i=n;i>1;--i){
		swap(a[1],a[i]);
		--Heapsize;
		Heapify(a,1);
	}
}
int a[N];
int main()
{
	int n;
	cin>>n;
	for (int i=1;i<=n;++i)
		cin>>a[i];
	HeapSort(a,n);
	for (int i=1;i<=n;++i)
		cout<<a[i]<<" ";
	cout<<endl;
	return 0;
}
