package com.algorithmhelper.graphs.pathfinding;

import com.algorithmhelper.datastructures.lists.Queue;
import com.algorithmhelper.datastructures.lists.QueueDynamicArray;
import com.algorithmhelper.graphs.graphs.DirectedGraph;

public class KahnsTopologicalSortAlgorithmQueue<T extends Comparable<T>> {

    private Queue<T> topologicalOrdering;

    /**
     * Initialize a KahnsTopologicalSortAlgorithmQueue object with a graph G, and run
     * kahnsTopologicalSort on G.
     *
     * @param G, the graph
     */
    public KahnsTopologicalSortAlgorithmQueue(DirectedGraph<T> G) {
        if (G == null)
            throw new IllegalArgumentException("constructor with null graph G");

        topologicalOrdering = new QueueDynamicArray<>();

        if (G.V() == 0)
            return;

        kahnsTopologicalSort(G);
    }

    /**
     * Run Kahn's topological sort algorithm, building up the topological ordering.
     *
     * @param G, the graph
     */
    private void kahnsTopologicalSort(DirectedGraph<T> G) {
        DirectedGraph<T> reverseGraph = G.getReverseGraph();
        Queue<T> queue = new QueueDynamicArray<>();

        for (T u : reverseGraph.getVertices()) {
            if (reverseGraph.getDegree(u) == 0)
                queue.enqueue(u);
        }

        while (!queue.isEmpty()) {
            T current = queue.dequeue();
            topologicalOrdering.enqueue(current);

            for (T v : G.getAdjacent(current)) {
                reverseGraph.deleteEdge(v, current);

                if (reverseGraph.getDegree(v) == 0)
                    queue.enqueue(v);
            }
        }
    }

    /**
     * Returns an Iterable to the topological ordering found by Kahn's topological sort algorithm
     * using a stack.
     *
     * @return an Iterable to the topological ordering found by Kahn's topological sort algorithm
     *         using a stack
     */
    public Iterable<T> getTopologicalOrder() {
        return topologicalOrdering;
    }
}
