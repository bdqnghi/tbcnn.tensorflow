package de.graphioli.algorithms;

import de.graphioli.model.Graph;
import de.graphioli.model.Vertex;
import java.util.ArrayList;
import java.util.LinkedList;

/**
 * This class performs the breadth-first-search algorithm.
 * 
 * @author Team Graphioli
 */
public final class BreadthFirstSearch {
	private static ArrayList<Vertex> reachableVertex = new ArrayList<Vertex>();
	private static LinkedList<Vertex> queue = new LinkedList<Vertex>();

	/**
	 * Private empty constructor, to ensure that no instance is being created.
	 */
	private BreadthFirstSearch() {
	}

	/**
	 * The method performs the BFS algorithm. It needs a {@link Graph}, a start
	 * {@link Vertex} and a depth. The algorithms run as long as the depth
	 * hasn't reached 0 and as long as the queue isn't empty.
	 * 
	 * @param graph
	 *            the graph to perform BFS on
	 * @param vertex
	 *            the starting {@link Vertex}
	 * @param depth
	 *            the depth to perform BFS
	 * @return list of all vertices that can be reached within the given depth
	 */
	public static ArrayList<Vertex> performAlgorithm(Graph graph, Vertex vertex, int depth) {
	
		int curDepth = depth;
		if (graph != null && vertex != null && graph.getVertices().contains(vertex) && curDepth > -1) {
			reachableVertex = new ArrayList<Vertex>();
			queue = new LinkedList<Vertex>();
			LinkedList<Vertex> nextQueue = new LinkedList<Vertex>();
	
			Vertex tmpVertex = vertex;
			queue.add(tmpVertex);
	
			// Goes through the queue until the given depth is reached
			while (curDepth > 0) {
				Vertex queueVertex = queue.pop();
	
				// Adds the adjacent vertices to the queue and list of reachable
				// vertices
				for (Vertex adjacentVertex : queueVertex.getAdjacentVertices()) {
					if (!reachableVertex.contains(adjacentVertex)) {
						nextQueue.add(adjacentVertex);
						reachableVertex.add(adjacentVertex);
					}
				}
	
				if (queue.isEmpty()) {
					if (nextQueue.isEmpty()) {
						return reachableVertex;
					}
					// Next layer starts
					for (Vertex copy : nextQueue) {
						queue.add(copy);
					}
					nextQueue.clear();
					curDepth--;
				}
			}
			return reachableVertex;
		}
		return null;
	}
}
