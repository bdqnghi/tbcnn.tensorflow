package arun.problems.ds.graphs;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;

public class BreadthFirstSearch<T> extends GraphSearch<T>{
	
	private Graph<T> graphToBeUsed;

	/**
	 * @param graph
	 */
	public BreadthFirstSearch(final Graph<T> graph) {
		this.graphToBeUsed = graph;
	}
	
	/**
	 * 
	 */
	public BreadthFirstSearch() {
		/* Nothing */
	}
	
	
	@Override
	public boolean searchElement(T vertex, Graph<T> grpah) {
		// TODO Auto-generated method stub
		return false;
	}

	/* (non-Javadoc)
	 * @see arun.problems.ds.graphs.GraphSearch#searchPath(java.lang.Object, java.lang.Object, arun.problems.ds.graphs.Graph)
	 */
	@Override
	public Collection<T> searchPath(T startingVertex, T endVertex, Graph<T> graph) {
		
		Collection<T> pathList = new ArrayList<T>();
		Graph<T> graphToBeSearched = graph;

		if(graph == null)
			return pathList;

		if(!graphToBeSearched.exists(startingVertex)
				|| !graphToBeSearched.exists(endVertex))
			return pathList;
		
		final HashSet<T> visitedElements = new HashSet<T>();
		final Queue<T> toVisitQueue = new LinkedList<T>();
		final Map<T, T> childToParentMap = new HashMap<T, T>();
		
		toVisitQueue.add(startingVertex);
		
		while(!toVisitQueue.isEmpty()) {
			
			T vertexInSearchContext = toVisitQueue.poll();
			
			System.out.println("BFS: Visiting Node: " + vertexInSearchContext);

			if(vertexInSearchContext.equals(endVertex)) {
				return getPathListFromVisitedMap(childToParentMap, vertexInSearchContext);
			}
			
			visitedElements.add(vertexInSearchContext);

			final Collection<T> neighbours = graphToBeSearched.getNeighbours(vertexInSearchContext);
			
			for(final T neighbour : neighbours) {
				if(!visitedElements.contains(neighbour)) {
					visitedElements.add(neighbour);
					toVisitQueue.add(neighbour);
					childToParentMap.put(neighbour, vertexInSearchContext);
				}
			}
			
		}
		
		return pathList;
	}


	/* (non-Javadoc)
	 * @see arun.problems.ds.graphs.GraphSearch#searchPath(java.lang.Object, java.lang.Object)
	 */
	@Override
	public Collection<T> searchPath(T startingVertex, T endVertex) {
		return searchPath(startingVertex, endVertex, graphToBeUsed);
	}

}
