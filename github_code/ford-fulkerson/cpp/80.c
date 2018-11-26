/*
The Solution of maximum flow problems by Ford�CFulkerson algorithm
*/

#include<stdio.h>  
#include<stdlib.h>  
#include<vector>  
#include<algorithm>  

#define MAXVEX 100  
#define INF 65535  

struct edge
{
	int to;
	int cap;
	int rev;  
};
std::vector<edge>G[MAXVEX];
bool used[MAXVEX];

void addEdge(int from, int to, int cap)
{
	edge e;
	e.cap = cap; e.to = to; e.rev = G[to].size();
	G[from].push_back(e);
	e.to = from; e.cap = 0; e.rev = G[from].size() - 1;
	G[to].push_back(e);
}

int dfs(int v, int t, int f)
{
	if (v == t)return f;
	used[v] = true;
	for (int i = 0; i < G[v].size(); ++i)
	{
		edge &e = G[v][i];
		if (!used[e.to] && e.cap > 0)
		{
			int d = dfs(e.to, t, std::min(f, e.cap));
			if (d > 0){
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

int max_flow(int s, int t)
{
	int flow = 0;
	for (;;)
	{
		memset(used, 0, sizeof(used));
		int f = dfs(s, t, INF);
		if (f == 0)return flow;
		flow += f;
	}
}