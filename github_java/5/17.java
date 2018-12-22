static int[] dfs_low;
static int[] dfs_num;
static int[] dfs_parent;
static boolean[] articulation_vertex;
static final int UNVISITED = -1;
static int dfsNumberCounter;
static int dfsRoot;
static int rootChildren;
static LinkedList<int[]> bridges;
static LinkedList<Integer> articul;
static void articulationPointAndBridge(int u, LinkedList<Integer>[] g) {
  dfs_low[u] = dfs_num[u] = dfsNumberCounter++; // dfs_low[u] <= dfs_num[u]
  for(int v : g[u]) {
    if(dfs_num[v] == UNVISITED) { // a tree edge
      dfs_parent[v] = u;
      if(u == dfsRoot) rootChildren++; // special case if u is a root
      articulationPointAndBridge(v, g);
      if(dfs_low[v] >= dfs_num[u]) // for articulation point
        articulation_vertex[u] = true; // store this information first
      if(dfs_low[v] > dfs_num[u]) // for bridge
        bridges.add(new int[] {u,v});
      dfs_low[u] = Math.min(dfs_low[u], dfs_low[v]); // update dfs_low[u]
    }
    else if(v != dfs_parent[u]) // a back edge and not direct cycle
      dfs_low[u] = Math.min(dfs_low[u], dfs_num[v]); // update dfs_low[u]
  }
}

static void articulAndBridges(LinkedList<Integer>[] g) {
  bridges = new LinkedList<int[]>();
  articul = new LinkedList<Integer>();
  int n = g.length;
  dfsNumberCounter = 0;
  dfs_num = new int[n];
  Arrays.fill(dfs_num, UNVISITED);
  dfs_low = new int[n];
  dfs_parent = new int[n];
  articulation_vertex = new boolean[n];
  for(int i = 0; i < n; i++) {
    if (dfs_num[i] == UNVISITED) {
      dfsRoot = i; rootChildren = 0;
      articulationPointAndBridge(i,g);
      articulation_vertex[dfsRoot] = (rootChildren > 1); // special case
    }
  }
  for(int i = 0; i < n; i++)
    if(articulation_vertex[i])
      articul.add(i);
}
