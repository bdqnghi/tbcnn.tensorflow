package algorithms.river_issue;

import algorithms.utility.GraphPreconditions;
import algorithms.utility.Stopwatch;
import com.google.common.base.Preconditions;
import com.google.common.collect.ImmutableList;
import org.apache.log4j.Logger;
import org.graphstream.graph.Edge;
import org.graphstream.graph.Graph;
import org.graphstream.graph.Node;
import org.graphstream.graph.implementations.Graphs;
import org.graphstream.graph.implementations.SingleGraph;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.*;

/**
 * Ford Folkerson algorithm for max flow in a graph with capacities.
 */
public class FordFulkerson implements MaxFlowStrategy {
    private static final Logger LOG = Logger.getLogger(FordFulkerson.class);
    public static boolean preview = false;
    Stopwatch stopwatch;
    boolean computable = false;

    Graph graph;
    private List<Node> nodes = new LinkedList<>();
    Node source;
    Node sink;

    Double capacity[][]; // capacity
    Double flow[][]; // flow
    private Node predecessor[]; // predecessor
    Double delta[]; // delta
    private boolean forward[];
    boolean inspected[];

    double maxFlow;

    public void init(@NotNull final Graph graph,
                     @NotNull final Node source,
                     @NotNull final Node sink) throws IllegalArgumentException {
        Preconditions.checkNotNull(graph, "graph has to be not null!");
        Preconditions.checkNotNull(source, "source has to be not null!");
        Preconditions.checkNotNull(sink, "target has to be not null!");
        GraphPreconditions.isNetwork(graph);

        this.source = source;
        this.sink = sink;
        nodes = ImmutableList.copyOf(graph.getEachNode());
        final int size = nodes.size();
        this.graph = graph;

        capacity = new Double[size][size];
        flow = new Double[size][size];
        predecessor = new Node[size];
        delta = new Double[size];
        forward = new boolean[size];
        inspected = new boolean[size];
        maxFlow = 0;

        // Initialize empty flow & capacity.
        final Iterator<Node> iIterator = nodes.iterator();
        for (int i = 0; i < size; i++) {
            final Node nodeI = iIterator.next();
            final Iterator<Node> jIterator = nodes.iterator();
            for (int j = 0; j < size; j++) {
                final Node nodeJ = jIterator.next();
                final Edge edgeBetween = nodeI.getEdgeBetween(nodeJ);
                if (edgeBetween != null) {
                    capacity[i][j] = edgeBetween.getAttribute("capacity");
                }
                flow[i][j] = 0.0;
            }
            delta[i] = Double.POSITIVE_INFINITY;
        }

        delta[indexOf(source)] = Double.POSITIVE_INFINITY;
        mark(indexOf(source), null, true, delta[indexOf(source)]);
        computable = true;
    }

