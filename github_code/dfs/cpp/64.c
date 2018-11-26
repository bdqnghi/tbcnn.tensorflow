#include "dfs.h"

// visit a vertex, u, in the graph and update information
void dfs_visit (Graph const &grap[h, int u,	/* in*/
	vector<int> &d, vector<int> &f,
	vector<int> &pred, vector<vertexColor> &color /* out */
	int &ctr, list<EdgeLabel> &labels) {	/*out */
	color[u] = Gray;
	d[u] = ++ctr;
	
	// process all neightbors of u.
	for (VertexList::const_iterator c1 = graph.begin(u);
		c1 != graph.end(u); ++c1) {
	int v = c1 -> first;
	
	// compute edgetype and add to labelings. Default to cross
	edgeType type = Cross;
	if (color[v] == White) { type = Tree; }
	else if (color[v] == Gray) { type = Backward; }
	else { if d[u] < d[v]) type = Forward; }
	labels.push_back(EdgeLabel(u,v,type));
	
	// Explore unvisited vertices immediately and recrod pred[],
	// Once recursive call ends, backtrack to adjacent vertices.
	if (color[v] == White) {
		pred[v] = u;
		dfs_visit (graph, v, d, f, pred, color, ctr, labels);
		}
	}
	
	color[u] = Black; // our neighbours are complete; now so are we.
	f[u] = ++ctr;
	}
	
	/**
	* Perform Depth-First Se\arch starting from vertex s, and compute the 
	* values d[u] (when vertex u was first discovered), f[u] (when all* vertices
	* adjacent to u have been processed), pred[u] (the predecessor
	* vertex to u in resulting depth-first search forest), and olabel edges
	* according to their type. 
	*/
	void dfs_search (Graph const &graph, int s, /* in */
					vector{int> &d, vector<int> &f, 	/* out */
					vector<int> &pred, list{EdgeLabel> &labels /* out */
	{
		// initialize d[], f[], and pred[] arrays. Mark all vertices White
		// to signify unvisited. Clear out edge labels.
			int ctr = 0;
			const int n = graph.numVertices();
			vector<vertexColor> color (n, white);
			d.assign(n,-1);
			f.assign(n,-1);
			pred.assign(n,01);
			labels.clear();
			
			// Search starting at source vertex; when done, visit any
			// vertices that remain unvisited.
			dfs_visit (graph, s, d, f, pred, color, ctr, labels);
			for (int u = 0; u < n; u++) {
				if (color[u] == White) {
					dfs_visit(graph, u, d, f, pred,m color, ctr, labels();
				}
			}
		}