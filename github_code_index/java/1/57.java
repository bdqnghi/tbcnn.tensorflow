package algorithms.graph;

import datastructures.graph.Graph;
import datastructures.graph.GraphTraverseStrategy;

import java.util.*;

/**
 * Graph Traverse Strategy that implement the BFS algorithm.
 * The Graph cannot be modified while being traversed otherwise, unexpected behavior can happen.
 *
 * @param <T> Graph element type
 */
public class BreadthFirstSearch<T> implements GraphTraverseStrategy<T> {
    private T source;

    /**
     * Constructor for the search that will traverse only the nodes reachable from the source.
     *
     * @param source Source Node from which to start the traverse.
     */
    public BreadthFirstSearch(T source) {
        this.source = source;
    }

    @Override
    public Iterator<T> iterator(Collection<? extends Graph.Node<T>> nodes) {
        return new BfsIterator<>(source, nodes);
    }

    public static class BfsEnhancedNode<T> implements Graph.Node<T> {
        private final Graph.Node<T> node;
        private boolean marked = false;
        private final int distance;

        /**
         * @param node     Graph node
         * @param distance Distance from the BFS source
         */
        BfsEnhancedNode(Graph.Node<T> node, int distance) {
            this.node = node;
            this.distance = distance;
        }

        @Override
        public List<Graph.Edge<T>> getAdjacent() {
            return node.getAdjacent();
        }

        @Override
        public T getValue() {
            return node.getValue();
        }

        @Override
        public boolean hasEdgeTo(Graph.Node<T> target) {
            return node.hasEdgeTo(target);
        }

        public int getDistance() {
            return distance;
        }

        public boolean isMarked() {
            return marked;
        }

        public void mark() {
            marked = true;
        }
    }

    public static class BfsIterator<T> implements Iterator<T> {
        private LinkedList<BfsEnhancedNode<T>> queue = new LinkedList<>();
        private Collection<? extends Graph.Node<T>> nodes;

        private HashMap<T, BfsEnhancedNode> nodeMap = new HashMap<>();

        BfsIterator(T source, Collection<? extends Graph.Node<T>> nodes) {
            this.nodes = nodes;
            Graph.Node<T> sourceNode = nodes.stream()
                    .filter(node -> source.equals(node.getValue()))
                    .findAny()
                    .orElseThrow(IllegalArgumentException::new);
            BfsEnhancedNode<T> enhancedNode = new BfsEnhancedNode(sourceNode, 0);
            queue.add(enhancedNode);
            nodeMap.put(source, enhancedNode);
        }

        @Override
        public boolean hasNext() {
            return queue.stream().map(node -> nodeMap.get(node.getValue()))
                    .anyMatch(node -> !node.isMarked());

        }

        @Override
        public T next() {
            return nextNode().getValue();
        }

        /**
         * @return Node enhanced with BFS-related data
         */
        public BfsEnhancedNode<T> nextNode() {
            BfsEnhancedNode nextNode = null;
            while (!queue.isEmpty() && (nextNode = queue.removeFirst()).isMarked()) {
                //just loop
            }
            if (nextNode != null && !nextNode.isMarked()) {
                nextNode.mark();
                addAdjacentToMap(nextNode);
                return nextNode;
            } else {
                throw new NoSuchElementException();
            }
        }

        private void addAdjacentToMap(final BfsEnhancedNode<T> previousNode) {
            previousNode.getAdjacent().stream()
                    .map(edge -> edge.getTarget())
                    .forEach(adjNode ->
                            nodeMap.computeIfAbsent(adjNode.getValue(),
                                    key -> {
                                        BfsEnhancedNode<T> newEnhancedNode = new BfsEnhancedNode(adjNode, previousNode.getDistance() + 1);
                                        queue.add(newEnhancedNode); // simple performance enhancement - if it's in the map, it's already in the queue, so no point adding it again
                                        return newEnhancedNode;
                                    }));
        }
    }
}
