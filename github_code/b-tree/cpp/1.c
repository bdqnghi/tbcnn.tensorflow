// ━━━━━━神兽出没━━━━━━
//      ┏┓       ┏┓
//     ┏┛┻━━━━━━━┛┻┓
//     ┃           ┃
//     ┃     ━     ┃
//     ████━████   ┃
//     ┃           ┃
//     ┃    ┻      ┃
//     ┃           ┃
//     ┗━┓       ┏━┛
//       ┃       ┃
//       ┃       ┃
//       ┃       ┗━━━┓
//       ┃           ┣┓
//       ┃           ┏┛
//       ┗┓┓┏━━━━━┳┓┏┛
//        ┃┫┫     ┃┫┫
//        ┗┻┛     ┗┻┛
//
// ━━━━━━感觉萌萌哒━━━━━━

// Author        : WhyWhy
// Created Time  : 2016年05月01日 星期日 14时23分31秒
// File Name     : B.cpp

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
#include <bitset>

using namespace std;

// 静态Trie，时间复杂度 O(n)，空间复杂度 O(kn)。
// 输入：字符串。
// 输出：匹配值(灵活改动)。
// 注意：使用init初始化。
// 原理：建树。

const int MaxNode=1000000;

int next1[500000],val[500000];
int ncou;

struct Trie
{
	int next[MaxNode][2],head[MaxNode];
	int Tcou,root;

	int newNode()
	{
		++Tcou;

		memset(next[Tcou],0,sizeof(next[Tcou]));
		head[Tcou]=-1;

		return Tcou;
	}

	void init()
	{
		Tcou=-1;
		root=newNode();
	}

	Trie()
	{
		init();
	}

	void insert(int len,int s)
	{
		int p=0;

		for(int i=0,j=31;i<len;++i,--j)
		{
			if(next[p][(s>>j)&1]==0)
				next[p][(s>>j)&1]=newNode();

			p=next[p][(s>>j)&1];
		}

		next1[ncou]=head[p];
		head[p]=ncou;
	}

	void match(int s,bitset <1025> &r)
	{
		int p=0;

		for(int i=31;i>=0;--i)
		{
			for(int j=head[p];j!=-1;j=next1[j]) r.set(val[j]);

			if(next[p][(s>>i)&1]==0)
				return;

			p=next[p][(s>>i)&1];
		}
	}
}tree;

bitset <1025> can,r1,r2;

int main() {
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);

	char s[10];
	int x,y;
	int a,b,c,d,e;
	int t;

	tree.init();
	ncou=0;

	can.reset();

	while(~scanf("%s",s)) {
		if(s[0]=='E') {
			scanf("%d %d",&x,&y);
			for(int i=1;i<=y;++i) {
				scanf("%d.%d.%d.%d/%d",&a,&b,&c,&d,&e);
				t=(a<<24)+(b<<16)+(c<<8)+d;

				val[ncou]=x;
				tree.insert(e,t);
				++ncou;
			}
			can.set(x);
		}
		else if(s[0]=='F') {
			r1.reset();
			scanf("%d.%d.%d.%d",&a,&b,&c,&d);
			t=(a<<24)+(b<<16)+(c<<8)+d;
			tree.match(t,r1);

			r2.reset();
			scanf("%d.%d.%d.%d",&a,&b,&c,&d);
			t=(a<<24)+(b<<16)+(c<<8)+d;
			tree.match(t,r2);

			if((r1&r2&can).count()) puts("F");
			else puts("D");
		}
		else {
			scanf("%d",&x);
			can.reset(x);
		}
	}
	
	return 0;
}
