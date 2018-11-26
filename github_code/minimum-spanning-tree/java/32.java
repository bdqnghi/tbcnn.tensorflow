package algorithms;

import static shared.ADTFactories.ADTs;
import static shared.AlgorithmsService.Algos;

import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

import dataStructures.DisjointSet;
import dataStructures.PriorityQueue;
import dataStructures.graph.Edge;
import dataStructures.graph.UndirectedGraph;
import dataStructures.graph.Vertex;
import dataStructures.graph.Weight;

/**
 * This class contains algorithms that calculate minimum-spanning-tree.
 */
public class MST {

	/**
	 * This method computes a minimum-spanning tree of a given undirected graph
	 * using the Kruskal algorithm.
	 * 
	 * @param g
	 * @preconditions
	 *                <ol>
	 *                <li><code>g != null</code></li>
	 *                <li><code>g</code> is simple and connected</li>
	 *                </ol>
	 * @return A list of the edges that form the MST
	 */
	public static <V, E extends Weight> List<Edge<V, E>> Kruskal(UndirectedGraph<V, E> g) {
		if (g.verticesCount() < 2) {
			assert (g.edgesCount() == 0);
			return ADTs().genList();
		}

		@SuppressWarnings("unchecked")
		Edge<V, E>[] edges = g.edges().toArray(Edge[]::new);
		Algos().sort(edges, (e, f) -> Double.compare(e.getData().getWeight(), f.getData().getWeight()));
		return Kruskal(g, edges);
	}

	/**
	 * This method computes a minimum-spanning tree of a given undirected graph
	 * using the Kruskal algorithm.
	 * 
	 * @param g
	 * @param edges A sorted list of the edges in <code>g</code>
	 * @preconditions
	 *                <ol>
	 *                <li><code>g != null</code></li>
	 *                <li><code>g</code> is simple and connected</li>
	 *                <li><code>edges</code> is a sorted list of the edges in g</li>
	 *                </ol>
	 * @return A list of the edges that form the MST
	 */
	public static <V, E> List<Edge<V, E>> Kruskal(UndirectedGraph<V, E> g, Edge<V, E>[] edges) {
		assert (g.edgesCount() == edges.length);
		if (g.verticesCount() < 2) {
			assert (g.edgesCount() == 0);
			return ADTs().genList();
		}

		List<Edge<V, E>> res = ADTs().genList();
		DisjointSet<Vertex<V>> disjointSets = ADTs().genDisjointSet();
		disjointSets.addAll(g.vertices());

		for (var i = 0; i < edges.length; i++) {
			var e = edges[i];
			if (!disjointSets.findSet(e.getA()).equals(disjointSets.findSet(e.getB()))) {
				res.add(e);
				disjointSets.union(e.getA(), e.getB());
			}
		}

		return res;
	}

	/**
	 * This method computes a minimum-spanning tree of a given undirected graph
	 * using the Prim algorithm.
	 * 
	 * @param g
	 * @param r The root of the MST
	 * @preconditions
	 *                <ol>
	 *                <li><code>g != null</code></li>
	 *                <li><code>g</code> is simple and connected</li>
	 *                <li><code>r</code> has been inserted into <code>g</code></li>
	 *                </ol>
	 * @return A list of the edges that form the MST
	 */
	public static <V, E extends Weight> List<Edge<V, E>> Prim(UndirectedGraph<V, E> g, Vertex<V> r) {
		if (g.verticesCount() < 2) {
			assert (g.edgesCount() == 0);
			return ADTs().genList();
		}

		PriorityQueue<Vertex<V>> queue = ADTs().genPriorityQueue();
		Map<Vertex<V>, Edge<V, E>> pi = ADTs().genMap();

		g.vertices().filter(v -> !v.equals(r)).forEach(v -> {
			queue.insert(v, Double.POSITIVE_INFINITY);
		});
		queue.insert(r, 0);

		while (queue.size() > 0) {
			var u = queue.findMin().get();
			queue.deleteMin();

			for (var iter = g.outgoing(u).iterator(); iter.hasNext();) {
				var e = iter.next();
				var v = e.getB();
				var k = queue.getKey(v);
				if (k.isPresent() && e.getData().getWeight() < k.getAsDouble()) {
					pi.put(v, e);
					queue.decreaseKey(v, e.getData().getWeight());
				}
			}
		}

		return pi.entrySet().stream().map(Map.Entry::getValue).collect(Collectors.toCollection(ADTs()::genList));
	}
}