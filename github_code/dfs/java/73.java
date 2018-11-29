package sac.graph;

import java.util.Comparator;

/**
 * Depth First Search algorithm.
 * 
 * @author Przemysław Klęsk (<a href="mailto:pklesk@wi.zut.edu.pl">wi.zut.edu.pl</a>)
 * @author Marcin Korzeń (<a href="mailto:mkorzen@wi.zut.edu.pl">wi.zut.edu.pl</a>)
 */
public class DepthFirstSearch extends GraphSearchAlgorithm {

	/**
	 * Creates new instance of Depth First Search algorithm.
	 * 
	 * @param initial reference to initial state
	 * @param configurator reference to configurator object
	 */
	public DepthFirstSearch(GraphState initial, GraphSearchConfigurator configurator) {
		super(initial, configurator);
		setupOpenAndClosedSets(new DepthFirstSearchComparator());
	}

	/**
	 * Creates new instance of Depth First Search algorithm.
	 * 
	 * @param initial reference to initial state
	 */
	public DepthFirstSearch(GraphState initial) {
		this(initial, null);
	}

	/**
	 * Creates new instance of Depth First Search algorithm.
	 */
	public DepthFirstSearch() {
		this(null, null);
	}

	/**
	 * Comparator for Depth First Search algorithm.
	 */
	private class DepthFirstSearchComparator implements Comparator<GraphState> {

		/*
		 * (non-Javadoc)
		 * 
		 * @see java.util.Comparator#compare(java.lang.Object, java.lang.Object)
		 */
		@Override
		public int compare(GraphState gs1, GraphState gs2) {
			double difference = -(gs1.getDepth() - gs2.getDepth());
			if (difference == 0.0) {
				return gs1.getIdentifier().compareTo(gs2.getIdentifier());
			} else {
				return (difference > 0.0) ? 1 : -1;
			}
		}
	}
}