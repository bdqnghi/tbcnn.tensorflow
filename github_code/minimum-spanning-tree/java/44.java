package ch.ethz.sg.cuttlefish.networks;

import java.util.Collection;

import org.gephi.data.attributes.api.AttributeController;
import org.gephi.data.attributes.api.AttributeType;
import org.gephi.filters.plugin.AbstractAttributeFilter;
import org.gephi.filters.plugin.attribute.AttributeEqualBuilder.EqualNumberFilter;
import org.gephi.graph.api.HierarchicalDirectedGraph;
import org.gephi.graph.api.Node;
import org.openide.util.Lookup;


/**
 * For the input Graph, creates a MinimumSpanningTree using a variation of
 * Prim's algorithm.
 * 
 * NOTE (irinis): This algorithm is adapted to compute a MST on the Graph
 * structure of the Gephi Toolkit 0.8.3. An important point is that there do not
 * exist multiple graph/forest instances, but rather a single Singleton. For
 * this reason the input structure should not be empty, since the MST will be
 * computed on the existing graph.
 * 
 * The algorithm does not remove edges from the graph. Rather, it computes a MST
 * by marking the edges that belong to the MST rather than deleting the ones
 * that do not.
 * 
 * @author Tom Nelson - tomnelson@dev.java.net
 * @author irinis
 * 
 */

public class MinimumSpanningTree {

	// Static fields

	private final static String EDGE_ATTR_MST;
	private final static String NODE_ATTR_MST;

	private static final long MST_ID_BASE;
	private static long MST_ID;

	static {
		MST_ID_BASE = 46200;
		MST_ID = MST_ID_BASE;

		EDGE_ATTR_MST = "edge_int_mstid";
		NODE_ATTR_MST = "node_int_mstid";

		Edge.addAttribute(EDGE_ATTR_MST, AttributeType.LONG, -1);
		Vertex.addAttribute(NODE_ATTR_MST, AttributeType.LONG, -1);
	}

	// Instance fields

	private HierarchicalDirectedGraph tree;
	private Collection<Node> roots;

	public MinimumSpanningTree(HierarchicalDirectedGraph tree,
			Collection<Node> roots) {
		this.tree = tree;
		this.roots = roots;
	}

	public HierarchicalDirectedGraph create() {

		// Minimum Spanning Tree identifier
		MST_ID++;

		Node root = null;
		if (roots != null && !roots.isEmpty()) {
			root = roots.iterator().next();
			roots.remove(root);
			System.out.println("MST Root Vertex: " + root);

		} else {
			throw new RuntimeException("No root(s) specified for the MST!");
		}

		for (Node n : tree.getNodes())
			reset(n);

		for (org.gephi.graph.api.Edge e : tree.getEdges())
			reset(e);

		mark(root);
		updateTree();

		return tree;
	}

	/**
	 * Creates a filter for the edges that belong to the MST. This filter is
	 * used to query a view of the graph containing only these edges (a view
	 * equivalent to the computed MST).
	 * 
	 * @return The AbstractAttributeFilter edge filter created.
	 */
	protected AbstractAttributeFilter getEdgeFilter() {
		EqualNumberFilter edgeFilter = new EqualNumberFilter(Lookup
				.getDefault().lookup(AttributeController.class).getModel()
				.getEdgeTable().getColumn(EDGE_ATTR_MST));

		edgeFilter.setMatch(new Long(MST_ID));
		return edgeFilter;
	}

	protected void updateTree() {

		org.gephi.graph.api.Edge nextEdge = null;
		Node nextVertex = null;
		Node currentVertex = null;

		for (org.gephi.graph.api.Edge e : tree.getEdges()) {

			if (isMarked(e))
				continue;

			Node first = e.getSource();
			Node second = e.getTarget();

			if (isMarked(first) && !isMarked(second)) {
				nextEdge = e;
				currentVertex = first;
				nextVertex = second;

			} else if (!e.isDirected() && isMarked(second) && !isMarked(first)) {
				nextEdge = e;
				currentVertex = second;
				nextVertex = first;
			}
		}

		if (nextVertex != null && nextEdge != null) {
			mark(nextVertex);
			mark(currentVertex);
			mark(nextEdge);
			updateTree();
		}

		// Check for disconnected nodes
		for (Node n : tree.getNodes()) {

			if (isMarked(n))
				continue;

			// Found unmarked node
			Node root = n;
			if (roots != null && !roots.isEmpty()) {
				root = roots.iterator().next();
				roots.remove(root);
			}

			System.out.println("MST Root Vertex: " + root);
			mark(root);
			updateTree();
		}
	}

	private void reset(Node n) {
		n.getAttributes().setValue(NODE_ATTR_MST, MST_ID_BASE);
	}

	private void reset(org.gephi.graph.api.Edge e) {
		e.getAttributes().setValue(EDGE_ATTR_MST, MST_ID_BASE);
	}

	private void mark(Node n) {
		n.getAttributes().setValue(NODE_ATTR_MST, MST_ID);
	}

	private void mark(org.gephi.graph.api.Edge e) {
		e.getAttributes().setValue(EDGE_ATTR_MST, MST_ID);
	}

	private boolean isMarked(Node n) {
		return n.getAttributes().getValue(NODE_ATTR_MST).equals(MST_ID);
	}

	private boolean isMarked(org.gephi.graph.api.Edge e) {
		return e.getAttributes().getValue(EDGE_ATTR_MST).equals(MST_ID);
	}
}
