/* Ford-Fulkerson
 * Finds the max-flow in a flow graph. \\
 * Input: A source vertex $s$, a sink vertex $t$ and an adjacency matrix $G$. \\
 * Output: The value of the max-flow $f$.
 ** Ef
 */
//START
public static int fordFulkerson(int s, int t, int[][] G) {
	int maxFlow = 0;
	while (true) { // as long as we can find a new path
		List<Integer> path = new LinkedList<Integer>();
		if (!DFS(s, t, G, path, new LinkedList<Integer>()))
			break;
		// path found -> look for min edge
		int min = Integer.MAX_VALUE;
		for (int i = 0; i < path.size() - 1; i++) {
			int v = path.get(i);
			int w = path.get(i + 1);
			if (G[v][w] < min)
				min = G[v][w];
		}
		// remove min from path and add back edges
		for (int i = 0; i < path.size() - 1; i++) {
			int v = path.get(i);
			int w = path.get(i + 1);
			G[v][w] -= min;
			G[w][v] += min;
		}
		maxFlow += min;
	}
	return maxFlow;
}
//END
