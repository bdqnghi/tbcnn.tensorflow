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
        cin >> nodes;                       
        cin >> edges;                       
        for(int i = 0;i < edges;++i) {
         cin >> x >> y;
     
         adj[x].push_back(y);                   
         adj[y].push_back(x);                   
        }

                                

        for(int i = 1;i <= nodes;++i) {
         if(!visited[i])     {
             dfs(i);
             connectedComponents++;
         }
        }
        cout << "Number of connected components: " << connectedComponents << endl;
        return 0;
    }
