#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MOD 1000000007
#define unsigned long long ull;
#define rep(i,n) for(ll i=0;i<n;i++)

class Graph
{
	int v;
	list<int> *adj;

public:
	Graph(int v);
	void addEdge(int v,int w);
	void topologicalsort_U(int v,bool visited[],stack<int> &S);
	void topologicalsort();
};

Graph :: Graph(int v)
{
	this->v=v;	
	adj = new list<int> [v];
}

void Graph :: addEdge(int v,int w)
{
	adj[v].push_back(w);
}

void Graph :: topologicalsort_U(int v,bool visited[],stack<int> &S)
{
	visited[v]=true;

	list<int> :: iterator it;

	for(it=adj[v].begin();it!=adj[v].end();it++)
	{
		if(!visited[*it])
			topologicalsort_U(*it,visited,S);
	}
	S.push(v);
}

void Graph :: topologicalsort()
{
	bool visited[v];
	memset(visited,false,sizeof(visited));
	stack<int> S;
	for(int i=0;i<v;i++)
	{
		if(!visited[i])
			topologicalsort_U(i,visited,S);
	}

	while(!S.empty())
	{
		cout<<S.top()<<" ";
		S.pop();
	}
}

int main()
{
	Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
 
 	g.topologicalsort();
	return 0;
}
