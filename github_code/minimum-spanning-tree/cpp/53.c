// minimum-spanning-tree algorithms: kruskal.

// PSEUDO CODE:
MST-KRUSKAL(G, w)
1  A = NULL
2  for each vertex v in V[G]
3       do MAKE-SET(v)
4  sort the edges of E into nondecreasing order by weight w
5  for each edge (u, v) in E, taken in nondecreasing order by weight
6       do if FIND-SET(u) != FIND-SET(v)
7             then A = A | {(u, v)}
8                  UNION(u, v)
9  return A


// CPP CODE:
void kruskal() {
	int i, u, v, cnt;
	for (i = 0; i < cntNode; i++) make_set(i);
	// sort the edge in increasing order.
	qsort(edge, cntEdge, sizeof(Edge), cmp);
	for (i = 0; i < cntEdge ; i++) {
		int u = edge[i].u;
		int v = edge[i].v;
		if (find_set(u) != find_set(v)) {
			union_set(u, v);
		}
	}
}

