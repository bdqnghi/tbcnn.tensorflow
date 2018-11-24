#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Graph{
    int V, E;
    unordered_map<T, list< pair<T, int> > > adjList;
public:
    void addEdge(T u, T v, int weight, bool bidir = true) {
        adjList[u].push_back(make_pair(v, weight));
        if (bidir) {
            adjList[v].push_back(make_pair(u, weight));            
        }
    }

    void djikshtra(int V) {
        cout << "Djikshtra Algorithm" << endl;

        for(int src = 0; src < V; src++) {            
            unordered_map<T, int> dist;
            // unordered_map<T, T> parent;
            for (auto j: adjList) {
                dist[j.first] = INT_MAX;
                // parent[j.first] = src;
            }

            priority_queue<pair <int, T> > p;
            dist[src] = 0;
            p.push(make_pair(dist[src], src));

            while(!p.empty()) {
                T node = p.top().second;
                p.pop();
                for(auto neighbour: adjList[node]) {
                    if (dist[neighbour.first] > dist[node] + neighbour.second) {
                        dist[neighbour.first] = dist[node] + neighbour.second;
                        // parent[neighbour.first] = node;
                        p.push(make_pair(dist[neighbour.first], neighbour.first));
                    }
                }
            }
            for(int i = 0; i < V; i++) {
                cout << dist[i] << " ";
            }
            cout << endl;
        }
        // stack<T> s;
        // T node = dest;
        // s.push(node);
        // while(node != src) {
        //     node = parent[node];
        //     s.push(node);
        // }
        // while(!s.empty()) {
        //     T node = s.top();
        //     cout << node << "-->";
        //     s.pop();
        // }
        // cout << "Distance Covered: " << dist[dest] << endl;
    }

    void floyd_warshall(int V) {
        long long dist[V][V];
        for(int i = 0; i < V; i++) {
            for(int j = 0; j < V; j++) {
                dist[i][j] = INT_MAX;
            }
            dist[i][i] = 0;
        }

        for(auto i : adjList) {
            for(auto j : adjList[i.first]) {
                dist[i.first][j.first] = j.second;
            }
        }

        for(int k = 0; k < V; k++) {
            for(int i = 0; i < V; i++) {
                for(int j = 0; j < V; j++) {
                    if (dist[i][j] > (dist[i][k] + dist[k][j])) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        cout << "Floyd Warshall Matrix" << endl;
        for(int i = 0; i < V; i++) {
            for(int j = 0; j < V; j++) {
                cout << dist[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph<int> g;
    
    g.addEdge(1, 2, 10);
    g.addEdge(1, 0, 5);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 4, 3);
    g.addEdge(3, 4, 3);
    g.addEdge(4, 5, 2);
    g.addEdge(4, 0, 10);
    g.addEdge(5, 0, 4);


    g.djikshtra(6);
    cout << endl;
    g.floyd_warshall(6);

    return 0;
}