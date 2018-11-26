package graph;

import heap.AugmentedBinaryHeap;

import java.io.FileReader;
import java.util.*;

public class MinimumSpanningTree<T> {
    public static class Node<T> extends AugmentedBinaryHeap.AbstractElement{
        private final T val;
        private List<Edge<T>> edges;
        private boolean visited = false;

        private Edge<T> minEdge;

        private int getPriority() {
            return minEdge == null ? Integer.MAX_VALUE : minEdge.cost;
        }

        public Node(T val) {
            Objects.requireNonNull(val);
            this.val = val;
        }

        private List<Edge<T>> getEdges() {
            return edges == null ? Collections.emptyList() : edges;
        }

        public Edge<T> connect(Node<T> other, int cost) {
            Edge<T> edge = new Edge<T>(this, other, cost);
            this.addEdge(edge);
            other.addEdge(edge);
            return edge;
        }

        private void addEdge(Edge<T> edge) {
            if(edges == null) edges = new ArrayList<>();
            edges.add(edge);
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;

            Node<?> node = (Node<?>) o;

            return val.equals(node.val);
        }

        @Override
        public String toString() {
            return val.toString();
        }

        @Override
        public int hashCode() {
            return val.hashCode();
        }
    }

    public static class Edge<T> {
        private final Node<T> a;
        private final Node<T> b;
        private final int cost;
        public Edge(Node<T> a, Node<T> b, int cost) {
            this.a = a;
            this.b = b;
            this.cost = cost;
        }

        @Override
        public String toString() {
            final StringBuffer sb = new StringBuffer("{");
            sb.append(a);
            sb.append(",").append(b);
            sb.append(", cost=").append(cost);
            sb.append('}');
            return sb.toString();
        }

        public Node<T> getOtherEnd(Node<T> oneEnd) {

            return oneEnd.equals(a) ? b : a;
        }
    }

    private Map<T, Node<T>> nodes;
    private List<Edge<T>> edges;

    public MinimumSpanningTree() {
        this.nodes = new HashMap<>();
        this.edges = new ArrayList<>();
    }

    private void addNode(T value) {
        assertContainNode(false, value);
        nodes.put(value, new Node<>(value));
    }

    private void assertContainNode(boolean isContained, T... value) {
        for(T val : value) {
            if (isContained != nodes.containsKey(val)) throw new IllegalArgumentException();
        }
    }

    private void addEdge(T a, T b, int cost) {
        assertContainNode(true, a, b);
        this.edges.add(nodes.get(a).connect(nodes.get(b), cost));
    }

    public List<Edge<T>> computeMinimumSpanningTree() {
        if(edges.isEmpty()) return Collections.emptyList();
        return computeMSTPrim();
    }

    private void prepareMSTPRIM() {
        for(Node<T> node : nodes.values()) {
            node.visited = false;
            node.minEdge = null;
        }
    }

    private List<Edge<T>> computeMSTPrim() {
        // initialize
        prepareMSTPRIM();
        List<Edge<T>> selectedEdges = new ArrayList<>();
        AugmentedBinaryHeap<Node<T>> heap = new AugmentedBinaryHeap<>(Comparator.comparingInt(n -> n.getPriority()));

        Set<Node<T>> unProcessedVertices = new HashSet<>(nodes.values());
        Node<T> arbitraryNode = unProcessedVertices.iterator().next();
        arbitraryNode.visited = true;
        unProcessedVertices.remove(arbitraryNode);

        for(Edge<T> edge : arbitraryNode.getEdges()) {
            Node<T> otherEnd = edge.getOtherEnd(arbitraryNode);
            otherEnd.minEdge = edge;
            heap.insert(otherEnd);
            unProcessedVertices.remove(otherEnd);
        }

        for(Node<T> left : unProcessedVertices)
            heap.insert(left);

        // ready to process
        while(!heap.isEmpty()) {
            Node<T> node = heap.delMin();
            node.visited = true;
            selectedEdges.add(node.minEdge);

            for(Edge<T> edge : node.getEdges()) {
                Node<T> otherEnd = edge.getOtherEnd(node);
                if(!otherEnd.visited && edge.cost < otherEnd.getPriority()) {
                    heap.delete(otherEnd);
                    otherEnd.minEdge = edge;
                    heap.insert(otherEnd);
                }
            }
        }
        return selectedEdges;
    }

    public static void main(String[] args) throws Exception {
        MinimumSpanningTree<Integer> min = new MinimumSpanningTree<>();
        Scanner in = new Scanner(new FileReader("./testData/graph/minSpanningTree.txt"));
        String[] size = in.nextLine().trim().split(" ");
        for(int i = 1; i <= Integer.valueOf(size[0]); i ++) min.addNode(i);

        while (in.hasNextLine()) {
            String[] edge = in.nextLine().trim().split("\\s+");
            System.out.println(Arrays.toString(edge));
            min.addEdge(Integer.valueOf(edge[0]), Integer.valueOf(edge[1]), Integer.valueOf(edge[2]));
        }
        System.out.println(min.computeMinimumSpanningTree().stream().map(i -> i.cost).reduce(0, (i1, i2) -> i1 + i2));
    }
}
