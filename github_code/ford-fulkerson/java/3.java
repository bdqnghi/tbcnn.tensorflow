package GKA_A3;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Set;

import GKA_A1.IAIGraph;

public class EdmondsKarp extends FlowAlgorithms {

	// Der EdmondsKarp Algorithmus ist laut wikipedia(english)
	// fast gleich wie dem Ford-Fulkerson. Der Einzige Unterschied
	// ist, dass Ford-Fulkerson eine Praeferenz bei der Auswahl der
	// zu inspizierenden Knoten hat und der EdmondsKArp Algorithmus
	// eine BreitenSuche verwenden um den shortest augmenthing path zu finden.

	// Kommantare stehe daher nur im Breath First Algorithmus
	// da der Rest identisch zum Ford-Fulkerson ist.

	// Die markierten aber uninspizierten Knoten werden in
	// der Queue gespeichert. Sobald sie inspiziert werden,
	// werden sie aus der Queue entfernt
	// Aus der Verwendung der Queue resultiert dann die
	// Breitensuche.

	Queue<Long> inspectable;

	public EdmondsKarp(IAIGraph graph, long srcId, long destId, String capAttr,
			String flowAttr) {
		super(graph, srcId, destId, capAttr, flowAttr);
		inspectable = new LinkedList<>();
		algo();
	}

	private void algo() {

		// Step 1 -
		// initialize the zero flow (if none is given)
		// mark Quelle
		init();

		// Step 2
		// save the current to be inspected Vertice into vi.
		// end loop, if there are no more.
		for (Long vi = popFromQueue(); vi != -1L; vi = popFromQueue()) {

			// filter all edges by O(vi) and I(vi).
			List<Set<Long>> partition = makeInOutPartitionOf(vi);
			Set<Long> incoming = partition.get(0);
			Set<Long> outgoing = partition.get(1);

			// Forward-edges
			for (Long eID : outgoing) {
				increaseAccess(); // Zugriff auf ein Edge
				long vj = graph.getTarget(eID);

				// make the forward-mark of for every edge that goes from vi to
				// an yet unmarked
				if (!verticeIsMarked(vj) && f(eID) < c(eID)) {
					saveForwardEdge(eID, vj, vi);
				}
			}

			// Backward-edges
			for (Long eID : incoming) {
				increaseAccess(); // Zugriff auf ein Edge
				long vj = graph.getSource(eID);

				// make the backward-mark of for every edge that goes from vi to
				// an yet unmarked vj
				if (!marked.containsKey(vj) && f(eID) > 0) {
					saveBackwardEdge(eID, vj, vi);
				}
			}
			
			// an dieser Stelle im Code wurde frueher der Vertice als inspected
			// gesetzt. In EdmondsKarp passiert dies schon beim Entnehmen aus der Queue.
			
			// Step 3
			// if the senke/destination was reached(marked) then augment the flow
			if (verticeIsMarked(destId)) {
				// step three. calculate the augmenting path and update the flow
				updateByAugmentingPath();
			}
		}

		// Step 4
		// we're finished now!

	}

	// TODO: change this four methods to use the queue
	private Long popFromQueue() {
		Long maybeVertice = inspectable.poll();
		if (maybeVertice  != null) {
			getMarkedTuple(maybeVertice).inspect();
			return maybeVertice;
		}
		else {
			return -1L;
			
		}
	}

	public boolean verticeIsMarked(long vID) {
		increaseAccess(); // Zugriff auf die markierten Vertices
		return marked.containsKey(vID);
	}

	public void markVertice(long vID, Tuple4 info) {
		increaseAccess(); // Zugriff auf die Datenstruktur
		inspectable.offer(vID);
		marked.put(vID, info);
	}

	public Tuple4 getMarkedTuple(long vID) {
		increaseAccess(); // Zugriff auf die markierten Vertices
		return marked.get(vID);
	}

	public void inspectVertice(long vID) {
		getMarkedTuple(vID).inspect();
	}

	public void resetMarks() {
		inspectable = new LinkedList<>();
		marked = new HashMap<>();
		initQMark();
	}
}
