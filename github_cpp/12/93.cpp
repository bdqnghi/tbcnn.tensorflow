#include <bits/stdc++.h>

using namespace std;



int p[50000];
int totalWeight = 0;


int find(int x)
{
	if(p[x] < 0)
	{
		return x;
	}
	
	p[x] = find(p[x]);
	
	return p[x];
}


void unite(int x, int y)
{
	if((x = find(x)) == (y = find(y)))
	{
		return;
	}
	
	if(p[y] < p[x])
		swap(x,y);
	
	p[x] += p[y];
	p[y] = x;
}


struct edge
{
	int u,v;
	int weight;
	
	edge(int _u, int _v, int _w)
	{
		u = _u;
		v = _v;
		weight = _w;
	};
};


bool edge_cmp(const edge &lhs, const edge &rhs)
{
	return lhs.weight < rhs.weight;
}


vector<edge> mst(int n, vector<edge>edges)
{
	
	for(int i = 0; i < 50000; i++)
	{
		p[i] = -1;	
	}
	
	sort(edges.begin(), edges.end(), edge_cmp);
	
	vector<edge> result;
	totalWeight = 0;
	
	for(int i = 0; i < edges.size(); i++)
	{
		int u = edges[i].u;
		int v = edges[i].v;
		
		
		if(find(u) != find(v))
		{
			unite(u,v);
			result.push_back(edges[i]);
			totalWeight += edges[i].weight;
		}
	}
	
	return result;
}

int main()
{

	return 0;
}
