package OtherAlgorithms;

import Chapter3StackQueue.Queue;
import Chapter4Trees.BinarySearchTree;
import Chapter4Trees.Node;

/**
 * Created by admin on 2016-02-22.
 */
public class BreadthFirstSearch {
    public BinarySearchTree tree;
    public Queue queue;


    public BreadthFirstSearch() {
        tree = new BinarySearchTree();
        tree.insertNode(50);
        tree.insertNode(40);
        tree.insertNode(150);
        tree.insertNode(45);
        tree.insertNode(30);
        tree.insertNode(35);
        tree.insertNode(15);
        tree.insertNode(120);
        tree.insertNode(160);
        tree.insertNode(125);
        tree.insertNode(121);
        queue = new Queue();
    }

    public void breadthFirstSearch() {

        if(tree.root == null) {
            return;
        }
        Node current;
        queue.enqueue(tree.root);
        while(!queue.isEmpty()) {
            current = (Node) queue.dequeue().item;
            if(current.leftChild != null) {
                queue.enqueue(current.leftChild);
            }
            if(current.rightChild != null) {
                queue.enqueue(current.rightChild);
            }
            System.out.println("Visited Node: " + current.data);
        }
    }

    public static void main(String[] args) {
        BreadthFirstSearch bfs = new BreadthFirstSearch();
        bfs.breadthFirstSearch();
    }
}