    public void compute() {
        stopwatch = new Stopwatch();
        if (preview) LOG.debug("==== (2) compute ====");
        if (!computable)
            throw new IllegalStateException("Do init(Graph) before compute()");
        /* (2) Inspektion und Markierung */
        // current setzten wir auch einen bel. markierten aber nicht inspizierten wert
        while (!areAllMarkedNodesInspected()) {
            final Node node = getMarkedButNotInspected(); // V_i
            final Integer i = indexOf(node);
            if (preview) LOG.debug("Found marked but not inspected node (v_i): " + node);
            if (preview) LOG.debug(">>> Starting inspection >>>");

            // OUTPUT
            for (final Edge leavingEdge : node.getEachLeavingEdge()) {   // E_ij elemOf Output(V_i)
                final Node targetNode = leavingEdge.getTargetNode();
                final Integer j = indexOf(targetNode);

                if (!isMarked(targetNode) && flow[i][j] < capacity[i][j]) { // nur unmarkierte Knoten markieren V_j mit f(E_ij) < c(E_ij)
                    if (preview)
                        LOG.debug(String.format("Found unmarked node %s (v_j) with f(E_ij)=%f < c(E_ij))=%f", targetNode.getId(), flow[i][j], capacity[i][j]));
                    // markiere VERTEX_j
                    mark(j, node, true, Math.min(delta[i], capacity[i][j] - flow[i][j]));
                }
            }

            // INPUT
            for (final Edge enteringEdge : node.getEachEnteringEdge()) {   // E_ji elemOf Input(V_i)
                final Node sourceNode = enteringEdge.getSourceNode();
                final Integer j = indexOf(sourceNode);

                if (!isMarked(sourceNode) && flow[j][i] > 0) { // nur unmarkierter Knoten V_j mit f(E_ji) > 0
                    if (preview)
                        LOG.debug(String.format("Found unmarked node %s (v_j) with f(E_ji)=%f > 0", sourceNode.getId(), flow[j][i]));
                    // markiere V_j
                    mark(j, node, false, Math.min(delta[i], flow[i][j]));
                }
            }

            inspected[indexOf(node)] = true;
            if (preview) LOG.debug("<<< Inspection done <<<");

            // (3) Vergrößerung der Flussstärke
            if (isMarked(sink)) {
                compute_AugmentedPath();
            }
        }

        // (4) Es gibt keinen vergrößernden Weg
        compute_Cut();
    }

    /* (3) Vergrößerung der Flussstärke */
    void compute_AugmentedPath() {
        if (preview) LOG.debug("==== (3) compute augmentedPath ====");
        Node current = sink;
        maxFlow += delta[indexOf(sink)];
        while (hasPred(current)) {
            final int j = indexOf(current);
            final Node pred = predecessor[j];
            Edge edge = pred.getEdgeBetween(current);
            if (edge == null)
                edge = current.getEdgeBetween(pred);
            final Double delta_s = delta[indexOf(sink)]; // DELTA_s

            if (edge.getTargetNode() == current) { // Wenn Vorwärtskante...
                final int i = indexOf(edge.getSourceNode());
                flow[i][j] = flow[i][j] + delta_s; // ...dann wird f(E_ij) um d_s erhöhen
                if (preview)
                    LOG.debug(String.format("%s[%s -> %s] got increased by %f and is now %f", edge.getId(), nodes.get(i), nodes.get(j), delta_s, flow[i][j]));

            } else if (edge.getSourceNode() == current) { // Wenn Rückwärtskante...
                final int i = indexOf(edge.getTargetNode());
                flow[j][i] = flow[j][i] - delta_s; // ...dann wird f(E_ji) um d_s verringert
                if (preview)
                    LOG.debug(String.format("%s[%s -> %s] got decreased by %f and is now %f", edge.getId(), nodes.get(j), nodes.get(i), delta_s, flow[j][i]));

            } else {
                throw new IllegalArgumentException("WTF: Something impossible went wrong");
            }
            current = pred;
        }
        deleteAllMarks();
        if (preview) LOG.debug("==== done with augmentedPath ====");
    }

    /* (4) Es gibt keinen vergrößernden Weg ( Max-Flow-Min-Cut-Theorem ) */
    // from: https://de.wikipedia.org/wiki/Max-Flow-Min-Cut-Theorem
    void compute_Cut() {
        if (preview) LOG.debug("==== (4) compute_Cut ====");
        computable = false;
        final Graph residualGraph = residualNetwork(); // Residualnetzwerk(G)

        final Set<Node> nodesS = new HashSet<>();
        final Set<Node> nodesT = new HashSet<>();
        for (final Node v : residualGraph.getEachNode()) {
            if (hasPath(residualGraph.getNode(source.getId()), v)) { // Wenn ein Pfad(s,v) in G existiert...
                nodesS.add(v);
                if (preview) LOG.debug("Path(s,v) exists: S <- S v {" + v + "}");
            } else {
                nodesT.add(v);
                if (preview) LOG.debug("Path(s,v) doesn't exists: T <- T v {" + v + "}");
            }
        }

        final Set<Edge> cut = new HashSet<>();

        for (final Edge e : residualGraph.getEachEdge()) { // Für jede Kante e aus E
            final Node sourceNode = e.getSourceNode();
            final Node targetNode = e.getTargetNode();
            if ((nodesS.contains(sourceNode) && nodesT.contains(targetNode)) || (nodesS.contains(targetNode) && nodesT.contains(sourceNode))) { // Wenn startNode(e) aus S und endNode(e) aus T liegt...
                cut.add(e);
                if (preview) LOG.debug(String.format("%s->%s added to Cut", sourceNode, targetNode));
            }

        }

        stopwatch.stop();
        if (preview) LOG.debug("Cut[" + cut + "]");
        if (preview) LOG.debug("==== compute_Cut done ====");
        if (preview) LOG.debug("Algorithms finished in " + stopwatch.getEndTimeString());
    }


