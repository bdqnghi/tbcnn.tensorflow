package datastructures.graphs;

import java.util.Stack;

public class DepthFirstSearch {
	private Graph g;
	private boolean visited[];
	private int parent[];
	private int src;

	/**
	 * Count of Connected components
	 */
	private int connected;

	/**
	 * DFS traversal
	 * 
	 * @param g
	 * @param src
	 */
	public DepthFirstSearch(Graph g, int src) {
		this.g = g;
		this.src = src;
		visited = new boolean[g.getVerticesCount()];
		parent = new int[g.getVerticesCount()];
		dfsUtil(src);
	}

	private void dfsUtil(int src) {
		connected++;
		visited[src] = true;
		for (Edge edge : g.getAdjList(src)) {
			Integer vertice = edge.to();
			if (!visited[vertice]) {
				parent[vertice] = src;
				dfsUtil(vertice);
			}
		}
	}

	/**
	 * Returns path to destination from source if it exists
	 * 
	 * @param dest
	 * @return
	 */
	public Iterable<Integer> pathToDest(int dest) {
		if (!visited[dest])
			return null;
		Stack<Integer> pathStack = new Stack<>();
		for (int i = dest; i != src; i = parent[i]) {
			pathStack.push(i);
		}
		pathStack.push(src);
		return pathStack;
	}

	public void printPathTo(int dest) {
		if (!visited[dest]) {
			System.out.println("No Path");
		} else {
			for (int vertice : pathToDest(dest)) {
				System.out.print(vertice + "<-");
			}
			System.out.println();
		}
	}

	public int getCountOfConnectedComps() {
		return this.connected;
	}
}
