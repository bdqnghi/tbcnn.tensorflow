package Algorithms;

import com.sun.org.apache.regexp.internal.recompile;

import java.util.TreeMap;

/**
 * Created by А on 30.10.14.
 */
public class RedBlackTree {

    private static final boolean RED   = false;
    private static final boolean BLACK = true;

    static class Node {
        private Node rightChild;
        private Node leftChild;
        private Node parent;
        private int value;
        private boolean color;

        Node(int value) {
            this.value = value;
            leftChild = rightChild = parent = null;
        }

        @Override
        public String toString() {
            return "Node{ " +
//                    "leftChild=" + leftChild.value +
//                    ", rightChild=" + rightChild.value +
//                    ", parent=" + parent.value +
                    ", value=" + value +
                    ", color=" + color +
                    '}';
        }
    }

    private Node root;
    private Node tempParent = root;
    private int size;

    public RedBlackTree() {
        root = null;
        size = 0;
    }

    public void insert(int value) {
        Node current;
        if (root == null) {
            root = new Node(value);
            root.color = BLACK;
        } else {
            current = this.insertInto(root, value);
            if (current != null)
                current.color = RED;
            if (current.parent.color == RED)
                balance(current);
        }
        size++;
    }

    private Node insertInto(Node current, int value) {
        if (current == null) {
            current = new Node(value);
            current.parent = tempParent;
            if (current.value < tempParent.value)
                tempParent.leftChild = current;
            else
                tempParent.rightChild = current;
            return current;
        } else if (value == current.value)
            return null;
        else if (value < current.value) {
            tempParent = current;
            return insertInto(current.leftChild, value);

        } else {
            tempParent = current;
            return insertInto(current.rightChild, value);
        }
    }

    private void balance(Node current) {
        while (current != root && current.color == RED) {
            Node parent = current.parent;
            Node grandParent;
            try {
                grandParent = parent.parent;
            } catch (NullPointerException e) {
                break;
            }
            Node uncle;
            if (grandParent == null) break;
            if (parent == grandParent.leftChild) {
                uncle = grandParent.rightChild;
                if (uncle == null)
                    rotateRight(grandParent);
                else {
                    if (uncle.color == RED) {
                        recolor(current);
                        continue;
                    } else if (current == parent.rightChild) {
                        current = rotateLeft(parent);  // after rotation "current" references to Node who previously was current's parent
                    }
                    rotateRight(current.parent.parent); // method is called for "new current"'s grandparent
                }
            } else {
                uncle = grandParent.leftChild;
                if (uncle == null)
                    rotateLeft(grandParent);
                else {
                    if (uncle.color == RED) {
                        recolor(current);
                        continue;
                    } else if (current == parent.leftChild)
                        current = rotateRight(parent);
                    rotateLeft(current.parent.parent);
                }
            }
            current = current.parent;
        }
        root.color = BLACK;
    }

    private void recolor(Node current) {
        while (current != root && current.color == RED) {
            Node parent = current.parent;
            Node grandParent;
            try {
                grandParent = parent.parent;
            } catch (NullPointerException e) {
                break;
            }
            Node uncle;
            if (parent == grandParent.leftChild)
                uncle = grandParent.rightChild;
            else
                uncle = grandParent.leftChild;
            parent.color = uncle.color = BLACK;
            grandParent.color = RED;
            current = grandParent;
        }
    }

    private Node rotateLeft(Node current) {
        Node y = current.rightChild;
        current.rightChild = y.leftChild;
        if (y.leftChild != null)
            y.leftChild.parent = current;
        y.parent = current.parent;
        if (current.parent != null) {
            if (current == current.parent.leftChild)
                current.parent.leftChild = y;
            else
                current.parent.rightChild = y;
        }
        y.leftChild = current;
        current.parent = y;
        return current;
    }

    private Node rotateRight(Node current) {
        Node y = current.leftChild;
        current.leftChild = y.rightChild;
        if (y.rightChild != null)
            y.rightChild.parent = current;
        y.parent = current.parent;
        if (current.parent != null) {
            if (current == current.parent.leftChild)
                current.parent.leftChild = y;
            else
                current.parent.rightChild = y;
            }
        y.rightChild = current;
        current.parent = y;
        return current;
    }

    public void printAll() {
        walkTree(root);
    }

    private void walkTree(Node node) {
        if (node != null) {
            System.out.println(node.toString());
            walkTree(node.leftChild);
            walkTree(node.rightChild);
        }
    }
}
