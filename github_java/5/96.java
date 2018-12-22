package com.algorithmhelper.graphs.pathfinding;

import com.algorithmhelper.datastructures.hashing.HashMapLinearProbing;
import com.algorithmhelper.datastructures.hashing.HashSetLinearProbing;
import com.algorithmhelper.datastructures.lists.Stack;
import com.algorithmhelper.datastructures.lists.StackDynamicArray;
import com.algorithmhelper.datastructures.trees.Map;
import com.algorithmhelper.datastructures.trees.Set;
import com.algorithmhelper.graphs.graphs.Graph;

public class DepthFirstSearchRecursion<T extends Comparable<T>> {

    private Set<T> visited;
    private Map<T, T> predecessor;
    private int vertexCount;

    /**
     * Initializes the DepthFirstSearchRecursion and runs the depth first search
     * algorithm starting from vertex u.
     *
     * @param G, the graph
     * @param u, the starting vertex
     * @throws IllegalArgumentException if the graph G is null
     * @throws IllegalArgumentException if the vertex u is null
     */
    public DepthFirstSearchRecursion(Graph<T> G, T u) {
        if (G == null)
            throw new IllegalArgumentException("constructor with null graph G");
        if (u == null)
            throw new IllegalArgumentException("constructor with null vertex u");

        visited = new HashSetLinearProbing<>();
        predecessor = new HashMapLinearProbing<>();
        vertexCount = 0;
        predecessor.put(u, null);
        depthFirstSearch(G, u);
    }

    /**
     * Run the depth first search algorithm, building up the set of vertices visited.
     *
     * @param G, the graph
     * @param u, the starting vertex
     */
    private void depthFirstSearch(Graph<T> G, T u) {
        visited.put(u);
        vertexCount++;
        for (T v : G.getAdjacent(u)) {
            if (!visited.contains(v)) {
                predecessor.put(v, u);
                depthFirstSearch(G, v);
            }
        }
    }

    /**
     * Return the vertex count (i.e. the number of vertices visited by the depth first search
     * algorithm.
     *
     * @return vertexCount
     */
    public int getVertexCount() {
        return vertexCount;
    }

    /**
     * Return an Iterable to the vertices visited.
     *
     * @return an Iterable to the vertices visited
     */
    public Iterable<T> getVisited() {
        return visited.keys();
    }

    /**
     * Returns true if the vertex u has been visited by the depth first search algorithm,
     * false otherwise.
     *
     * @param u, the vertex
     * @return true if the vertex u has been visited by the depth first search algorithm,
     *         false otherwise
     * @throws IllegalArgumentException if the vertex u is null
     */
    public boolean isVisited(T u) {
        if (u == null)
            throw new IllegalArgumentException("isVisited with null vertex u");
        return visited.contains(u);
    }

    /**
     * Returns an Iterable to the path from the starting vertex for the depth first search
     * algorithm to the vertex u.
     *
     * @param u, the vertex
     * @return an Iterable to the path from the starting vertex for the depth first search
     *         algorithm to the vertex u
     * @throws IllegalArgumentException if the vertex u is null
     * @throws IllegalArgumentException if the vertex u is not contained in Set visited
     */
    public Iterable<T> getPath(T u) {
        if (u == null)
            throw new IllegalArgumentException("getPath with null vertex u");
        if (!isVisited(u))
            throw new IllegalArgumentException("getPath with non-existent vertex u");

        Stack<T> stack = new StackDynamicArray<>();
        T current = u;
        stack.push(current);
        while (predecessor.get(current) != null) {
            stack.push(predecessor.get(current));
            current = predecessor.get(current);
        }
        return stack;
    }
}
