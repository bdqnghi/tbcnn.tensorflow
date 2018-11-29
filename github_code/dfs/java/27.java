package com.twb.graph;

import java.util.List;
import java.util.Stack;

// Equivalent to preorder tree traversal
public class DepthFirstSearch { // TODO add a visitor consumer to verify the order...
    public static void recursive(Graph g, int i) {
        boolean[] visited = new boolean[g.numVertices()];
        recursive(g, i, visited);
    }

    public static void recursive(Graph g, int i, boolean[] visited) {
        visited[i] = true;
        System.out.println(i);
        List<Integer> edges = g.getEdges(i);
        if (edges != null) {
            for (int e : edges) {
                if (!visited[e]) {
                    recursive(g, e, visited);
                }
            }
        }
    }

    public static void iterative(Graph g, int i) {
        boolean[] visited = new boolean[g.numVertices()];
        Stack<Integer> stack = new Stack<Integer>();
        stack.add(i);

        while (!stack.isEmpty()) {
            int v = stack.pop();
            if (!visited[v]) {
                visited[v] = true;
                System.out.println(v);
                List<Integer> edges = g.getEdges(v);
                if (edges != null) { // Look at left edges first
                    for (int j = edges.size() - 1; j >= 0; j--) {
                        stack.add(edges.get(j));
                    }
                }
            }
        }
    }

    public static void main(String[] args) {
        Graph g = new AdjacencyMatrix(7);
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(0, 4);
        g.addEdge(1, 3);
        g.addEdge(1, 5);
        g.addEdge(2, 6);
        g.addEdge(5, 4);

        System.out.println("recursive");
        recursive(g, 0);
        System.out.println("iterative");
        iterative(g, 0);

        // Expected values: 0 1 3 5 4 2 6
    }
}