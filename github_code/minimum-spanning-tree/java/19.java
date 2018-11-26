package uk.co.alkanani.mst;

import uk.co.alkanani.domain.Edge;
import uk.co.alkanani.domain.Graph;
import uk.co.alkanani.file.FileUtil;

import java.util.Set;

public class ResultGenerator {

    public static void main(String... args) {
        Graph graph = FileUtil.loadEdges("edges.txt");
        MinimumSpanningTree minimumSpanningTree = new MinimumSpanningTree(1);
        Set<Edge> mst = minimumSpanningTree.generateSpanningTree(graph);

        long totalCost = mst.stream().mapToLong(Edge::getCost).sum();

        System.out.print("Total minimum spanning tree cost: " +totalCost);

    }
}
