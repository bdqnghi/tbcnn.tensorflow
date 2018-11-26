package kata.java;

import java.util.ArrayDeque;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Set;
import java.util.stream.Collectors;

public class MinimumSpanningTree
        implements Iterable<WeightedEdge> {
    private final Collection<WeightedEdge> edges;

    private MinimumSpanningTree(Collection<WeightedEdge> edges) {
        this.edges = edges;
    }

    public static MinimumSpanningTree create(EdgeWeightedGraph graph) {
        if (graph.numberOfEdge() < 1) {
            throw new RuntimeException();
        }
        return new MinimumSpanningTree(new LazySpanningTreeBuilder(graph).buildTree());
    }

    @Override
    public Iterator<WeightedEdge> iterator() {
        return edges.iterator();
    }

    private static class LazySpanningTreeBuilder {
        private final EdgeWeightedGraph graph;
        private final Queue<WeightedEdge> priority = new PriorityQueue<>();
        private final Set<Integer> marked = new HashSet<>();

        public LazySpanningTreeBuilder(EdgeWeightedGraph graph) {
            this.graph = graph;
        }

        public Collection<WeightedEdge> buildTree() {
            final Queue<WeightedEdge> tree = new ArrayDeque<>();
            visit(graph.firstVertex());
            while (!priority.isEmpty()) {
                WeightedEdge edge = priority.poll();
                int v = edge.either();
                int w = edge.other(v);
                if (!marked.contains(v) || !marked.contains(w)) {
                    tree.add(edge);
                    if (!marked.contains(v)) {
                        visit(v);
                    }
                    if (!marked.contains(w)) {
                        visit(w);
                    }
                }
            }
            return tree;
        }

        private void visit(int vertex) {
            marked.add(vertex);
            priority.addAll(
                    graph.adjacentTo(vertex)
                            .filter(e -> !marked.contains(e.other(vertex)))
                            .collect(Collectors.toList())
            );
        }
    }
}
