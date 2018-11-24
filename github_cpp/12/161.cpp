#include<stdio.h>

// Number of vertices in the graph 
#define V 4 
  
/* Define Infinite as a large enough value. This value will be used 
  for vertices not connected to each other */
#define INF 99999 
  
// A function to print the solution matrix 
void printSolution(int dist[][V]); 

void floydWarshall(int graph[][V]) {
    int dist[V][V], i, j, k;

    for (i=0; i<V; i++) 
        for(j=0; j<V; j++)
            dist[i][j] = graph[i][j];

    /* Add all vertices one by one to the set of intermediate vertices
     * Before start of an iteration, we have shortest distances between all vertices in set {0, 1, 2, ..., k-1} as intermediate vertices.
     * After the end of an iteration, vertex no. k is added to the set of intermediate vertices and the set becomes {0, 1, 2, .. k} */

    for (k=0; k<V; k++) {
        for(i=0; i<V; i++) {
            for(j=0; j<V; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

	printSolution(dist);
}

void printSolution(int dist[][V]) 
{ 
    printf ("The following matrix shows the shortest distances"
            " between every pair of vertices \n"); 
    for (int i = 0; i < V; i++) 
    { 
        for (int j = 0; j < V; j++) 
        { 
            if (dist[i][j] == INF) 
                printf("%7s", "INF"); 
            else
                printf ("%7d", dist[i][j]); 
        } 
        printf("\n"); 
    } 
} 
  
// driver program to test above function 
int main() 
{ 
    /* Let us create the following weighted graph 
            10 
       (0)------->(3) 
        |         /|\ 
      5 |          | 
        |          | 1 
       \|/         | 
       (1)------->(2) 
            3           */
    int graph[V][V] = { {0,   5,  INF, 10}, 
                        {INF, 0,   3, INF}, 
                        {INF, INF, 0,   1}, 
                        {INF, INF, INF, 0} 
                      }; 
  
    // Print the solution 
    floydWarshall(graph); 
    return 0; 
} 
