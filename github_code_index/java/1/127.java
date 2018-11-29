package graphs;

import java.util.LinkedList;
import java.util.Queue;

public class BreadthFirstSearch<T> {

    public void searchIterative(GraphNode<T> root) {
        Queue<GraphNode<T>> queue = new LinkedList<GraphNode<T>>();
        queue.add(root);
        while (!queue.isEmpty()) {
            GraphNode<T> currentNode = queue.element();
            if (!currentNode.visited) {
                System.out.println("Visited node " + currentNode.value);
                currentNode.visited = true;
                if (currentNode.children != null) {
                    queue.addAll(currentNode.children);
                }
            }
        }
    }

    public void searchRecursive(GraphNode<T> node) {
        for (GraphNode<T> child : node.children) {
            System.out.println("Visited node " + child.value);
        }

        for (GraphNode<T> child : node.children) {
            if (!child.visited) {
                child.visited = true;
                searchRecursive(child);
            }
        }
    }


}
