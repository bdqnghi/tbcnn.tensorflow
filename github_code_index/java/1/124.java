package trees;

import java.util.LinkedList;
import java.util.Queue;

public class BreadthFirstSearchQueue {
    static class Node {
        int key;
        Node left,right;
        public Node (int key) {
            this.key = key;
            left = right = null;
        }
    }

    Node root;

    int getHeight(Node node) {
        if (node == null)
            return 0;
        int height =1;
        int treeheight = height + Math.max(getHeight(node.left), getHeight(node.right));
        return treeheight;
    }

    void printBST(Node node) {
        if (node == null)
            return;
        Queue queue = new LinkedList();
        ((LinkedList) queue).add(node);

        while (!queue.isEmpty()) {
            Node queueNode = (Node) queue.remove();
            System.out.print(queueNode.key + " ");
            if (queueNode.left!=null)
                ((LinkedList) queue).add(queueNode.left);
            if (queueNode.right!=null)
                ((LinkedList) queue).add(queueNode.right);
        }
    }

    public static void main(String[] args) {
        BreadthFirstSearchQueue breadthFirstSearch = new BreadthFirstSearchQueue();
        breadthFirstSearch.root = new Node(1);
        breadthFirstSearch.root.left = new Node(2);
        breadthFirstSearch.root.left.left = new Node(4);
        breadthFirstSearch.root.left.left.left = new Node(8);
        breadthFirstSearch.root.left.right = new Node(5);
        breadthFirstSearch.root.right = new Node(3);
        breadthFirstSearch.root.right.left = new Node(6);
        breadthFirstSearch.root.right.left.left = new Node(9);
        breadthFirstSearch.root.right.right = new Node(7);
        breadthFirstSearch.root.right.right.right = new Node(10);

        int height = breadthFirstSearch.getHeight(breadthFirstSearch.root);
        breadthFirstSearch.printBST(breadthFirstSearch.root);

    }
}
