package prim;

import java.util.HashMap;
import java.util.Map;

import prim.util.*;


public class MinimumSpanningTree {
	private Map<Edge, Integer> weights;
	private Map<Vertex, Edge> toEdge;
	private Vertex startVertex;
	private final UndirectedGraph g;


	public MinimumSpanningTree(UndirectedGraph g, Vertex root, Map<Edge, Integer> weights) {
		this.weights = weights;
		this.startVertex= root;
		this.g = g;
		this.toEdge = new HashMap<Vertex, Edge>();
	}

	/**
	 * This is where you will implement your solution.
	 * You should follow the steps outlined on the website and when this method 
	 *  is finished running, the toEdge map should be populated.
	 */
	public void run() {
		// FIXME
	}

	
	/**
	 * Return the length of the MST.  This method is completed for you.
	 * @return
	 */
	public int returnValue() {
		int pathValue = 0;
		for(Edge e : toEdge.values()) {
			pathValue += weights.get(e);
		}

		return pathValue;

	}
	
	/**
	 * Return the mapping of vertices to edges. This method is completed for you.
	 * @return
	 */
	public Map<Vertex, Edge> getToEdge() {
		return toEdge;
	}

}
