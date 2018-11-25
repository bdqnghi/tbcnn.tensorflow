#include<iostream>
using namespace std;
void sort(char [],int);
void adjust(char [],int,int);
void maxheap(char a[],int n)
{
	int i;
	i=(n/2)-1;
	while(i>=0)
	{
		adjust(a,i,n);
		i--;
	}
}
void adjust(char a[],int p,int n)
{
	int l,r,largest;
	int temp;
	l=2*p+1;
	r=2*p+2;
	if(l<n &&a[l]>a[p])
	largest=l;
	else
	largest=p;
	if(r<n&&a[r]>a[largest])
	largest=r;
	if(largest!=p)
	{
		temp=a[largest];
		a[largest]=a[p];
		a[p]=temp;
		adjust(a,largest,n);
	}
}
void sort(char a[],int n)
{
	maxheap(a,n);
	int q;
	q=n;
	while(q>=2)
	{
		int temp;
		temp=a[0];
		a[0]=a[q-1];
		a[q-1]=temp;
		q--;
		adjust(a,0,q);
	}
}
int main()
{
	int arraysize;
	char array[10];
	cout<<"size of the array";
	cin>>arraysize;
	cout<<"enter the array elements";
	for(int i=0;i<arraysize;i++)
		cin>>array[i];
	sort(array,arraysize);
	cout<<"\n"<<"sorted array";
	for(int i=0;i<arraysize;i++)
		cout<<array[i]<<" ";
}
