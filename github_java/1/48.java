package ru.sazonovkirill.algorithms.graphs;

import ru.sazonovkirill.algorithms.graphs.domain.Edge;
import ru.sazonovkirill.algorithms.graphs.domain.Graph;

import java.util.*;

public class BreadthFirstSearch {
    private final Graph graph;

    private final List<List<Integer>> layers = new LinkedList<>();
    private int[] distances;

    public BreadthFirstSearch(Graph graph) {
        this.graph = graph;
        this.distances = new int[graph.getVerticesCount()];
    }

    public void search(int source) {
        layers.clear();
        distances = new int[graph.getVerticesCount()];

        Queue<Integer> q1 = new LinkedList<>();
        Queue<Integer> q2 = new LinkedList<>();
        Queue<Integer> currentQueue = q1;
        Queue<Integer> anotherQueue = q2;
        currentQueue.add(source);

        Set<Integer> visitedVertices = new HashSet<>();
        Set<Edge> visitedEdges = new HashSet<Edge>();

        int layerNumber = 0;
        while (!(q1.isEmpty() && q2.isEmpty())) {
            if (currentQueue.size() == 0) {
                currentQueue = q1.size() > 0 ? q1 : q2;
                anotherQueue = q1.size() == 0 ? q1 : q2;
                layerNumber++;
            }

            int currentVertex = currentQueue.poll();
            visitVertex(currentVertex);

            if (layerNumber >= layers.size()) layers.add(new ArrayList<>());
            layers.get(layerNumber).add(currentVertex);

            distances[currentVertex] = layerNumber;

            for (Edge edge : graph.getEdges(currentVertex)) {
                if (!visitedEdges.contains(edge)) {
                    visitEdge(edge);
                    visitedEdges.add(edge);

                    int anotherVertex =  edge.getAnotherVertex(currentVertex);
                    if (!visitedVertices.contains(anotherVertex)) {
                        anotherQueue.add(anotherVertex);
                        visitedVertices.add(anotherVertex);
                    }
                }
            }
        }
    }

    public int getLayersCount() {
        return layers.size();
    }

    public List<Integer> getLayer(int index) {
        return layers.get(index);
    }

    public int getDistanceToVertex(int vertex) {
        return distances[vertex];
    }

    private void visitVertex(int v) {
        System.out.println("Visiting vertex " + v);
    }

    private void visitEdge(Edge e) {
        System.out.println("Visiting edge " + e);
    }
}
