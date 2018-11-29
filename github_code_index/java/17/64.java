package Code.DSA;

/**
 * This is implementation of Red-Black Tree as explained in Introduction
 * to Algorithms by CLRS. Please refer the same for more details.
 * All the methods here are implementation of psuedo code from "Introduction to
 * Algorithms" by Cormen.
 *
 * @author Ashok Rajpurohit (ashok1113@gmail.com)
 * @see     BSTAVL
 * @see     BSTbyNode
 * @see     RankTree
 */
public class RedBlackTree {
    private final static Node NIL = new Node(0);
    private final static boolean RED = true, BLACK = false;
    private int size = 0;
    private Node root;

    static {
        NIL.color = BLACK;
    }

    public RedBlackTree(int t) {
        size = 1;
        root = new Node(t);
        root.color = BLACK;
    }

    public RedBlackTree(int[] ar) {
        this(ar[0]);

        for (int i = 1; i < ar.length; i++)
            add(ar[i]);
    }

    public int size() {
        return size;
    }

    /**
     * Adds the specified element to this tree.
     *
     * @param value element to be added to this tree
     */
    public void add(int value) {
        Node node = insert(value);
        insertFix(node);
    }

    private Node insert(int value) {
        size++;
        Node temp = root;

        while (true) {
            if (temp.key > value) {
                if (temp.left == NIL) {
                    temp.left = new Node(value);
                    temp.left.parent = temp;
                    return temp.left;
                }
                temp = temp.left;
            } else {
                if (temp.right == NIL) {
                    temp.right = new Node(value);
                    temp.right.parent = temp;
                    return temp.right;
                }
                temp = temp.right;
            }
        }
    }

    /**
     * Restructures the tree in case if any property is violated during
     * element addition.
     *
     * @param node
     */
    private void insertFix(Node node) {
        while (node.parent.color == RED) {
            if (node.parent == node.parent.parent.left) {
                Node tau = node.parent.parent.right;

                if (tau.color == RED) {
                    node.parent.color = BLACK;
                    tau.color = BLACK;
                    node.parent.parent.color = RED;
                    node = node.parent.parent;
                } else {
                    if (node == node.parent.right) {
                        node = node.parent;
                        rotateLeft(node);
                    }
                    node.parent.color = BLACK;
                    node.parent.parent.color = RED;
                    rotateRight(node.parent.parent);
                }
            } else {
                Node chacha = node.parent.parent.left;

                if (chacha.color == RED) {
                    node.parent.color = BLACK;
                    chacha.color = BLACK;
                    node.parent.parent.color = RED;
                    node = node.parent.parent;
                } else {
                    if (node == node.parent.right) {
                        node = node.parent;
                        rotateLeft(node);
                    }
                    node.parent.color = BLACK;
                    node.parent.parent.color = RED;
                    rotateRight(node.parent.parent);
                }
            }
        }
        root.color = BLACK;
    }

    /**
     * Returns <tt>true</tt> if this set contains the specified element.
     *
     * @param value element whose presence in this tree is to be tested
     * @return <tt>true</tt> if this tree contains the specified element
     */
    public boolean contains(int value) {
        return find(value) != NIL;
    }

    public int successor(int value) {
        Node node = find(value);
        if (node == NIL)
            throw new RuntimeException("No such element exists: " + value);

        if (node.right != NIL)
            return findMin(node.right).key;

        while (node.parent != NIL && node == node.parent.right)
            node = node.parent;

        if (node.parent != NIL)
            return node.parent.key;

        throw new RuntimeException("No successor exists for " + value);
    }

    public int predecessor(int value) {
        Node node = find(value);
        if (node == NIL)
            throw new RuntimeException("No such element exists: " + value);

        if (node.left != NIL)
            return findMax(node.left).key;

        while (node.parent != NIL && node == node.parent.left)
            node = node.parent;

        if (node.parent != NIL)
            return findMin(node.parent).key;

        throw new RuntimeException("No predecessor exists for " + value);
    }

    private void rotateLeft(Node node) {
        if (node.right == NIL)
            return;

        Node right = node.right;
        node.right = right.left;
        right.left.parent = node;
        right.parent = node.parent;

        if (node.parent == NIL)
            root = right;
        else {
            if (node == node.parent.left)
                node.parent.left = right;
            else
                node.parent.right = right;
        }

        right.left = node;
        node.parent = right;
    }

