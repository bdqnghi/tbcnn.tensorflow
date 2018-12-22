/**
 * Lab 2: Debugging with Eclipse and Red Black Tree) <br />
 * The {@code RedBlackTree} class of integers only <br />
 * Reference: <a href="https://en.wikipedia.org/wiki/Red%E2%80%93black_tree">
 * https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
 * </a>
 * <p>
 * Name: Nathan Klapstein
 * ID: 1449872
 */


public class RedBlackTree {

    /**
     * Rotate globals
     * rotate left: true
     * rotate right: false
     */
    private static boolean ROTATE_LEFT = true;
    private static boolean ROTATE_RIGHT = false;

    /**
     * Root node of the red black tree
     */
    private Node root = null;


    /**
     * Size of the tree
     */
    private int size = 0;

    /**
     * Main entry
     *
     * @param args {@code String[]} Command line arguments
     */
    public static void main(String[] args) {
        RedBlackTree rbt = new RedBlackTree();
        for (int i = 0; i < 10; i++) {
            int var = (int) (Math.random() * 200);
            // print for debugging
            System.out.println(var);
            rbt.insert(var);
        }

        assert rbt.root.color == RedBlackTree.Node.BLACK;
        System.out.println(rbt);
        System.out.println(rbt.size());

    }

    /**
     * Recursively search the tree to find if the value is contained
     *
     * @param value {@code int} the value to be checked
     * @return {@code boolean} If contains, return {@code true}, otherwise return {@code false}
     */
    private boolean checkRecursively(Node tree, int value) {
        // end of a branch pull out
        if (tree == null || tree.value == null)
            return false;

        // found the value pull out
        if (tree.value == value) {
            return true;
        } else {
            // recursively check the left branches then
            // if not found check the right branches
            if (checkRecursively(tree.lChild, value)) {
                return true;
            } else {
                return checkRecursively(tree.rChild, value);
            }
        }
    }

    /**
     * Search the tree to find if the value is contained
     *
     * @param value {@code int} the value to be checked
     * @return {@code boolean} If contains, return {@code true}, otherwise return {@code false}
     */
    public boolean contains(int value) {
        return checkRecursively(root, value);
    }


    /**
     * Rotate the node left
     *
     * @param node {@code Node} the node to be rotated about
     */
    private void rotateTree(Node node, boolean direction) {
        Node parent = node.parent;
        Node grandParent = parent.parent;

        if (grandParent == null) {
            root = node;
        } else {
            if (parent.isLeftChild())
                grandParent.lChild = node;
            else
                grandParent.rChild = node;

        }
        node.parent = grandParent;
        parent.parent = node;

        if (direction == ROTATE_LEFT) {
            parent.rChild = node.lChild;
            if (node.lChild != null)
                node.lChild.parent = parent;

            node.lChild = parent;
        } else {
            parent.lChild = node.rChild;
            if (node.rChild != null)
                node.rChild.parent = parent;

            node.rChild = parent;
        }
    }

    /**
     * Check the node ensuring that all color cases are covered correctly
     *
     * @param node {@code Node} the node to be checked for color validity
     */
    private void fixInsertColor(Node node) {
        // case 1: if node is root set color to black and return
        if (node == root) {
            node.color = Node.BLACK;

        } else if (node.parent.color == Node.RED) {
            Node parent = node.parent;
            Node grandparent = parent.parent;
            Node uncle;

            if (parent.isLeftChild()) {
                uncle = grandparent.rChild;
            } else {
                uncle = grandparent.lChild;
            }

            // case 3
            if (parent.color == Node.RED && uncle.color == Node.RED) {
                parent.color = Node.BLACK;
                uncle.color = Node.BLACK;
                grandparent.color = Node.RED;
                fixInsertColor(grandparent);
                return;
            }

            // case 4
            if (parent.color == Node.RED && uncle.color == Node.BLACK) {
                if (node.isRightChild() && parent.isLeftChild()) {
                    rotateTree(node, ROTATE_LEFT);
                    node = node.lChild;
                } else if (node.isLeftChild() && parent.isRightChild()) {
                    rotateTree(node, ROTATE_RIGHT);
                    node = node.rChild;
                }
            }

            parent = node.parent;
            parent.color = Node.BLACK;
            grandparent.color = Node.RED;

            // case 5
            if (node.isLeftChild() && parent.isLeftChild())
                rotateTree(parent, ROTATE_RIGHT);
            else
                rotateTree(parent, ROTATE_LEFT);
        }
    }

    /**
     * Insert an integer to the tree
     *
     * @param value {@code int} New element to be inserted
     */
    public void insert(int value) {
        Node curNode = root;
        while (curNode != null && curNode.value != null) {
            // go left if less than current node
            if (value < curNode.value)
                curNode = curNode.lChild;
                // go right if greater than current node
            else if (value > curNode.value)
                curNode = curNode.rChild;
                // skip values already present
            else
                return;
        }
        Node node = new Node(value);
        if (size == 0) {
            root = node;
        } else {
            Node parent = curNode.parent;
            node.parent = parent;
            if (curNode == parent.lChild) {
                parent.lChild = node;
            } else {
                parent.rChild = node;
            }
        }
        size++;
        // initialize new node as red
        node.color = Node.RED;
        // fix red black trees color
        fixInsertColor(node);
    }


    /**
     * Get the size of the tree
     *
     * @return {@code int} size of the tree
     */
    public int size() {
        return size;
    }

    /**
     * Recurse down the tree and generate a string describing it
     *
     * @return {@code treeString} string format of the tree
     */
    public String toStringRecursive(Node node) {
        // end of a branch or null value pull out and don't record
        if (node == null || node.value == null) {
            return "N";
        } else {
            // recursively get the left and right child's strings and return them
            return String.format(
                    "%s={%s%s}",
                    node.toString(),
                    toStringRecursive(node.lChild),
                    toStringRecursive(node.rChild)
            );
        }
    }

    /**
     * Cast the tree into a string
     *
     * @return {@code String} Printed format of the tree
     */
    @Override
    public String toString() {
        // TODO: Lab 2 Part 2-3 -- print the tree, where each node contains both value and color
        // You can print it by in-order traversal
        return toStringRecursive(root);
    }

    /**
     * The {@code Node} class for {@code RedBlackTree}
     */
    private class Node {
        public static final boolean BLACK = true;
        public static final boolean RED = false;

        public Integer value;
        public boolean color = BLACK;
        public Node parent = null, lChild = null, rChild = null;

        public Node(Integer value) {             // By default, a new node is black with two NIL children
            this.value = value;
            if (value != null) {
                lChild = new Node(null);         // And the NIL children are both black
                lChild.parent = this;
                rChild = new Node(null);
                rChild.parent = this;
            }
        }


        /**
         * check if a node is a parents left child
         *
         * @return {@code boolean}
         */
        public boolean isLeftChild() {
            return this == this.parent.lChild;
        }

        /**
         * check if a node is a parents right child
         *
         * @return {@code boolean}
         */
        public boolean isRightChild() {
            return this == this.parent.rChild;
        }


        /**
         * Print the tree node: red node wrapped by "<>"; black node by "[]"
         *
         * @return {@code String} The printed string of the tree node
         */
        @Override
        public String toString() {
            if (value == null) {
                return "";
            }
            return (color == RED) ? "<" + value + ">" : "[" + value + "]";
        }
    }

}