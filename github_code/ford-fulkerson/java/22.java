package com.pkgG;

import java.util.LinkedList;
import java.util.Queue;

public class FordFulkerson {

	public static void main(String[] args) {
		int graph[][] = { { 0, 16, 13, 0, 0, 0 }, { 0, 0, 10, 12, 0, 0 },
				{ 0, 4, 0, 0, 14, 0 }, { 0, 0, 9, 0, 0, 20 },
				{ 0, 0, 0, 7, 0, 4 }, { 0, 0, 0, 0, 0, 0 } };

		FordFulkerson flow = new FordFulkerson();
		int maxPath = flow.fordFulkerson(graph);
		System.out.println(maxPath);
	}

	/**
	 * This Implementation of Ford Fulkerson Algorithm is called Edmonds-Karp
	 * Algorithm.
	 * 
	 * @param graph
	 * @return
	 */
	private int fordFulkerson(int[][] graph) {
		int N = graph.length;

		int[][] residual = new int[N][N];
		for (int i = 0; i < graph.length; i++) {
			for (int j = 0; j < graph.length; j++) {
				residual[i][j] = graph[i][j];
			}
		}

		int[] parent = new int[N];
		for (int i = 0; i < parent.length; i++) {
			parent[i] = -1;
		}

		int maxFlow = 0;
		int s = 0;
		int t = graph.length - 1;

		while (bfs(residual, parent, s, t)) {

			int pathFlow = Integer.MAX_VALUE;

			// Min weight edge to select
			for (int v = t; v != s; v = parent[v]) {
				int u = parent[v];
				pathFlow = Math.min(residual[u][v], pathFlow);
			}

			for (int v = t; v != s; v = parent[v]) {
				int u = parent[v];
				residual[u][v] -= pathFlow;
				residual[v][u] += pathFlow;
			}

			maxFlow += pathFlow;
		}

		return maxFlow;
	}

	private boolean bfs(int[][] residual, int[] parent, int s, int t) {
		boolean[] visited = new boolean[residual.length];

		Queue<Integer> queue = new LinkedList<Integer>();
		queue.add(s);
		visited[s] = true;

		while (!queue.isEmpty()) {
			int u = queue.poll();

			for (int v = 0; v < residual.length; v++) {
				if (visited[v] == false && residual[u][v] > 0) {
					parent[v] = u;
					queue.add(v);
					visited[v] = true;
				}
			}
		}

		return (visited[t] == true);
	}
}
