#include "bfs.h"

 
void bfs_search(Graph const &graph, int s,	
				vector<int> &dist, vector<int> &pred) 
{
	
	
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
	