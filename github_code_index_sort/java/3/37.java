package geek.topinterview;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Stack;

/**
 * Created by ssiddiqu on 3/17/18.
 */
public class TopologicalSort {
    public static class Node {
        // these are all the child nodes of the current node
        List<Node> children;
        // value of the current node
        int val;
        int id;
        // tracks whether a node has been visited or not
        boolean visited;

        /**
         * creates a node with given id and value
         * id is not required but kept just for identification purpose to
         * verify the results
         * @param id
         * @param val
         */
        public Node(int id, int val) {
            // creates a node with given value
            this.val= val;
            children = new LinkedList<>();
            this.id = id;
            visited = false;
        }
        public String toString() {
            return "node id"+id+": value ="+val;
        }
    }
    public static class Graph {
        // these are all the nodes in the graph
        // the index in the graph matches the node id
        Node[] graph;
        // creates a graph of given size
        public Graph(int size) {
            graph = new Node[size];
        }
        public void clearVisited() {
            Arrays.stream(graph).forEach((nd)-> {
                if(nd!=null) {
                    nd.visited=false;
                }
            });
        }
        /**
         * adds a new node with given id and value
         * @param id
         * @param val
         */
        public void addNode(int id, int val) {
            // id must be between 0 and graph.length -1
            // if node with given id already exists, it will be
            // overridden
            Node nd = new Node(id, val);
            // update the graph nodes to keep track of the new node
            graph[id] = nd;
        }

        /**
         * add edge between two nodes of given ids
         * @param fromNode
         * @param toNode
         */
        public void addEdge(int fromNode, int toNode) {
            // if the node with given id does not exist
            if((graph[fromNode]==null)||(graph[toNode]==null)) {
                throw new RuntimeException("Node does not exist");
            }
            graph[fromNode].children.add(graph[toNode]);
        }

        public void printTopologicalOrder() {
            Stack<Node> tOrder = getTopologicalOrder();
            tOrder.stream().forEach((nd)-> System.out.println("Visited node"+ nd));
        }

        /**
         * For all nodes in the graph, call visitTopological
         * @return
         */
        public Stack<Node> getTopologicalOrder() {
            Stack<Node> tOrder = new Stack<Node>();
            for(Node nd:graph) {
                visitTopological(nd, tOrder);
            }
            return tOrder;
        }
        private void visitTopological(Node nd, Stack<Node> tOrder) {
            if(!nd.visited) {
                List<Node> childr= nd.children;
                if((childr!=null)||(!childr.isEmpty())) {
                    for(Node chld: childr) {
                        visitTopological(chld, tOrder);
                    }
                }
                nd.visited=true;
                tOrder.add(nd);
            }
        }

    }
    public static void testTopologicalOrder() {
        int sz = 7;
        Graph graph = new Graph(sz);
        for(int i=0; i<sz; i++ ) {
            graph.addNode(i, i+10);
        }
        graph.addEdge(0,1);
        graph.addEdge(0,5);
        graph.addEdge(1,3);
        graph.addEdge(5,1);
        graph.printTopologicalOrder();
    }
    public static void main(String[] args) {
        testTopologicalOrder();
    }

}
