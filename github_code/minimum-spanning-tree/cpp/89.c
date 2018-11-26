// minimum-spanning-tree algorithms: prim

// PSEUDO CODE:
MST-PRIM(G, w, r)
1  for each u in V[G]
2    do key[u] = oo
3      prev[u] = NIL
4  key[r] = 0
5  Q = V[G]
6  while Q NOT EMPTY
7    do u = EXTRACT-MIN(Q)
8      for each v in Adj[u]
9        do if v in Q and w(u, v) < key[v]
10         then prev[v] = u
11              key[v] = w(u, v)


// CPP CODE:
void prim() {
	priority_queue< pair<int, int> > pq;
	vector<bool> visit(N, false);
	vector<int> dist(N, INT_MAX);
	dist[0] = 0;
	pq.push(make_pair(0, 0));
	while (!pq.empty()) {
		pair<int, int> p = pq.top();
		pq.pop();
		int u = p.second;
		if (visit[u]) continue;
		visit[u] = true;
		for (int v = 0; v < N; v++)	if (v != u && !visit[v]) {
			if (graph[u][v] < dist[v]) {
				dist[v] = graph[u][v];
				pq.push(make_pair(-dist[v], v));
			}
		}
	}
	int i, ans = 0;
	for (i = 0; i < N; i++) ans += dist[i];
	printf("The highest possible quality is 1/%d.\n", ans);
}

