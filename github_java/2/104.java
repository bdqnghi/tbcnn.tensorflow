package Goodrich_AVLTree;

import java.util.Comparator;
import java.util.Dictionary;

/**
 * Created by alex on 02.11.15.
 */
public class AVLTree<Key extends Comparable <Key>>{

    int height;

    Node root;

    Comparator C;

    public int getHeight() {
        return height;
    }

    public int setHeight(int h) {
        int oldGeight = height;
        height = h;
        return oldGeight;
    }

    private class Node {
        private Key key;
        private Node right, left, parent;
        private int height;

        private Node(Key key) {
            if (root == null)
                root = this;
            this.key = key;
            this.left = null;
            this.right = null;
            height = 1;
        }

        private int height() {
            return height;
        }

        public int setHeight(int h) {
            int oldHeight = height;
            height = h;
            return oldHeight;
        }

        private Key key() {
            return key;
        }

        private void setKey(Key key) {
            this.key = key;
        }

        private int bfactor() {
            return this.right.height() - this.left.height();
        }

        private void fixheight() {
            int hl = this.left.height();
            int hr = this.right.height();
           // this.height =
        }

    }



    private void rebalance(Node z) {
        while(z != root) {
            z = z.parent;
            setHeight(z.height());
            if (!isBalanced(z)) {
                Node x = tallerChild(tallerChild(z));
              //  z =
            }
        }
    }

    private Node tallerChild(Node z) {
        if (z.left.height() >= z.right.height())
            return z.left;
        else
            return z.right;
    }

    private boolean isBalanced(Node x) {
        int bf = x.left.height() - x.right.height();
        return ((-1 <= bf) && (bf <= 1));
    }

    public Node find(Key key) {
        Node current = root;
        while(current.key != key) {
            if (key.compareTo(current.key) < 0)
                current = current.left;
            else
                current = current.right;
            if (current == null)
                return null;
        }
        return current;
    }

}
