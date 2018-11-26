package uk.co.alkanani.mst;

import uk.co.alkanani.domain.Edge;
import uk.co.alkanani.domain.Graph;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class MinimumSpanningTree {
    private final int initialEdge;

    public MinimumSpanningTree(int e) {
        initialEdge = e;
    }

    public Set<Edge> generateSpanningTree(Graph graph) {
        int nodeCount = graph.getNodes();
        Set<Edge> spanningTree = new HashSet<Edge>();
        Set<Integer> nodesInSpanningTree = new HashSet<Integer>();
        Edge[] edges = graph.getEdges();
        Arrays.sort(edges, new EdgeComparator());

        nodesInSpanningTree.add(initialEdge);

        while (nodesInSpanningTree.size() < nodeCount) {
            boolean found = false;
            int i = 0;

            while (!found) {
                if ( nodesInSpanningTree.contains( edges[i].getStart()) && !nodesInSpanningTree.contains(edges[i].getEnd()) ) {
                    spanningTree.add(edges[i]);
                    nodesInSpanningTree.add(edges[i].getEnd());
                    found = true;
                } else if ( nodesInSpanningTree.contains( edges[i].getEnd()) && !nodesInSpanningTree.contains(edges[i].getStart()) ) {
                    spanningTree.add(edges[i]);
                    nodesInSpanningTree.add(edges[i].getStart());
                    found = true;
                }
                i++;
            }
        }

        return spanningTree;
    }
}
