#include <stdio.h>
#include <limits.h>

#include <Eigen/Dense>

// http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
// Number of vertices in the graph
// #define V 9

int minDistance(int V, int dist[], bool sptSet[]) {
  int min = INT_MAX, min_index;

  for (int v = 0; v < V; v++)
    if (sptSet[v] == false && dist[v] <= min)
      min = dist[v], min_index = v;

  return min_index;
}

void dijkstra(MatrixXd Graph, int src) {
  int V = Graph.rows();
  int dist[V];
  bool sptSet[V];
  for (int i = 0; i < V; i++) {
    dist[i] = INT_MAX, sptSet[i] = false;
  }
  dist[src] = 0;
  for (int count = 0; count < V-1; count++) {
    int u = minDistance(V, dist, sptSet);
    sptSet[u] = true;
    for (int v = 0; v < V; v++) {
      if (!sptSet[v] && Graph(u, v) && dist[u] != INT_MAX
          && dist[u] + Graph(u, v) < dist[v])
        dist[v] = dist[u] + Graph(u, v);
    }
  }
  cout << dist << endl;
}

