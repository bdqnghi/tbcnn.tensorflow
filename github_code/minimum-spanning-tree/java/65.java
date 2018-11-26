package io.acoia.graphs;

import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

import com.google.common.graph.EndpointPair;
import com.google.common.graph.MutableValueGraph;
import com.google.common.graph.ValueGraph;
import com.google.common.graph.ValueGraphBuilder;

import io.acoia.sets.UnionFind;

/**
 * Algorithms for computing the minimum spanning tree of graphs.
 * 
 * Copyright (c) 2017 Royce Ausburn This code is available for use in accordance with the MIT
 * License https://opensource.org/licenses/MIT
 * 
 * @author Royce Ausburn (esapersona@royce.id.au)
 * 
 */
public class MinimumSpanningTree {

  /**
   * Sorts the edges of the provided ValueGraph and then calls kruskals(ValueGraph<N, E> g,
   * List<EndpointPair<N>> sortedEdges). Due to the need to sort the edges this method requires edge
   * values in the graph to implement Comparable.
   * 
   * Due to the need to sort this method sorts the edges (O(E log(E))) before calling Kruskal's (O(E α(V))) .
   */
  public static <N, E extends Comparable<E>> ValueGraph<N, E> kruskals(ValueGraph<N, E> g) {
    Set<EndpointPair<N>> edges = g.edges();

    List<EndpointPair<N>> sortedEdges =
        edges.stream()
          .sorted((ep1, ep2) -> g.edgeValue(ep1.nodeU(), ep1.nodeV()).compareTo(g.edgeValue(ep2.nodeU(), ep2.nodeV())))
          .collect(Collectors.toList());

    return kruskals(g, sortedEdges);
  }

  /**
   * An implementation of Kruskal's minimum spanning tree algorithm.
   * 
   * Description from Wiki: Kruskal's algorithm is a minimum-spanning-tree algorithm which finds an
   * edge of the least possible weight that connects any two trees in the forest. It is a greedy
   * algorithm in graph theory as it finds a minimum spanning tree for a connected weighted graph
   * adding increasing cost arcs at each step. This means it finds a subset of the edges that forms
   * a tree that includes every vertex, where the total weight of all the edges in the tree is
   * minimized. If the graph is not connected, then it finds a minimum spanning forest (a minimum
   * spanning tree for each connected component).
   * 
   * This implementation uses io.acoia.sets.UnionFind and expects a sorted list of edges, and thus
   * runs in O(E α(V)) time.
   */
  public static <E, N> ValueGraph<N, E> kruskals(ValueGraph<N, E> g, List<EndpointPair<N>> sortedEdges) {

    if (g.isDirected())
      throw new IllegalArgumentException("Kruskal's does not support directed graphs");

    // Set up a Graph to store the result. 
    MutableValueGraph<N, E> tree = ValueGraphBuilder
        .undirected()
        .allowsSelfLoops(false)
        .expectedNodeCount(g.nodes().size())
        .build();

    for (N n : g.nodes()) {
      tree.addNode(n);
    }

    // Now we start kruskals.. most of the work is done by the UnionFind really...
    UnionFind<N> uf = new UnionFind<>(g.nodes());
    for (EndpointPair<N> e : sortedEdges) {
      
      N nodeU = e.nodeU();
      N nodeV = e.nodeV();
      
      if (uf.findRoot(nodeU) != uf.findRoot(nodeV)) {
        tree.putEdgeValue(nodeU, nodeV, g.edgeValue(nodeU, nodeV));
        uf.join(nodeU, nodeV);
      }
    }

    return tree;
  }

}
