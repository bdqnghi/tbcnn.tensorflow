package com.vivek.graph;

import java.util.*;

public class MinimumSpanningTree {

    public static void main(String[] args) {

        try (Scanner in = new Scanner(System.in)) {
            int n = in.nextInt();
            int m = in.nextInt();

            List<Graph.Vertex> vertices = new ArrayList<>();
            List<Graph.Edge> edges = new ArrayList<>();

            for (int i = 1; i <= n; i++) {
                vertices.add(new Graph.Vertex(i));
            }

            for (int i = 0; i < m; i++) {
                Graph.Vertex u = vertices.get(in.nextInt() - 1);
                Graph.Vertex v = vertices.get(in.nextInt() - 1);
                int w = in.nextInt();
                Graph.Edge e = new Graph.Edge(u, v, w);
                u.addAdjacentEdge(v, e);
                v.addAdjacentEdge(u, e);
                edges.add(e);
            }

            Graph graph = new Graph(vertices, edges);
            System.out.println(getMst(graph, vertices.get(in.nextInt() - 1)));

        }

    }


    static int getMst(Graph graph, Graph.Vertex start) {
        int cost = 0;

        final Set<Graph.Vertex> unvisited = new HashSet<>();
        unvisited.addAll(graph.getVertices());
        unvisited.remove(start);

        final Queue<Graph.Edge> edgesAvailable = new PriorityQueue<>();

        Graph.Vertex vertex = start;

        while (!unvisited.isEmpty()) {
            // Add all edges to unvisited vertices
            for (Graph.Edge e : vertex.getAdjacencyMap().values()) {
                if (unvisited.contains(e.getDest()) ||
                        unvisited.contains(e.getSrc()))
                    edgesAvailable.add(e);
            }

            // Remove the lowest cost edge
            Graph.Edge e = edgesAvailable.remove();
            while (!unvisited.contains(e.getDest()) && !unvisited.contains(e.getSrc())) {
                e = edgesAvailable.remove();
            }
            cost += e.getWeight();

            vertex = vertex != e.getDest() ? e.getDest() : e.getSrc();
            if (!unvisited.contains(vertex)) {
                for (Graph.Vertex v : unvisited) {
                    vertex = v;
                    break;
                }
            }
            unvisited.remove(vertex);
        }
        return cost;
    }

}