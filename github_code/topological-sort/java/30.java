package coursera.exercise.digraph;

import com.coursera.algorithms.algs4.EdgeWeightedDigraph;
import com.coursera.algorithms.algs4.EdgeWeightedDirectedCycle;
import com.coursera.algorithms.stdlib.StdOut;

/*************************************************************************
 *  Compilation:  javac Topoological.java
 *  Dependencies: Digraph.java DepthFirstOrder.java DirectedCycle.java
 *                EdgeWeightedDigraph.java EdgeWeightedDirectedCycle.java
 *  Data files:   http://algs4.cs.princeton.edu/42directed/jobs.txt
 *
 *  Compute topological ordering of a DAG or edge-weighted DAG.
 *  Runs in O(E + V) time.
 *
 *  % java Topological jobs.txt "/"
 *  Calculus
 *  Linear Algebra
 *  Introduction to CS
 *  Programming Systems
 *  Algorithms
 *  Theoretical CS
 *  Artificial Intelligence
 *  Machine Learning
 *  Neural Networks
 *  Robotics
 *  Scientific Computing
 *  Computational Biology
 *  Databases
 *
 *
 *************************************************************************/

class Topological {
    private Iterable<Integer> order;    // topological order

    // topological sort in a ExactDigraph
    public Topological(ExactDigraph G) {
        DirectedCycle finder = new DirectedCycle(G);
        if (!finder.hasCycle()) {
            DepthFirstOrder dfs = new DepthFirstOrder(G);
            order = dfs.reversePost();
        }
    }

    // topological sort in an edge-weighted digraph
    public Topological(EdgeWeightedDigraph G) {
        EdgeWeightedDirectedCycle finder = new EdgeWeightedDirectedCycle(G);
        if (!finder.hasCycle()) {
            DepthFirstOrder dfs = new DepthFirstOrder(G);
            order = dfs.reversePost();
        }
    }

    // return topological order if a DAG; null otherwise
    public Iterable<Integer> order() {
        return order;
    }

    // does digraph have a topological order?
    public boolean hasOrder() {
        return order != null;
    }
}
