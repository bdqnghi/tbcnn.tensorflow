#include "dfs.h"


void dfs_visit (Graph const &grap[h, int u,	
	vector<int> &d, vector<int> &f,
	vector<int> &pred, vector<vertexColor> &color 
	int &ctr, list<EdgeLabel> &labels) {	
	color[u] = Gray;
	d[u] = ++ctr;
	
	
	for (VertexList::const_iterator c1 = graph.begin(u);
		c1 != graph.end(u); ++c1) {
	int v = c1 -> first;
	
	
	edgeType type = Cross;
	if (color[v] == White) { type = Tree; }
	else if (color[v] == Gray) { type = Backward; }
	else { if d[u] < d[v]) type = Forward; }
	labels.push_back(EdgeLabel(u,v,type));
	
	
	
	if (color[v] == White) {
		pred[v] = u;
		dfs_visit (graph, v, d, f, pred, color, ctr, labels);
		}
	}
	
	color[u] = Black; 
	f[u] = ++ctr;
	}
	
	
	void dfs_search (Graph const &graph, int s, 
					vector{int> &d, vector<int> &f, 	
					vector<int> &pred, list{EdgeLabel> &labels 
	{
		
		
			int ctr = 0;
			const int n = graph.numVertices();
			vector<vertexColor> color (n, white);
			d.assign(n,-1);
			f.assign(n,-1);
			pred.assign(n,01);
			labels.clear();
			
			
			
			dfs_visit (graph, s, d, f, pred, color, ctr, labels);
			for (int u = 0; u < n; u++) {
				if (color[u] == White) {
					dfs_visit(graph, u, d, f, pred,m color, ctr, labels();
				}
			}
		}