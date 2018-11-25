#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;
#define maxv(A,B) (A>B?A:B)
#define minv(A,B) (A>B?B:A)
long u,v,visit[110];
vector<long>ve[110],toposort;
 void dfs(long x)
 {
	 visit[x]=1;
	 long i;
	 
	 for(i=0;i<ve[x].size();i++)
	 {
		 v=ve[x][i];
		 if(visit[v]==0)	 
		 dfs(v);
	 }
	 
//	 printf(" %ld",x);
	 toposort.push_back(x);
 }
int main()
{
//	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
long n,e,i;
while(scanf("%ld %ld",&n,&e))
{
	for(i=1;i<=n;i++) visit[i]=0;
	if(n==0&&e==0)
		break;
	for(i=0;i<e;i++)
	{
		scanf("%ld %ld",&u,&v);
		ve[u].push_back(v);
	}
	for(i=1;i<=n;i++)
	{
		if(visit[i]==0)
          dfs(i);
	}
	long f=0;
	for(i=toposort.size()-1;i>=0;i--)
	{
		if(f==0)
		{
			f=1;
			printf("%ld",toposort[i]);
		}
		else
			printf(" %ld",toposort[i]);
	}
	toposort.clear();
	printf("\n");
}
	return 0;
}