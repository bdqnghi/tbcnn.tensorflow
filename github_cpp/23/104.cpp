#include <algorithm>
#include <limits>

template<int N, int M, class Flow>
struct FordFulkerson {
	int n, e, first[N], next[M], to[M], s, t, q[N], pre[N];
	Flow cap[M], flow;
	bool vis[N];
	void init(int _n, int _s, int _t) {
		n = _n, s = _s, t = _t;
		std::fill(first, first + n, -1);
		e = 0;
	}
	void add(int u, int v, Flow w) {
		next[e] = first[u], to[e] = v, cap[e] = w, first[u] = e++;
		next[e] = first[v], to[e] = u, cap[e] = 0, first[v] = e++;
	}
	Flow findPath() {
		std::fill(vis, vis + n, false);
		int st = 0, ed = 0;
		pre[s] = -1, q[ed++] = s, vis[s] = true;
		while (st != ed) {
			int u = q[st++];
			if (u == t) {
				break;
			}
			for (int edge = first[u]; edge != -1; edge = next[edge]) {
				int v = to[edge];
				if (!vis[v] && cap[edge] > 0) {
					pre[v] = edge, q[ed++] = v, vis[v] = true;
				}
			}
		}
		if (!vis[t]) {
			return 0;
		}
		Flow f = std::numeric_limits<Flow>::max();
		for (int u = t; pre[u] != -1; u = to[pre[u] ^ 1]) {
			f = std::min(f, cap[pre[u]]);
		}
		for (int u = t; pre[u] != -1; u = to[pre[u] ^ 1]) {
			cap[pre[u]] -= f;
			cap[pre[u] ^ 1] += f;
		}
		return f;
	}
	Flow solve() {
		flow = 0;
		while (true) {
			Flow f = findPath();
			if (!f) {
				break;
			}
			flow += f;
		}
		return flow;
	}
};

