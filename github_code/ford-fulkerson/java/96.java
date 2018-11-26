/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package graph_algorithms.maxflow_micut;

import edu.princeton.cs.algs4.StdOut;
import java.util.LinkedList;
import java.util.Queue;

/**
 * The class implements Ford-Fulkerson Algorithm for solving Maxflow-Mincut
 * problem.
 *
 * @author manishjoshi394
 */
public class FordFulkerson {

    private boolean[] marked;       // vertex indexed array for checking reachability
    private FlowEdge[] edgeTo;      // last edge on path to v
    private double value;           // current value of the maxflow

    /**
     * Pre-processes the FlowNetwork G to efficiently respond to the client
     * queries.
     *
     * @param G the FlowNetwork
     * @param s the source vertex
     * @param t the target vertex
     */
    public FordFulkerson(FlowNetwork G, int s, int t) {
        value = 0;
        while (hasAugmentingPath(G, s, t)) {

            // compute bottle-neck capacity 
            double bottle = Double.POSITIVE_INFINITY;
            for (int v = t; v != s; v = edgeTo[v].other(v)) {
                //System.out.println(edgeTo[v].residualCapacityTo(v));
                bottle = Math.min(edgeTo[v].residualCapacityTo(v), bottle);
            }

            // Augment the flow
            for (int v = t; v != s; v = edgeTo[v].other(v)) {
                edgeTo[v].addResidualFlowTo(v, bottle);
            }

            // update Flow value
            value += bottle;
        }
    }

    private boolean hasAugmentingPath(FlowNetwork G, int s, int t) {
        marked = new boolean[G.V()];
        edgeTo = new FlowEdge[G.V()];

        // Breadth first search 
        Queue<Integer> q = new LinkedList<>();
        q.add(s);
        marked[s] = true;               // Mark the source
        while (!q.isEmpty() && !marked[t]) {
            int v = q.remove();

            for (FlowEdge e : G.adj(v)) {
                int w = e.other(v);

                if (e.residualCapacityTo(w) > 0 && !marked[w]) {
                    // mark the vertex, update the path to it, put ont the queue
                    marked[w] = true;
                    edgeTo[w] = e;
                    q.add(w);
                }
            }
        }
        return marked[t];
    }

    /**
     * Returns the value of the Max-Flow.
     *
     * @return the value of the Max-Flow
     */
    public double value() {
        return value;
    }

    /**
     * Returns true if v is reachable from source vertex s.
     *
     * @param v a FlowNetwork vertex
     * @return true if v is reachable from source vertex s
     */
    public boolean inCut(int v) {
        return marked[v];
    }

    // Unit tester for the class
    public static void main(String[] args) {

        // create flow network with V vertices and E edges
        int V = 5;
        int s = 0, t = V - 1;
        FlowNetwork G = new FlowNetwork(V);
        G.addEdge(new FlowEdge(0, 1, 2.0));
        G.addEdge(new FlowEdge(0, 2, 2.0));
        G.addEdge(new FlowEdge(0, 3, 2.0));
        G.addEdge(new FlowEdge(1, 4, 10.0));
        G.addEdge(new FlowEdge(2, 4, 1.0));
        G.addEdge(new FlowEdge(3, 4, 10.0));

        // compute maximum flow and minimum cut
        FordFulkerson maxflow = new FordFulkerson(G, s, t);
        StdOut.println("Max flow from " + s + " to " + t);
        for (int v = 0; v < G.V(); v++) {
            for (FlowEdge e : G.adj(v)) {
                if ((v == e.from()) && e.flow() > 0) {
                    StdOut.println("   " + e);
                }
            }
        }

        // print min-cut
        StdOut.print("Min cut: ");
        for (int v = 0; v < G.V(); v++) {
            if (maxflow.inCut(v)) {
                StdOut.print(v + " ");
            }
        }
        StdOut.println();

        StdOut.println("Max flow value = " + maxflow.value());
    }
}
