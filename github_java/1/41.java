package com.algo.quiz;

import edu.princeton.cs.algs4.Graph;
import edu.princeton.cs.algs4.Queue;

public class BFS {

  private static final int INFINITY = Integer.MAX_VALUE;
  public boolean[] marked;
  public int[] edgeTo;
  public int[] distTo;

  public BFS(Graph g, int s) {
    marked = new boolean[g.V()];
    distTo = new int[g.V()];
    edgeTo = new int[g.V()];
  }

  public void bfs(Graph G, int s) {
    Queue<Integer> q = new Queue<Integer>();
    for (int v = 0; v < G.V(); v++) {
      distTo[v] = INFINITY;
    }
    distTo[s] = 0;
    marked[s] = true;
    q.enqueue(s);
    while (!q.isEmpty()) {
      int v = q.dequeue();
      for (int w : G.adj(v)) {
        if (!marked[w]) {
          edgeTo[w] = v;
          distTo[w] = distTo[v] + 1;
          marked[w] = true;
        }
      }
    }
  }

  public boolean hasPathTo(int v) {
    return marked[v];
  }

  public int distTo(int v) {
    return distTo[v];
  }
}
