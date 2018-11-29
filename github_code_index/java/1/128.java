package sac.graph;

import java.util.Comparator;

/**
 * Breadth First Search algorithm.
 * 
 * @author Przemysław Klęsk (<a href="mailto:pklesk@wi.zut.edu.pl">wi.zut.edu.pl</a>)
 * @author Marcin Korzeń (<a href="mailto:mkorzen@wi.zut.edu.pl">wi.zut.edu.pl</a>)
 */
public class BreadthFirstSearch extends GraphSearchAlgorithm {

	/**
	 * Creates new instance of Breadth First Search algorithm.
	 * 
	 * @param initial reference to initial state
	 * @param configurator reference to configurator object
	 */
	public BreadthFirstSearch(GraphState initial, GraphSearchConfigurator configurator) {
		super(initial, configurator);
		setupOpenAndClosedSets(new BreadthFirstSearchComparator());
	}

	/**
	 * Creates new instance of Breadth First Search algorithm.
	 * 
	 * @param initial reference to initial state
	 */
	public BreadthFirstSearch(GraphState initial) {
		this(initial, null);
	}

	/**
	 * Creates new instance of Breadth First Search algorithm.
	 */
	public BreadthFirstSearch() {
		this(null, null);
	}

	/**
	 * Comparator for Breadth First Search algorithm.
	 */
	private class BreadthFirstSearchComparator implements Comparator<GraphState> {

		/*
		 * (non-Javadoc)
		 * 
		 * @see java.util.Comparator#compare(java.lang.Object, java.lang.Object)
		 */
		@Override
		public int compare(GraphState gs1, GraphState gs2) {
			double difference = gs1.getDepth() - gs2.getDepth();
			if (difference == 0.0) {
				return gs1.getIdentifier().compareTo(gs2.getIdentifier());
			} else {
				return (difference > 0.0) ? 1 : -1;
			}
		}
	}
}