// Implementer: Jatin Kumar
// Matrix chain multiplication problem
// given the matrices, we have to find minimum no. of scalar multiplications
// dynamic programming top down approach is used
// time complexity= O(n^3)

#include<iostream>
#include<limits.h>
using namespace std;
#define infinity INT_MAX
int n;
int matrixMultiplication(int*,int*,int,int);
int main()
{
	int r,c;
	cout<<"enter the no. of matrices:";
	cin>>n;
	int p[n+1];			// to store the size of the matrices
	int m[n+1][n+1];	// assume matrices starts from index one
	for(int i=0;i<n;i++)
	{
		cout<<"enter the size of matrix "<<i+1<<":";
		cin>>r>>c;
		if(i==n-1)
		{
			p[i]=r;
			p[i+1]=c;
		}
		else
		{
			p[i]=r;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			m[i][j]=infinity;
		}
	}
	int cost=matrixMultiplication(&m[0][0],p,1,n);
	cout<<"minimum multiplication cost is "<<cost<<endl;
}
int matrixMultiplication(int *m,int *p,int i,int j)
{
	if(*(m+i*(n+1)+j)<infinity)
	{
		return (*(m+i*(n+1)+j));
	}
	if(i==j)
	{
		*(m+i*(n+1)+j)=0;
		return 0;
	}
	else
	{
		for(int k=i;k<=j-1;k++)
		{
			int q=matrixMultiplication(m,p,i,k)+matrixMultiplication(m,p,k+1,j)+p[i-1]*p[k]*p[j];
			if(q<*(m+i*(n+1)+j))
			{
				*(m+i*(n+1)+j)=q;	
			}
		}
	}
	return (*(m+i*(n+1)+j));
}
