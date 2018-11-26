package com.sharpandrew.learndropwizard;

import com.google.common.collect.ImmutableSet;
import com.google.common.collect.Sets;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

public class MinimumSpanningTree {
    public static Set<Edge> minimumSpanningTree(Set<Edge> graph) {
        Set<Integer> vertices = getVertices(graph);
        return minimumSpanningTree(vertices, graph);
    }

    private static Set<Edge> minimumSpanningTree(Set<Integer> vertices, Set<Edge> edges) {
        Map<Integer, Set<Integer>> connectedComponents = vertices.stream()
                .collect(Collectors.toMap(i -> i, Sets::newHashSet));
        List<Edge> edgesByWeight = getEdgesByWeight(edges);
        Set<Edge> minimumSpanningTree = Sets.newHashSet();

        for (Edge edge : edgesByWeight) {
            if (connectedComponents.get(edge.getVertex1()).contains(edge.getVertex2())) {
                continue;
            } else {
                Set<Integer> updatedConnectedComponent = connectedComponents.get(edge.getVertex1());
                updatedConnectedComponent.add(edge.getVertex2());
                connectedComponents.put(edge.getVertex1(), updatedConnectedComponent);
                connectedComponents.put(edge.getVertex2(), updatedConnectedComponent);
                minimumSpanningTree.add(edge);
            }
        }

        return minimumSpanningTree;
    }

    private static Set<Integer> getVertices(Set<Edge> edges) {
        return edges.stream()
                .map(edge -> ImmutableSet.of(edge.getVertex1(), edge.getVertex2()))
                .flatMap(Set::stream)
                .collect(Collectors.toSet());
    }

    private static List<Edge> getEdgesByWeight(Set<Edge> edges) {
        return edges.stream().sorted(Comparator.comparingInt(Edge::getWeight)).collect(Collectors.toList());
    }

    private MinimumSpanningTree() {}
}
