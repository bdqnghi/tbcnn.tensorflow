package kata.java;

import java.util.ArrayDeque;
import java.util.HashSet;
import java.util.Iterator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Set;
import java.util.stream.Collectors;

public class MinimumSpanningTree
        implements Iterable<WeightEdge> {
    private final Iterable<WeightEdge> tree;

    private MinimumSpanningTree(Iterable<WeightEdge> tree) {
        this.tree = tree;
    }

    public static MinimumSpanningTree create(EdgeWeightedGraph graph) {
        if (graph.numberOfEdges() < 1) {
            throw new RuntimeException();
        }
        return new MinimumSpanningTree(new LazySpanningTreeBuilder(graph).buildTree());
    }

    @Override
    public Iterator<WeightEdge> iterator() {
        return tree.iterator();
    }

    private static class LazySpanningTreeBuilder {
        private final Set<Integer> marked = new HashSet<>();
        private final Queue<WeightEdge> priority = new PriorityQueue<>();
        private final Queue<WeightEdge> tree = new ArrayDeque<>();
        private final EdgeWeightedGraph graph;

        private LazySpanningTreeBuilder(EdgeWeightedGraph graph) {
            this.graph = graph;
        }

        private Iterable<WeightEdge> buildTree() {
            visit(graph, graph.startingVertex());
            while (!priority.isEmpty()) {
                WeightEdge edge = priority.poll();
                int v = edge.either();
                int w = edge.other(v);
                if (!marked.contains(v) || !marked.contains(w)) {
                    tree.add(edge);
                    if (!marked.contains(v)) {
                        visit(graph, v);
                    }
                    if (!marked.contains(w)) {
                        visit(graph, w);
                    }
                }
            }
            return tree;
        }

        private void visit(EdgeWeightedGraph graph, int vertex) {
            marked.add(vertex);
            priority.addAll(graph.adjacentTo(vertex)
                    .filter(edge -> !marked.contains(edge.other(vertex)))
                    .collect(Collectors.toList()));
        }
    }
}
