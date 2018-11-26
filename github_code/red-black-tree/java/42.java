/*
 * Created by Trenton Shell on 3/15/17.
 */

public class RedBlackTree extends BinarySearchTree {

    private final int RED = 1;
    private final int BLACK = 0;

    class RedBlackNode extends Node {
        int color;
        RedBlackNode parent;

        RedBlackNode(Entry entry) {
            super(entry);
            color = RED;
        }

        public String toString() {
            if (color == RED) return getEntry().getWord() + " (red)";
            else return getEntry().getWord() + " (black)";
        }
    }

    RedBlackTree() {
    }

    @Override
    public void add(String word, String definition) {
        if (root == null) {
            RedBlackNode node = new RedBlackNode(new Entry(word, definition));
            node.color = BLACK;
            root = node;
        } else {
            Node current = root;
            while (true) {
                if (word.compareToIgnoreCase(current.getEntry().getWord()) < 0 ) {

                    if (current.left == null) {
                        current.left = new RedBlackNode(new Entry(word, definition));
                        setParentOf((RedBlackNode) current.left, (RedBlackNode) current);
                        balance((RedBlackNode)current.left);
                        break;
                    } else {
                        current = current.left;
                    }
                } else if (word.compareToIgnoreCase(current.getEntry().getWord()) > 0) {
                    if (current.right == null) {
                        current.right = new RedBlackNode(new Entry(word, definition));
                        setParentOf((RedBlackNode) current.right, (RedBlackNode) current);
                        balance((RedBlackNode)current.right);
                        break;
                    } else {
                        current = current.right;
                    }
                } else {
                    if (!current.getEntry().getDefinition().contains(definition)) {
                        current.getEntry().addDefinition(definition);
                    }
                    break;
                }
            }
        }
    }
    @Override
    public void delete(String word) {
        System.out.println("Delete functionality not implemented with Red Black Trees");
    }

    private void balance(RedBlackNode node) {

        if (node != null && node != root && isRed(node.parent)) {
            if (hasSibling(node.parent) && isRed(getSiblingOf(node.parent))) {
                node.parent.color = BLACK;
                getSiblingOf(node.parent).color = BLACK;
                node.parent.parent.color = RED;
                balance(node.parent.parent);
            } else if (node.parent == (node.parent.parent.left)) {
                if (node == node.parent.right) {
                    node = node.parent;
                    rotateLeft(node);
                }
                node.parent.color = BLACK;
                node.parent.parent.color = RED;
                rotateRight(node.parent.parent);
            } else if (node.parent == node.parent.parent.right) {
                if (node == node.parent.left) {
                    node = node.parent;
                    rotateRight(node);
                }
                node.parent.color = BLACK;
                node.parent.parent.color = RED;
                rotateLeft(node.parent.parent);
            }
        }
        if (isRed((RedBlackNode) root)) changeColor((RedBlackNode) root);
    }

    private void rotateRight(RedBlackNode x) {
        RedBlackNode y = getLeftOf(x);
        x.left = y.right;
        if (y.right != null) setParentOf(getRightOf(y), x);
        y.parent = x.parent;
        if (x.parent == null) root = y;
        else {
            if (x == getRightOf(x.parent)) x.parent.right = y;
            else x.parent.left = y;
        }
        y.right = x;
        x.parent = y;
    }

    private void rotateLeft(RedBlackNode x) {
        RedBlackNode y = getRightOf(x);
        x.right = y.left;
        if (y.left != null) setParentOf(getLeftOf(y), x);
        y.parent = x.parent;
        if (x.parent == null) root = y;
        else {
            if (x == getLeftOf(x.parent)) x.parent.left = y;
            else x.parent.right = y;
        }
        y.left = x;
        x.parent = y;
    }

    private void changeColor(RedBlackNode node) {
        if (node.color == RED) node.color = BLACK;
        else node.color = RED;
    }
    private boolean isRed(RedBlackNode node) {
        return node == null || node.color == RED;
    }
    private RedBlackNode getLeftOf(RedBlackNode node) {
        if (node != null) return (RedBlackNode) node.left;
        else return null;
    }
    private RedBlackNode getRightOf(RedBlackNode node) {
        if (node != null) return (RedBlackNode) node.right;
        else return null;
    }
    private void setParentOf(RedBlackNode node, RedBlackNode newParent) {
        node.parent = newParent;
    }
    private boolean hasSibling(RedBlackNode node) {
        if (node != null && node.parent != null) {
            if (node == node.parent.left && node.parent.right != null) return true;
            else if (node == node.parent.right && node.parent.left != null) return true;
        }
        return false;
    }

    private RedBlackNode getSiblingOf(RedBlackNode node) {
        if (node != null && node.parent != null) {
            if (node == node.parent.left) return (RedBlackNode) node.parent.right;
            else return (RedBlackNode) node.parent.left;
        } else return null;
    }



}
