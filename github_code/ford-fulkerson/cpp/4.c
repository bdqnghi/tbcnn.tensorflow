#pragma warning(disable:4996)
//
// Ford-Fulkerson's maximum flow 
// 
// Description:
//   Given a directed network G = (V, E) with edge capacity c: E->R.
//   The algorithm finds a maximum flow. 
//
// Algorithm:
//   Ford-Fulkerson's augmenting path algorithm
//
// Complexity:
//   O(m F), where F is the maximum flow value.
// 
// Verified:
//   AOJ GRL_6_A: Maximum Flow
//
// Reference:
//   B. H. Korte and J. Vygen (2008):
//   Combinatorial Optimization: Theory and Algorithms.
//   Springer Berlin Heidelberg. 
//

#include "MaxFlowFordFulkerson.h"

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

namespace SBR
{

	const int INF = 1 << 30;
	void Graph::AddEdge(int src, int dst, flow_type capacity) {
			adj[src].push_back({ src, dst, capacity, 0, adj[dst].size() });
			adj[dst].push_back({ dst, src, 0, 0, adj[src].size() - 1 });
	}
	int Graph::MaxFlow(int s, int t) {
		vector<bool> visited(n);
		function<Graph::flow_type(int, Graph::flow_type)> augment = [&](int u, Graph::flow_type cur) {
			if (u == t) return cur;
			visited[u] = true;
			for (auto &e : adj[u]) {
				if (!visited[e.dst] && e.capacity > e.flow) {
					flow_type f = augment(e.dst, min(e.capacity - e.flow, cur));
					if (f > 0) {
						matched[e.src].push_back(e.dst);
						//matched[e.dst] = e.src;
						e.flow += f;
						adj[e.dst][e.rev].flow -= f;
						return f;
					}
				}
			}
			return flow_type(0);
		};
		for (int u = 0; u < n; ++u)
			for (auto &e : adj[u]) e.flow = 0;

		flow_type flow = 0;
		while (1) {
			fill(all(visited), false);
			flow_type f = augment(s, INF);
			if (f == 0) break;
			flow += f;
		}
		return flow;
	}
	
	int mainTest() {
		for (int n, m; scanf("%d %d", &n, &m) == 2; ) {
			Graph g(n);
			for (int i = 0; i < m; ++i) {
				int u, v, w;
				scanf("%d %d %d", &u, &v, &w);
				g.AddEdge(u, v, w);
			}
			printf("%d\n", g.MaxFlow(0, n - 1));
			// printing those who are matched
			for (int i = 0; i < g.matched.size(); ++i)
			{
				for (int j = 0; j < g.matched[i].size(); ++j)
				if (g.matched[i][j] != UNMATCHED)
				{
					cout << "(i, j): (" << i << ", " << g.matched[i][j] << ")" << endl;
				}
			}
		}
		return 0;
	}
	
}