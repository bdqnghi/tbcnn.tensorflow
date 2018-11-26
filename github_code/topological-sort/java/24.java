package com.hrishikeshmishra.practices.graph;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.Stack;

import static com.hrishikeshmishra.practices.graph.TopologicalSort.Graph;
import static com.hrishikeshmishra.practices.graph.TopologicalSort.toplogicalSortWithStack;
import static com.hrishikeshmishra.practices.graph.TopologicalSort.topologicalSortRecursive;

/**
 * Problem:
 * Topological Sorting
 * Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices such
 * that for every directed edge uv, vertex u comes before v in the ordering.
 *;
 * Topological ordering lists vertices without violating dependencies.
 * ;
 * ;
 * Solution:
 * - There are two solutions - Recursive and Non-Recursive
 * - Recursive - We will create one map for vertex and in-degree, and each time we decrease value when it reaches zero
 * we add to sort list.
 * - Second method is to use stack and push at the end when even all adjacent node processed.
 *
 * @author hrishikesh.mishra
 * @link http://hrishikeshmishra.com/topological-sorting/
 */
public class TopologicalSort {

    public static class Graph {
        private int numberOfVertices;
        private List<Integer> adjacencyLists[];

        public Graph(int numberOfVertices) {
            this.numberOfVertices = numberOfVertices;
            init(numberOfVertices);
        }

        private void init(int numberOfVertices) {
            adjacencyLists = (List<Integer>[]) Array.newInstance(List.class, numberOfVertices);

            for (int i = 0; i < numberOfVertices; i++) {
                adjacencyLists[i] = new LinkedList<>();
            }
        }

        public void addEdge(int source, int destination) {
            adjacencyLists[source].add(destination);
        }

        @Override
        public String toString() {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < numberOfVertices; i++) {
                sb.append(i + " -> " + adjacencyLists[i] + "\n");
            }
            return sb.toString();
        }
    }

    /**
     * It works in reverse way
     * It pushes all those vertices who has not adjacent node first in
     * stack bottom
     *
     * @param graph
     * @return
     */
    public static List<Integer> toplogicalSortWithStack(Graph graph) {
        boolean[] visited = new boolean[graph.numberOfVertices];
        Stack<Integer> stack = new Stack<>();

        for (int currentVertex = 0; currentVertex < graph.numberOfVertices; currentVertex++) {
            if (!visited[currentVertex]) {
                toplogicalSortWithStack(graph, currentVertex, stack, visited);
            }
        }

        List<Integer> topologicalOrder = new ArrayList<>(graph.numberOfVertices);

        while (!stack.isEmpty()) {
            topologicalOrder.add(stack.pop());
        }

        return topologicalOrder;
    }

    private static void toplogicalSortWithStack(Graph graph, int currentVertex,
                                                Stack<Integer> stack, boolean[] visited) {

        visited[currentVertex] = true;

        for (Integer adjacentVertex : graph.adjacencyLists[currentVertex]) {

            if (!visited[adjacentVertex]) {
                toplogicalSortWithStack(graph, adjacentVertex, stack, visited);
            }
        }

        stack.push(currentVertex);
    }


    public static List<Integer> topologicalSortRecursive(Graph graph) {
        /** Get Vertex InDegree Map count **/
        Map<Integer, Integer> vertexInDegreeMap = getVertexInDegreeMap(graph);

        /** Zero InDegree vertices  **/
        Set<Integer> zeroInDegreeVertices = getZeroIndegreeVertices(vertexInDegreeMap);

        if (zeroInDegreeVertices.isEmpty()) {
            throw new RuntimeException("Not possible, not found any zero indegree vertices in graph.");
        }

        List<Integer> topologicalOrder = new ArrayList<>(graph.numberOfVertices);
        boolean[] visited = new boolean[graph.numberOfVertices];

        for (Integer vertexWithZeroIndegree : zeroInDegreeVertices) {
            topologicalSortRecursive(graph, vertexWithZeroIndegree, visited, topologicalOrder, vertexInDegreeMap);
        }

        return topologicalOrder;

    }

    private static void topologicalSortRecursive(Graph graph, Integer currentVertex, boolean[] visited,
                                                 List<Integer> topologicalOrder, Map<Integer, Integer> vertexInDegreeMap) {

        topologicalOrder.add(currentVertex);
        visited[currentVertex] = true;

        for (Integer adjacentVertex : graph.adjacencyLists[currentVertex]) {

            if (!visited[adjacentVertex]) {
                vertexInDegreeMap.put(adjacentVertex, vertexInDegreeMap.get(adjacentVertex) - 1);

                if (vertexInDegreeMap.get(adjacentVertex) == 0) {
                    topologicalSortRecursive(graph, adjacentVertex, visited, topologicalOrder, vertexInDegreeMap);
                }
            }
        }

    }

    private static Map<Integer, Integer> getVertexInDegreeMap(Graph graph) {
        Map<Integer, Integer> map = new HashMap<>();

        for (int sourceVertex = 0; sourceVertex < graph.numberOfVertices; sourceVertex++) {
            map.put(sourceVertex, 0);
        }

        for (int sourceVertex = 0; sourceVertex < graph.numberOfVertices; sourceVertex++) {
            for (Integer destination : graph.adjacencyLists[sourceVertex]) {
                map.put(destination, map.get(destination) + 1);
            }
        }

        return map;
    }

    private static Set<Integer> getZeroIndegreeVertices(Map<Integer, Integer> vertexInDegreeMap) {
        Set<Integer> set = new HashSet<>();
        for (Map.Entry<Integer, Integer> entry : vertexInDegreeMap.entrySet()) {
            if (entry.getValue() == 0) {
                set.add(entry.getKey());
            }
        }

        return set;
    }
}


class TopologicalSortTest {
    public static void main(String[] args) {
        Graph g = new Graph(6);
        g.addEdge(5, 2);
        g.addEdge(5, 0);
        g.addEdge(4, 0);
        g.addEdge(4, 1);
        g.addEdge(2, 3);
        g.addEdge(3, 1);

        System.out.println(g);
        List<Integer> topologicalOrder = topologicalSortRecursive(g);
        System.out.println(topologicalOrder);

        System.out.println(toplogicalSortWithStack(g));
    }
}