#include <iostream>
using namespace std;

typedef struct ArrayHolder
{
	int *r,*s;
}AH;

AH* Rod_Cutting_DP(int p[],AH *holder,int n)
{
	holder->r[1]=p[1];
	holder->s[1]=1;
	holder->r[0]=0;
	for(int i=2;i<=n;i++)
	{
		int q=-1;
		for(int j=1;j<=i;j++)
		{
			if(q < p[j]+holder->r[i-j] )
			{
				q = p[j]+holder->r[i-j];
				holder->s[i]=j;
			}
		}
		holder->r[i]=q;
	}
	return holder;
}

int main()
{
	int n;
	cout<<"\nEnter the size of the rod : ";
	cin>>n;
	AH *arrs;
	arrs=new AH;
	int p[n+1];
	arrs->r=new int[n+1];
	arrs->r[0]=0;
	arrs->s=new int[n+1];
	arrs->s[0]=0;
	for(int i=1;i<n+1;i++)
	{
		cout<<"\nEnter the price of piece of rod of length "<<i<<" : ";
		cin>>p[i];
	}
	arrs=Rod_Cutting_DP(p,arrs,n);
	int temp=n;
	cout<<"\nBy cutting the rod into these pieces ";
	while(n>0)
	{
		cout<<arrs->s[n]<<" ";
		n-=arrs->s[n];
	}
	cout<<"the max value is obtained which is equal to "<<arrs->r[temp]<<endl;
	return 0;
}
