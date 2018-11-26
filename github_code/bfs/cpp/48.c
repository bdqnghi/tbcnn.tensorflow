// Breadth First Search

// INPUT:
//     - A graph
//     - Starting vertex
// OUTPUT: 
//     - Prints the bfs traversal of the given graph
//     - Returns a vector representing shortest path from start node to each and every node


#include "bits/stdc++.h"
using namespace std;

typedef vector< int > vi;
const int MAX = 1e5, INF = 1e9;
vector< bool > seen(MAX+2, false);
vector< int > graph[MAX+2];

struct BFS{
	void buildGraph(int V, int E){
		int x, y;
		for(int i = 0;i<E;i++){
			cin>>x>>y;
			graph[x].push_back(y);
			graph[y].push_back(x); // Undirected Edge. For directed just make this line comment
		}
	}

	vector<int> bfs(int id){
        int start = id, tid;
              
        queue< int > Q;
        vi dist(MAX+1, INF);
        Q.push(id);
        seen[id] = true; dist[id] = 0;
            
        while(!Q.empty()){
            tid = Q.front();
            printf("%d\n", tid);
            Q.pop();
            for(auto it: graph[tid]){
                if(seen[it]==false){
                    dist[it] = dist[tid] + 1;
                    seen[it] = true;
                    Q.push(it);
                }
            }
        }
            
        return dist;
    }
};
