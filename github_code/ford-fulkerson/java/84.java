package com.example.ds.graph.maxflow.adjm;

import java.util.LinkedList;
import java.util.Queue;
/*============================================================
Back edges are necessary when doing the Ford-Fulkerson algorithm in case the path that you choose ends up not being a part of the overall flow.
As an example where back edges are necessary, consider this flow network:

    s
   / \
  a   b
   \ / \
    c   d
     \ /
      t
Assume that all edges point down and that all edges have capacity 1 and that you want to find a flow from s to t.
Suppose on the first iteration of Ford-Fulkerson that you take the path s -> b -> c -> t.
At this point, you've pushed one unit of flow from s to t. If you don't add in any back edges, you're left with this:

    s
   /
  a   b
   \   \
    c   d
       /
      t
There are no more s-t paths, but that doesn't mean you have a max flow.
You can push two units of flow from s to t by sending one along the path s -> a -> c -> t and the other along the path s -> b -> d -> t.
Without any back edges in the residual flow network, you would never discover this other path.

==============================================================*/
public class FordFulkerson {
    static int[] parent;

    static int findMaxFlow(Graph g, int src, int dest) {
        int N = g.adjMat.length;
        parent = new int[N];
        Graph rg = new Graph(g);
        int maxFlow = 0;
        while (hasAugmentedPath(rg, src, dest)) {
            int flow = Integer.MAX_VALUE;
            for (int i = dest; i != src; i = parent[i]) {
                flow = Math.min(flow, rg.adjMat[parent[i]][i]);
            }
            maxFlow += flow;
            for (int i = dest; i != src; i = parent[i]) {
                rg.adjMat[parent[i]][i] -= flow;
                rg.adjMat[i][parent[i]] += flow;
            }
        }
        return maxFlow;
    }


    static boolean hasAugmentedPath(Graph g, int src, int dest) {
        int[][] adjMat = g.adjMat;
        boolean[] visited = new boolean[adjMat.length];
        Queue<Integer> queue = new LinkedList<>();
        visited[src] = true;
        queue.offer(src);
        while (!queue.isEmpty()) {
            int u = queue.poll();
            for (int v = 0; v < adjMat.length; v++) {
                if (!visited[v] && adjMat[u][v] > 0) {
                    visited[v] = true;
                    parent[v] = u;
                    queue.offer(v);
                }
            }
        }
        return visited[dest];
    }
}
