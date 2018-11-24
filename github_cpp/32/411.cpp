#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXV = 100005;
const int MAXE = 1000005;
const int INF = 1e6;

struct edge {
	int u, v, w;

	bool operator < (const edge & t) const
	{
		return w < t.w;
	}
} es[MAXE];

int V, E;
int fa[MAXV];

void initFa()
{
	for(int i = 1; i <= V; i++)
		fa[i] = i;
}

int findfa(int u)
{
	if(fa[u] != u)
		fa[u] = findfa(fa[u]);

	return fa[u];
}

bool join(int u, int v)
{
	int fau = findfa(u);
	int fav = findfa(v);
	if(fau == fav)
		return false;
	if(fau < fav)
		fa[fav] = fau;
	else 
		fa[fau] = fav;
	return true;
}

int kruskal()
{
	sort(es, es + E);
	initFa();

	int res = 0;
	for(int i = 0; i < E; i++)
	{
		edge e = es[i];
		if(join(e.u, e.v))
			res += e.w;
	}

	return res;
}

int main()
{
	scanf("%d %d", &V, &E);

	int a, b, c;

	for(int i = 0; i < E; i++)
		scanf("%d %d %d", &es[i].u, &es[i].v, &es[i].w);

	printf("%d\n", kruskal());

	return 0;
}