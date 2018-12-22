package com.alexvolov.ads.ds.impl;

import com.alexvolov.ads.ds.BinaryTree;
import com.alexvolov.ads.ds.common.TreeNode;

/**
 * Red-black tree is a binary search tree which guaranties searching,
 * insertion and deletion in logarithmic time. As all extensions of
 * BST it has additional properties which helps to keep tree balanced:
 * </p>
 * <ol>
 * <li> A node has color either black or red associated with it.
 * <li> The root node is black.
 * <li> All leaves are black and don’t contain data. Sometimes to reduce
 * memory consumption a single node performs the role of all leaves.
 * <li> Every red node must have two black child. This implies that on
 * any path there can’t be two consecutive red nodes or in other words
 * a red node can’t have a red child.
 * <li> Every path from a node to a descendant leaf contains the same
 * number of black nodes. This number is called black height.
 * </ol>
 *
 * @author Alexander Volov (mailto: alevolov@gmail.com)
 * @see com.alexvolov.ads.ds.BinaryTree
 * @see com.alexvolov.ads.ds.impl.BinarySearchTree
 * @version 25.01.15
 */
public class RedBlackTree extends BinarySearchTree implements BinaryTree {

    private static final boolean RED   = false;
    private static final boolean BLACK = true;

    /**
     * Creates a new instance of a red-black tree.
     */
    public RedBlackTree() {
        super();
        nil = new TreeNode(null);
        nil.setColor(BLACK);
    }

    @Override
    public TreeNode insert(int value) {
        TreeNode newNode = super.insert(value);
        if (null != newNode) {
            newNode.setColor(RED);
            newNode.setLeft(nil);
            newNode.setRight(nil);
            restoreBalanceAfterInsert(newNode);
        }
        return newNode;
    }

    @Override
    public TreeNode delete(int value) {
        TreeNode delNode = search(value);
        TreeNode node = super.delete(value);
        if (null != delNode && BLACK == originalColor) {
           restoreBalanceAfterDelete(node);
        }
        return node;
    }

    private void restoreBalanceAfterInsert(TreeNode node) {
        while (null != node.getParent() && RED == node.getParent().getColor()) {
            TreeNode uncle = getUncle(node);
            TreeNode grandparent = getGrantParent(node);
            if (null != uncle && RED == uncle.getColor() && RED == node.getParent().getColor()) {
                node.getParent().setColor(BLACK);
                uncle.setColor(BLACK);
                grandparent.setColor(RED);
                node = grandparent;
            } else if (null != grandparent) {
                if (node.equals(node.getParent().getRight()) && node.getParent().equals(grandparent.getLeft())) {
                    rotateLeft(node.getParent());
                    node = node.getLeft();
                } else if (node.equals(node.getParent().getLeft()) && node.getParent().equals(grandparent.getRight())) {
                    rotateRight(node.getParent());
                    node = node.getRight();
                }
                grandparent = getGrantParent(node);
                node.getParent().setColor(BLACK);
                grandparent.setColor(RED);
                if (node.equals(node.getParent().getLeft()) && node.getParent().equals(grandparent.getLeft())) {
                    rotateRight(grandparent);
                } else {
                    rotateLeft(grandparent);
                }
            }
        }
        root.setColor(BLACK);
    }

    private void restoreBalanceAfterDelete(TreeNode node) {
        while (node != null && !node.equals(root) && BLACK == node.getColor()) {
            if (node.equals(node.getParent().getLeft())) {
                TreeNode sibling = getSibling(node);
                if (null != sibling && RED == sibling.getColor()) {
                    sibling.setColor(BLACK);
                    node.getParent().setColor(RED);
                    rotateLeft(node.getParent());
                    sibling = node.getParent().getRight();
                }
                if (null != sibling && null!= sibling.getLeft() && BLACK == sibling.getLeft().getColor() && null != sibling.getRight() &&
                        BLACK == sibling.getRight().getColor()) {
                    sibling.setColor(RED);
                    node = node.getParent();
                } else {
                    if (null != sibling.getRight() && BLACK == sibling.getRight().getColor()) {
                        sibling.getLeft().setColor(BLACK);
                        sibling.setColor(RED);
                        rotateRight(sibling);
                        sibling = node.getParent().getRight();
                    }
                    sibling.setColor(node.getParent().getColor());
                    node.getParent().setColor(BLACK);
                    sibling.getRight().setColor(BLACK);
                    rotateLeft(node.getParent());
                    node = root;
                }
            } else {
                TreeNode sibling = getSibling(node);
                if (null != sibling && RED == sibling.getColor()) {
                    sibling.setColor(BLACK);
                    node.getParent().setColor(RED);
                    rotateRight(node.getParent());
                    sibling = node.getParent().getLeft();
                }
                if (null != sibling && null!= sibling.getLeft() && BLACK == sibling.getLeft().getColor() && null != sibling.getRight() &&
                        BLACK == sibling.getRight().getColor()) {
                    sibling.setColor(RED);
                    node = node.getParent();
                } else {
                    if (null != sibling.getLeft() && BLACK == sibling.getLeft().getColor()) {
                        sibling.getRight().setColor(BLACK);
                        sibling.setColor(RED);
                        rotateLeft(sibling);
                        sibling = node.getParent().getLeft();
                    }
                    sibling.setColor(node.getParent().getColor());
                    node.getParent().setColor(BLACK);
                    sibling.getLeft().setColor(BLACK);
                    rotateRight(node.getParent());
                    node = root;
                }
            }
        }
        node.setColor(BLACK);
    }

    private TreeNode getSibling(TreeNode node) {
        TreeNode sibling = null;
        if (null != node && null != node.getParent()) {
            if (null != node.getParent().getRight() && node.equals(node.getParent().getLeft())) {
                sibling = node.getParent().getRight();
            } else {
                sibling = node.getParent().getLeft();
            }
        }
        return sibling;
    }

    private TreeNode getGrantParent(TreeNode node) {
        TreeNode grandParent = null;

        if (null != node && null != node.getParent() && null != node.getParent().getParent()) {
            grandParent = node.getParent().getParent();
        }

        return grandParent;
    }

    private TreeNode getUncle(TreeNode node) {
        TreeNode uncle = null;
        TreeNode grandParent = getGrantParent(node);

        if (null != grandParent) {
            if (null != grandParent.getLeft() && node.getParent().equals(grandParent.getLeft())) {
                uncle = grandParent.getRight();
            } else {
                uncle = grandParent.getLeft();
            }
        }

        return uncle;
    }

}
