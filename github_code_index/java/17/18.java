/*
 * This file is part of the CS372Assignment6Exercise5 project.
 *
 * Author: Omid Jafari - omidjafari.com
 * Copyright (c) 2018
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

public class RedBlackTree {

    // Instance variables
    private Node root;

    // Constructor
    public RedBlackTree() {
        this.root = null;
    }

    // Check to see if tree is a Binary Search Tree
    public boolean isBST() {
        return isBST(this.root, null, null);
    }

    private boolean isBST(Node x, Integer min, Integer max) {
        if (x == null)
            return true;

        if (min != null && x.getValue() <= min)
            return false;

        if (max != null && x.getValue() >= max)
            return false;

        return isBST(x.getLeftChild(), min, x.getValue()) && isBST(x.getRightChild(), x.getValue(), max);
    }

    // Check to see if root is black
    public boolean isRootBlack() {
        if (this.root != null && this.root.getColor() == 'r')
            return false;

        return true;
    }

    // Check to see if red nodes have any red child
    public boolean isRedRedChild() {
        return isRedRedChild(this.root);
    }

    private boolean isRedRedChild(Node x) {
        if (x == null)
            return false;

        if (x.getColor() == 'r')
            if (x.getLeftChild() != null && x.getLeftChild().getColor() == 'r')
                return true;
            else if (x.getRightChild() != null && x.getRightChild().getColor() == 'r')
                return true;

        return isRedRedChild(x.getLeftChild()) || isRedRedChild(x.getRightChild());
    }

    // Check to see if Black Height of different paths is the same
    public boolean isBlackHeightSame() {
        if (blackHeight(this.root) == 0)
            return false;
        else
            return true;
    }

    private int blackHeight(Node x) {
        if (x == null)
            return 1;

        int leftBlackHeight = blackHeight(x.getLeftChild());
        if (leftBlackHeight == 0)
            return 0;

        int rightBlackHeight = blackHeight(x.getRightChild());
        if (rightBlackHeight == 0)
            return 0;

        if (leftBlackHeight != rightBlackHeight)
            return 0;

        if (x.getColor() == 'b')
            return rightBlackHeight + 1;
        else
            return rightBlackHeight;
    }

    // Insert function (we need this to create a RedBlack tree from input file)
    public boolean insert(Node x) {
        if (this.root == null) {
            root = x;
            return true;
        } else {
            return insert(this.root, x);
        }
    }

    private boolean insert(Node root, Node x) {
        if (root == null)
            return false;

        if (x.getPosition() == root.getLeftChildPos()) {
            root.setLeftChild(x);
            return true;
        } else if (x.getPosition() == root.getRightChildPos()) {
            root.setRightChild(x);
            return true;
        } else {
            return insert(root.getLeftChild(), x) || insert(root.getRightChild(), x);
        }
    }
}
