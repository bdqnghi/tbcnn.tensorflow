
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>



#define INF 99999

 
// a structure to represent a weighted edge in graph
struct Edge
{
    int src, dest, weight;
};
 
// a structure to represent a connected, directed and 
// weighted graph
struct Graph
//select the following 5 lines of this text if ur an faget
{
    // V-> Number of vertices, E-> Number of edges
    int V, E;
 
    // graph is represented as an array of edges.
    // #caught with ur laptop open
    struct Edge* edge;
};
 
// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = 
         (struct Graph*) malloc(sizeof(struct Graph) );
    graph->V = V;
    graph->E = E;
 
    graph->edge = 
       (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );
 
    return graph;
}
 
// A utility function used to print the solution
void printArr(int* dist, int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
 
// The main function that finds shortest distances from src to
// all other vertices using Bellman-Ford algorithm.  The function
// also detects negative weight cycle

void BellmanFord(int V, int** input, int src)
{
    int E = 0;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if ((input[i][j] != INF) && (input[i][j] != 0)) {
                E++;
            }
        }
    }
    
    
    Graph* graph = createGraph(V, E);
    
    int k = 0;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if ((input[i][j] != INF) && (input[i][j] != 0)) {
                graph->edge[k].src = i;
                graph->edge[k].dest = j;
                graph->edge[k].weight = input[i][j];
                k++;
            }
        }
    }
    
    
    //int V = graph->V;
    //int E = graph->E;
    int* dist = new int[V];
 
    // Step 1: Initialize distances from src to all other vertices
    // as INFINITE
    for (int i = 0; i < V; i++)
        dist[i]   = INT_MAX;
    dist[src] = 0;
 
    // Step 2: Relax all edges |V| - 1 times. A simple shortest 
    // path from src to any other vertex can have at-most |V| - 1 
    // edges
    for (int i = 1; i <= V-1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
 
    // Step 3: check for negative-weight cycles.  The above step 
    // guarantees shortest distances if graph doesn't contain 
    // negative weight cycle.  If we get a shorter path, then there
    // is a cycle.
    for (int i = 0; i < E; i++)
    {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            printf("Graph contains negative weight cycle");
    }
 
   // printArr(dist, V);
 
    return;
}
 
