package ca.wilkinsonlab.sadi.utils.graph;

import java.util.Collection;
import java.util.Collections;
import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Queue;
import java.util.Set;

/**
 * <p>Iterate through a graph using breadth first search.</p>
 * 
 * <p>Note: This iterator is not thread-safe.</p>
 * 
 * @author Ben Vandervalk
 *
 * @param <V> The type of nodes in the graph being traversed.    
 */
public class BreadthFirstIterator<V> extends OpenGraphIterator<V> {
	
	Queue<SearchNode<V>> BFSQueue;
	
	public BreadthFirstIterator(SearchNode<V> startNode) {
		this(Collections.singleton(startNode), null);
	}
	
	public BreadthFirstIterator(Collection<? extends SearchNode<V>> startNodes) {
		this(startNodes, null);
	}
	
	public BreadthFirstIterator(SearchNode<V> startNode, NodeVisitationConstraint<V> nodeVistationConstraint) {
		this(Collections.singleton(startNode), nodeVistationConstraint);
	}

	public BreadthFirstIterator(Collection<? extends SearchNode<V>> startNodes, NodeVisitationConstraint<V> nodeVistationConstraint) {
		super(nodeVistationConstraint);
		BFSQueue = new LinkedList<SearchNode<V>>();
		BFSQueue.addAll(startNodes);
	}

	@Override
	public boolean hasNext() {

		for(SearchNode<V> node = getQueue().peek(); node != null; node = getQueue().peek()) {
			if(nodeIsVisitable(node)) {
				return true;
			} else {
				getQueue().remove();
			}
		}
		return false;
	}

	@Override
	public V next() {
		
		for(SearchNode<V> node = getQueue().poll(); node != null; node = getQueue().poll()) {
			if(nodeIsVisitable(node)) {
				addVisitedNode(node);
				appendToQueue(node.getSuccessors());
				return node.getNode();
			}
		}
		throw new NoSuchElementException();
	}

	@Override
	public void remove() {
		throw new UnsupportedOperationException("remove() operation is not supported, this iterator is read-only");
	}


	protected Queue<SearchNode<V>> getQueue() {
		return BFSQueue;
	}
	
	protected void appendToQueue(Set<SearchNode<V>> nodes) {
		BFSQueue.addAll(nodes);
	}

}
