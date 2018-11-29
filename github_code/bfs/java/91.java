package com.abhi.study.dsa.graphs;

import com.abhi.study.dsa.heaps.PriorityQueue;

import java.util.*;

/**
 * @author abhishek
 * @version 1.0, 5/3/17
 */
public class Graph {

    private int[][] graph = null;
    private Vertex[][] wGraph = null;
    private BfsInfo[] bfsInfos = null;

    public Graph(int[][] adjList) {
        this.graph = adjList;
        this.bfsInfos = new BfsInfo[graph.length];
    }

    public Graph(Vertex[][] adjList) {
        this.wGraph = adjList;
        this.bfsInfos = new BfsInfo[wGraph.length];
    }

    public void doBfs(int source) {
        for (int i = 0; i < graph.length; i++) {
            bfsInfos[i] = new BfsInfo(null, null);
        }

        bfsInfos[source].dist = 0; // prev for source will remain null
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(source);

        while (!queue.isEmpty()) {
            int u = queue.poll();
            for (int v : graph[u]) {
                if (bfsInfos[v].dist == null) {
                    queue.offer(v);
                    bfsInfos[v].dist = bfsInfos[u].dist + 1;
                    bfsInfos[v].prev = u;
                }
            }
        }
    }

    public List<Integer> shortestPath(int source, int dest) {
        List<Integer> result = new ArrayList<>();
        while (dest != source) {
            result.add(dest);
            dest = bfsInfos[dest].prev;
        }
        result.add(dest);
        Collections.reverse(result);
        return result;
    }

    public void fastestPathDijkstra(int source) {
        for (int i = 0; i < wGraph.length; i++) {
            // vertex, distance, prev
            bfsInfos[i] = new BfsInfo(i, Integer.MAX_VALUE, null);
        }
        bfsInfos[source].dist = 0; // set source dist 0
        PriorityQueue<BfsInfo> queue = new PriorityQueue<>(8);
        queue.build(bfsInfos); // add to PQ with distance as priority

        while (!queue.isEmpty()) {
            BfsInfo u = queue.extractMin();
            u.settled = true; // mark settled
            bfsInfos[u.v] = u; // no longer checked for dist

            for (Vertex neighV : wGraph[u.v]) {
                BfsInfo v = bfsInfos[neighV.v];
                if (!v.settled && u.dist + neighV.w < v.dist) {
                    BfsInfo vNew = new BfsInfo(neighV.v, u.dist + neighV.w, u.v);
                    queue.changePriority(v, vNew);
                    bfsInfos[neighV.v] = vNew;
                }
            }
        }
    }

    public BfsInfo[] getBfsInfos() {
        return bfsInfos;
    }

    public static void main(String[] args) {
        int[][] adjList = new int[][]{
                {1},
                {0, 4, 5},
                {3, 4, 5},
                {2, 6},
                {1, 2},
                {1, 2, 6},
                {3, 5},
                {}
        };
        Graph graph = new Graph(adjList);
        graph.doBfs(3);
        Arrays.stream(graph.getBfsInfos()).forEach(n -> System.out.println(n));
        System.out.println(graph.shortestPath(3, 0));
        System.out.println(graph.shortestPath(3, 1));
        System.out.println(graph.shortestPath(3, 5));
        System.out.println(graph.shortestPath(3, 6));
        System.out.println(graph.shortestPath(3, 3));

        Vertex[][] adjListWeighted = new Vertex[][]{
                {new Vertex(1, 4)},
                {new Vertex(0, 4), new Vertex(4, 8), new Vertex(5, 6)},
                {new Vertex(3, 5), new Vertex(4, 4), new Vertex(5, 7)},
                {new Vertex(2, 5), new Vertex(6, 3)},
                {new Vertex(1, 8), new Vertex(2, 4)},
                {new Vertex(1, 6), new Vertex(2, 7), new Vertex(6, 12)},
                {new Vertex(3, 3), new Vertex(5, 12)},
                {}
        };
        graph = new Graph(adjListWeighted);
        graph.fastestPathDijkstra(0);
        Arrays.stream(graph.getBfsInfos()).forEach(n -> System.out.println(n));
    }

    static class BfsInfo implements PriorityQueue.Priorityable {
        public Integer v;
        public Integer dist;
        public Integer prev;
        public boolean settled;

        public BfsInfo(Integer dist, Integer prev) {
            this.dist = dist;
            this.prev = prev;
        }

        public BfsInfo(Integer v, Integer dist, Integer prev) {
            this.v = v;
            this.dist = dist;
            this.prev = prev;
        }

        @Override
        public int priority() {
            return dist;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;

            BfsInfo bfsInfo = (BfsInfo) o;

            if (settled != bfsInfo.settled) return false;
            if (v != null ? !v.equals(bfsInfo.v) : bfsInfo.v != null) return false;
            if (dist != null ? !dist.equals(bfsInfo.dist) : bfsInfo.dist != null) return false;
            return prev != null ? prev.equals(bfsInfo.prev) : bfsInfo.prev == null;

        }

        @Override
        public int hashCode() {
            int result = v != null ? v.hashCode() : 0;
            result = 31 * result + (dist != null ? dist.hashCode() : 0);
            result = 31 * result + (prev != null ? prev.hashCode() : 0);
            result = 31 * result + (settled ? 1 : 0);
            return result;
        }

        @Override
        public String toString() {
            return "BfsInfo{" +
                    "v=" + v +
                    ", dist=" + dist +
                    ", prev=" + prev +
                    ", settled=" + settled +
                    '}';
        }
    }

    static class Vertex {
        public int v;
        public int w;

        public Vertex(int v, int w) {
            this.v = v;
            this.w = w;
        }
    }
}
