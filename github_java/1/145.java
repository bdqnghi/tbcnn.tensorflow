package datastructures.graphs;

import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Stack;

/**
 * BFS of an unweighted graph
 * 
 * @author aaqib
 *
 */
public class BreadthFirstSearch {
	private Graph g;

	private boolean[] visited;
	private int[] dist;
	private int[] parent;
	private int src;

	public BreadthFirstSearch(Graph g, int src) {
		this.g = g;
		this.src = src;
		visited = new boolean[g.getVerticesCount()];
		initDistances();
		bfs(src);
	}

	/**
	 * Initializes BFS for traversal
	 */
	private void initDistances() {
		dist = new int[g.getVerticesCount()];
		parent = new int[g.getVerticesCount()];
		for (int i = 0; i < dist.length; i++) {
			dist[i] = Integer.MAX_VALUE;
		}
	}

	/**
	 * BFS traversal
	 * 
	 * @param src
	 */
	private void bfs(int src) {
		initDistances();
		Queue<Integer> q = new PriorityQueue<>();

		q.add(src);
		visited[src] = true;
		dist[src] = 0;
		parent[src] = 0;

		while (!q.isEmpty()) {
			int item = q.poll();
			visited[item] = true;
			for (Edge edge : g.getAdjList(item)) {
				Integer vertice = edge.to();
				if (!visited[vertice]) {
					visited[vertice] = true;
					parent[vertice] = item;
					q.add(vertice);
					dist[vertice] = dist[item] + 1;
				}
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

	public int[] getDistancesArray() {
		return this.dist;
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
}
