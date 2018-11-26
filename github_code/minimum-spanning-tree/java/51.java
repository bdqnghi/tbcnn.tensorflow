package com.carmatech.algo.graphs.operations;

import com.carmatech.algo.graphs.Edge;
import com.carmatech.algo.graphs.IWeightedGraph;
import com.carmatech.algo.unionfind.QuickUnion;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.function.Function;

public class MinimumSpanningTreeVisitor implements Function<IWeightedGraph<Edge>, List<Edge>> {

    @Override
    public List<Edge> apply(final IWeightedGraph<Edge> graph) {
        return Collections.unmodifiableList(
                (graph == null) ?
                new ArrayList<Edge>() :
                new KruskalAlgorithm(graph).minimumSpanningTree()
            );
    }

    private class KruskalAlgorithm {
        private final List<Edge> minimumSpanningTree = new ArrayList<>();
        private final IWeightedGraph<Edge> graph;
        private final QuickUnion components;
        private final Edge[] edges;

        private int currentEdge = 0;

        private KruskalAlgorithm(final IWeightedGraph<Edge> graph) {
            this.graph = graph;
            components = new QuickUnion(graph.numVertices());
            edges = graph.allEdges().toArray(new Edge[graph.numEdges()]); // Safe-copy
            Arrays.sort(edges);
        }

        private List<Edge> minimumSpanningTree() {
            while (!isTreeComplete()) {
                final Edge edge =  edges[currentEdge++];
                if (!createsCycle(edge))
                    add(edge);
            }
            return minimumSpanningTree;
        }

        private boolean isTreeComplete() {
            return (currentEdge == graph.numEdges()) || (minimumSpanningTree.size() == graph.numVertices() - 1);
        }

        private boolean createsCycle(final Edge edge) {
            return components.connected(edge.either(), edge.other());
        }

        private void add(final Edge edge) {
            components.union(edge.either(), edge.other());
            minimumSpanningTree.add(edge);
        }
    }
}
