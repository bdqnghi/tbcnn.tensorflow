//	Minimum Spanning Trees
//  P12887_MinimumSpanningTrees.cpp
//  programes
//
//  Created by Júlia Gasull Navarro on 26/5/18.
//  Copyright © 2018 Júlia Gasull Navarro. All rights reserved.
//

#include <vector>
#include <queue>
#include <iostream>
using namespace std;

typedef pair<int , int> P; // (cost, vertex)
typedef vector <vector <P>> graph;

/*
 	Given a connected, undirected graph:
 		- 	a spanning tree of that graph is a subgraph which is a tree
 			and connects all the vertices together.
 	On a weighted graph:
 		- 	the weight of a spanning tree is the sum of the weights of its
 			edges. A minimum spanning tree is a spanning tree with weight
 			less than or equal to the weight of every other spanning tree.

 	Input
 		Input consists of different weighted, connected, undirected graphs.
 		For each graph, the following integers are given: First, n ≥ 1
 		represents the number of vertices on the graph. Then, m represents
 		the number of edges on the graph. Finally, a set of m weighted edges
 		u,v,w is given by specifying its two end points u and v and its weight
 		w ≥ 1. Vertices are numbered starting from 1. There are no edges
 		connecting a vertex to itself, but there may be more than two edges
 		connecting the same pair of vertices. Every given graph is connected.
 		All weights are strictly positive integers.

 	Output
 		For every graph in the input, write the weight of its minimum spanning tree.
*/



int mst (const graph &G)
{
	int n = int(G.size());			// n = |V|
	
	vector<bool> vis(n, false);		// seen
	vis[0] = true;
	
	priority_queue< P, vector<P>, greater<P> > pq;		// priority queue of pairs (cost, vertex)
	
	for (P v : G[0]) pq.push(v);	// push of all adj of vertex 0 -> always connex
	
	int sum = 0;		// sum of costs
	
	while (not pq.empty())
	{
		int c = pq.top().first;
		int v = pq.top().second;		// adj to priority
		pq.pop();
		
		if (not vis[v])
		{
			vis[v] = true;
			for (P u : G[v]) pq.push(u);
			sum += c;		// compto un vertex nomes un cop ?
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
		--u; --v; 	// Vertices are numbered starting from 1
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
