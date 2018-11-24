// Single Souce Shortest Path
// Bellman-Ford algorithm.

// PSEUDO CODE:
INITIALIZE-SINGLE-SOURCE(G, s)
1  for each vertex v in V[G]
2       do d[v] = oo
3          prev[v] = NIL
4  d[s] = 0

RELAX(u, v, w)
1  if d[v] > d[u] + w(u, v)
2     then d[v] = d[u] + w(u, v)
3          prev[v] = u

BELLMAN-FORD(G, w, s)
1  INITIALIZE-SINGLE-SOURCE(G, s)
2  for i = 1 to |V[G]| - 1
3    do for each edge (u, v) in E[G]
4      do RELAX(u, v, w)
5  for each edge (u, v) in E[G]
6    do if d[v] > d[u] + w(u, v)
7      then return FALSE
8  return TRUE

