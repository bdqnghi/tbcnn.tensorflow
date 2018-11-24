#include <bits/stdc++.h>
    using namespace std;

    vector <int> adj[10];
    bool visited[10];

    void dfs(int s) {
        visited[s] = true;
        for(auto x : adj[s])
        {
        	if(!visited[x])
        		dfs(x);
        }

    }


    int main() {
        int nodes, edges, x, y, connectedComponents = 0;
        cin >> nodes;                       //Number of nodes
        cin >> edges;                       //Number of edges
        for(int i = 0;i < edges;++i) {
         cin >> x >> y;
     //Undirected Graph
         adj[x].push_back(y);                   //Edge from vertex x to vertex y
         adj[y].push_back(x);                   //Edge from vertex y to vertex x
        }

                                //Initialize all nodes as not visited

        for(int i = 1;i <= nodes;++i) {
         if(!visited[i])     {
             dfs(i);
             connectedComponents++;
         }
        }
        cout << "Number of connected components: " << connectedComponents << endl;
        return 0;
    }
