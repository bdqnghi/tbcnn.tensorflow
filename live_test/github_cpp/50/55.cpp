#include<iostream>
#include<cstring>

int max(int a,int b)
{
	if(a>=b)
		return a;
	else
		return b;
}

void ks(int b[],int p[],int n,int W)
{
	int i,w;
	int V[n+1][W+1];
	int v[n+1],wt[n+1];

	int keep[n+1][W+1];

//	memset(keep,0,sizeof(keep));

	v[0]=wt[0]=0;
	for(i=0;i<n;i++)
	{
		v[i+1]=b[i];
		wt[i+1]=p[i];
	}

	//memset(V,0,sizeof(V));
	for(w=0;w<=W;w++)
		V[0][w] = keep[0][w] = 0;
	for(i=1;i<=n;i++)
		V[i][0] = keep[i][0] = 0;

	for(i=1;i<=n;i++)
	{
		for(w=1;w<=W;w++)
		{
			if(wt[i]<=w)
			{
				V[i][w] = max((v[i]+V[i-1][w-wt[i]]) , V[i-1][w]);
				keep[i][w]=1;
			}
			else
			{
				V[i][w] = V[i-1][w];
				keep[i][w]=0;
			}
		}
	}

	int k=W;
	for(i=n;i>=1;i--)
	{
		if(keep[i][k]==1)
		{
			std::cout<<i<<" ";
			k=k-wt[i];
		}
	}
	

/*	for(i=0;i<=n;i++)
	{
		for(int j=0;j<=W;j++)
			std::cout<<V[i][j]<<" ";
		std::cout<<"\n";
	}
*/
	std::cout<<"\nMax profit : "<<V[n][W]<<std::endl;

}


int main()
{
	int v[] = {1,6,18,22,28};
	int w[] = {1,2,5,6,7};
	int n = sizeof(v)/sizeof(int);
	int W = 11;

	ks(v,w,n,W);
return 0;
}
