import java.util.Collection;

/**
 * Implementation of an AVL Tree.
 *
 * @author gatechStudent
 * @userid none01
 * @GTID 903000000
 * @version 1
 */
public class AVL<T extends Comparable<? super T>> implements AVLInterface<T> {
    private AVLNode<T> root;
    private int size;

    /**
     * A no argument constructor that should initialize an empty AVL tree.
     * DO NOT IMPLEMENT THIS CONSTRUCTOR!
     */
    public AVL() {
    }

    /**
     * Initializes the AVL tree with the data in the Collection. The data
     * should be added in the same order it is in the Collection.
     *
     * @param data the data to add to the tree
     * @throws IllegalArgumentException if data or any element in data is null
     */
    public AVL(Collection<T> data) {
        if (data == null) {
            throw new IllegalArgumentException("error: cannot initialize an " +
                    "AVL with null data");
        }
        for (T t: data) {
            add(t);
        }
    }

    /**
     * Add the data as a leaf to the AVL. Should traverse the tree to find the
     * appropriate location. If the data is already in the tree, then nothing
     * is done
     * @throws java.lang.IllegalArgumentException if the data is null
     * @param data the data to be added
     */
    @Override
    public void add(T data) {
        if (data == null) {
            throw new IllegalArgumentException("error: cannot add null data");
        }
        root = add(root, data);
    }

    /**
     * Helper method for add(T data)
     *
     * @param node current node (input should be root)
     * @param data the data to be added
     * @return the new root node
     */
    private AVLNode<T> add(AVLNode<T> node, T data) {
        if (node == null) {
            size++;
            node = new AVLNode<T>(data);
        }
        if (data.compareTo(node.getData()) < 0) {
            node.setLeft(add(node.getLeft(), data));
            node.setBalanceFactor(nodeHeight(node.getLeft())
                    - nodeHeight(node.getRight()));
            node = balance(node);
        } else if (data.compareTo(node.getData()) > 0) {
            node.setRight(add(node.getRight(), data));
            node.setBalanceFactor(nodeHeight(node.getLeft())
                    - nodeHeight(node.getRight()));
            node = balance(node);
        }
        node.setHeight(Math.max(nodeHeight(node.getRight()),
                nodeHeight(node.getLeft())) + 1);
        node.setBalanceFactor(nodeHeight(node.getLeft())
                - nodeHeight(node.getRight()));
        return node;
    }

    /**
     * Removes the data from the tree.
     *
     * @throws java.lang.IllegalArgumentException if the data is null
     * @throws java.util.NoSuchElementException if the data is not in the tree
     * @param data data to remove from the tree
     * @return the data removed from the tree.
     */
    @Override
    public T remove(T data) {
        if (data == null) {
            throw new IllegalArgumentException("error: cannot remove null " +
                    "data");
        }
        AVLNode<T> node2 = new AVLNode<T>(null);
        root = remove(root, data, node2);
        return node2.getData();
    }

    /**
     * Helper method for remove(T data)
     *
     * @param node the current node
     * @param data data to remove from the tree
     * @param node2
     * @return new root of the AVL
     */
    private AVLNode<T> remove(AVLNode<T> node, T data, AVLNode<T> node2) {
        AVLNode<T> none = new AVLNode<T>(null);
        if (node == null) {
            throw new java.util.NoSuchElementException("error: data not found");
        } else if (data.compareTo(node.getData()) < 0) {
            node.setLeft(remove(node.getLeft(), data, node2));
            node.setHeight(Math.max(nodeHeight(node.getRight()),
                    nodeHeight(node.getLeft())) + 1);
            node.setBalanceFactor(nodeHeight(node.getLeft())
                    - nodeHeight(node.getRight()));
            node = balance(node);
        } else if (data.compareTo(node.getData()) > 0) {
            node.setRight(remove(node.getRight(), data, node2));
            node.setHeight(Math.max(nodeHeight(node.getRight()),
                    nodeHeight(node.getLeft())) + 1);
            node.setBalanceFactor(nodeHeight(node.getLeft())
                    - nodeHeight(node.getRight()));
            node = balance(node);
        } else {
            if (node.getLeft() == null) {
                size--;
                node2.setData(node.getData());
                node.setBalanceFactor(nodeHeight(node.getLeft())
                        - nodeHeight(node.getRight()));
                return node.getRight();
            } else if (node.getRight() == null) {
                size--;
                node2.setData(node.getData());
                node.setBalanceFactor(nodeHeight(node.getLeft())
                        - nodeHeight(node.getRight()));
                return node.getLeft();
            } else {
                node2.setData(node.getData());
                node.setData(successor(node.getLeft()));
                node.setLeft(remove(node.getLeft(),
                        node.getData(), none));
                node.setHeight(Math.max(nodeHeight(node.getRight()),
                        nodeHeight(node.getLeft())) + 1);
                node.setBalanceFactor(nodeHeight(node.getLeft())
                        - nodeHeight(node.getRight()));
                node = balance(node);
            }
        }
        node.setBalanceFactor(nodeHeight(node.getLeft())
                - nodeHeight(node.getRight()));
        return node;
    }

