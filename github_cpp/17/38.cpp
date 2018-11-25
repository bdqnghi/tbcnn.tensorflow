
























#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <climits>

using namespace std;

const int MaxN=100005;

struct Treap
{
	int tot,root;
	int ch[MaxN][2];				
	int key[MaxN],pri[MaxN];		
	int cou[MaxN],size[MaxN];		

	void init()
	{
		tot=1;
		root=0;
		pri[0]=INT_MAX;				
		size[0]=0;
	}

	void update(int x)				
	{
		size[x]=size[ch[x][0]]+cou[x]+size[ch[x][1]];
	}

	void rotate(int &x,int t)		
	{
		int y=ch[x][t];

		ch[x][t]=ch[y][1-t];
		ch[y][1-t]=x;

		update(x);
		update(y);

		x=y;
	}

	void _insert(int &x,int k)
	{
		if(x)
		{
			if(key[x]==k)
				++cou[x];
			else
			{
				int t=key[x]<k;

				_insert(ch[x][t],k);

				if(pri[ch[x][t]]<pri[x])
					rotate(x,t);
			}
		}
		else
		{
			x=tot++;
			key[x]=k;
			cou[x]=1;
			pri[x]=rand();			
			ch[x][0]=ch[x][1]=0;
		}

		update(x);
	}

	void _erase(int &x,int k)
	{
		if(!x)				
			return;

		if(key[x]==k)
			if(cou[x]>1)
				--cou[x];
			else
			{
				if(ch[x][0]==0 && ch[x][1]==0)
				{
					x=0;				
					return;
				}

				int t=pri[ch[x][0]]>pri[ch[x][1]];

				rotate(x,t);
				_erase(x,k);
			}
		else
			_erase(ch[x][key[x]<k],k);

		update(x);
	}

	int find(long long k)
	{
		if(k>1000000000) return 0;

		int u=root;
		int ret=0;

		while(u)
		{
			if(key[u]==k)
			{
				ret+=size[ch[u][0]];
				break;
			}

			if(key[u]<k) ret+=cou[u]+size[ch[u][0]];
			u=ch[u][key[u]<k];
		}
		return size[root]-ret;
	}

	void insert(int k)
	{
		_insert(root,k);
	}

	void erase(int k)
	{
		_erase(root,k);
	}
}tree[10];

int N;

long long getans(int x)
{
	long long t=10;
	long long ret=0;

	for(int i=0;i<10;++i)
	{
		ret+=tree[i].find(t-x%t);
		t*=10LL;
	}
	return ret;
}

int main()
{
	
	

	srand(time(0));

	int a;
	long long t;
	long long ans;

	while(~scanf("%d",&N))
	{
		ans=0;
		for(int i=0;i<10;++i)
			tree[i].init();
		for(int i=1;i<=N;++i)
		{
			scanf("%d",&a);
			ans+=getans(a);
			t=10;
			for(int i=0;i<10;++i)
			{
				tree[i].insert(a%t);
				t*=10LL;
			}
		}
		
		printf("%lld\n",ans);
	}
	
	return 0;
}