    private void rotateRight(Node node) {
        if (node.left == NIL)
            return;

        Node left = node.left;
        node.left = left.right;
        left.right.parent = node;
        left.parent = node.parent;

        if (node.parent == NIL)
            root = left;
        else {
            if (node == node.parent.left)
                node.parent.left = left;
            else
                node.parent.right = left;
        }

        left.right = node;
        node.parent = left;
    }

    public void remove(int value) {
        if (size == 0)
            return;

        Node node = find(value);

        if (node != NIL)
            delete(node);
    }

    public void update(int oldValue, int newValue) {
        if (size == 0 || oldValue == newValue)
            return;

        Node node = find(oldValue);
        if (node == NIL)
            throw new RuntimeException("key does not exists");

        Node end = NIL;

        if (node.left != NIL)
            end = findMax(node.left);
        else if (node.right != NIL)
            end = findMin(node.right);
        else {
            node.key = newValue;
            return;
        }

        node.key = end.key;
        delete(end);
        insert(newValue);
    }

    private void delete(Node node) {
        --size;
        Node copy = node, fixUp = NIL;
        boolean copy_red = copy.color;

        if (node.left == NIL) {
            fixUp = node.right;
            replace(node, node.right);
        } else if (node.right == NIL) {
            fixUp = node.left;
            replace(node, node.left);
        } else {
            copy = findMin(node.right);
            copy_red = copy.color;
            fixUp = copy.right;

            if (copy.parent == node)
                fixUp.parent = copy;
            else {
                replace(copy, copy.right);
                copy.right = node.right;
                copy.right.parent = copy;
            }

            replace(node, copy);
            copy.left = node.left;
            copy.left.parent = copy;
            copy.color = node.color;
        }

        if (!copy_red)
            deleteFix(fixUp);
    }

    private Node findMin(Node node) {
        while (node.left != NIL)
            node = node.left;

        return node;
    }

    private Node findMax(Node node) {
        while (node.right != NIL)
            node = node.right;

        return node;
    }

    private void deleteFix(Node node) {
        while (node != root && node.color == BLACK) {
            if (node == node.parent.left) {
                Node temp = node.parent.right;
                if (temp.color == RED) {
                    temp.color = BLACK;
                    node.parent.color = RED;
                    rotateLeft(node.parent);
                    temp = node.parent.right;
                }

                if (temp.left.color == BLACK && temp.right.color == BLACK) {
                    temp.color = RED;
                    node = node.parent;
                } else {
                    if (temp.right.color == BLACK) {
                        temp.left.color = BLACK;
                        temp.color = RED;
                        rotateRight(temp);
                        temp = node.parent.right;
                    }

                    temp.color = node.parent.color;
                    node.parent.color = BLACK;
                    temp.right.color = BLACK;
                    rotateLeft(node.parent);
                    node = root;
                }
            } else {
                Node temp = node.parent.left;
                if (temp.color == RED) {
                    temp.color = BLACK;
                    node.parent.color = RED;
                    rotateRight(node.parent);
                    temp = node.parent.left;
                }

                if (temp.left.color == BLACK && temp.right.color == BLACK) {
                    temp.color = RED;
                    node = node.parent;
                } else {
                    if (temp.left.color == BLACK) {
                        temp.right.color = BLACK;
                        temp.color = RED;
                        rotateLeft(temp);
                        temp = node.parent.left;
                    }

                    temp.color = node.parent.color;
                    node.parent.color = BLACK;
                    temp.left.color = BLACK;
                    rotateRight(node.parent);
                    node = root;
                }
            }
        }
        node.color = BLACK;
    }

    private void replace(Node u, Node v) {
        if (u.parent == NIL)
            root = v;
        else if (u == u.parent.left)
            u.parent.left = v;
        else
            u.parent.right = v;

        v.parent = u.parent;
    }

    private Node find(int value) {
        Node temp = root;

        while (temp != NIL && temp.key != value) {
            if (temp.key > value)
                temp = temp.left;
            else
                temp = temp.right;
        }
        return temp;
    }

    final static class Node {
        int key;
        boolean color = RED;
        Node left = NIL, right = NIL, parent = NIL;

        Node(int value) {
            key = value;
        }
    }
}
