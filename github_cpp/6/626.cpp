#include <iostream>
#include <vector>
using namespace std;
const int inf = 0x3f3f3f3f;

struct Edge {
	int from, to, cost;
	Edge(int f = 0, int t = 0, int c = 0) :from(f), to(t), cost(c) {}
};
int n, m; // n: num of vertex, m: num of edge

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;
	vector<int> dist(n + 1, inf);
	vector<Edge> p;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		p.push_back(Edge(u, v, w));
	}
	
	dist[1] = 0;	// assume that the start node is 1

	bool cycle = false;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			int now = p[j].from;
			int next = p[j].to;
			int ncost = p[j].cost;
			if (dist[next] > dist[now] + ncost) {
				dist[next] = dist[now] + ncost;
				if (i == n) {	// In non-cycle cases, the update is completed only n-1 times
					cycle = true;
					break;
				}
			}
		}
	}
	if (cycle);	// case that negative cycle exists
	else;		// else
}