    /**
     * Transforms the given graph to a residual network
     */
    Graph residualNetwork() {
        final Graph residualGraph = Graphs.clone(graph);
        if (preview) LOG.debug(">>> residualNetwork >>>");

        for (final Edge e : residualGraph.getEachEdge()) {
            final double currCapacity = e.getAttribute("capacity");
            final Node sourceNode = e.getSourceNode();
            final Node targetNode = e.getTargetNode();
            final double currFlow = flow[indexOfWithClone(sourceNode.getId())][indexOfWithClone(targetNode.getId())];

            if (currFlow > 0) {
                residualGraph.addEdge(
                        targetNode.getId() + sourceNode.getId(),
                        targetNode.getId(),
                        sourceNode.getId(),
                        true).setAttribute("capacity", currFlow);
                if (preview)
                    LOG.debug(String.format("Edge %s created with %f capacity", targetNode.getId() + sourceNode.getId(), currFlow));

                if (currCapacity - currFlow == 0) {
                    residualGraph.removeEdge(sourceNode.getEdgeToward(targetNode).getId());
                    if (preview)
                        LOG.debug(String.format("Edge %s deleted because 0 capacity left", sourceNode.getId() + targetNode.getId()));
                } else {
                    residualGraph.getEdge(
                            sourceNode.getEdgeToward(targetNode).getId()
                    ).setAttribute("capacity", (currCapacity - currFlow));
                    if (preview)
                        LOG.debug(String.format("Capacity from Edge %s decreased from  %f to %f", sourceNode.getId() + targetNode.getId(), currCapacity, (currCapacity - currFlow)));
                }
            }

        }
        if (preview) LOG.debug("<<< residualNetwork done <<<");
        return residualGraph;
    }


    /**
     * Returns true if node can be reached
     *
     * @param from source node
     * @param to   target node
     * @return true if node can be reached
     */
    private boolean hasPath(final Node from, final Node to) {
        final Iterator<Node> breadthFirstIterator = from.getBreadthFirstIterator(true);
        while (breadthFirstIterator.hasNext()) {
            final Node next = breadthFirstIterator.next();
            if (next.equals(to))
                return true;
        }
        return false;
    }

    /**
     * @return true if all marked nodes are inspected
     */
    private boolean areAllMarkedNodesInspected() {
        for (final Node node : graph.getEachNode()) {
            if (isMarked(node) && !inspected[indexOf(node)])
                return false;
        }
        return true;
    }

    /**
     * Returns marked but not inspected node
     *
     * @return marked but not inspected node
     */
    @NotNull
    private Node getMarkedButNotInspected() {
        for (final Node node : graph.getEachNode()) {
            if (isMarked(node) && !inspected[indexOf(node)]) {
                return node;
            }
        }
        throw new IllegalArgumentException("no node found!");
    }

    /**
     * Returns index of a Node
     *
     * @param node from we want to know the index
     * @return index
     * @throws NoSuchElementException no such node in the list
     */
    @NotNull
    Integer indexOf(@NotNull final Node node) {
        final int i = nodes.indexOf(node);
        if (i < 0) throw new NoSuchElementException();
        return i;
    }

