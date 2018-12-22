/**
 *
 */
package avltree;

import java.util.ArrayList;

/**
 * @author Dinesh Appavoo
 *
 */

/**
 * This class is the complete and tested implementation of an AVL-tree.
 */
public class AVLTree<T extends Comparable<T>, U extends Comparable<U>> {

    protected AVLNode root; // the root node
    protected int sizeOfTree = 0;
    protected ArrayList<AVLNode> nodesToBeRemoved;


    /**
     * Add a new element with key "k" and value "value" into the tree.
     *
     * @param k The key of the new node.
     */
    public void insert(long k, long value) {
        AVLNode n = new AVLNode(k, value);
        insertAVL(this.root, n);
    }

    /**
     * Recursive method to insert a node into a tree.
     *
     * @param p The node currently compared, usually you start with the root.
     * @param q The node to be inserted.
     */
    public void insertAVL(AVLNode p, AVLNode q) {
        // If  node to compare is null, the node is inserted. If the root is null, it is the root of the tree.
        if (p == null) {
            this.root = q;
        } else {

            // If compare node is smaller, continue with the left node
            if (q.key.compareTo(p.key)<0) {
                if (p.left == null) {
                    p.left = q;
                    q.parent = p;

                    // Node is inserted now, continue checking the balance
                    recursiveBalance(p);
                } else {
                    insertAVL(p.left, q);
                }

            } else if (q.key.compareTo(p.key)>0) {
                if (p.right == null) {
                    p.right = q;
                    q.parent = p;

                    // Node is inserted now, continue checking the balance
                    recursiveBalance(p);
                } else {
                    insertAVL(p.right, q);
                }
            }
        }
    }

    /**
     * Check the balance for each node recursivly and call required methods for balancing the tree until the root is reached.
     *
     * @param cur : The node to check the balance for, usually you start with the parent of a leaf.
     */
    public void recursiveBalance(AVLNode cur) {

        setBalance(cur);
        int balance = cur.balance;

        // check the balance
        if (balance == -2) {

            if (height(cur.left.left) >= height(cur.left.right)) {
                cur = rotateRight(cur);
            } else {
                cur = doubleRotateLeftRight(cur);
            }
        } else if (balance == 2) {
            if (height(cur.right.right) >= height(cur.right.left)) {
                cur = rotateLeft(cur);
            } else {
                cur = doubleRotateRightLeft(cur);
            }
        }

        if (cur.parent != null) {
            recursiveBalance(cur.parent);
        } else {
            this.root = cur;
        }
    }

    /**
     * Removes a node from the tree, if it is existent.
     */
    public void remove(long k) {
        removeAVL(this.root, k);
    }

    /**
     * Finds a node and calls a method to remove the node.
     *
     * @param p The node to start the search.
     * @param q The KEY of node to remove.
     */
    public void removeAVL(AVLNode p, long q) {
        if (p == null) {
            return;
        } else {
            if (p.key.compareTo(q)>0) {
                removeAVL(p.left, q);
            } else if (p.key.compareTo(q)<0) {
                removeAVL(p.right, q);
            } else if (p.key.compareTo(q)==0) {
                removeFoundNode(p);
            }
        }
    }

    /**
     * Removes a node from a AVL-Tree, while balancing will be done if necessary.
     *
     * @param q The node to be removed.
     */
    public void removeFoundNode(AVLNode q) {
        AVLNode r;
        if (q.left == null || q.right == null) {
            // the root is deleted
            if (q.parent == null) {
                this.root = null;
                q = null;
                return;
            }
            r = q;
        } else {
            // q has two children --> will be replaced by successor
            r = successor(q);
            q.key = r.key;
            q.value = r.value;
        }

        AVLNode p;
        if (r.left != null) {
            p = r.left;
        } else {
            p = r.right;
        }

        if (p != null) {
            p.parent = r.parent;
        }

        if (r.parent == null) {
            this.root = p;
        } else {
            if (r == r.parent.left) {
                r.parent.left = p;
            } else {
                r.parent.right = p;
            }
            // balancing must be done until the root is reached.
            recursiveBalance(r.parent);
        }
        r = null;
    }

    /**
     * Left rotation using the given node.
     *
     * @param n The node for the rotation.
     * @return The root of the rotated tree.
     */
    public AVLNode rotateLeft(AVLNode n) {

        AVLNode v = n.right;
        v.parent = n.parent;

        n.right = v.left;

        if (n.right != null) {
            n.right.parent = n;
        }

        v.left = n;
        n.parent = v;

        if (v.parent != null) {
            if (v.parent.right == n) {
                v.parent.right = v;
            } else if (v.parent.left == n) {
                v.parent.left = v;
            }
        }
        setBalance(n);
        setBalance(v);
        return v;
    }