    /**
     * Returns the data in the tree matching the parameter passed in.
     *
     * @throws java.lang.IllegalArgumentException if the data is null
     * @throws java.util.NoSuchElementException if the data is not found
     * @param data data to get in the AVL tree
     * @return the data in the tree equal to the parameter.
     */
    @Override
    public T get(T data) {
        if (data == null) {
            throw new IllegalArgumentException("error: cannot get null data");
        }
        return get(root, data);
    }

    /**
     * Helper method for get
     *
     * @param node the current node (input should be root)
     * @param data data to get in the AVL tree
     * @return the data in the tree equal to the parameter.
     */
    private T get(AVLNode<T> node, T data) {
        if (node == null) {
            throw new java.util.NoSuchElementException("data is not found!");
        }
        if (data.compareTo(node.getData()) == 0) {
            return node.getData();
        } else if (data.compareTo(node.getData()) < 0) {
            return get(node.getLeft(), data);
        } else {
            return get(node.getRight(), data);
        }

    }

    /**
     * Returns whether or not the parameter is contained within the tree.
     *
     * @throws java.lang.IllegalArgumentException if the data is null
     * @param data data to find in the AVL tree
     * @return whether or not the parameter is contained within the tree
     */
    @Override
    public boolean contains(T data) {
        if (data == null) {
            throw new IllegalArgumentException("error: cannot check null data");
        }
        return contains(root, data);
    }

    /**
     * Helper method for contains(T data)
     *
     * @param node the current node (input should be root)
     * @param data data to find in the AVL tree
     * @return whether or not the parameter is contained within the tree
     */
    private boolean contains(AVLNode<T> node, T data) {
        if (node == null) {
            return false;
        } else if (data.compareTo(node.getData()) < 0) {
            return contains(node.getLeft(), data);
        } else if (data.compareTo(node.getData()) > 0) {
            return contains(node.getRight(), data);
        } else {
            return true;
        }
    }

    /**
     * Retrieves the second largest data from the tree.
     *
     * @throws java.util.NoSuchElementException if there isn't enough data in
     * the tree for there to be a second largest element
     * @return the second largest data in the tree
     */
    @Override
    public T getSecondLargest() {
        if (size < 2) {
            throw new java.util.NoSuchElementException("error: size(" + size
                    + ") too small for AVL to contain a second largest " +
                    "element");
        }
        return getSecondLargest(root);
    }

    /**
     * Helper method for getSecondLargest()
     *
     * @param node the current node
     * @return the data of the second largest node
     */
    private T getSecondLargest(AVLNode<T> node) {
        if (size == 2) {
            if (root.getLeft() != null) {
                return root.getLeft().getData();
            } else {
                return root.getData();
            }
        }
        while (node.getRight().getRight() != null) {
            node = node.getRight();
        }
        return node.getData();
    }

    /**
     * Determines whether this tree is equal to the passed in object.
     *
     * Two trees are considered equal if they are equivalent structurally
     * with equal data being in the same locations in each (use value equality)
     *
     * @param obj the object we are checking equality with
     * @return true if the trees are equal, false otherwise
     */
    @Override
    public boolean equals(Object obj) {
        return false;
    }

    /**
     * Clear the tree.
     */
    @Override
    public void clear() {
        root = null;
        size = 0;
    }

