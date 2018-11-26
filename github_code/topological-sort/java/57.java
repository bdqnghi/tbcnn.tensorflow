package com.dlh.zambas.graph;

import java.util.Iterator;
import java.util.Stack;

public class TopologicalSort {
	public void addEdge(Graph graph, int v, int w) {
		graph.adjListArray[v].add(w);
	}

	public void topologicalSort(Graph graph) {
		Stack<Integer> stack = new Stack<>();
		boolean visited[] = new boolean[graph.vertex];

		for (int i = 0; i < graph.vertex; i++) {
			if (!visited[i])
				topologicalSortUtil(graph, i, visited, stack);
		}

		// Print contents of stack
		while (stack.empty() == false)
			System.out.print(stack.pop() + " ");
	}

	private void topologicalSortUtil(Graph graph, int vertex, boolean[] visited, Stack<Integer> stack) {
		visited[vertex] = true;
		int i;
		Iterator<Integer> it = graph.adjListArray[vertex].listIterator();
		while (it.hasNext()) {
			i = it.next();
			if (!visited[i]) {
				topologicalSortUtil(graph, vertex, visited, stack);
			}
		}
		stack.push(vertex);
	}

	public static void main(String[] args) {
		Graph g = new Graph(6);
		TopologicalSort topologicalSort = new TopologicalSort();
		/*topologicalSort.addEdge(g, 5, 2);
		topologicalSort.addEdge(g, 5, 0);
		topologicalSort.addEdge(g, 4, 0);
		topologicalSort.addEdge(g, 4, 1);
		topologicalSort.addEdge(g, 2, 3);
		topologicalSort.addEdge(g, 3, 1);
*/
		topologicalSort.addEdge(g, 3, 1);
		topologicalSort.addEdge(g, 2, 1);
		topologicalSort.addEdge(g, 4, 2);
		topologicalSort.addEdge(g, 5, 3);
		

		System.out.println("Following is a Topological " + "sort of the given graph");
		topologicalSort.topologicalSort(g);
	}
}
