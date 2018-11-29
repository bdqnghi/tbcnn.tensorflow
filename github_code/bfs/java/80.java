package graphs;

import java.util.LinkedList;
import java.util.Queue;

public class Bfs {
	private int v; // Number of vertices
	private LinkedList<Integer> adj[]; // Adjacency List

	Bfs(int num) {
		v = num;
		adj = new LinkedList[v];

		for (int i = 0; i < num; i++) {
			adj[i] = new LinkedList();
		}
	}

	// add edge to the nodes for the directed graph
	public void addEdgeDirected(int v, int w) {
		adj[v].add(w);
	}

	// add edge to the nodes for undirected graph
	public void addEdgeUndirected(int v, int w) {
		adj[v].add(w);

		if (v != w) // avoid twice for self loop
			adj[w].add(v);
	}

	public void start(int s) {
		boolean visited[] = new boolean[v];
		Queue<Integer> qs = new LinkedList();

		qs.add(s);
		visited[s] = true;

		while (!qs.isEmpty()) {

			int ele = qs.remove();

			System.out.println(ele);

			for (int i = 0; i < adj[ele].size(); i++) {
				if (!visited[adj[ele].get(i)]) {
					qs.add(adj[ele].get(i));
					visited[adj[ele].get(i)] = true;
				}
			}
		}
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Bfs g = new Bfs(4);

		System.out.println("the following is bfs for directed graph: ");
		g.addEdgeDirected(0, 1);
		g.addEdgeDirected(0, 2);
		g.addEdgeDirected(1, 2);
		g.addEdgeDirected(2, 0);
		g.addEdgeDirected(2, 3);
		g.addEdgeDirected(3, 3);

		g.start(2);

		Bfs ug = new Bfs(4);
		System.out.println("\nthe following is bfs for undirected graph: ");
		ug.addEdgeUndirected(0, 1);
		ug.addEdgeUndirected(0, 2);
		ug.addEdgeUndirected(1, 2);
		ug.addEdgeUndirected(2, 0);
		ug.addEdgeUndirected(2, 3);
		ug.addEdgeUndirected(3, 3);

		ug.start(2);

	}

}
