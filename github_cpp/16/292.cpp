// Topological Sorting 

// INPUT:
//     - A directed graph

// OUTPUT: 
//		- Returns a stack containing the topological sorting order of vertices in the given graph.

#include "bits/stdc++.h"
using namespace std;

typedef vector< int > vi;
const int MAX = 1e5;
vector< bool > seen(MAX+1, false);
vector< int > graph[MAX+1];
stack<int> torder;

struct TopologicalSort{
	void buildGraph(int V, int E){
		int x, y;
		for(int i = 0;i<E;i++){
			cin>>x>>y;
			graph[x].push_back(y);
		}
	}

	void dfs(int id){
		seen[id] = true;
		for(auto it: graph[id]){
			if(seen[it]==false) dfs(it);	
		}
		torder.push(id);
	}

	stack< int > topSort(int n){
        for(int id = 1;id<n+1;id++){
            if(!seen[id]) dfs(id);
        }

        stack<int> topological;
        while(!torder.empty()){
        	topological.push(torder.top());
            torder.pop();
        }
        
        return topological;
    }
};
