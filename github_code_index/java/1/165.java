package com.github.phenomics.ontolib.graph.algo;

import java.util.ArrayDeque;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import com.github.phenomics.ontolib.graph.data.DirectedGraph;
import com.github.phenomics.ontolib.graph.data.Edge;

// TODO: Create a helper class with static methods similar to OntologyTerms
/**
 * Breadth-first-search for {@link DirectedGraph}s using the <b>visitor pattern</b>.
 *
 * @param <V> vertex type of graph, see {@link DirectedGraph} for requirements on vertex type
 * @param <E> edge type to use in the graph, also see {@link DirectedGraph} for details
 *
 * @author <a href="mailto:manuel.holtgrewe@bihealth.de">Manuel Holtgrewe</a>
 */
public final class BreadthFirstSearch<V extends Comparable<V>, E extends Edge<V>>
    extends AbstractGraphVertexStartFromVertexTraversal<V, E, DirectedGraph<V, E>> {

  /**
   * Generic implementation of BFS; forward/reverse edges are chosen using <code>selector</code>.
   *
   * @param g {@link DirectedGraph} to use for iteration.
   * @param v Vertex to start from.
   * @param visitor {@link VertexVisitor} to use for visiting vertices.
   * @param selector {@link NeighborSelector} for selecting forward/reverse vertices.
   */
  @Override
  protected void startFromImpl(DirectedGraph<V, E> g, V v, VertexVisitor<V, E> visitor,
      NeighborSelector<V, E> selector) {
    final Set<V> seen = new HashSet<V>();
    final ArrayDeque<V> dequeue = new ArrayDeque<V>();
    dequeue.addLast(v);
    while (!dequeue.isEmpty()) {
      final V vertex = dequeue.pollFirst();
      if (!seen.contains(vertex)) { // skip seen ones
        seen.add(vertex);
        if (!visitor.visit(g, vertex)) {
          break;
        }
        final Iterator<V> it = selector.nextFrom(g, vertex);
        while (it.hasNext()) {
          dequeue.add(it.next());
        }
      }
    }
  }

}
