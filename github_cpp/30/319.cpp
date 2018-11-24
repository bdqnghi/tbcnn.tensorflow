#include <ctime>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
#include <numeric>

#define pb              push_back
#define all(a)          (a).begin(), (a).end()
#define forn(i, n)      for(int i = 0; i < int(n); ++i)
#define fore(i, a, b)   for(int i = int(a); i <= int(b); ++i)
#define foreach(it, a)  for(typeof((a).begin()) it=(a).begin(); it != (a).end(); ++it)
#define rforeach(it, a) for(typeof((a).rbegin()) it=(a).rbegin(); it != (a).rend(); ++it)

using namespace std;

const int inf = int(1e9+7);
typedef pair<int,int>   ii;
typedef vector<int>     vi;
typedef vector<ii>      vii;
typedef long long       i64;
typedef vector<i64>     vi64;

vector<vii> g;
int dijkstra(const int src, const int dst)
{
	set<ii> q;
	vi dist(g.size(), inf);
	dist[src] = 0;
	q.insert( ii(dist[src], src) );
	while ( !q.empty() )
	{
		int u = q.begin()->second, d = q.begin()->first;
		q.erase(q.begin());
		if ( d != dist[u] ) continue;
		if ( u == dst ) break;
		forn(i,g[u].size())
		{
			int v = g[u][i].second, v_we = g[u][i].first;
			if ( dist[u] + v_we < dist[v] )
			{
				dist[v] = dist[u] + v_we;
				q.insert( ii(dist[v], v) );
			}
		}
	}
	return (dist[dst] == inf ? -1 : dist[dst]);
}

int main()
{
    int n, s, f;
	scanf("%d %d %d", &n, &s, &f);
	g.assign(n, vii());
	forn(i,n) forn(j,n)
	{
		int we;
		scanf("%d", &we);
		if ( we != -1 )
			g[i].push_back( ii(we, j) );
	}
	printf("%d\n", dijkstra(s-1, f-1));
    return 0;
}
