package model.search.uninformed;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;

import model.Action;
import model.Problem;
import model.search.Node;
import model.search.SearchStrategy;
import model.search.result.Failure;
import model.search.result.SearchResult;
import sun.reflect.generics.reflectiveObjects.NotImplementedException;


/**
 * Breadth-first graph search
 *
 */
public abstract class BreadthFirst {

	static final BreadthFirst factory = new BreadthFirst() {};
	
	public static SearchStrategy treeSearch() {
		throw new NotImplementedException();
		// return new TreeSearch();
	}

	public static SearchStrategy graphSearch() {
		return factory.new GraphSearch();
	}

	private class GraphSearch implements SearchStrategy {

		private Queue<Node> frontier;
		private Set<Node> explored;

		
		@Override
		public SearchResult search(Problem problem) {
			Node node = new Node(problem.initialState());
			if (problem.isGoal(node.state())) {
				return node.solution();
			}

			frontier = new LinkedList<Node>();
			frontier.add(node);
			explored = new HashSet<Node>();

			while (!frontier.isEmpty()) {
				node = frontier.poll();
				explored.add(node);
				for (Action action : problem.actions(node.state())) {
					Node child = node.child(problem, action);
					if (!frontier.contains(child) && !explored.contains(child)) {
						if (problem.isGoal(child.state())) {
							return child.solution();
						}
						frontier.add(child);
					}
				}
			}
			return new Failure();
		}
	}
}
