#include <bits/stdc++.h>

using namespace std;

//Kruskals algorithm

int p[50000];
int totalWeight = 0;

//union find find
int find(int x)
{
	if(p[x] < 0)
	{
		return x;
	}
	
	p[x] = find(p[x]);
	
	return p[x];
}

//union find union
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

//each edge contains a source(u) dest(v) and a weight
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

//greedy method so orders in ascending order
bool edge_cmp(const edge &lhs, const edge &rhs)
{
	return lhs.weight < rhs.weight;
}

//n is the number of nodes
vector<edge> mst(int n, vector<edge>edges)
{
	//make set
	for(int i = 0; i < 50000; i++)
	{
		p[i] = -1;	
	}
	//sort in ascending order to pick least value edge
	sort(edges.begin(), edges.end(), edge_cmp);
	
	vector<edge> result;
	totalWeight = 0;
	//Loop through edge and make sure graph is not connected 
	for(int i = 0; i < edges.size(); i++)
	{
		int u = edges[i].u;
		int v = edges[i].v;
		
		//if graph is not connected, connect them and put in result vector
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
