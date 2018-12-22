import java.util.Collection;
import java.util.NoSuchElementException;

/**
 * Your implementation of an AVL Tree.
 *
 * @author Le-En Huang
 * @userid ehuang42
 * @GTID 903303142
 * @version 3.0
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
            throw new IllegalArgumentException("The data set is empty.");
        } else {
            for (T el: data) {
                if (el == null) {
                    throw new IllegalArgumentException("The data is empty.");
                }
                add(el);
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
            throw new IllegalArgumentException("The data is empty.");
        } else if (size == 0) {
            root = new AVLNode<>(data);
            updateHeight(root);
            size++;
        } else {
            root = addH(data, root);
        }
    }

    /**
     * Add data to the correct location in the tree with recursion.
     *
     * @param data the data to be added.
     * @param node the node pointer of traversal.
     * @return the node being passed in.
     */
    private AVLNode<T> addH(T data, AVLNode<T> node) {
        if (node == null) {
            size++;
            return new AVLNode<>(data);
        } else if (node.getData().compareTo(data) > 0) {
            node.setLeft(addH(data, node.getLeft()));
        } else if (node.getData().compareTo(data) < 0) {
            node.setRight(addH(data, node.getRight()));
        }
        updateHeight(node);
        return rotate(node);
    }
    /**
     * Removes the data from the tree. There are 3 cases to consider:
     * 1: The data is a leaf. In this case, simply remove it.
     * 2: The data has one child. In this case, simply replace the node with
     * the child node.
     * 3: The data has 2 children. For this assignment, use the predecessor to
     * replace the data you are removing, not the successor.
     *
     * Remember to recalculate heights going up the tree, re-balancing if
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
            throw new IllegalArgumentException("The data can't be empty.");
        } else {
            AVLNode<T> dummy = new AVLNode<>(null);
            root = removeH(data, root, dummy);
            size--;
            return dummy.getData();
        }
    }

    /**
     * Helper method that removes the data from the tree with recursion.
     *
     * @param data the data to remove from the tree.
     * @param node the node pointer of traversal.
     * @param dummy the node that holds the data of the removed node.
     * @return the new root node of the subtree after rotation.
     * @throws NoSuchElementException if the data is not found in the tree
     */

    private AVLNode<T> removeH(T data, AVLNode<T> node, AVLNode<T> dummy) {
        if (node == null) {
            throw new NoSuchElementException("Data not found in the tree.");
        } else {
            if (node.getData().equals(data)) {
                dummy.setData(node.getData());
                if (node.getRight() == null && node.getLeft() == null) {
                    return null;
                } else if (node.getRight() == null) {
                    return node.getLeft();
                } else if (node.getLeft() == null) {
                    return node.getRight();
                } else {
                    AVLNode<T> temp = new AVLNode<>(node.getData());
                    node.setLeft(predH(node.getLeft(), temp));
                    node.setData(temp.getData());
                }
            } else if (data.compareTo(node.getData()) < 0) {
                node.setLeft(removeH(data, node.getLeft(), dummy));
            } else if (data.compareTo(node.getData()) > 0) {
                node.setRight(removeH(data, node.getRight(), dummy));
            }
        }
        updateHeight(node);
        return rotate(node);
    }

    /**
     * Helper method that finds the predecessor of the node with recursion.
     *
     * @param node the node pointer of traversal.
     * @param temp the node that holds the data of the removed node.
     * @return the new root node of the subtree in after rotation.
     */
    private AVLNode<T> predH(AVLNode<T> node, AVLNode<T> temp) {
        if (node.getRight() == null) {
            temp.setData(node.getData());
            return node.getLeft();
        }
        node.setRight(predH(node.getRight(), temp));
        updateHeight(node);
        return rotate(node);
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
            throw new IllegalArgumentException("The data is empty.");
        }
        return getH(data, root);
    }

    /**
     * Helper method that returns the data in the tree matching the parameter
     * passed in with recursion.
     *
     * @param data the data to search for in the tree.
     * @param node the node pointer for traversal.
     * @return a self call or data in the tree equal to the parameter.
     * @throws java.util.NoSuchElementException if the data is not found.
     */
    private T getH(T data, AVLNode<T> node) {
        if (node == null) {
            throw new NoSuchElementException("The data isn't found.");
        } else if (node.getData().equals(data)) {
            return node.getData();
        } else {
            if (node.getData().compareTo(data) > 0) {
                return getH(data, node.getLeft());
            } else {
                return getH(data, node.getRight());
            }
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
            throw new IllegalArgumentException("The data is empty.");
        }
        return searchH(data, root);
    }

    /**
     * Helper method that returns whether or not data equivalent to the given
     * parameter is contained within the tree.
     *
     * @param data the data to search for in the tree.
     * @param node the node pointer of the traversal
     * @return whether or not the parameter is contained within the tree.
     */
    private boolean searchH(T data, AVLNode<T> node) {
        if (node == null) {
            return false;
        } else if (node.getData().equals(data)) {
            return true;
        } else {
            if (node.getData().compareTo(data) > 0) {
                return searchH(data, node.getLeft());
            } else {
                return searchH(data, node.getRight());
            }
        }
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
            throw new IllegalArgumentException("The data is empty.");
        }
        return findingsucc(data, root);
    }


    /**
     * Return the data contained in predecessor.
     *
     * @param data the data passed in.
     * @param node the node pointer for recursion traversal.
     * @return the data of the predecessor.
     */
    private T findingsucc(T data, AVLNode<T> node) {
        if (node == null) {
            throw new NoSuchElementException("There's no such "
                    + "data in the tree.");
        } else if (node.getData().equals(data)) {
            if (node.getRight() != null) {
                return traverseR(node.getRight());
            } else {
                return null;
            }
        } else if (data.compareTo(node.getData()) > 0) {
            return findingsucc(data, node.getRight());
        } else {
            T result = findingsucc(data, node.getLeft());
            if (result == null) {
                return node.getData();
            } else {
                return result;
            }
        }
    }

    /**
     * Return the data contained in predecessor node after
     * traversing right subtree.
     *
     * @param node the target node desired to find the predecessor on.
     * @return the data of the predecessor.
     */
    private T traverseR(AVLNode<T> node) {
        if (node.getLeft() == null) {
            return node.getData();
        } else {
            return traverseR(node.getLeft());
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
        if (size == 0) {
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
     * Rotate the tree using balance factor.
     *
     * @param node the current node.
     * @return the new root of the tree.
     */
    private AVLNode<T> rotate(AVLNode<T> node) {
        int bf = node.getBalanceFactor();
        if (bf > 1) {
            int leftBf = node.getLeft().getBalanceFactor();
            return (leftBf < 0) ? leftRightR(node) : rightRotate(node);
        } else if (bf < -1) {
            int rightBf = node.getRight().getBalanceFactor();
            return (rightBf > 0) ? rightLeftR(node) : leftRotate(node);
        } else {
            return node;
        }
    }

    /**
     * Rotate to the left because tree is right heavy.
     *
     * @param root the root node.
     * @return the new root of the tree.
     */
    private AVLNode<T> leftRotate(AVLNode<T> root) {
        AVLNode<T> rightChild = root.getRight();
        root.setRight(rightChild.getLeft());
        rightChild.setLeft(root);
        updateHeight(root);
        updateHeight(rightChild);
        return rightChild;
    }


    /**
     * Rotate to the right because tree is left heavy.
     *
     * @param root the root node.
     * @return the new root of the tree.
     */
    private AVLNode<T> rightRotate(AVLNode<T> root) {
        AVLNode<T> leftChild = root.getLeft();
        root.setLeft(leftChild.getRight());
        leftChild.setRight(root);
        updateHeight(root);
        updateHeight(leftChild);
        return leftChild;
    }

    /**
     * Perform left right rotation to the root node passed in.
     *
     * @param root the root node.
     * @return the new root of the tree.
     */
    private AVLNode<T> rightLeftR(AVLNode<T> root) {
        root.setRight(rightRotate(root.getRight()));
        return leftRotate(root);
    }

    /**
     * Perform right left rotation to the root node passed in.
     *
     * @param root the root node.
     * @return the new root of the tree.
     */
    private AVLNode<T> leftRightR(AVLNode<T> root) {
        root.setLeft(leftRotate(root.getLeft()));
        return rightRotate(root);
    }

    /**
     * Update the node with its new height after balancing,
     * adding, and removing.
     * Storing the balance factor to the node.
     *
     * @param node the node to be updated with new height.
     */
    private void updateHeight(AVLNode<T> node) {
        int leftH = (node.getLeft() == null) ? -1
                : node.getLeft().getHeight();
        int rightH = (node.getRight() == null) ? -1
                : node.getRight().getHeight();
        node.setHeight(Math.max(leftH, rightH) + 1);
        node.setBalanceFactor(leftH - rightH);
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
