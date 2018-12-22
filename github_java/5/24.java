package algorithms.graph;

import datastructures.graph.Graph;
import datastructures.graph.GraphTraverseStrategy;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class DepthFirstSearch<T> implements GraphTraverseStrategy<T> {
    private T source;

    public DepthFirstSearch(T source) {
        this.source = source;
    }

    @Override
    public Iterator<T> iterator(Collection<? extends Graph.Node<T>> nodes) {
        return new DfsIterator<>(source, nodes);
    }

    public static class DfsIterator<T> implements Iterator<T> {
        private LinkedList<DfsEnhancedNode<T>> stack = new LinkedList<>();
        private Map<T, DfsEnhancedNode> nodeMap = new HashMap<>();

        public DfsIterator(T source, Collection<? extends Graph.Node<T>> nodes) {
            Graph.Node<T> node = nodes.stream()
                    .filter(streamNode -> source.equals(streamNode.getValue()))
                    .findAny()
                    .orElseThrow(IllegalArgumentException::new);

            DfsEnhancedNode<T> enhancedNode = new DfsEnhancedNode<>(node);
            stack.push(enhancedNode);
            nodeMap.put(source, enhancedNode);
        }

        @Override
        public boolean hasNext() {
            return stack.stream().anyMatch(node -> !node.isMarked());
        }

        @Override
        public T next() {
            DfsEnhancedNode<T> nextNode = null;
            while (!stack.isEmpty() && (nextNode = stack.pop()).isMarked()) {
                // just loop
            }
            if (nextNode != null && !nextNode.isMarked()) {
                LinkedList<Graph.Node<T>> adjacent = StreamSupport.stream(nextNode.getAdjacent().spliterator(), false)
                        .map(Graph.Edge::getTarget)
                        .collect(Collectors.toCollection(LinkedList::new));
                // put node on stack in reverse order to keep natural order when processing
                ListIterator<Graph.Node<T>> lit = adjacent.listIterator(adjacent.size());
                while (lit.hasPrevious()) {
                    Graph.Node<T> adjNode = lit.previous();
                    DfsEnhancedNode adjEnhanced = nodeMap.computeIfAbsent(adjNode.getValue(), key -> new DfsEnhancedNode(adjNode));
                    if (!adjEnhanced.isMarked()) { //performance improvement - no point of putting node on the stack if it was already visited
                        stack.push(adjEnhanced);
                    }
                }
                nextNode.mark();
                return nextNode.getValue();
            } else {
                throw new NoSuchElementException();
            }
        }
    }

    public static class DfsEnhancedNode<T> implements Graph.Node<T> {
        private final Graph.Node<T> node;
        private boolean marked = false;

        /**
         * @param node Graph node
         */
        DfsEnhancedNode(Graph.Node<T> node) {
            this.node = node;
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

        public boolean isMarked() {
            return marked;
        }

        public void mark() {
            marked = true;
        }
    }
}
