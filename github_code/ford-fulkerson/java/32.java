package com.ttsoftware.utilities.algorithm.fordfulkerson;

/*****************************************************************************
 * File: FordFulkersonScaling.java
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * An implementation of the capacity-scaling Ford-Fulkerson algorithm.  As its
 * name suggests, the algorithm works by iteratively calling the Ford-Fulkerson
 * algorithm as a subroutine, constantly updating the capacities, with the aim
 * of computing a maximum s-t flow in the graph.  Amazingly, although the raw
 * Ford-Fulkerson algorithm runs in worst-case exponential time (its runtime
 * depends on the size of the maximum flow in the graph), the capacity-scaling
 * version of the algorithm runs in polynomial time, though the runtime is not
 * strongly polynomial (it depends on the maximum capacity in the graph).
 *
 * The key insight behind the capacity-scaling Ford-Fulkerson algorithm is that
 * we can compute an exact maximum flow by iteratively refining an approximate
 * max-flow until we arrive at the final solution.  In particular, let's
 * assume that all the capacities in the graph can be written out as k-bit
 * binary values.  Begin by constructing the flow network where each capacity
 * is 1 if the most-significant bit of the capacity is 1 and 0 otherwise.  The
 * maximum flow in this graph is m, since in the best possible case each edge
 * in the graph has flow across it.  Now, suppose that we refine this first
 * guess of a max-flow by "uncovering" the next bit of the capacities of each
 * of the edges.  This is equivalent to doubling the flow and capacity across
 * each edge, then possibly increasing the capacities of some edges by one
 * (if the next bit is one).  The doubling step doesn't change the fact that
 * our current flow is a maximum flow; you can see this either by looking at
 * the LP formulation of maximum flow, or by a simple proof by contradiction.
 * This means that if we have a flow of value F from the previous iteration,
 * after the doubling step we now have a flow of value 2F that's still a max-
 * flow.  However, after adding one to some of the edges, our new flow may no
 * longer be a max-flow, but we know that the total amount of flow that could
 * get pushed through this graph is at most 2F + O(m), since each edge (and 
 * its residual edge) might have a new unit of flow pushed across it.  Since
 * we already have a flow of value 2F, this means that if we run the Ford-
 * Fulkerson algorithm in this new graph, it will take at most O(m^2) time to
 * complete.  Repeating this procedure and uncovering progressively more bits
 * until all the bits of the capacities are uncovered will ultimately result
 * in a valid max-flow for the resulting graph.
 *
 * The beauty of this algorithm is that it has a marvelous runtime.  As said
 * above, each iteration of the Ford-Fulkerson algorithm takes at most O(m^2)
 * time to complete.  Moreover, the number of iterations is given by the
 * number of bits in the largest-capacity edge in the graph.  This is given by
 * the log of the maximum capacity (which we'll call C), giving us a total
 * runtime of O(m^2 lg C), which is polynomial in the size of the input.  For
 * arbitrary graphs, this is often much faster than the O(mF) guarantee of the
 * raw Ford-Fulkerson algorithm.
 *
 * This code relies on the FordFulkerson class also available from the Archive
 * of Interesting Code.  You can find it at
 *
 *       http://www.keithschwarz.com/interesting/code/?dir=ford-fulkerson
 */
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.NoSuchElementException;

import com.ttsoftware.utilities.algorithm.common.FlowNetwork;
import com.ttsoftware.utilities.algorithm.common.IntegralDirectedMapGraph;
// For HashMap

public final class FordFulkersonScaling {
    /**
     * Given a graph and a pair of nodes s and t, produces a maximum s-t flow
     * in that graph.
     *
     * @param g The graph to search.
     * @param s The start node of the flow.
     * @param t The end node of the flow.
     * @return f A flow network for g containing a maximum s/t flow.
     * @throws IllegalArgumentException If any of the edges in the input graph
     *                                  have negative length.
     * @throws NoSuchElementException If s or t are not nodes in the graph.
     */
    public static <T> FlowNetwork<T> maxFlow(IntegralDirectedMapGraph<T> g, T s, T t) {
        /* Construct the structure of the resulting flow network. */
        FlowNetwork<T> result = new FlowNetwork<T>();

        /* Copy over nodes. */
        for (T node: g)
            result.addNode(node);

        /* Copy over edges. */
        for (T node: g)
            for (Map.Entry<T, Integer> edge: g.edgesFrom(node).entrySet())
                result.addEdge(node, edge.getKey()).setCapacity(edge.getValue());

        /* Compute a max-flow in this flow network. */
        findMaxFlow(result, s, t);
        return result;
    }

    /**
     * Given a flow network and a pair of nodes s and t, produces a maximum
     * s-t in that network.  Any flow that already exists in the input network
     * will be used as a guess of the maximum flow.
     *
     * @param g The flow graph to search.
     * @param s The start node of the flow.
     * @param t The end node of the flow.
     * @throws NoSuchElementException If s or t are not nodes in the graph.
     */
    public static <T> void findMaxFlow(FlowNetwork<T> g, T s, T t) {
        /* This algorithm is going to work by scaling up the capacities.  This
         * will require us to begin by storing all of the capacities, then
         * setting them all to zero.  To preserve this information, we'll make
         * a map from edges to their original capacities.
         */
        Map<FlowNetwork.Edge<T>, Integer> edges = new HashMap<FlowNetwork.Edge<T>, Integer>();
        for (T node: g) {
            for (FlowNetwork.Edge<T> edge: g.edgesFrom(node)) {
                /* Cache the capacity for later on. */
                edges.put(edge, edge.getCapacity());

                /* Clear the capacity of this edge.  This will require us to
                 * clear both the flow and the capacity.
                 */
                edge.setFlow(0);
                edge.setCapacity(0);
            }
        }

        /* Run the capacity-scaling rounds. */
        for (int bit = numRequiredBits(edges.values()); bit >= 0; --bit) {
            /* Scan across all edges, uncovering the next bit. */
            for (Map.Entry<FlowNetwork.Edge<T>, Integer> edge: edges.entrySet()) {
                /* Uncovering a bit entails doubling the flow and capacity,
                 * then increasing the capacity by one if the next bit in its
                 * representation is a one.  We determine the amount to add by
                 * bitmasking out everything except the bit in question, then
                 * shifting it down so that it occupies the 1s position in the
                 * number.
                 */
                edge.getKey().setCapacity(2 * edge.getKey().getCapacity() +
                                          ((edge.getValue() & (1 << bit)) >>> bit));
                edge.getKey().setFlow(2 * edge.getKey().getFlow());
            }

            /* Run another iteration of Ford-Fulkerson on this flow graph. */
            FordFulkerson.findMaxFlow(g, s, t);
        }
    }

    /**
     * Given a collection of integers representing capacities, returns the
     * number of bits required to represent all of the integers.
     *
     * @param capacities The collection of capacities to search.
     * @return The number of bits required to represent the capacities.
     */
    private static int numRequiredBits(Collection<Integer> capacities) {
        /* Iterate across the capacities seeing how many bits we need.  Begin
         * by assuming we don't need any.
         */
        int numBits = -1;

        /* The number of bits required to encode a number is given by the
         * total number of bits (32) less the number of leading zeros on that
         * value.
         */
        for (Integer capacity: capacities)
            numBits = Math.max(numBits, 32 - Integer.numberOfLeadingZeros(capacity));

        return numBits;
    }
}