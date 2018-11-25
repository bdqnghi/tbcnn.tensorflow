







#include <vector>
#include <queue>
#include <iostream>
using namespace std;

typedef pair<int , int> P; 
typedef vector <vector <P>> graph;





int mst (const graph &G)
{
	int n = int(G.size());			
	
	vector<bool> vis(n, false);		
	vis[0] = true;
	
	priority_queue< P, vector<P>, greater<P> > pq;		
	
	for (P v : G[0]) pq.push(v);	
	
	int sum = 0;		
	
	while (not pq.empty())
	{
		int c = pq.top().first;
		int v = pq.top().second;		
		pq.pop();
		
		if (not vis[v])
		{
			vis[v] = true;
			for (P u : G[v]) pq.push(u);
			sum += c;		
		}
	}
	return sum;
}


void read (graph &G, int m)
{
	for (int i = 0; i < m; ++i)
	{
		int v, u, w;
		cin >> v >> u >> w;
		--u; --v; 	
		G[v].push_back(make_pair(w,u));
		G[u].push_back(make_pair(w,v));
	}
}

int main ()
{
	int n, m;
	while (cin >> n >> m)
	{
		graph G(n);
		read(G, m);
		cout << mst(G) << endl;
	}
}
