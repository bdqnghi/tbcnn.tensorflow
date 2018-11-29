package GeekCoder;

import java.util.*;

public class TopologicalSort {

    private Map<Node, Set<Node>> adjList = new HashMap<>();

    private Stack<Node> topoSorted = new Stack<>();

    public TopologicalSort() {}

    void addNeighbor(Node from, Node to) {
        adjList.computeIfAbsent(from, s -> new HashSet<>()).add(to);
    }

    void topologicalSort() throws Exception {

        for (Node n: adjList.keySet()) {
            if (n.visited == 0) {
                dfs(n);
            }
        }
    }

    void dfs(Node node) throws Exception {

        if (node.visited == 1) {
            throw new Exception("graph cyclic");
        }

        if (node.visited == 0) {
            node.visited = 1;
            if (adjList.containsKey(node)) {
                for (Node m : adjList.get(node)) {
                    dfs(m);
                }
            }

            node.visited = 2;
            topoSorted.push(node);
        }
    }


    public class Node {
        String value;
        int visited = 0;

        Node (String value) {
            this.value = value;
        }
    }

    public static void main(String[] args) {
        TopologicalSort g = new TopologicalSort();
        g.instantiateGraph();
    }

    void instantiateGraph() {
        Node seven = new Node("7");
        Node five = new Node("5");
        Node three = new Node("3");
        Node eleven = new Node("11");
        Node eight = new Node("8");
        Node two = new Node("2");
        Node nine = new Node("9");
        Node ten = new Node("10");

        addNeighbor(seven, eleven);
        addNeighbor(seven, eight);
        addNeighbor(five, eleven);
        addNeighbor(three, eight);
        addNeighbor(three, ten);
        addNeighbor(eleven, two);
        addNeighbor(eleven, nine);
        addNeighbor(eleven, ten);
        addNeighbor(eight, nine);

        try {
            topologicalSort();
        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        for (Node node: topoSorted) {
            System.out.print(node.value + " ");
        }
    }
}