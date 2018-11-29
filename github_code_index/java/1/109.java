package search;

import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.Set;

import search.path.impl.Path;


public class BreadthFirstSearch<T extends Number & Comparable<T>, U> {
	
	private final Set<U> goal;
	private final Set<U> explored = new HashSet<U>();
	private final PriorityQueue<Path<T, U>> frontier = new PriorityQueue<Path<T, U>>();
	private final Problem<U> problem;
	private final Set<BreadthFirstSearchListener<T, U>> breadthFirstSearchListeners = new HashSet<BreadthFirstSearchListener<T, U>>();
	
	public BreadthFirstSearch(final Set<U> goal, final U initial,
			final Problem<U> problem) {
		this.goal = goal;
		this.frontier.offer(new Path<T, U>(null, initial));
		this.problem = problem;
	}
	
	public Path<T, U> search() {
		return search(new NoStopCriteria<T, U>());
	}

	public Path<T, U> search(StopCriteria<T, U> stopCriteria) {
		stopCriteria.init();
		
		while (true) {
			if (stopCriteria.isStop() || isFrontierEmpty()) {
				break;
			}
			Path<T, U> path = removeChoice();
			if (path == null || stopCriteria.isStop(path)) {
				break;
			}
			U end = path.getEnd();
			addToExplored(end);
			if (isGoal(end)) {
				return path;
			}
			
			for (U action : problem.getActions(end)) {
				addToFrontierUnlessNotAlreadyExplored(path, action);
			}
		}
		// TODO: avoid null
		return null;
	}

	public void addListener(
			BreadthFirstSearchListener<T, U> breadthFirstSearchListener) {
		breadthFirstSearchListeners.add(breadthFirstSearchListener);
	}

	public void removeListener(
			BreadthFirstSearchListener<T, U> breadthFirstSearchListener) {
		breadthFirstSearchListeners.remove(breadthFirstSearchListener);
	}

	private void addToFrontierUnlessNotAlreadyExplored(Path<T, U> path, U action) {
		if (!(isInExplored(action) || isInFrontier(action))) {
			Path<T, U> newPath = new Path<T, U>(path, action);
			frontier.offer(newPath);
			// addToExplored(action);
			for (BreadthFirstSearchListener<T, U> breadthFirstSearchListener : breadthFirstSearchListeners) {
				breadthFirstSearchListener.addPathPerformed(newPath);
			}
		}
	}

	private boolean isInExplored(U action) {
		return explored.contains(action);
	}

	private boolean isInFrontier(U action) {
		for (Path<T, U> path : frontier) {
			if (action.equals(path.getEnd()))
				return true;
		}
		return false;
	}

	private boolean isFrontierEmpty() {
		return frontier.isEmpty();
	}

	private void addToExplored(U end) {
		explored.add(end);
	}

	private boolean isGoal(final U head) {
		return goal.contains(head);
	}

	private Path<T, U> removeChoice() {
		return frontier.poll();
	}
}