package graphadjacency;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

import disjointsets.DisjointSet;
import graphadjacency.GraphWeighted.Edge;


// Find the spanning tree edges using disjoint set.
// Prim's algorithm.
public class MinimumSpanningTree {

	public MinimumSpanningTree() {}
	
	public List<Edge> getMST(GraphWeightedUndirected g) {
		List<Edge> el = g.getAllEdges();	  // Getting the edge list. Duplicates are removed.	
		Collections.sort(el);    // Sort the edges.
		System.out.println("Sorted Edges: " + el);
		
		DisjointSet<String> ds = new DisjointSet<>();
		for(String v : g.vertices)
			ds.makeSet(v);
//		ds.makeSet("a");
//		ds.makeSet("b");
//		ds.makeSet("c");
//		ds.makeSet("d");
//		ds.makeSet("e");
//		ds.makeSet("f");
		
		List<Edge> result = new LinkedList<>();
		for(Edge e : el) {			
			String rootU = ds.findSet(g.vertices.get(e.u));
			String rootV = ds.findSet(g.vertices.get(e.v));
			if(rootU.equals(rootV)) {
				// Vertices are in the same set.
			} else {
				 result.add(e);   //  minimum weight edge.
				 ds.joinSet(rootU, rootV);
			}
		}
		return result;
	}
	
	public static void main(String[] args) {
		GraphWeightedUndirected g = new GraphWeightedUndirected();
		
		g.addVertex("a");
		g.addVertex("b");
		g.addVertex("c");
		g.addVertex("d");
		g.addVertex("e");
		g.addVertex("f");
		
		g.addEdge("a", "b", 3);
		g.addEdge("a", "d", 1);
		g.addEdge("b", "d", 3);
		g.addEdge("b", "c", 1);
		g.addEdge("c", "d", 1);
		g.addEdge("d", "e", 6);
		g.addEdge("e", "c", 5);
		g.addEdge("e", "f", 2);
		g.addEdge("f", "c", 4);		
		g.display();
		
		MinimumSpanningTree mst = new MinimumSpanningTree();
		System.out.println("MST Edges: " + mst.getMST(g));
	}

}
