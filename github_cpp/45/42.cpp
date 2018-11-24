/* Ford Fulkerson algorithm -- Max flow
 * */
 // http://en.wikipedia.org/wiki/Ford%E2%80%93Fulkerson_algorithm
#include <iostream>
#include <climits>
#include <string>
#include <queue>
#include <vector>

using namespace std;
#define V 6

bool bfs( vector<vector<int>>& rGraph, int s, int t, vector<int>& parent)
{
    // Visited vector, mark all as unvisited.
	vector<bool> visited(V,0);
    // BFS queue. Enqueue start point s.
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    cout << "Get in bfs"<< endl;
    // BFS
    while (!q.empty())
    {
        int u = q.front();
        cout << "in bfs, u is: " << u << endl;
        q.pop();

        for (int i=0; i<V; i++)
        {
            if (visited[i]==false && rGraph[u][i] > 0)
            {
                q.push(i);
                parent[i] = u;
                visited[i] = true;
            }
        }
    }
    cout<< "leaving bfs visited is: " << endl;
    for(int i =0; i <V; i++){
    	cout << visited[i] << endl;
    }
    cout<< "leaving bfs parent is: " << endl;
    for(int i =0; i <V; i++){
    	cout << parent[i] << endl;
    }
    //return true if s can reach sink t!
    return (visited[t] == true);
}

int fordFulkerson(vector<vector<int>>& graph, int s, int t)
{
    int u, v;
    //residual graph.
    vector<vector<int>> rGraph(V, vector<int>(V));
    rGraph = graph;


    vector<int> parent(V,-1);

    int max_flow = 0;

    while (bfs(rGraph, s, t, parent))
    {
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

int main()
{
    vector<vector<int>> graph =
    			{ {0, 15, 9, 0, 0, 0},
                        {0, 0, 10, 2, 0, 0},
                        {0, 1, 0, 0, 3, 0},
                        {0, 0, 9, 0, 0, 12},
                        {0, 0, 0, 9, 0, 5},
                        {0, 0, 0, 0, 0, 0}
                      };

    cout << "The maximum possible flow is " << fordFulkerson(graph, 0, 5) << endl;

    return 0;
}