    /**
     * Returns index of a Node
     *
     * @param nodeId from we want to know the index
     * @return index
     * @throws NoSuchElementException no such node in the list
     */
    @NotNull
    private Integer indexOfWithClone(@NotNull final String nodeId) {
        final Node first = nodes.stream().filter(e -> e.getId().equals(nodeId)).findFirst().get();
        final int i = nodes.indexOf(first);
        if (i < 0) throw new NoSuchElementException();
        return i;
    }

    private boolean hasPred(final Node node) {
        return (predecessor[indexOf(node)] != null);
    }

    /**
     * returns true if given node is marked;
     */
    @NotNull
    Boolean isMarked(@NotNull final Node node) {
        final int i = indexOf(node);
        return node == source || (delta[i] != Double.POSITIVE_INFINITY && predecessor[i] != null);
    }

    /**
     * Marks an Node and sets values in the arrays predecessor[], forward[] and delta[]
     *
     * @param idx         Index
     * @param predecessor Predecessor
     * @param forward     True if Edge goes forward
     * @param delta       Delta value
     */
    void mark(@NotNull final Integer idx,
              @Nullable final Node predecessor,
              @NotNull final Boolean forward,
              @NotNull final Double delta) {
        Preconditions.checkNotNull(idx, "idx has to be not null!");
        Preconditions.checkNotNull(forward, "forward has to be not null!");
        Preconditions.checkNotNull(delta, "delta has to be not null!");

        this.predecessor[idx] = predecessor;
        this.forward[idx] = forward;
        this.delta[idx] = delta;
        if (preview)
            LOG.debug(String.format("%s (%s%s, %f)", nodes.get(idx), (forward ? "+" : "-"), predecessor, delta));
    }

    /**
     * Reset of the arrays for the mark
     */
    private void deleteAllMarks() {
        if (preview) LOG.debug(">>> Starting deleteAllMarks >>>");
        for (int i = 0; i < nodes.size(); i++) {
            inspected[i] = false;
            if (i != indexOf(source)) {
                mark(i, null, false, Double.POSITIVE_INFINITY);
            }
        }
        if (preview) LOG.debug("<<< DeleteAllMarks done <<<");
    }

    // === MAIN ===
    public static void main(final String[] args) throws Exception {
        // https://de.wikipedia.org/wiki/Max-Flow-Min-Cut-Theorem
        final Graph maxFminCGraph = new SingleGraph("maxFminCGraph");
        maxFminCGraph.addNode("O");
        maxFminCGraph.addNode("P");
        maxFminCGraph.addNode("Q");
        maxFminCGraph.addNode("R");
        maxFminCGraph.addNode("S");
        maxFminCGraph.addNode("T");

        maxFminCGraph.addEdge("SO", "S", "O", true).addAttribute("capacity", 3.0);
        maxFminCGraph.addEdge("SP", "S", "P", true).addAttribute("capacity", 3.0);
        maxFminCGraph.addEdge("OP", "O", "P", true).addAttribute("capacity", 2.0);
        maxFminCGraph.addEdge("OQ", "O", "Q", true).addAttribute("capacity", 3.0);
        maxFminCGraph.addEdge("PR", "P", "R", true).addAttribute("capacity", 2.0);
        maxFminCGraph.addEdge("QR", "Q", "R", true).addAttribute("capacity", 4.0);
        maxFminCGraph.addEdge("QT", "Q", "T", true).addAttribute("capacity", 2.0);
        maxFminCGraph.addEdge("RT", "R", "T", true).addAttribute("capacity", 3.0);

        final FordFulkerson ford = new FordFulkerson();
        ford.init(maxFminCGraph, maxFminCGraph.getNode("S"), maxFminCGraph.getNode("T"));
        ford.compute();
    }

}
