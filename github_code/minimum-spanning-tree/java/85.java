package algorithm;

import data.Edge;
import data.WeightedEdge;
import structure.UnionFind;

import java.util.*;

// this class handles computing minimum spanning trees in undirected graphs
// actually if the graph is not connected a minimum spanning forest is computed
public class MinimumSpanningTree {

    private final PriorityQueue<WeightedEdge<Integer>> edges;
    private final int size;

    // result fields
    private Set<WeightedEdge<Integer>> mstEdges;
    private int cost;

    // initialize with weights array, use -1 for non-existing edges
    public MinimumSpanningTree(int[][] weights) {
        int n = weights.length;
        this.size = n;
        this.edges = new PriorityQueue<>(n*n,
                Comparator.comparing(e -> e.weight));
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                if (weights[i][j] != -1) {
                    this.edges.add(new WeightedEdge<>(i,j,weights[i][j]));
                }
            }
        }
    }

    // initialize with number of vertices and a collection of weighted edges
    public MinimumSpanningTree(int n, Collection<WeightedEdge<Integer>> edges) {
        this.edges = new PriorityQueue<>(n*n,
                Comparator.comparing(e -> e.weight));
        this.edges.addAll(edges);
        this.size = n;
    }

    // compute a MST using Kruskal's algorithm
    public void computeMST() {
        this.mstEdges = new HashSet<>();
        UnionFind uf = new UnionFind(this.size);

        while (!edges.isEmpty() && this.mstEdges.size() < this.size - 1) {
            WeightedEdge<Integer> top = edges.poll();
            if (uf.find(top.origin) != uf.find(top.target)) {
                uf.union(top.origin, top.target);
                this.cost += top.weight;
                this.mstEdges.add(top);
            }
        }
    }

    // get edges of mst
    public Set<WeightedEdge<Integer>> getEdges() {
       return this.mstEdges;
    }

    // get mst as graph
    public List<List<WeightedEdge<Integer>>> getMST() {
        List<List<WeightedEdge<Integer>>> adjacencyList = new ArrayList<>(this.size);
        for (int i = 0; i < this.size; ++i) {
            adjacencyList.add(new ArrayList<>());
        }
        for (WeightedEdge<Integer> edge : this.mstEdges) {
            adjacencyList.get(edge.origin).add(edge);
            adjacencyList.get(edge.target).add(new WeightedEdge<>(edge.target, edge.origin, edge.weight));
        }
        return adjacencyList;
    }

    // get cost of mst
    public int getCost() {
        return this.cost;
    }
}
