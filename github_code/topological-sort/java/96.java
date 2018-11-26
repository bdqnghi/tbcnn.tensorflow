package com.algorithmhelper.graphs.pathfinding;

import com.algorithmhelper.datastructures.hashing.HashSetLinearProbing;
import com.algorithmhelper.datastructures.lists.Stack;
import com.algorithmhelper.datastructures.lists.StackDynamicArray;
import com.algorithmhelper.datastructures.trees.Set;
import com.algorithmhelper.graphs.graphs.DirectedGraph;

public class TopologicalSort<T extends Comparable<T>> {

    private Stack<T> topologicalOrdering;
    private Set<T> visited;

    /**
     * Initializes a TopologicalSort object and runs depth first search starting from some
     * arbitrary vertex u.
     *
     * @param G, the graph
     */
    public TopologicalSort(DirectedGraph<T> G) {
        if (G == null)
            throw new IllegalArgumentException("constructor with null graph G");

        topologicalOrdering = new StackDynamicArray<>();

        if (G.V() == 0)
            return;

        visited = new HashSetLinearProbing<>();
        for (T u : G.getVertices()) {
            if (visited.contains(u))
                continue;
            depthFirstSearch(G, u);
        }
    }

    /**
     * Run the depth first search algorithm, building up the set of vertices visited and the
     * topological ordering after the recursive calls to depthFirstSearch on vertex u's
     * neighbors.
     *
     * @param G, the graph
     * @param u, the starting vertex
     */
    private void depthFirstSearch(DirectedGraph<T> G, T u) {
        visited.put(u);
        for (T v : G.getAdjacent(u)) {
            if (!visited.contains(v)) {
                depthFirstSearch(G, v);
            }
        }
        topologicalOrdering.push(u);
    }

    /**
     * Returns an Iterable to the topological ordering found by the depth first search algorithm.
     *
     * @return an Iterable to the topological ordering found by the depth first search algorithm
     */
    public Iterable<T> getTopologicalOrdering() {
        return topologicalOrdering;
    }
}
