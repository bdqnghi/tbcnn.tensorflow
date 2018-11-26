package sac.examples.tsp;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.SortedSet;
import java.util.TreeSet;

/**
 * Minimum Spanning Tree solver via Kruskal's algorithm, used in TSP as heuristics.
 * 
 * @author Przemysław Klęsk (<a href="mailto: pklesk@wi.zut.edu.pl">wi.zut.edu.pl</a>)
 * @author Marcin Korzeń (<a href="mailto: mkorzen@wi.zut.edu.pl">wi.zut.edu.pl</a>)
 */
public class MinimumSpanningTree {

	/**
	 * List of connections.
	 */
	private List<Connection> connections;

	/**
	 * Cost of the minimum spanning tree.
	 */
	private double cost;

	/**
	 * Creates a new instance of minimum spanning tree as a copy.
	 * 
	 * @param toCopy minimum spanning tree to be copied
	 */
	public MinimumSpanningTree(MinimumSpanningTree toCopy) {
		connections = new ArrayList<Connection>();
		connections.addAll(toCopy.connections);
		cost = toCopy.cost;
	}

	/**
	 * Creates a minimum spanning tree from a collection of places. The Kruskal's algorithm is performed inside this
	 * constructor.
	 * 
	 * @param places collection of places (as a SortedSet).
	 */
	public MinimumSpanningTree(SortedSet<Place> places) {
		connections = new ArrayList<Connection>();
		cost = 0.0;

		SortedSet<Connection> orderedConnections = new TreeSet<Connection>(new ConnectionCostComparator());

		// building sorted set of all valid connections
		for (Place place : places) {
			for (Connection connection : place.getConnections()) {
				if (!places.contains(connection.getPlace1()))
					continue;
				if (!places.contains(connection.getPlace2()))
					continue;
				orderedConnections.add(connection);
			}
		}

		SortedSet<Place> placesInsideMSP = new TreeSet<Place>();

		if (orderedConnections.isEmpty())
			return;

		// adding first connection
		Connection firstConnection = orderedConnections.first();
		connections.add(firstConnection);
		cost += firstConnection.getCost();
		placesInsideMSP.add(firstConnection.getPlace1());
		placesInsideMSP.add(firstConnection.getPlace2());
		orderedConnections.remove(firstConnection);

		while (placesInsideMSP.size() < places.size()) {
			Iterator<Connection> iterator = orderedConnections.iterator();
			while (iterator.hasNext()) {
				Connection connection = iterator.next();
				boolean place1InsideMSP = placesInsideMSP.contains(connection.getPlace1());
				boolean place2InsideMSP = placesInsideMSP.contains(connection.getPlace2());
				if (((place1InsideMSP) && (!place2InsideMSP)) || ((!place1InsideMSP) && (place2InsideMSP))) {
					connections.add(connection);
					cost += connection.getCost();
					placesInsideMSP.add(connection.getPlace1());
					placesInsideMSP.add(connection.getPlace2());
					iterator.remove();
					break;
				}
				if ((place1InsideMSP) && (place2InsideMSP))
					iterator.remove();
			}
		}
	}

	/**
	 * Returns the connections.
	 * 
	 * @return connections
	 */
	public List<Connection> getConnections() {
		return connections;
	}

	/**
	 * Returns the cost of this minimum spanning tree.
	 * 
	 * @return cost of this minimum spanning tree
	 */
	public double getCost() {
		return cost;
	}

	/**
	 * Explicitly sets the cost of this minimum spanning tree. This method may be useful in case some simple
	 * modifications from outside (e.g. removal of some connection) are made on this tree, and its cost is the
	 * recalculated in a control manner.
	 * 
	 * @param cost new cost to be set
	 */
	public void setCost(double cost) {
		this.cost = cost;
	}

	/**
	 * Checks if a given place is associated with only one connection in this minimum spanning tree. If so the
	 * connection is returned, otherwise a null is returned.
	 * 
	 * @param place reference to given place
	 * @return single connection or null if more than one connection exists
	 */
	public Connection isPlaceWithSingleConnection(Place place) {
		int occurrences = 0;
		Connection singleConnection = null;
		for (Connection connection : connections) {
			if (connection.getPlace1().equals(place) || connection.getPlace2().equals(place)) {
				occurrences++;
				singleConnection = connection;
				if (occurrences > 1)
					return null;
			}
		}
		return singleConnection;
	}
}