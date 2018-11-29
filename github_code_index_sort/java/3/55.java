package com.hrishikeshmishra.ns.graph;

import com.hrishikeshmishra.ns.stack.LinkedStack;
import com.hrishikeshmishra.ns.stack.Stack;

import java.util.*;
import java.util.stream.Collectors;

/**
 * Topological Sort
 *
 * @author hrishikesh.mishra
 * @link http://hrishikeshmishra.com/topological-sort/
 */
public class TopologicalSort {

    public <V> List<V> sortRecursive(Digraph<V> digraph) {
        List<V> topologicalOrder = new ArrayList<>();
        VertexInDegreeCounter vertexInDegreeCounter = new VertexInDegreeCounter(digraph);
        Set<V> zeroInDegreeVertices = getZeroInDegreeVertices(digraph);
        if (zeroInDegreeVertices.isEmpty()) throw new RuntimeException("Graph has loop.");
        zeroInDegreeVertices.stream().forEach(vertex -> sortRecursive(topologicalOrder, vertex, digraph, vertexInDegreeCounter));
        return topologicalOrder;
    }

    private <V> void sortRecursive(List<V> topologicalOrder, V vertex, Digraph<V> digraph, VertexInDegreeCounter vertexInDegreeCounter) {
        topologicalOrder.add(vertex);
        for (V outgoingVertex : digraph.getOutboundNeighbors(vertex)) {
            vertexInDegreeCounter.decreaseInDegreeCountByOne(outgoingVertex);
            if (!vertexInDegreeCounter.hasMoreInDegree(outgoingVertex))
                sortRecursive(topologicalOrder, outgoingVertex, digraph, vertexInDegreeCounter);
        }
    }

    public <V> List<V> sortNonRecursive(Digraph<V> digraph) {
        List<V> topologicalOrder = new ArrayList<>();
        Stack<V> stack = new LinkedStack<>();

        getZeroInDegreeVertices(digraph).forEach(stack::push);
        VertexInDegreeCounter vertexInDegreeCounter = new VertexInDegreeCounter(digraph);

        if (stack.isEmpty())
            throw new RuntimeException("Graph has loop.");

        while (!stack.isEmpty()) {
            V vertex = stack.pop();
            topologicalOrder.add(vertex);
            for (V outgoingVertex : digraph.getOutboundNeighbors(vertex)) {
                vertexInDegreeCounter.decreaseInDegreeCountByOne(outgoingVertex);
                if (!vertexInDegreeCounter.hasMoreInDegree(outgoingVertex))
                    stack.push(outgoingVertex);

            }
        }

        return topologicalOrder;
    }

    private <V> Set<V> getZeroInDegreeVertices(Digraph<V> digraph) {
        return digraph.getVertices().
                stream().
                filter(vertex -> digraph.getInboundNeighbors(vertex).size() == 0).
                collect(Collectors.toCollection(() -> new LinkedHashSet<>()));
    }

    private static class VertexInDegreeCounter<V> {
        private final Map<V, Integer> vertexInDegreeCountMap;

        private VertexInDegreeCounter(Digraph<V> digraph) {
            vertexInDegreeCountMap = getVertexInDegreeCountMap(digraph);
        }

        public void decreaseInDegreeCountByOne(V vertex) {
            vertexInDegreeCountMap.put(vertex, vertexInDegreeCountMap.get(vertex) - 1);
        }

        public boolean hasMoreInDegree(V vertex) {
            return (vertexInDegreeCountMap.get(vertex) > 0);
        }

        private <V> Map<V, Integer> getVertexInDegreeCountMap(Digraph<V> digraph) {
            Map<V, Integer> vertexInDegreeCountMap = new HashMap<>();
            for (V vertex : digraph.getVertices())
                vertexInDegreeCountMap.put(vertex, digraph.inDegree(vertex));
            return vertexInDegreeCountMap;
        }

    }
}


class TopologicalSortTest {

    public static void main(String[] args) {
        Digraph<Integer> graph = new Digraph<>();

        graph.addVertex(7);
        graph.addVertex(5);
        graph.addVertex(3);
        graph.addVertex(11);
        graph.addVertex(8);
        graph.addVertex(2);
        graph.addVertex(9);
        graph.addVertex(10);

        graph.addEdge(3, 8);
        graph.addEdge(3, 10);
        graph.addEdge(5, 11);
        graph.addEdge(7, 11);
        graph.addEdge(7, 8);
        graph.addEdge(11, 2);
        graph.addEdge(11, 9);
        graph.addEdge(11, 10);
        graph.addEdge(8, 9);

        System.out.println("Graph:\n" + graph);

        TopologicalSort topologicalSort = new TopologicalSort();
        System.out.println("\n\nNon-Sort: " + topologicalSort.sortNonRecursive(graph));
        System.out.println("\n\nRecursive Sort: " + topologicalSort.sortRecursive(graph));


    }
}