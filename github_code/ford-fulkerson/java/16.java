package Max_Flow;

import edu.princeton.cs.algs4.Queue;

public class FordFulkerson {
	private boolean[] marked;	// true if s -> v path in residual network
	private FlowEdge[] edgeTo;	// last edge on s -> v path
	private double value;		// value of flow
	
	public FordFulkerson(FlowNetwork G, int s, int t) {
		value = 0.0;
		while (hasAugmentingPath(G, s, t)) {
			double bottle = Double.POSITIVE_INFINITY;
			for (int v = t; v != s; v = edgeTo[v].other(v)) {
				bottle = Math.min(bottle, edgeTo[v].residualCapacityTo(v));
			}
			for (int v = t; v != s; v = edgeTo[v].other(v)) {
				edgeTo[v].addResidualFlowTo(v, bottle);
			}
			value += bottle;
		}
	}

	// finding a shortest augmenting path
	private boolean hasAugmentingPath(FlowNetwork G, int s, int t) {
		marked = new boolean[G.V()];
		edgeTo = new FlowEdge[G.V()];
		Queue<Integer> queue = new Queue<>();
		queue.enqueue(s);
		marked[s] = true;
		while (!queue.isEmpty() && !marked[t]) {
			int v = queue.dequeue();
			for (FlowEdge e: G.adj(v)) {
				int w = e.other(v);
				
				if (e.residualCapacityTo(w) > 0 && !marked[w]) {
					edgeTo[w] = e;
					marked[w] = true;
					queue.enqueue(w);
				}
			}
		}
		return marked[t];
	}
	
	public double value() {
		return value;
	}
	
	// Returns true if the specified vertex is on the {@code s} side of the mincut.
	public boolean inCut(int v) {
		return marked[v];
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
