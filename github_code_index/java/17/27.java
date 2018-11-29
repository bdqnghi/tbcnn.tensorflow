package algorithms.CrackingTheCodingInterview;

import java.util.Collection;

public class RedBlackTree {

    /*
    *
    * 1) Every node has a color either red or black.
    * 2) Root of tree is always black.
    * 3) There are no two adjacent red nodes (A red node cannot have a red parent or red child).
    * 4) Every path from root to a NULL node has same number of black nodes.
    *
    *
    *              4
    *            /  \
    *          2     6
    *         / \   / \
    *        1  3  5  7
    *
    *
    */

    enum Color {
        RED,
        BLACK
    }

    static class Node {
        private int data;
        private Color color;
        private Node left;
        private Node right;

        Node (int data) {
            this.data = data;
            this.color = Color.BLACK;
            this.left = null;
            this.right = null;
        }
    }

    private Node root;

    // TODO: insert
    // TODO: delete

    public static void main(String[] args) {

    }

}
