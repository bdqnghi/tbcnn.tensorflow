const int INF = 0x3f3f3f3f;

int nno, ned;
struct edge {
	int u, v, cap, flow, next;
	edge(int _u, int _v, int _cap, int _next = -1) :
		u(_u), v(_v), cap(_cap), next(_next) { flow = 0; }
};
vector<edge> edges;
vector<int> first, prev;

bool bfs(int s, int t) {
	vector<int> vis(nno, 0);
	queue<int> q;
	prev = vector<int>(nno, -1);
	q.push(s), vis[s] = 1;
	while(!q.empty() && !vis[t]) {
		s = q.front(); q.pop();
		for(int i = first[s]; i != -1; i = edges[i].next) {
			if(!vis[edges[i].v] && edges[i].cap - edges[i].flow > 0) {
				q.push(edges[i].v), vis[edges[i].v] = 1;
				prev[edges[i].v] = i;
			}
		}
	}
	return vis[t];
}

int maxflow(int s, int t) {
	int mf = 0;
	while(bfs(s, t)) {
		int cf = INF;
		for(int i = prev[t]; i != -1; i = prev[edges[i].u])
			cf = min(cf, edges[i].cap - edges[i].flow);
		for(int i = prev[t]; i != -1; i = prev[edges[i].u])
			edges[i].flow += cf, edges[i^1].flow -= cf;
		mf += cf;
	}
	return mf;
}

void reset(int n) {
	nno = n, ned = 0, edges.clear();
	first = vector<int>(nno, -1);
}

void addedge(int u, int v, int cap) {
	edges.push_back(edge(u, v, cap, first[u])); first[u] = ned++;
	edges.push_back(edge(v, u,   0, first[v])); first[v] = ned++;
}
