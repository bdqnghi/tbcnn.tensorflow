package pathfinder.algorithm;

import java.util.LinkedList;
import java.util.Queue;

import pathfinder.representations.graph.IGraph;
import pathfinder.representations.graph.Path;

//Straight-forward BFS implementation using a queue
public class BreadthFirstSearch<E> extends AbstractPathFinder<E> {
	final private Queue<E> _q;
	
	public BreadthFirstSearch() {
		super();
		
		_q = new LinkedList<E>();
	}
	@Override
	public Path<E> run(IGraph<E> graph, E origin, E destination) {
		initialize(graph, origin, destination);
		
		_q.add(_origin);
		markVertexAsVisited(_origin);
		
		while(!_q.isEmpty()) {
			E current = _q.remove();
			
			//terminates if destination is found
			if (current.equals(destination)) {
				_foundDestination = true;
				break;
			}
			
			// iterate over current neighbors
			for (E neigh : _graph.adj(current)) {
				if (!vertexIsVisited(neigh)) {
					markVertexParent(neigh, current);
					markVertexAsVisited(neigh);
					_q.add(neigh);
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
