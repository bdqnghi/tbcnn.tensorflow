/*
 * Implementations of Ford-Fulkerson and Dinitz's algorithms for computing the
 * max flow through a graph.
 *
 * Ford-Fulkerson simply uses DFS to find augmenting paths, and has complexity
 * O(|E| * F), where F is the max flow.
 *
 * Dinitz's algorithm is a combination of Edmonds-Karp and Ford-Fulkerson. The
 * key observation is that in Edmonds-Karp, the lengths of the augmenting paths
 * increase monotonically. If we use BFS to compute the shortest path lengths
 * for the entire graph, then we can use DFS to simultaneously push flow along
 * all shortest paths at the same time. The overall performance becomes
 * O(|V|^2 * |E|), as opposed to O(|V| * |E|^2) for Edmonds-Karp.
 *
 * Quick usage notes and caveats:
 *
 *   * When F is small (much less than |V|^2), Ford-Fulkerson is faster;
 *     otherwise, Dinitz is faster.
 */

// Ford-Fulkerson
template <int V, typename T = int>
struct MaxFlowGraph {
T inf = numeric_limits<T>::max();

void add_edge(int i, int j, T c = 1) {
	Edge *e0 = new Edge{j, c, 0, nullptr}, *e1 = new Edge{i, 0, 0, nullptr};
	e0->r = e1, e1->r = e0;
	g[i].push_back(e0), g[j].push_back(e1);
}

T max_flow(int s, int t) {
	T ans = 0, f;
	while (f = dfs(s, t, inf)) {
		ans += f;
		clr0(seen);
	}
	return ans;
}

private:
struct Edge { int j; T c, f; Edge *r; };

vector<Edge*> g[V];
bool seen[V];

T dfs(int s, int t, T f) {
	if (s == t) return f;
	if (seen[s]) return 0;
	seen[s] = true;
	for (auto e : g[s]) if (e->c > e->f) {
		T f2 = dfs(e->j, t, min(f, e->c - e->f));
		if (f2) {
			e->f += f2, e->r->f -= f2;
			return f2;
		}
	}
	return 0;
}
};

// Dinitz
template <int V, typename T = int>
struct MaxFlowGraph {
T inf = numeric_limits<T>::max();

void add_edge(int i, int j, T c = 1) {
	Edge *e0 = new Edge{j, c, 0, nullptr}, *e1 = new Edge{i, 0, 0, nullptr};
	e0->r = e1, e1->r = e0;
	g[i].push_back(e0), g[j].push_back(e1);
}

T max_flow(int s, int t) {
	T ans = 0;
	while (bfs(s, t)) {
		rep (i, V) p[i] = g[i].begin();
		ans += dfs(s, t, inf);
	}
	return ans;
}

private:
struct Edge { int j; T c, f; Edge *r; };

vector<Edge*> g[V];
int q0[V], d[V];
typename vector<Edge*>::iterator p[V];

bool bfs(int s, int t) {
	clr1(d);
	d[q0[0] = s] = 0;
	for (int *i = q0, *q1 = q0 + 1; i < q1; i++)
	for (auto e : g[*i]) if (e->c > e->f && d[e->j] == -1)
		d[e->j] = d[*i] + 1, *(q1++) = e->j;
	return d[t] > -1;
}

T dfs(int i, int t, T f) {
	if (i == t) return f;
	T ans = 0;
	for (; p[i] != g[i].end(); p[i]++) {
		Edge *e = *p[i];
		if (e->c == e->f || d[e->j] != d[i] + 1) continue;
		T f2 = dfs(e->j, t, min(f, e->c - e->f));
		e->f += f2, e->r->f -= f2;
		ans += f2, f -= f2;
		if (!f) break;
	}
	return ans;
}
};
