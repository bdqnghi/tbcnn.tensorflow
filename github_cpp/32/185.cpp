#include <iostream>
using namespace std;


const int MAX = 1000;

class UnionFind
{
	int parent[MAX];  // parent link 
	int sz[MAX];  // size of component for roots (site indexed)
public:
	UnionFind(int n)
	{
		for (int i = 0; i < n; ++i)
		{
			parent[i] = i;
			sz[i] = 1;
		}
	}

	int root(int i)
	{
		while (i!= parent[i])
		{
			parent[i] = parent[parent[i]];  // path compression
			i = parent[i];
		}
		return i;
	}

	int find(int p, int q)
	{
		return root(p) == root(q);
	}

	void unite(int p, int q)
	{
		int p_root = root(p);
		int q_root = root(q);

		if (sz[p] < sz[q])
		{
			parent[p] = parent[q];
			sz[q] += sz[p];
		}
		else
		{
			parent[q] = parent[p];
			sz[p] += sz[q]; 
		}

	}
};

struct Edge{
	int v, u, w;  //weight
};

const int nodes = 30;
const int maxEdges = 100;
struct Edge graph[maxEdges];
int front = 0; 

long long KruskalMST()
{
	UnionFind UF(nodes + 1);
	
	long long T = 0;
	int u;
	int v;

	for (int i = 0; i < maxEdges; i++)
	{
		u = graph[i].u;
		v = graph[i].v;

		if ( !UF.find(u, v) )
		{
			UF.unite(u, v);
			T += graph[i].w;
		}
	}
	return T; 
}

void exch(struct Edge arr[], int i, int j)
{
	struct Edge e;
	e = arr[i];
	arr[i] = arr[j];
	arr[j] = e;
}

//selection sort
void sort(struct Edge arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		int min = i;
		for (int j = i + 1; j < len; j++)
		{
			if (arr[j].w < arr[min].w)
				min = j;
		}
		exch(arr, i, min);
	}
}

int main()
{
	int V, E;
	int  u, v, w;

	cin >> V >> E;
	for (int i = 0; i < E; i++)
	{
		cin >> u >> v >> w;
		graph[i].u = u;
		graph[i].v = v;
		graph[i].w = w; 
	}

	sort(graph, E);

	long long ans = KruskalMST();
	cout << ans << endl;
	return 0;
}