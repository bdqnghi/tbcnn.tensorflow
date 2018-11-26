/**
 * Ford Fulkersen
 * @param s source
 * @param d destination
 * @param c capacity
 * @param f flow, init with 0
 * @return
 */
static int ff(int s, int d, int[][] c, int[][] f) {
	List<Integer> path = dfs(s, d, c, f, new boolean[c.length]); // find path
	if (path.size() < 2) {
		int flow = 0;
		for (int i = 0; i < f[s].length; i++) { // leaving flow of source
			flow += f[s][i];
		}
		return flow;
	}
	int cap = Integer.MAX_VALUE; // capacity of current path
	for (int i = 0; i < path.size() - 1; i++) {
		int a = path.get(i), b = path.get(i + 1);
		cap = Math.min(cap, c[a][b] - f[a][b]);
	}
	for (int i = 0; i < path.size() - 1; i++) { //update flow
		int a = path.get(i), b = path.get(i + 1);
		f[a][b] += cap;
		f[b][a] -= cap;
	}
	return ff(s, d, c, f); // tail recursion
}

/**
 * depth first search in flow network
 * @param s source
 * @param d destination
 * @param c capacity
 * @param f flow
 * @param v visited, init with false
 * @return
 */
static List<Integer> dfs(int s, int d, int[][] c, int[][] f, boolean[] v) {
	v[s] = true;
	if (s == d) { // destination found
		LinkedList<Integer> path = new LinkedList<Integer>();
		path.add(d);
		return path;
	}
	for (int i = 0; i < c[s].length; i++) {
		if (!v[i] && c[s][i] - f[s][i] > 0) {
			List<Integer> path = dfs(i, d, c, f, v);
			if (path.size() > 0) {
				((LinkedList<Integer>) path).addFirst(s);
				return path;
			}
		}
	}
	return ((List<Integer>) Collections.EMPTY_LIST);
}