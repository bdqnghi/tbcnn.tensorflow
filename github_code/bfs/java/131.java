package mohamed.graphs;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import mohamed.graphs.SparseGraph.Vertex;
import mohamed.graphs.SparseGraph.Edge;

/**
 * @author Omar Mohamed
 */
public class BreadthFirstSearch implements GraphSearch<Vertex,Edge> {

    private HashMap hMIndex;
    private HashMap hMVisited;
    private HashMap hMFather;
    private LinkedList q;


    /**
     * Breadth-first visit of graph starting from the vertex passed as source
     *
     * @param graph graph where we want to use the search
     * @param source starting vertex of the visit
     * @param callback  object that analyse vertices and edges during the visit
     */
    public void search(Graph<Vertex, Edge> graph, Vertex source, SearchCallback<Vertex, Edge> callback) {
        graph.hasVertex(source);
        q = new LinkedList();
        ArrayList<Vertex> ALVertices = (ArrayList<Vertex>)graph.getVertices();
        hMIndex = new HashMap();
        hMVisited = new HashMap();
        hMFather = new HashMap();

        for (Iterator<Vertex> it = ALVertices.iterator(); it.hasNext();) {
            Vertex temp = it.next();
            hMIndex.put(temp, ALVertices.indexOf((Vertex)temp));
            hMVisited.put(temp, false);
            hMFather.put(temp, null);
        }
        hMFather.put(source, source);

        for(Vertex vertex: ALVertices)
            if(!(Boolean)hMVisited.get(vertex)) recursiveSearch(graph, vertex, callback);
    }

    /**
     * Auxiliary method, make recursively the visit of the vertices adjacent to "vertex",
     * implementing effectively the breadth-first visit
     *
     * @param graph graph where we want to use the search
     * @param source starting vertex of the visit
     * @param callback  object that analyse vertices and edges during the visit
     */
    private void recursiveSearch(Graph<Vertex, Edge> graph, Vertex source, SearchCallback<Vertex, Edge> callback){

        q.add(source);
        hMVisited.put(source, true);
        callback.onVisitingVertex(source);
        while(!q.isEmpty()){
            Vertex node = (Vertex)q.removeFirst();
            hMVisited.put(node,true);//end of the visit
            ArrayList<Vertex> neighbors = (ArrayList<Vertex>)graph.getNeighbours(node);
            if(neighbors!=null)
                for (Vertex neighbor : neighbors) {
                    if(!(Boolean)hMVisited.get(neighbor)){
                        hMVisited.put(neighbor,true);
                        hMFather.put(neighbor, node);
                        callback.onVisitingVertex(neighbor);
                        q.add(neighbor);
                    }
                }
        }
    }
}
