package kata.java;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Set;
import java.util.stream.Collectors;

public class MinimumSpanningTree implements Iterable<WeightEdge> {

    private final Collection<WeightEdge> weightEdges;

    private MinimumSpanningTree(Collection<WeightEdge> weightEdges) {
        this.weightEdges = weightEdges;
    }

    public static MinimumSpanningTree create(EdgeWeightGraph graph) {
        if (graph.numberOfEdges() < 1) {
            throw new RuntimeException();
        }
        return new MinimumSpanningTree(new LazySpanningTreeBuilder(graph).buildTree());
    }

    @Override
    public Iterator<WeightEdge> iterator() {
        return weightEdges.iterator();
    }

    private static class LazySpanningTreeBuilder {
        private final Queue<WeightEdge> priority = new PriorityQueue<>();
        private final Set<Integer> marked = new HashSet<>();
        private final EdgeWeightGraph graph;

        private LazySpanningTreeBuilder(EdgeWeightGraph graph) {
            this.graph = graph;
        }

        private Collection<WeightEdge> buildTree() {
            Collection<WeightEdge> tree = new ArrayList<>();
            visit(graph.startVertex());
            while(!priority.isEmpty()) {
                WeightEdge edge = priority.poll();
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
                    graph.adjacentTo(vertex).filter(e -> !marked.contains(e.other(vertex))).collect(Collectors.toList())
            );
        }
    }
}
