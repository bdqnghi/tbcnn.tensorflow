package org.interview.datastructures.graph;

import org.interview.datastructures.graph.Graph.Vertex;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import static org.interview.datastructures.graph.Graph.Edge;
import static org.interview.datastructures.graph.Graph.Vertex.Color.BLACK;

public class MinimumSpanningTree {
    public static List<Vertex> mstPrim(Graph graph, Vertex startVertex) {
        if (startVertex == null) throw new IllegalArgumentException("Can't start traverse from null vertex");
        if (graph == null) throw new IllegalArgumentException("Graph is null");
        if (graph.graph.isEmpty()) throw new IllegalArgumentException("Graph is empty");
        if (!graph.graph.containsKey(startVertex)) throw new IllegalArgumentException("No such vertex in the graph");

        List<Vertex> mst = new ArrayList<>();
        LinkedList<Edge> edgesToProcess = new LinkedList<>();
        startVertex.setColor(BLACK);
        mst.add(startVertex);
        edgesToProcess.addAll(graph.getEdges(startVertex));
        while (!edgesToProcess.isEmpty()) {
            Edge minimumWeightEdge = getMinimumWeightEdge(edgesToProcess);

            minimumWeightEdge.to.setColor(BLACK);
            mst.add(minimumWeightEdge.to);

            addValidEdgesFromVertex(minimumWeightEdge.to, graph, edgesToProcess);
            removeInvalidEdgesFromProcessing(edgesToProcess, minimumWeightEdge);
        }
        return mst;
    }

    private static void removeInvalidEdgesFromProcessing(LinkedList<Edge> edgesToProcess, Edge minimumWeightEdge) {
        Iterator<Edge> it = edgesToProcess.iterator();
        while (it.hasNext()) {
            Edge edge = it.next();
            if (edge.to.getColor() == BLACK || edge.equals(minimumWeightEdge)) {
                it.remove();
            }
        }
    }

    private static void addValidEdgesFromVertex(Vertex vertex, Graph g, LinkedList<Edge> edgesToProcess) {
        for (Edge e : g.getEdges(vertex)) {
            if (e.to.getColor() != BLACK)
                edgesToProcess.add(e);
        }
    }

    private static Edge getMinimumWeightEdge(LinkedList<Edge> edgesToProcess) {
        Edge minimumWeightEdge = edgesToProcess.getFirst();
        for (Edge e : edgesToProcess) {
            if (minimumWeightEdge.weight > e.weight) minimumWeightEdge = e;
        }
        return minimumWeightEdge;
    }
}
