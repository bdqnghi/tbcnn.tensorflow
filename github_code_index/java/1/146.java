package com.twb.graph;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class BreadthFirstSearch {
    public static void iterative(Graph g, int i) {
        boolean[] visited = new boolean[g.numVertices()];
        Queue<Integer> queue = new LinkedList<>();
        queue.add(i);

        while (!queue.isEmpty()) {
            int v = queue.remove();
            if (!visited[v]) {
                visited[v] = true;
                System.out.println(v);
                List<Integer> edges = g.getEdges(v);
                if (edges != null) {
                    for (int e : edges) {
                        queue.add(e);
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

        iterative(g, 0);

        // Expected values: 0 1 2 4 3 5 6
    }
}