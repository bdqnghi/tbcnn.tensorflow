package com.kmcho.com.geeks.graph.toposort;

import java.util.*;

/**
 * https://practice.geeksforgeeks.org/problems/topological-sort/1
 *
 * Given a directed graph you need to complete the function topoSort
 * which returns an array having the topologically sorted elements of the array and takes two arguments.
 * The first argument is the Graph graph represented as adjacency list and
 * the second is the number of vertices N.
 *
 * Note : There can be multiple topological sorts of a Graph.
 * The driver program that calls your function doesn't match your output element by element,
 * but checks whether the output produced by your function is a valid topological sort or not.
 *
 * Input:
 * The first line of input takes the no of test cases then T test cases follow.
 * Each test case contains two lines.
 * The first line of each test case contains two integers E and N representing no of edges and the no of vertices.
 * Then in the next line are E pairs of integers u v representing an edge from u to v in the graph.
 *
 * Output:
 * For each test case output will be 1 if the topological sort is done correctly else it will be 0.
 *
 * Constraints:
 * 1<=T<=50
 * 1<=E,N<=50
 * 0<=u,v
 *
 * Example:
 *
 * Input
 * 1
 * 6 6
 * 5 0 5 2 2 3 4 0 4 1 1 3
 *
 * Output
 * 1
 *
 * The output 1 denotes that the order is valid.
 * So if you have implemented your function correctly, then output would be 1 for all test cases.
 */
class GfG {
    public static int[] topoSort(ArrayList<Integer> graph[], int N) {
        boolean[] visited = new boolean[N];
        Stack<Integer> path;
        Stack<Integer> output = new Stack<>();;

        List<Integer> startList = findStart(graph, N);
        Iterator<Integer> iterator = startList.iterator();

        List<Integer> outputList = new ArrayList<>();

        while (iterator.hasNext()) {
            int start = iterator.next();

            path = new Stack<>();

            DFS(graph, start, visited, path, output);
        }

        while (!output.isEmpty()) {
            int popped = output.pop();
            outputList.add(popped);
        }

        return outputList.stream().mapToInt(i->i).toArray();
    }

    private static List<Integer> findStart(ArrayList<Integer>[] graph, int N) {
        boolean[] hasParent = new boolean[N];
        for (int i = 0; i < N; i++) {
            Iterator<Integer> iterator = graph[i].iterator();
            while (iterator.hasNext()) {
                int n = iterator.next();
                hasParent[n] = true;
            }
        }

        List<Integer> startList = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            if (!hasParent[i]) startList.add(i);
        }
        return startList;
    }

    private static void DFS(ArrayList<Integer> graph[], int start, boolean[] visited, Stack<Integer> path, Stack<Integer> output) {
        if (visited[start]) {
            return;
        }
        visited[start] = true;
        path.push(start);

        Iterator<Integer> iterator = graph[start].iterator();

        while (iterator.hasNext()) {
            int next = iterator.next();

            DFS(graph, next, visited, path, output);

            while (path.peek() != start) {
                output.push(path.pop());
            }
        }
        output.push(path.pop());
    }


}
