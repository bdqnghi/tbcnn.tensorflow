
package jdd.graph;

import jdd.util.*;

import java.util.*;

/**
 * Class for the minimum-spanning-tree algorithms
 *
 */
public class MinimumSpanningTree {

	/**
	 *
	 * MST-Kruskal.
	 *
	 * <p>side-effects: changes Node.extra1 and Edga.flags:FLAGS_STRONG.
	 * <p>output: Edga.flags:FLAGS_STRONG is set of that edge is included in the tree
	 * <p>complexity: O( E lg V) ???
	 *
	 */

	public static void kruskal(Graph g) {
		EdgeHeap eh = new EdgeHeap(g, true);
		DisjointSet ds = new DisjointSet( g.numOfNodes() );
		int offset = 0, set_flag = Edge.FLAGS_STRONG, remove_flag = ~Edge.FLAGS_STRONG;

		for (Enumeration e = g.getNodes().elements() ; e.hasMoreElements() ;) ((Node) e.nextElement()).extra1 = offset++;

		// for (Enumeration e = g.getEdges().elements() ; e.hasMoreElements() ;) ((Edge) e.nextElement()).flags &= remove_flag;
		AttributeExplorer.resetEdgeFlag(g, Edge.FLAGS_STRONG);

		while(!eh.isEmpty() ) {
			Edge e = (Edge) eh.pop();
			int r1 = ds.find(e.n1.extra1);
			int r2 = ds.find(e.n2.extra1);
			if( r1 != r2 ) {
				ds.union(r1, r2);
				e.flags |= set_flag;
			}
		}
	}

	// ------------------------------------------
	/** testbench. do not call */
	public static void internal_test() {
		Test.start("MinimumSpanningTree");

		// this is the graph  at page 568 in Cormen
		WeightedGraph wg = new WeightedGraph(false);
		Node a = wg.addNode();		Node b = wg.addNode();		Node c = wg.addNode();
		Node d = wg.addNode();		Node e = wg.addNode();		Node f = wg.addNode();
		Node g = wg.addNode();		Node h = wg.addNode();		Node i = wg.addNode();
		wg.addEdge(a,b,4);		wg.addEdge(b,c,8);
		wg.addEdge(b,h,11);		wg.addEdge(c,d,7);		wg.addEdge(c,f,4);
		wg.addEdge(d,e,9);		wg.addEdge(d,f,14);		wg.addEdge(e,f,10);
		wg.addEdge(f,g,2);		wg.addEdge(g,i,6);		wg.addEdge(g,h,1);
		wg.addEdge(h,i,7);		wg.addEdge(i,c,2);		wg.addEdge(a,h,8);

		GraphIO.saveEdgeList(wg,"data/p568.pcg");

		// check kruskal on cormens graph
		kruskal(wg);
		double total = 0;
		for (Enumeration it = wg.getEdges().elements() ; it.hasMoreElements() ;) {
			Edge x = (Edge) it.nextElement();
			if((x.flags & Edge.FLAGS_STRONG) != 0) total += x.weight;
		}
		Test.check( total == 37.0, "kruskal");	// trust me, I have counted it :)


		// check in a a complete graph
		int count = 0;
		Graph k12 = Factory.complete(12);
		kruskal(k12);
		for (Enumeration it = k12.getEdges().elements() ; it.hasMoreElements() ;)
			if((((Edge) it.nextElement()).flags & Edge.FLAGS_STRONG) != 0) count++;
		Test.checkEquality( count, k12.numOfNodes() -1, "In a complete graph |MST| = |V| -1");


		Test.end();

	}
}
