#include<bits/stdc++.h>
using namespace std;
#define LL long long

const int maxn=1e5+10;
const int mo=998244353;

int n,m,x,y,f[maxn],cnt;
bool vis[maxn],deg[maxn];

bool search(int u)
{
	if (vis[u]) return 0;
	vis[u]=1;
	return f[u]?!search(f[u]):0;
}

int main()
{
	freopen("permutation.in","r",stdin);
	freopen("permutation.out","w",stdout);
	int i;
	scanf("%d",&n);
	if (n&1) {puts("0"); return 0;}
	for (i=1;i<=n;i++)
	{
		scanf("%d",&f[i]);
		if (f[i]) deg[f[i]]=1;
	}
	for (i=1;i<=n;i++)
		if (!deg[i])
		{
			int tmp=search(i);
			tmp?y++:x++;
		}
	for (i=1;i<=n;i++)
		if (!vis[i])
		{
			int tmp=search(i);
			if (tmp)
			{
				puts("0");
				return 0;
			}
		}
	int Ans=1;
	for (i=1;i<=x;i+=2)
		Ans=(LL)Ans*i%mo;
	Ans=(LL)Ans*Ans%mo;
	for (i=x+1;i<=x+y;i++)
		Ans=(LL)Ans*i%mo;
	printf("%d\n",Ans);
}