    /**
     * Right rotation using the given node.
     *
     * @param n The node for the rotation
     * @return The root of the new rotated tree.
     */
    public AVLNode rotateRight(AVLNode n) {
        AVLNode v = n.left;
        v.parent = n.parent;
        n.left = v.right;

        if (n.left != null) {
            n.left.parent = n;
        }
        v.right = n;
        n.parent = v;
        if (v.parent != null) {
            if (v.parent.right == n) {
                v.parent.right = v;
            } else if (v.parent.left == n) {
                v.parent.left = v;
            }
        }
        setBalance(n);
        setBalance(v);
        return v;
    }

    /**
     * @param u The node for the rotation.
     * @return The root after the double rotation.
     */
    public AVLNode doubleRotateLeftRight(AVLNode u) {
        u.left = rotateLeft(u.left);
        return rotateRight(u);
    }

    /**
     * @param u The node for the rotation.
     * @return The root after the double rotation.
     */
    public AVLNode doubleRotateRightLeft(AVLNode u) {
        u.right = rotateRight(u.right);
        return rotateLeft(u);
    }

    public AVLNode find(Comparable x) {
        AVLNode currentNode = root;

        while (currentNode != null)
            if (x.compareTo(currentNode.key) < 0)
                currentNode = currentNode.left;
            else if (x.compareTo(currentNode.key) > 0)
                currentNode = currentNode.right;
            else
                return currentNode;
        return null;
    }

    public AVLNode<T, U> findMin() {
        if (root == null)
            return root;

        AVLNode<T, U> currentNode = root;
        while (currentNode.left != null)
            currentNode = currentNode.left;
        return currentNode;
    }

    public AVLNode<T, U> findMax() {
        if (root == null)
            return root;

        AVLNode<T, U> currentNode = root;
        while (currentNode.right != null)
            currentNode = currentNode.right;
        return currentNode;
    }

    /**
     * Returns the successor of a given node in the tree (search recursively).
     *
     * @param q The predecessor.
     * @return The successor of node q.
     */
    public AVLNode successor(AVLNode q) {
        if (q.right != null) {
            AVLNode r = q.right;
            while (r.left != null) {
                r = r.left;
            }
            return r;
        } else {
            AVLNode p = q.parent;
            while (p != null && q == p.right) {
                q = p;
                p = q.parent;
            }
            return p;
        }
    }

    /**
     * Calculating the "height" of a node.
     *
     * @param cur
     * @return The height of a node (-1, if node is not existent eg. NULL).
     */
    private int height(AVLNode cur) {
        if (cur == null) {
            return -1;
        }
        if (cur.left == null && cur.right == null) {
            return 0;
        } else if (cur.left == null) {
            return 1 + cur.right.height;
        } else if (cur.right == null) {
            return 1 + cur.left.height;
        } else {
            return 1 + maximum(cur.left.height, cur.right.height);
        }
    }

    /**
     * Return the maximum of two integers.
     */
    private int maximum(int a, int b) {
        if (a >= b) {
            return a;
        } else {
            return b;
        }
    }

    private void setBalance(AVLNode cur) {
        cur.balance = height(cur.right) - height(cur.left);
    }

    /**
     * Function to find the nodes to be removed through preordering.
     *
     * @param n     The current node.
     * @param value The value to remove.
     */
    final protected void preorderRemoval(AVLNode<T, U> n, U value) {
        if (n == null) {
            return;
        }
        if (value.compareTo(n.value) == 0) {
            nodesToBeRemoved.add(n);
        }
        preorderRemoval(n.left, value);

        preorderRemoval(n.right, value);
    }

    public int removeValue(U value) {
        if (root == null) {
            return 0;
        }
        nodesToBeRemoved = new ArrayList<AVLNode>();
        preorderRemoval(root, value);
        for (AVLNode node : nodesToBeRemoved) {
            removeFoundNode(node);
        }
        return nodesToBeRemoved.size();
    }

    public int size() {
        AVLNode x = root;
        if (x == null)
            return sizeOfTree;
        int size = sizeHandler(x);
        sizeOfTree = 0;
        return size;
    }

    /**
     * return the size of the tree.
     */
    public int sizeHandler(AVLNode head) {

        if (head == null)
            return sizeOfTree;
        sizeOfTree++;
        sizeHandler(head.left);
        sizeHandler(head.right);
        return sizeOfTree;
    }

    public boolean isEmpty() {
        return null == root;
    }
}