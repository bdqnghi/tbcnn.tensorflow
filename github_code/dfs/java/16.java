package org.cs4j.core.algorithms;

import org.cs4j.core.SearchAlgorithm;
import org.cs4j.core.SearchDomain;
import org.cs4j.core.SearchResult;
import org.cs4j.core.collections.PackedElement;
import org.cs4j.core.collections.SearchQueueElement;
import java.util.*;

/**
 * Created by sepetnit on 11/7/2015.
 *
 * Implementation of the simple DFS algorithm (iterative implementation)
 */
public class DFS implements SearchAlgorithm {

    // The domain for the search
    private SearchDomain domain;
    private List<SearchDomain.Operator> path = new ArrayList<>(3);
    private List<SearchDomain.State> statesPath = new ArrayList<>(3);
    // Visited list (seen states)
    private Map<PackedElement, Node> visited;

    private Stack<Node> stack;

    @Override
    public String getName() {
        return "dfs";
    }

    /**
     * Initializes the general data structures for starting the search
     */
    private void _initDataStructures() {
        this.stack = new Stack<>();
        this.visited = new HashMap<>();
    }

    @Override
    public Map<String, Class> getPossibleParameters() {
        return null;
    }

    @Override
    public void setAdditionalParameter(String parameterName, String value) {
        throw new UnsupportedOperationException();
    }

    @Override
    public SearchResult search(SearchDomain domain) {
        double goalCost = Double.MAX_VALUE;
        this.domain = domain;
        // Initialize all the data structures relevant to the search
        this._initDataStructures();

        SearchResultImpl result = new SearchResultImpl();
        result.startTimer();

        // Let's instantiate the initial state
        SearchDomain.State state = domain.initialState();
        // Create a graph node from this state
        Node initNode = new Node(state);

        this.stack.push(initNode);

        while (!this.stack.isEmpty()) {
            Node currentNode = this.stack.pop();
            // Extract the state from the packed value of the node
            state = domain.unpack(currentNode.packed);

            // Check for goal condition on the state popped from stack
            if (domain.isGoal(state)) {
                // Goal cost is calculated by traversing the path from end to start
                goalCost = 0;
                // Let' extract the solution path
                for (Node p = currentNode; p != null; p = p.parent) {
                    if (p.op != null) {
                        // Operators path
                        this.path.add(p.op);
                    }
                    // States path
                    this.statesPath.add(domain.unpack(p.packed));
                    ++goalCost;
                }
                // Finally, reverse the paths (make them to be presented from start to goal)
                Collections.reverse(path);
                Collections.reverse(statesPath);
                break;
            }

            // Ignore if already visited
            if (!this.visited.containsKey(currentNode.packed)) {
                // Add to visited
                this.visited.put(currentNode.packed, currentNode);

                // Auxiliary stack to visit neighbors in the order they appear by applying the operators
                // alternatively: iterate through the generated neighbours in reverse order
                Stack<Node> auxiliaryStack = new Stack<>();
                // Go over all the possible operators and apply them
                for (int i = 0; i < domain.getNumOperators(state); ++i) {
                    SearchDomain.Operator op = domain.getOperator(state, i);
                    // Try to avoid loops
                    if (op.equals(currentNode.pop)) {
                        continue;
                    }
                    SearchDomain.State childState = domain.applyOperator(state, op);
                    Node childNode = new Node(childState, currentNode, op, op.reverse(state));
                    // Ignore if duplicate
                    if (!this.visited.containsKey(childNode.packed)) {
                        auxiliaryStack.push(childNode);
                        //System.out.println(childState.dumpState());
                        // Debug
                        //if (this.visited.size() % 1000 == 0) {
                        //    System.out.println(childState.dumpState());
                        //}
                    }
                }
                // Finally, push all the generated states to the main stack in the true order
                while (!auxiliaryStack.isEmpty()) {
                    this.stack.push(auxiliaryStack.pop());
                }
            }
        }

        result.stopTimer();

        // If a path was found, let's instantiate a solution
        if (this.path != null && this.path.size() > 0) {
            SearchResultImpl.SolutionImpl solution = new SearchResultImpl.SolutionImpl(this.domain);
            solution.addOperators(this.path);
            solution.addStates(this.statesPath);
            solution.setCost(goalCost);
            result.addSolution(solution);
        }

        return result;
    }

    /**
     * The node class
     */
    protected final class Node extends SearchQueueElementImpl {
        private Node parent;
        private PackedElement packed;
        private SearchDomain.Operator op;
        private SearchDomain.Operator pop;

        private Node(SearchDomain.State state, Node parent, SearchDomain.Operator op, SearchDomain.Operator pop) {
            // Size of key
            super(0);
            // Parent node
            this.parent = parent;
            this.packed = DFS.this.domain.pack(state);
            this.pop = pop;
            this.op = op;
        }

        /**
         * A constructor of the class that instantiates only the state
         *
         * @param state The state which this node represents
         */
        private Node(SearchDomain.State state) {
            this(state, null, null, null);
        }

        @Override
        public double getF() {
            return 0;
        }

        @Override
        public double getG() {
            return 0;
        }

        @Override
        public double getDepth() {
            return 0;
        }

        @Override
        public double getH() {
            return 0;
        }

        @Override
        public double getD() {
            return 0;
        }

        @Override
        public double getHhat() {
            return 0;
        }

        @Override
        public double getDhat() {
            return 0;
        }

        @Override
        public SearchQueueElement getParent() {
            return this.parent;
        }
    }
}
