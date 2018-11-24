 #include<bits/stdc++.h>
 using namespace std;
 void heapify(int a[],int i,int n)
 {
 	int l,r,max,temp;
 	max=i;
 	l=(2*i)+1;
 	r=(2*i)+2;
 	if(a[l]>a[max] && l<n)
 	{
 		max=l;
	}
	if(a[r]>a[max] && r<n)
	{
		max=r;
	}
	if(max!=i)
	{
		temp=a[i];
		a[i]=a[max];
		a[max]=temp;
		heapify(a,max,n);
	}
 }
 void buildheap (int a[],int n)
 {
 	for(int i=n/2;i>=0;i--)
 	{
 		heapify(a,i,n);
	}
 }
 int main()
 {
 	int n,i;
 	cout<<"Enter no. of elements: ";
 	cin>>n;
 	int a[n];
 	for(i=0;i<n;i++)
 	{
 		cin>>a[i];
	}
	buildheap(a,n);
	for(i=0;i<n;i++)
	{
		cout<<a[i]<<" ";
	}
	return 0;
 }
