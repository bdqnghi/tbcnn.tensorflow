// Depth First Search

// INPUT:
//     - A graph
//     - Starting vertex
// OUTPUT: 
//     - Prints the dfs traversal of the given graph

#include "bits/stdc++.h"
using namespace std;

typedef vector< int > vi;
const int MAX = 1e5;
vector< bool > seen(MAX+1, false);
vector< int > graph[MAX+1];

struct DFS{
	void buildGraph(int V, int E){
		int x, y;
		for(int i = 0;i<E;i++){
			cin>>x>>y;
			graph[x].push_back(y);
			graph[y].push_back(x); // Undirected Edge. For directed just make this line comment
		}
	}

	void dfs(int id){
		seen[id] = true;
		cout<<id<<endl;
		for(auto it: graph[id]){
			if(seen[it]==false) dfs(it);	
		}
	}
};
