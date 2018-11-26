package utilities.algo;

import java.util.*;

public class MinimumSpanningTree
{
    public static WeightedGraph prim(WeightedGraph g, int s)
    {
        int[] dist = new int[g.vertexCount()];
        int[] parent = new int[g.vertexCount()];
        boolean[] visited = new boolean[g.vertexCount()];

        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[s] = 0;

        for (int i = 0; i < dist.length; i++) {
            int next = nextVertex(dist, visited);
            visited[next] = true;

            for (int v : g.getNeighbors(next)) {
                int d = g.getEdgeWeight(next, v);
                if (dist[v] > d) {
                    dist[v] = d;
                    parent[v] = next;
                }
            }
        }

        WeightedGraph mst = new WeightedGraph(g.vertexCount());
        for (int i = 1; i < g.vertexCount(); i++)
            mst.addUndirectedEdge(i, parent[i], g.getEdgeWeight(i, parent[i]));
        return mst;
    }

    private static int nextVertex(int[] dist, boolean[] visited)
    {
        int min = Integer.MAX_VALUE;
        int minVertex = -1;
        for (int v = 0; v < dist.length; v++) {
            if (!visited[v] && dist[v] < min) {
                minVertex = v;
                min = dist[v];
            }
        }
        return minVertex;
    }

    public static void main(String[] args)
    {
        WeightedGraph g = new WeightedGraph(7);
        g.addUndirectedEdge(0, 1, 7);
        g.addUndirectedEdge(0, 3, 5);
        g.addUndirectedEdge(1, 2, 8);
        g.addUndirectedEdge(1, 3, 9);
        g.addUndirectedEdge(1, 4, 7);
        g.addUndirectedEdge(2, 4, 5);
        g.addUndirectedEdge(3, 4, 15);
        g.addUndirectedEdge(3, 5, 6);
        g.addUndirectedEdge(4, 5, 8);
        g.addUndirectedEdge(4, 6, 9);
        g.addUndirectedEdge(5, 6, 11);

        WeightedGraph mst = prim(g, 0);
        System.out.println(mst);
    }
}
