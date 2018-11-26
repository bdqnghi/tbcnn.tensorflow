package kata.java;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Set;
import java.util.stream.Collectors;

public class MinimumSpanningTree implements Iterable<WeightedEdge> {

    private final Collection<WeightedEdge> tree;

    private MinimumSpanningTree(Collection<WeightedEdge> tree) {
        this.tree = tree;
    }

    public static MinimumSpanningTree create(EdgeWeightedGraph graph) {
        if (graph.numberOfEdges() < 1) {
            throw new RuntimeException();
        }
        return new MinimumSpanningTree(new LazySpanningTreeBuilder(graph).createTree());
    }

    @Override
    public Iterator<WeightedEdge> iterator() {
        return tree.iterator();
    }

    private static class LazySpanningTreeBuilder {
        private final Queue<WeightedEdge> priority = new PriorityQueue<>();
        private final Set<Integer> marked = new HashSet<>();
        private final EdgeWeightedGraph graph;

        LazySpanningTreeBuilder(EdgeWeightedGraph graph) {
            this.graph = graph;
        }

        Collection<WeightedEdge> createTree() {
            visit(graph.startingVertex());
            final Collection<WeightedEdge> tree = new ArrayList<>();
            while (!priority.isEmpty()) {
                WeightedEdge edge = priority.poll();
                int v = edge.either();
                int w = edge.other(v);
                if (!marked.contains(v) || !marked.contains(w)) {
                    tree.add(edge);
                    if (!marked.contains(v)) visit(v);
                    if (!marked.contains(w)) visit(w);
                }
            }
            return tree;
        }

        private void visit(int vertex) {
            marked.add(vertex);
            priority.addAll(
                    graph.adjacentTo(vertex).filter(e -> !marked.contains(e.other(vertex))).collect(Collectors.toList())
            );
        }
    }
}
