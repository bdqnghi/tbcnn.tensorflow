package graph;

import java.util.LinkedList;

public class DepthFirstSearch {

	private int length = 0;

	private LinkedList<Integer> list[];
	boolean visited[];

	DepthFirstSearch(int length) {

		this.length = length;
		list = new LinkedList[length];
		visited = new boolean[length];
		for (int i = 0; i < length; i++) {
			list[i] = new LinkedList<Integer>();
		}
	}

	public void addEdge(int u, int v) {

		list[u].add(v);
	}

	public void depthFirstSearch(int v) {

		visited[v] = true;
		System.out.println(v);
		LinkedList<Integer> l = this.list[v];
		l.stream().forEach(node -> {
			if (!visited[node])
				depthFirstSearch(node);
		});

	}

	public static void main(String args[]) {
		DepthFirstSearch g = new DepthFirstSearch(4);

		g.addEdge(0, 1);
		g.addEdge(0, 2);
		g.addEdge(1, 2);
		g.addEdge(2, 0);
		g.addEdge(2, 3);
		g.addEdge(3, 3);

		g.visited[2] = true;
		g.depthFirstSearch(2);
	}

}
