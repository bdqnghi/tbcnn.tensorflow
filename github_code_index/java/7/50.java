package com.sm.playground.graph;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Deque;
import java.util.List;

/**
 * 1. DFS with reverse port order (stack after recursion)
 * 2. stack contains sorted elements
 */
public class TopologicalSort {
  private int count;
  private List<Integer>[] adjList;
  private boolean[] visited;
  private Deque<Integer> stack = new ArrayDeque();

  public TopologicalSort(int count) {
    this.count = count;
    adjList = new ArrayList[count];
    visited = new boolean[count];
    for(int i = 0; i < count; i++) {
      adjList[i] = new ArrayList<>();
    }
  }

  public void addEdge(int first, int second) {
    checkGpaphIndex(first);
    checkGpaphIndex(second);
    adjList[first].add(second);
  }

  private void checkGpaphIndex(int vertex) {
    if (vertex < 0 || vertex >= count) {
      throw new IllegalArgumentException("Wrong graph vertex index: " + vertex);
    }
  }

  private void dfs(int vertex) {
    if (visited[vertex]) {
      return;
    }
    visited[vertex] = true;
    for(int i: adjList[vertex]) {
      if (!visited[i]) {
        dfs(i);
      }
    }
    stack.push(vertex);
  }

  public Collection<Integer> sort() {
    for(int i = 0; i < count; i++) {
      dfs(i);
    }
    return stack;
  }

  public static void main(String[] args) {
    TopologicalSort topologicalSort = new TopologicalSort(13);

    topologicalSort.addEdge(0, 5);
    topologicalSort.addEdge(0, 1);
    topologicalSort.addEdge(0, 6);
    topologicalSort.addEdge(5, 4);
    topologicalSort.addEdge(2, 0);
    topologicalSort.addEdge(0, 3);
    topologicalSort.addEdge(3, 5);
    topologicalSort.addEdge(6, 4);
    topologicalSort.addEdge(7, 6);
    topologicalSort.addEdge(6, 9);
    topologicalSort.addEdge(8, 7);
    topologicalSort.addEdge(9, 10);
    topologicalSort.addEdge(9, 11);
    topologicalSort.addEdge(9, 12);
    topologicalSort.addEdge(11, 12);

    System.out.println(">>> topologicalSort: " + topologicalSort.sort());

  }

}
