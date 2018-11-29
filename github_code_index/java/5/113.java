package pathfinder.algorithm;

import java.util.LinkedList;
import java.util.Stack;

import pathfinder.representations.graph.IGraph;
import pathfinder.representations.graph.Path;

//Straight-forward iterative DFS implementation using a stack
public class DepthFirstSearch<E> extends AbstractPathFinder<E> {
	final private Stack<E> _s;
	
	public DepthFirstSearch() {
		super();
		
		_s = new Stack<E>();
	}
	@Override
	public Path<E> run(IGraph<E> graph, E origin, E destination) {
		initialize(graph, origin, destination);
		_s.push(_origin);
		markVertexAsVisited(_origin);
		
		while(!_s.isEmpty()) {
			E current = _s.pop();
			
			if (current.equals(destination)) {
				_foundDestination = true;
				break;
			}
			
			// iterate over current neighbors
			for (E neigh : _graph.adj(current)) {
				if (!vertexIsVisited(neigh)) {
					markVertexParent(neigh, current);
					markVertexAsVisited(neigh);
					_s.push(neigh);
				}
			}
		}
		
		//if the destination has been found, generate the path
		if (_foundDestination) {
			generatePath();
		}

		// TODO throw some exception here
		return _path;
	}
}
