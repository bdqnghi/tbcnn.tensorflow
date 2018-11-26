package alex.algorithms.graphs;

import java.util.LinkedList;

/*
 * Minimum Cut and Maximum Flow
 Like Maximum Bipartite Matching, this is another problem which can solved using Ford-Fulkerson Algorithm. This is based on max-flow min-cut theorem.

 The max-flow min-cut theorem states that in a flow network, the amount of maximum flow is equal to capacity of the minimum cut. See CLRS book for proof of this theorem.

 From Ford-Fulkerson, we get capacity of minimum cut. How to print all edges that form the minimum cut? The idea is to use residual graph.

 Following are steps to print all edges of minimum cut.

 1) Run Ford-Fulkerson algorithm and consider the final residual graph.

 2) Find the set of vertices that are reachable from source in the residual graph.

 3) All edges which are from a reachable vertex to non-reachable vertex are minimum cut edges. Print all such edges.
 */
public class MinCut {
	/*
	 * Returns true if there is a path from source 's' to sink 't' in residual
	 * graph. Also fills parent[] to store the path
	 */
	boolean bfs(int residualGraph[][], int s, int t, int parent[]) {
		if (residualGraph == null)
			return false;
		int V = residualGraph.length;
		// Create a visited array and mark all vertices as not visited
		boolean visited[] = new boolean[V];
		// Create a queue, enqueue source vertex and mark source vertex
		// as visited
		LinkedList<Integer> q = new LinkedList<Integer>();
		q.push(s);
		visited[s] = true;
		parent[s] = -1;

		// Standard BFS Loop
		while (!q.isEmpty()) {
			int u = q.poll();

			for (int v = 0; v < V; v++) {
				if (visited[v] == false && residualGraph[u][v] > 0) {
					q.push(v);
					parent[v] = u;
					visited[v] = true;
				}
			}
		}

		// If we reached sink in BFS starting from source, then return
		// true, else false
		return visited[t];
	}

	// A DFS based function to find all reachable vertices from s. The function
	// marks visited[i] as true if i is reachable from s. The initial values in
	// visited[] must be false. We can also use BFS to find reachable vertices
	void dfs(int residualGraph[][], int s, boolean visited[]) {
		if (residualGraph == null)
			return;
		int V = residualGraph.length;
		visited[s] = true;
		for (int i = 0; i < V; i++)
			if (residualGraph[s][i] > 0 && !visited[i])
				dfs(residualGraph, i, visited);
	}

	// Prints the minimum s-t cut
	void minCut(int graph[][], int s, int t) {
		if (graph == null)
			return;
		int V = graph.length;
		int u, v;

		// Create a residual graph and fill the residual graph with
		// given capacities in the original graph as residual capacities
		// in residual graph
		int residualGraph[][] = new int[V][V]; // residualGraph[i][j] indicates
												// residual
		// capacity of edge i-j
		for (u = 0; u < V; u++)
			for (v = 0; v < V; v++)
				residualGraph[u][v] = graph[u][v];

		int parent[] = new int[V]; // This array is filled by BFS and to store
									// path

		// Augment the flow while tere is path from source to sink
		while (bfs(residualGraph, s, t, parent)) {
			// Find minimum residual capacity of the edhes along the
			// path filled by BFS. Or we can say find the maximum flow
			// through the path found.
			int pathFlow = Integer.MAX_VALUE;
			for (v = t; v != s; v = parent[v]) {
				u = parent[v];
				pathFlow = Math.min(pathFlow, residualGraph[u][v]);
			}

			// update residual capacities of the edges and reverse edges
			// along the path
			for (v = t; v != s; v = parent[v]) {
				u = parent[v];
				residualGraph[u][v] -= pathFlow;
				residualGraph[v][u] += pathFlow;
			}
		}

		// Flow is maximum now, find vertices reachable from s
		boolean visited[] = new boolean[V];
		dfs(residualGraph, s, visited);

		// Print all edges that are from a reachable vertex to
		// non-reachable vertex in the original graph
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				if (visited[i] && !visited[j] && graph[i][j] > 0)
					System.out.println(i + " - " + j);

		return;
	}

	public static void main(String[] args) {
		int graph[][] = { { 0, 16, 13, 0, 0, 0 }, { 0, 0, 10, 12, 0, 0 },
				{ 0, 4, 0, 0, 14, 0 }, { 0, 0, 9, 0, 0, 20 },
				{ 0, 0, 0, 7, 0, 4 }, { 0, 0, 0, 0, 0, 0 } };

		new MinCut().minCut(graph, 0, 5);
	}
}
