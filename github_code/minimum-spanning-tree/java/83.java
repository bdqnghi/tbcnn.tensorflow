package org.hwer.engine.utilities.math;


import java.lang.IndexOutOfBoundsException;
import java.util.HashSet;

import org.hwer.engine.utilities.Utilities;


/**
 * @class MinimumSpanningTree
 * @brief Implements a mathematical, minimum spanning tree. Copying from
 *        https://en.wikipedia.org/wiki/Minimum_spanning_tree : \n\n
 *        Given a connected, undirected graph, a spanning tree of that graph is a sub-graph that is
 *        a tree and connects all the vertices together. A single graph can have many different
 *        spanning trees. We can also assign a weight to each edge, which is a number representing
 *        how unfavorable it is, and use this to assign a weight to a spanning tree by computing the
 *        sum of the weights of the edges in that spanning tree. A minimum spanning tree(MST) or
 *        minimum weight spanning tree is then a spanning tree with weight less than or equal to the
 *        weight of every other spanning tree.
 */
public class MinimumSpanningTree {
    /**
     * @brief Constructor
     *
     * @param connections
     *     The connections between the vertices of the MinimumSpanningTree
     */
    public MinimumSpanningTree (boolean[][] connections) {
        int numberOfVertices = connections.length;
        connections_ = new boolean[numberOfVertices][numberOfVertices];

        for (int i = 0; i < numberOfVertices; i++) {
            System.arraycopy(connections[i], 0, connections_[i], 0, numberOfVertices);
        }
    }

    /**
     * @brief Creates a MinimumSpanningTree using Kruskal's algorithm
     *
     * @param edgeWeights
     *     The weights of the edges of the graph
     * @param numberOfVertices
     *     The number of vertices on the graph
     *
     * @return The created MinimumSpanningTree
     */
    public static MinimumSpanningTree kruskal (double[] edgeWeights, int numberOfVertices) {
        if (numberOfVertices == 0) {
            return (new MinimumSpanningTree(new boolean[0][0]));
        }

        boolean[][] connections = new boolean[numberOfVertices][numberOfVertices];
        boolean[][] scope = new boolean[numberOfVertices][numberOfVertices];
        for (int i = 0; i < numberOfVertices; i++) {
            for (int j = 0; j < numberOfVertices; j++) {
                connections[i][j] = (i == j);
                scope[i][j] = (i == j);
            }
        }

        int[] sortedIndices = Utilities.sortArray(edgeWeights);

        // Use the first connection.
        int[] vertices = MinimumSpanningTree.connect(connections, sortedIndices[0]);
        scope = updateScope(scope, vertices[0], vertices[1]);

        for (int i = 1; i < sortedIndices.length; i++) {
            vertices = Utilities.vectorIndexToUpperTriangularIndices(connections.length,
                sortedIndices[i]);
            if (! scope[vertices[0]][vertices[1]]) {
                MinimumSpanningTree.connect(connections, sortedIndices[i]);
                scope = updateScope(scope, vertices[0], vertices[1]);

                if (Utilities.areAllTrue(scope)) {
                    break;
                }
            }
        }

        return (new MinimumSpanningTree(connections));
    }

    /**
     * @brief Returns true if the two given vertices are connected on this tree
     *
     * @param vertex1
     *     The first vertex
     * @param vertex2
     *     The second vertex
     *
     * @return True if the two given vertices are connected on this tree
     *
     * @throws IndexOutOfBoundsException If at least one of the vertices given is less that zero or
     *                                   greater or equal to the number of vertices.
     */
    public boolean areConnected (int vertex1, int vertex2) throws IndexOutOfBoundsException {
        if (vertex1 < 0 || vertex1 >= connections_.length ||
            vertex2 < 0 || vertex2 >= connections_.length) {
            throw new IndexOutOfBoundsException();
        }
        else {
            return connections_[vertex1][vertex2];
        }
    }

    /**
     * @brief Connects two vertices on a given graph
     *
     * @param connections
     *     The connections on the graph
     * @param vertex1
     *     The first vertex
     * @param vertex2
     *     The second vertex
     *
     * @throws IndexOutOfBoundsException
     *     If at least one of the vertices given is less than zero of greater of equal to
     *     the number of vertices.
     */
    public static void connect (boolean[][] connections, int vertex1, int vertex2)
        throws IndexOutOfBoundsException {
        if (vertex1 < 0 || vertex1 >= connections.length ||
            vertex2 < 0 || vertex2 >= connections.length) {
            throw new IndexOutOfBoundsException();
        }
        else {
            connections[vertex1][vertex2] = true;

            if (vertex1 != vertex2) {
                connections[vertex2][vertex1] = true;
            }
        }
    }

    /**
     * @brief Connects two vertices on a given graph
     *        The position of the vertices to be connected is provided by row-major, excluding the
     *        main diagonal representation.
     *
     * @param connections
     *     The graph
     * @param index
     *     The position of the vertices to be connected
     *
     * @return The corresponding matrix indices for the connected vertices
     */
    private static int[] connect (boolean[][] connections, int index) {
        int[] matrixIndices = Utilities.vectorIndexToUpperTriangularIndices(connections.length, index);

        MinimumSpanningTree.connect(connections, matrixIndices[0], matrixIndices[1]);

        return matrixIndices;
    }

    /**
     * @brief Returns all the possible unique paths upon the tree
     *        By unique, it is meant that, if path 0,1,2 is one of the returned paths, then 2,1,0
     *        will definitely not be in the returned paths.
     *
     * @param maxPathLength
     *     The maximum length of the paths
     *
     * @return All the possible unique paths upon the tree
     */
    public int[][] getUniquePaths (int maxPathLength) {
        return (Utilities.findUniquePaths(connections_, maxPathLength));
    }

    /**
     * @brief Returns the neighboring vertices of a group of vertices on the tree
     *
     * @param vertices
     *     The group of vertices
     *
     * @return The neighboring vertices of a group of vertices on the tree
     */
    public int[] getContext (int[] vertices) {
        return (Utilities.getContext(vertices, connections_));
    }

    /**
     * @brief Updates the scope of each vertex when a new connection is added to the tree
     *        Kruskal's algorithm, stops when there is a path from every vertex to every other
     *        vertex. That is when each vertex has in its scope, all the other vertices. This method
     *        will update the scope that Kruskal's algorithm keeps, for every vertex.
     *
     * @param scope
     *     The current scope of each vertex
     * @param row
     *     The first vertex of the new connection
     * @param column
     *     The second vertex of the new connection
     *
     * @return The updated scope of each vertex
     */
    public static boolean[][] updateScope (boolean[][] scope, int row, int column) {
        int numberOfVertices = scope.length;

        scope[row][column] = true;
        scope[column][row] = true;

        HashSet<Integer> vertexGroup = new HashSet<Integer>();
        vertexGroup.add(row);
        vertexGroup.add(column);
        int oldSize;
        int newSize = vertexGroup.size();

        do {
            oldSize = newSize;

            for (int i = 0; i < numberOfVertices; i++) {
                if (vertexGroup.contains(i)) {
                    continue;
                }

                for (Integer aVertexGroup : vertexGroup) {
                    if (scope[i][aVertexGroup]) {

                        for (Integer target : vertexGroup) {
                            scope[i][target] = true;
                            scope[target][i] = true;
                        }

                        vertexGroup.add(i);

                        break;
                    }
                }
            }

            newSize = vertexGroup.size();
        } while (oldSize != newSize);

        return scope;
    }

    public boolean[][] connections_; //!< The connections of this MinimumSpanningTree

}
