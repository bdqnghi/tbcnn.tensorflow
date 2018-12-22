package graphs;

import java.util.Stack;

public class DepthFirstSearch<T> {

    public void searchIterative(GraphNode<T> root) {
        Stack<GraphNode<T>> stack = new Stack<>();
        stack.push(root);

        System.out.println("Visited node " + root.value);
        while (!stack.isEmpty()) {
            GraphNode<T> node = stack.pop();
            if (!node.visited) {
                node.visited = true;
                node.children.forEach(stack::push);
                System.out.println("Visited node " + node.value);
            }

        }
    }

    public void searchRecursive(GraphNode<T> node) {
        node.visited = true;
        System.out.println("Visited node " + node.value);
        node.children.stream()
                .filter(child -> !child.visited)
                .forEachOrdered(this::searchRecursive);
    }
}
