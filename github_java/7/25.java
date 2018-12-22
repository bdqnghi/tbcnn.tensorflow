package com.kmcho.com.geeks.graph.toposort;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Stack;

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
public class GfG2 {
    public static int[] topoSort(ArrayList<Integer> graph[], int N) {
        boolean[] visited = new boolean[N];
        Stack<Integer> stack = new Stack<>();

        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                sort(graph, i, visited, stack);
            }
        }

        int[] result = new int[stack.size()];
        int i = 0;
        while (!stack.isEmpty()) {
            result[i++] = stack.pop();
        }

        return result;
    }

    private static void sort(ArrayList<Integer> graph[], int start, boolean[] visited, Stack<Integer> stack) {
        visited[start] = true;

        Iterator<Integer> iterator = graph[start].iterator();
        while (iterator.hasNext()) {
            int next = iterator.next();
            if (!visited[next]) {
                sort(graph, next, visited, stack);
            }
        }

        stack.push(start);
     }
}
