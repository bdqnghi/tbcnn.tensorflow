
package Graphs;

import java.util.*;

public class TopologicalSort {

	// Sort vertices such that if (u,v) is an edge, u comes before v.
	// Only works on acyclic graph. Gives wrong output otherwise! O(E + V)
	static void dfs(List<Integer>[] g, boolean[] used, List<Integer> res, int u) {
		used[u] = true;
		for (int v : g[u]) {
			if (!used[v]) {
				dfs(g, used, res, v);
			}
		}
		res.add(u);
	}

	static List<Integer> topSort(List<Integer>[] g) {
		int n = g.length;
		boolean[] used = new boolean[n];
		List<Integer> res = new ArrayList<>();
		for (int i = 0; i < n; i++)
			if (!used[i])
				dfs(g, used, res, i);
		Collections.reverse(res);
		return res;
	}

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();

		for (int i = 0; i < n; i++) {
			int nV = in.nextInt();
			int nE = in.nextInt();
			List<Integer>[] g = new List[nV];

			for (int j = 0; j < g.length; j++) {
				g[j] = new ArrayList<>();
			}

			for (int j = 0; j < nE; j++) {
				int start = in.nextInt();
				int end = in.nextInt();
				g[start].add(end);
				// g[end].add(start); //If the graph is not directed.
			}

			List<Integer> order = topSort(g);
			// System.out.println(order); //Print array of components.
		}
	}
}