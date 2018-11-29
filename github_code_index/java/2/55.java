import java.util.Collection;
import java.util.NoSuchElementException;

/**
 * Your implementation of an AVL Tree.
 *
 * @author Xiaohong Chen
 * @userid xchen671
 * @GTID 903392332
 * @version 1.0
 */
public class AVL<T extends Comparable<? super T>> {
    // DO NOT ADD OR MODIFY INSTANCE VARIABLES.
    private AVLNode<T> root;
    private int size;

    /**
     * A no argument constructor that should initialize an empty AVL tree.
     */
    public AVL() {
        // DO NOT IMPLEMENT THIS CONSTRUCTOR!
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
            throw new IllegalArgumentException("Null value cannot be data");
        } else {
            for (T element : data) {
                add(element);
            }
        }
    }

    /**
     * Add the data as a leaf to the AVL. Should traverse the tree to find the
     * appropriate location. If the data is already in the tree, then nothing
     * should be done (the duplicate shouldn't get added, and size should not be
     * incremented).
     *
     * Remember to recalculate heights going up the tree, rebalancing if
     * necessary.
     *
     * @throws java.lang.IllegalArgumentException if the data is null
     * @param data the data to be added
     */
    public void add(T data) {
        if (data == null) {
            throw new IllegalArgumentException("Null value cannot be data");
        } else {
            root = add(data, root);
        }

    }

    /**
     * add helper method
     * @param data the data added
     * @param node the root of the tree
     *
     * @return node the node was added, and then rotate to correct AVL tree
     */
    private AVLNode<T> add(T data, AVLNode<T> node) {
        if (node == null) {
            node = new AVLNode<>(data);
            size++;
            return node;
        } else {
            if (data.compareTo(node.getData()) < 0) {
                node.setLeft(add(data, node.getLeft()));
            } else if (data.compareTo(node.getData()) == 0) {
                return node;
            } else {
                node.setRight(add(data, node.getRight()));
            }
            updateAndBalance(node);
            return rotate(node);
        }
    }
    /**
     * left and then right rotate method, and update the new height and BF
     * @param node the root of the tree
     * @return completed right rotated AVL tree
     */
    private AVLNode<T> leftRightRotate(AVLNode<T> node) {
        node.setLeft(leftRotate(node.getLeft()));
        return rightRotate(node);
    }
    /**
     * right and then left rotate method, and update the new height and BF
     * @param node the root of the tree
     * @return completed left rotated AVL tree
     */
    private AVLNode<T> rightLeftRotate(AVLNode<T> node) {
        node.setRight(rightRotate(node.getRight()));
        return leftRotate(node);
    }
    /**
     * right rotate method, and update the new height and BF
     * @param node the root of the tree
     * @return completed right rotated AVL tree
     */
    private AVLNode<T> rightRotate(AVLNode<T> node) {
        AVLNode<T> leftChild = node.getLeft();
        node.setLeft(leftChild.getRight());
        leftChild.setRight(node);
        updateAndBalance(node);
        updateAndBalance(leftChild);
        return leftChild;
    }
    /**
     * left rotate method, and update the new height and BF
     * @param node the root of the tree
     * @return completed right rotated AVL tree
     */
    private AVLNode<T> leftRotate(AVLNode<T> node) {
        AVLNode<T> rightChild = node.getRight();
        node.setRight(rightChild.getLeft());
        rightChild.setLeft(node);
        updateAndBalance(node);
        updateAndBalance(rightChild);
        return rightChild;
    }
    /**
     * rotate method, update the new BF, there are three cases:
     * 1.if bf greater than 1, then get leftBF and if < 0, then leftRightRotate
     * either then rightRotate
     * 2.if bf less than -1, then get rightBF and if > 0, then rightLeftRotate
     * either then leftRotate
     * 3.else update the new height and BF, and return node.
     * @param node the root of the tree
     * @return completed correct rotated AVL tree
     */
    private AVLNode<T> rotate(AVLNode<T> node) {
        int bf = node.getBalanceFactor();
        if (bf > 1) {
            int leftBF = node.getLeft().getBalanceFactor();
            return (leftBF < 0) ? leftRightRotate(node) : rightRotate(node);
        } else if (bf < -1) {
            int rightBF = node.getRight().getBalanceFactor();
            return (rightBF > 0) ? rightLeftRotate(node) : leftRotate(node);
        } else {
            updateAndBalance(node);
            return node;
        }
    }
    /**
     * update the new height and BF method
     * @param node the root of the tree
     */
    private void updateAndBalance(AVLNode<T> node) {
        int leftH = (node.getLeft() == null) ? -1 : node.getLeft().getHeight();
        int rightH = (node.getRight() == null) ? -1
                : node.getRight().getHeight();
        node.setHeight(Math.max(leftH, rightH) + 1);
        node.setBalanceFactor(leftH - rightH);
    }

    /**
     * Removes the data from the tree. There are 3 cases to consider:
     * 1: The data is a leaf. In this case, simply remove it.
     * 2: The data has one child. In this case, simply replace the node with
     * the child node.
     * 3: The data has 2 children. For this assignment, use the predecessor to
     * replace the data you are removing, not the sucessor.
     *
     * Remember to recalculate heights going up the tree, rebalancing if
     * necessary.
     *
     * @throws java.lang.IllegalArgumentException if the data is null
     * @throws java.util.NoSuchElementException if the data is not in the tree
     * @param data data to remove from the tree
     * @return the data removed from the tree.  Do not return the same data
     * that was passed in. Return the data that was stored in the tree.
     */
    public T remove(T data) {
        if (data == null) {
            throw new IllegalArgumentException("Data can not be null");
        } else {
            AVLNode<T> dummy = new AVLNode<T>(data);
            root = remove(root, dummy, data);
            size--;
            return dummy.getData();
        }
    }
    /**
     * There are 3 cases to consider:
     *
     * 1: the data is a leaf. In this case, simply remove it.
     * 2: the data has one child. In this case, simply replace it with its
     * child.
     * 3: the data has 2 children. Use the successor to replace the data.
     * You must use recursion to find and remove the successor (you will likely
     * need an additional helper method to handle this case efficiently).
     *
     * @param data the data to be searched
     * @param node the node that traversal of the tree
     * @param dummy the node that store the value
     * @return the node removed from the tree.
     */
    private AVLNode<T> remove(AVLNode<T> node, AVLNode<T> dummy, T data) {
        if (node == null) {
            throw new NoSuchElementException("Data is not exist at this tree.");
        } else if (data.equals(node.getData())) {
            dummy.setData(node.getData());
            if (node.getRight() == null && node.getLeft() == null) {
                return null;
            } else if (node.getRight() == null && node.getLeft() != null) {
                return node.getLeft();
            } else if (node.getRight() != null && node.getLeft() == null) {
                return node.getRight();
            } else {
                AVLNode<T> sucDummy = new AVLNode<>(data);
                node.setLeft(predecessor(node.getLeft(), sucDummy));
                node.setData(sucDummy.getData());
            }
        } else {
            if (data.compareTo(node.getData()) < 0) {
                node.setLeft(remove(node.getLeft(), dummy, data));
            } else {
                node.setRight(remove(node.getRight(), dummy, data));
            }
        }
        updateAndBalance(node);
        return rotate(node);
    }

    /**
     * predecessor is the greatest node's value that smaller than the
     * input value
     * @param sucDummy the node that store the node's data
     * @param node the node that traversal of the tree
     *
     * @return node the greatest value stored at node
     */
    private AVLNode<T> predecessor(AVLNode<T> node, AVLNode<T> sucDummy) {
        if (node.getRight() == null) {
            sucDummy.setData(node.getData());
            return node.getLeft();
        } else {
            node.setRight(predecessor(node.getRight(), sucDummy));
        }
        return node;
    }
    /**
     * Returns the data in the tree matching the parameter passed in.
     *
     * @throws java.lang.IllegalArgumentException if the data is null
     * @throws java.util.NoSuchElementException if the data is not found
     * @param data data to get in the AVL tree
     * @return the data in the tree equal to the parameter.  Do not return the
     * same data that was passed in.  Return the data that was stored in the
     * tree.
     */
    public T get(T data) {
        if (data == null) {
            throw new IllegalArgumentException("Data can not be null");
        }
        return get(data, root).getData();

    }
    /**
     * get's helper method.
     *
     * @param data the data to be searched
     * @param node the node that traversal of the tree
     * @throws java.util.NoSuchElementException if the data is not found
     * @return node that expected data stored in the node
     */
    private AVLNode<T> get(T data, AVLNode<T> node) {
        if (node == null) {
            throw new NoSuchElementException("The data is not found in tree");
        } else if (data.compareTo(node.getData()) < 0) {
            return get(data, node.getLeft());
        } else if (data.compareTo(node.getData()) > 0) {
            return get(data, node.getRight());
        } else {
            return node;
        }
    }

    /**
     * Returns whether or not the parameter is contained within the tree.
     *
     * @throws java.lang.IllegalArgumentException if the data is null
     * @param data data to find in the AVL tree
     * @return whether or not the parameter is contained within the tree
     */
    public boolean contains(T data) {
        if (data == null) {
            throw new IllegalArgumentException("Data can not be null");
        }
        try {
            get(data);
        } catch (NoSuchElementException | IllegalArgumentException e) {
            return false;
        }
        return true;
    }

    /**
     * In your BST homework, you worked with the concept of the successor, the
     * smallest data that is larger than the current data. However, you only
     * saw it in the context of the 2-child remove case.
     *
     * This method should retrieve (but not remove) the successor of the data
     * passed in. There are 2 cases to consider:
     * 1: The right subtree is non-empty. In this case, the successor is the
     * leftmost node of the right subtree.
     * 2: The right subtree is empty. In this case, the successor is the lowest
     * ancestor of the node containing {@code data} whose left child is also
     * an ancestor of {@code data}.
     *
     * For example, in the tree below, the successor of 76 is 81, and the
     * successor of 40 is 76.
     *
     *                    76
     *                  /    \
     *                34      90
     *                  \    /
     *                  40  81
     *
     * @throws java.lang.IllegalArgumentException if the data is null
     * @throws java.util.NoSuchElementException if the data is not in the tree
     * @param data the data to find the successor of
     * @return the successor of {@code data}. If there is no larger data than
     * the one given, return null.
     */
    public T successor(T data) {
        if (data == null) {
            throw new IllegalArgumentException("Data can not be null");
        } else {
            return successor(root, data);
        }
    }
    /**
     * successor is the smallest node that greater than the input value
     * @param node the node that traversal of the tree
     * @param data the data to find the successor of
     * @return the smalled value stored at node
     */
    private T successor(AVLNode<T> node, T data) {
        if (node == null) {
            throw new NoSuchElementException("Data is not exist at this tree.");
        } else if (data.compareTo(node.getData()) > 0) {
            return successor(node.getRight(), data);
        } else if (data.compareTo(node.getData()) < 0) {
            T result = successor(node.getLeft(), data);
            if (result == null) {
                return node.getData();
            } else {
                return result;
            }
        } else {
            if (node.getRight() != null) {
                return getMin(node.getRight(), data);
            } else {
                return null;
            }
        }
    }

    /**
     * get the minimum value of node's subtree.
     * @param node the node that traversal of the tree
     * @param data the data to find the successor of
     * @return the smalled value stored at node
     */
    private T getMin(AVLNode<T> node, T data) {
        if (node.getLeft() == null) {
            return node.getData();
        } else {
            return getMin(node.getLeft(), data);
        }
    }



    /**
     * Return the height of the root of the tree.
     * 
     * This method does not need to traverse the tree since this is an AVL.
     *
     * @return the height of the root of the tree, -1 if the tree is empty
     */
    public int height() {
        if (root == null) {
            return -1;
        }
        return root.getHeight();
    }

    /**
     * Clears the tree.
     */
    public void clear() {
        root = null;
        size = 0;
    }

    /**
     * Get the number of elements in the tree.
     *
     * DO NOT USE OR MODIFY THIS METHOD!
     *
     * @return the number of elements in the tree
     */
    public int size() {
        // DO NOT MODIFY THIS METHOD!
        return size;
    }

    /**
     * Returns the root of the tree. Normally, you wouldn't do this, but it's
     * necessary to grade your code.
     *
     * DO NOT USE OR MODIFY THIS METHOD!
     *
     * @return the root of the tree
     */
    public AVLNode<T> getRoot() {
        // DO NOT MODIFY THIS METHOD!
        return root;
    }
}