    /**
     * Return the height of the root of the tree.
     *
     * This method does not need to traverse the tree since this is an AVL.
     *
     * @return the height of the root of the tree, -1 if the tree is empty
     */
    @Override
    public int height() {
        return rootHeight(root);
    }

    private int rootHeight(AVLNode<T> tempnode) {
        if (tempnode == null) {
            return -1;
        } else {
            return Math.max(rootHeight(tempnode.getLeft()), rootHeight(tempnode
                    .getRight())) + 1;
        }
    }

    /**
     * Returns the height of the node or -1 if the node is null
     * @param node the node we are checking the rootHeight of
     * @return the rootHeight of the node
     */
    private int nodeHeight(AVLNode<T> node) {
        if (node == null) {
            return -1;
        } else {
            return node.getHeight();
        }
    }

    /**
     * Balances a node
     *
     * @param node the node to be balanced
     * @return the new balanced node
     */
    private AVLNode<T> balance(AVLNode<T> node) {
        if (node.getBalanceFactor() > 1) {
            if (node.getLeft() != null
                    && node.getLeft().getBalanceFactor() >= 0) {
                node = rotateR(node);
            } else {
                node = rotateLR(node);
            }
        } else if (node.getBalanceFactor() < -1) {
            if (node.getRight() != null
                    && node.getRight().getBalanceFactor() <= 0) {
                node = rotateL(node);
            } else {
                node = rotateRL(node);
            }
        }
        return node;
    }

    /**
     * Rotates a node right
     *
     * @param node the node to be rotated
     * @return the new root of the subtree
     */
    private AVLNode<T> rotateR(AVLNode<T> node) {
            AVLNode<T> temp = node.getLeft();
            node.setLeft(temp.getRight());
            temp.setRight(node);
            node.setHeight(Math.max(nodeHeight(node.getRight()),
                nodeHeight(node.getLeft())) + 1);
            temp.setHeight(Math.max(nodeHeight(temp.getRight()),
                nodeHeight(temp.getLeft())) + 1);
            node.setBalanceFactor(nodeHeight(node.getLeft())
                - nodeHeight(node.getRight()));
            temp.setBalanceFactor(nodeHeight(temp.getLeft())
                    - nodeHeight(temp.getRight()));
            return temp;
        }

    /**
     * Rotates a node left
     *
     * @param node the node to be rotated
     * @return the new root of the subtree
     */
    private AVLNode<T> rotateL(AVLNode<T> node) {
        AVLNode<T> temp = node.getRight();
        node.setRight(temp.getLeft());
        temp.setLeft(node);
        node.setHeight(Math.max(nodeHeight(node.getRight()),
                nodeHeight(node.getLeft())) + 1);
        temp.setHeight(Math.max(nodeHeight(temp.getRight()),
                nodeHeight(temp.getLeft())) + 1);
        node.setBalanceFactor(nodeHeight(node.getLeft())
                - nodeHeight(node.getRight()));
        temp.setBalanceFactor(nodeHeight(temp.getLeft())
                - nodeHeight(temp.getRight()));
        return temp;
    }

    /**
     * Rotates a node right then left
     *
     * @param node the node to be rotated
     * @return the new root of the subtree
     */
    private AVLNode<T> rotateRL(AVLNode<T> node) {
        node.setRight(rotateR(node.getRight()));
        return rotateL(node);
    }

    /**
     * Rotates a node left then right
     *
     * @param node the node to be rotated
     * @return the new root of the subtree
     */
    private AVLNode<T> rotateLR(AVLNode<T> node) {
        node.setLeft(rotateL(node.getLeft()));
        return rotateR(node);
    }

    /**
     * Determines the successor of a node
     *
     * @param node the node we want to find the successor of
     * @return the data in the successor
     */
    private T successor(AVLNode<T> node) {
        while (node.getRight() != null) {
            node = node.getRight();
        }
        return node.getData();
    }

    /**
     * Get the number of elements in the tree.
     *
     * @return the number of elements in the tree
     */
    @Override
    public int size() {
        // DO NOT MODIFY THIS METHOD!
        return size;
    }

    @Override
    public AVLNode<T> getRoot() {
        // DO NOT MODIFY THIS METHOD!
        return root;
    }
}
