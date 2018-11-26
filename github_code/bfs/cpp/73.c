#include "bfs.h"

/**
* Perform breath-first search on graph from vertex s, and compute BFS
* distance and pred vertex for all vertices in the graph.
*/ 
void bfs_search(Graph const &graph, int s,	/* in */
				vector<int> &dist, vector<int> &pred) /* out */
{
	// initialise dist and pred to mark vertices as unvisited. Begin at search
	// and mark as Gray since we haven't yet visited its neighbours.
	cont int n = graph.numVertices();
	pred.assign(n,-1);
	dist.assign(n,numeric_limits<int>::max());
	vector<vertexColor> color (n,white);
	
	dist[s]=0;
	color[s] = Gray;
	
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		
		/Explore neighbours of u to expand the search horizon
		for (VertexList::const_iterator c1 = graph.begin(u);
			c1 != graph.end(u); ++c1){
		int v = c1-> first;
		if (color[v] = White) {
			dist[v] = dist[u]+1;
			pred[v] = u;
			color[v] = Gray;
			q.push(v);
		}
	}
	
	q.pop();
	color[u] = Black;
	}
	}
	