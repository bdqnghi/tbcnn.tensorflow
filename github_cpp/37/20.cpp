#include <iostream>
using namespace std;

typedef struct ArrayHolder
{
	int *r,*s;
}AH;

int Rod_Cutting(int p[],AH *holder,int n)
{
	if(n==0)
		return 0;
	else if(holder->r[n]>=0)
		return holder->r[n];
	else
	{
		int q=-1;
		for(int i=1;i<=n;i++)
			q=max(q,p[i]+Rod_Cutting(p,holder,n-i));	
		holder->r[n]=q;
		return q;
	}
}

int main()
{
	int n;
	cout<<"\nEnter the length of the rod : ";
	cin>>n;
	int p[n+1];
	AH *arrs;
	arrs->r=new int[n+1];
	arrs->s=new int[n+1];
	for(int i=1;i<n+1;i++)
	{
		cout<<"Enter the price of the piece of length "<<i<<" : ";
		cin>>p[i];
		arrs->r[i]=-1;
	}
	cout<<"\nMaximum price for the the rod can be sold after cutting it into desirable pices is : "<<Rod_Cutting(p,arrs,n)<<endl;
	return 0;
}
