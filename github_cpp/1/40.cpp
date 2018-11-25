#include <iostream>
#include <iomanip>
#include <utility>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <math.h>
#include <algorithm>
#include <math.h>
#include <cstdlib>
#include <functional>
#define rep(i, a, b) for(__typeof(a) i = (a); i < (b); ++i)
#define all(c) c.begin(), c.end() 
#define iter(it, c) for(__typeof((c).begin)it = (c).begin; it != (c).end(); it++)
#define MAX 1000
#define INF 2000000000
using namespace std;
int dist[MAX+1]; 
void bfs(int v, vector < vector <int> >& graph)
{
	dist[v] = 0;
	queue <int> q;
	q.push(v);
	while(!q.empty())
	{
		int current = q.front();
		rep(i, 0,(int)(graph[current].size()))
			if(dist[graph[current][i]] == INF)
			{
				dist[graph[current][i]] = dist[current] + 1;
				q.push(graph[current][i]);
			}
		q.pop();
	}
}

int main()
{
	int n, m;
	cin >> n >> m;
	vector < vector <int> > graph(n+1);
	rep(i, 0, m)
	{
		int x, y;
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}

	rep(i, 0, MAX+1)
		dist[i] = INF;

	int u, v;
	cin >> u >> v;
	bfs(u, graph);
	cout << endl << dist[v] << endl;
}


