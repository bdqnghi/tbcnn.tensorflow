package minimumSpanningTreeFinder;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * Represents the undirected graph.
 * @author sergeioff
 */
public class Graph {
    private int verticesNumber;
    private ArrayList<GraphEdge> graphEdges;
    private HashSet<Integer> connectedPoints;
    private int[][] adjacencyMatrix;

    /**
     * Creates new graph with specified number of vertices.
     * @param verticesNumber number of vertices in graph.
     */
    public Graph(int verticesNumber) {
        this.verticesNumber = verticesNumber;
        graphEdges = new ArrayList<>();
        connectedPoints = new HashSet<>();
        adjacencyMatrix = new int[verticesNumber][verticesNumber];
    }

    /**
     * Creates connection (edge) between points.
     * The order of points doesn't matter.
     * @param firstPoint first point of edge.
     * @param secondPoint second point of edge.
     * @param weight weight of edge.
     */
    public void addEdge(int firstPoint, int secondPoint, int weight) {
        graphEdges.add(new GraphEdge(firstPoint, secondPoint, weight));
        adjacencyMatrix[firstPoint][secondPoint] = 1;
        adjacencyMatrix[secondPoint][firstPoint] = 1;
        connectedPoints.add(firstPoint);
        connectedPoints.add(secondPoint);
    }

    /**
     * @see #addEdge(int, int, int)
     * @param edge graph edge.
     */
    private void addEdge(GraphEdge edge) {
        addEdge(edge.firstPoint, edge.secondPoint, edge.connectionWeight);
    }

    /**
     * @return adjacency matrix of graph.
     */
    public int[][] getAdjacencyMatrix() {
        return adjacencyMatrix;
    }

    /**
     * Returns a stream of graph edges which are available from specified vertex.
     * @param vertex vertex
     * @return <tt>Stream</tt> of graph edges
     */
    private Stream<GraphEdge> getAvailableEdgesFor(int vertex) {
        return graphEdges.stream().filter(graphEdge -> graphEdge.isContainsPoint(vertex));
    }

    /**
     * Returns graph edges sorted by weight which are available from specified vertices.
     * @param vertices vertices that already available.
     * @return sorted graph edges which are available from specified vertices.
     */
    private ArrayList<GraphEdge> getAvailableAndSortedGraphEdgesFor(HashSet<Integer> vertices) {
        Stream.Builder<GraphEdge> stream = Stream.builder();

        for (int vertex : vertices) {
            getAvailableEdgesFor(vertex).forEach(stream::accept);
        }

        return stream.build().sorted().collect(Collectors.toCollection(ArrayList<GraphEdge>::new));
    }

    /**
     * Checks if points are achievable.
     * @param firstPoint first point.
     * @param secondPoint second point.
     * @return <tt>true</tt> if points connected.
     */
    private boolean isPointsAlreadyAchievable(int firstPoint, int secondPoint) {
        return connectedPoints.contains(firstPoint) && connectedPoints.contains(secondPoint);
    }

    /**
     * Finds a minimum spanning tree for graph.
     * @return minimum spanning tree.
     */
    public Graph getMinimumSpanningTree() {
        Graph minimumSpanningTree = new Graph(verticesNumber);

        HashSet<Integer> spanningTreeConnectedPoints = minimumSpanningTree.connectedPoints;

        spanningTreeConnectedPoints.add(0);

        while (spanningTreeConnectedPoints.size() != minimumSpanningTree.verticesNumber) {
            ArrayList<GraphEdge> availableEdges = getAvailableAndSortedGraphEdgesFor(spanningTreeConnectedPoints);

            for (GraphEdge edge : availableEdges) {
                if (!minimumSpanningTree.isPointsAlreadyAchievable(edge.firstPoint, edge.secondPoint)) {
                    minimumSpanningTree.addEdge(edge);
                    break;
                }
            }
        }

        return minimumSpanningTree;
    }

    /**
     * Represents the edge of graph.
     */
    private class GraphEdge implements Comparable<GraphEdge> {
        private int firstPoint;
        private int secondPoint;
        private int connectionWeight;

        /**
         * Creates new graph edge
         * @param firstPoint first point of edge
         * @param secondPoint second point of edge
         * @param connectionWeight weight of edge
         */
        public GraphEdge(int firstPoint, int secondPoint, int connectionWeight) {
            this.firstPoint = firstPoint;
            this.secondPoint = secondPoint;
            this.connectionWeight = connectionWeight;
        }

        /**
         * Checks if edge contains the specified point.
         * @param point point of edge (vertex).
         * @return <tt>true</tt> if edge contains the specified point.
         */
        public boolean isContainsPoint(int point) {
            return firstPoint == point || secondPoint == point;
        }

        @Override
        public int compareTo(GraphEdge graphEdge) {
            return connectionWeight - graphEdge.connectionWeight;
        }

        @Override
        public String toString() {
            return firstPoint + ", " + secondPoint + " weight: " + connectionWeight;
        }
    }
}
