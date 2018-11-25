#include<iostream>

using namespace std;
int binaryrec(int *,int,int,int,int);
int main()
{
	int t,i;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		int l=0,u=n-1;
		int a[n];
		int count=0;
		for(i=0;i<n;i++)
		{
			cin >> a[i];
		}
		int key;
		cin >> key;
		int res=binaryrec(a,l,u,key,0);
		if(res==0)
		{
			cout<<"Not Present "<<endl;
		}
		else
		{
			cout<<"Present "<<res<<endl;
		}
	}
}

int binaryrec(int *a,int l, int u, int key,int count)
{
	int mid=(u+l)/2;
	int flag=0;
	if(l>=u)
	{
		return 0;
	}
	count++;
	if(a[mid]==key)
	{
		return count;
	}
	else
	if(key<a[mid])
	{
		 binaryrec(a,l,mid-1,key,count);
	}
	else if(key>a[mid])
		{
				binaryrec(a,mid+1,u,key,count);
		}
}
