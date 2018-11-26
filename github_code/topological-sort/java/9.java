package org.interviewelements.graph;

import org.interviewelements.graph.Graph.AdjList;
import org.interviewelements.graph.Graph.Edge;

import java.util.ArrayList;
import java.util.Deque;
import java.util.LinkedList;
import java.util.List;

public class Topological {

    private static enum VertextType {
        WHITE, GRAY, BLACK
    };

    private List<VertextType> colors = new ArrayList<>();
    private Deque<Integer> stack = new LinkedList<>();

    private final Graph graph;

    public Topological(Graph graph) {
        this.graph = graph;

        for (int i = 0; i < graph.getVCount(); i++)
            colors.add(VertextType.WHITE);
    }

    /**
     * Sort graph.
     * 
     * @return <code>true</code> if no cycles are detected.
     */
    public boolean sort() {
        for (int i = 0; i < colors.size(); i++) {
            if (colors.get(i) == VertextType.WHITE) {
                boolean hasCycle = dfs(i);

                if (hasCycle)
                    return false;
            }
        }

        return true;
    }

    /**
     * Depth first search.
     * 
     * @param vertex
     *            Current vertex number.
     * @return <code>true</code> if graph has cycles.
     */
    private boolean dfs(int vertex) {

        if (colors.get(vertex) == VertextType.GRAY)
            return true;
        if (colors.get(vertex) == VertextType.BLACK)
            return false;

        colors.set(vertex, VertextType.GRAY);

        AdjList adjacencies = graph.getAdjacencies(vertex);

        for (Edge edge : adjacencies) {
            if (dfs(edge.to())) {
                return true;
            }
        }

        stack.push(vertex);
        colors.set(vertex, VertextType.BLACK);

        return false;
    }

    public static void main(String[] args) {
        Graph graph = new Graph(true, 4);
        graph.add(new Edge(0, 1));
        graph.add(new Edge(0, 2));
        graph.add(new Edge(1, 3));
        graph.add(new Edge(2, 3));

        Topological topological = new Topological(graph);
        topological.sort();

        Deque<Integer> s = topological.stack;

        while (!s.isEmpty()) {
            System.out.println(s.pop());
        }
    }
}
