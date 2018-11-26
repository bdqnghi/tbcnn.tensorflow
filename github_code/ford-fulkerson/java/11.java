package algoritm;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;

/**Class for checking if a graph is bipartite, and get maximum matching in the graph
 * Created by Jimmy on 2015-11-09.
 */
public class BipartiteMatching {

    /**
     * Method for checking the maximum mathing of a bipartite graph
     * @param graph the graph tocheck
     * @return list of edges in maximum matching
     * @throws Exception
     */
    public static LinkedList<Edge> runAlgorithm(Graph graph) throws Exception {
        HashSet<Vertex> x = new HashSet<>();
        HashSet<Vertex> y = new HashSet<>();

        Vertex s = new Vertex("Source");
        Vertex t = new Vertex("Sink");
        Graph g = new Graph();

        List<Edge> edges = graph.getEdges();
        for (Edge e: edges) {
                x.add(e.getFrom());
                y.add(e.getTo());
        }
        for (Vertex v: x) {
            if (y.contains(v)){
                throw new Exception("algoritm.Vertex can'texist in both sets \nalgoritm.Graph is not Bipartite");
            }
        }
        for (Vertex v: y) {
            if (x.contains(v)){
                throw new Exception("algoritm.Vertex can'texist in both sets \nalgoritm.Graph is not Bipartite");
            }
        }

        for (Vertex v: x) {
            g.addEdge(new Edge(s, v, 1));
            for (Edge e: edges){
                if(e.getFrom().equals(v)){
                    g.addEdge(new Edge(e.getFrom(),e.getTo(), 1));
                }
            }
        }
        for (Vertex v: y) {
            g.addEdge(new Edge(v, t,1));
        }

        LinkedList<Edge> bipartiteEdges = new LinkedList<>();
        for (Edge e: FordFulkerson.fordFulkerson(g, s, t)) {
            if (!e.getFrom().equals(s) && !e.getTo().equals(t)) {
                bipartiteEdges.add(e);
            }
        }
        return bipartiteEdges;
        //return algoritm.FordFulkerson.fordFulkerson(g, s, t);
    }


}
