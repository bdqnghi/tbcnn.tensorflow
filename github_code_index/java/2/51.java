import java.util.Collection;

/**
 * Your implementation of an AVL Tree.
 *
 * @author Rosemary Blair
 * @userid rblair8
 * @GTID 903359318
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
            throw new IllegalArgumentException("Cannot have null data.");
        }
        for (T item : data) {
            add(item);
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
            throw new java.lang.IllegalArgumentException(
                "Cannot add null data to tree.");
        }
        root = addHelper(data, root);
    }

    /**
     * A recursive add method to add the data to the tree appropriately.
     * If added, the height and balance factor of curr will be updated.
     *
     * @param data - the data to be added
     * @param curr - the current AVLNode
     * @return the root AVLNode
     */
    private AVLNode<T> addHelper(T data, AVLNode<T> curr) {
        if (curr == null) { //found spot
            size++;
            return new AVLNode<T>(data);
        } else {
            if (data.compareTo(curr.getData()) < 0) { //go left
                curr.setLeft(addHelper(data, curr.getLeft()));
            } else if (data.compareTo(curr.getData()) > 0) { //go right
                curr.setRight(addHelper(data, curr.getRight()));
            }
        }
        update(curr); //update height/BF for curr
        return rotateCheck(curr);
    }

    /**
     * A method to update the height and balance factor of a node if needed.
     * Updating height/BF is necessary after add/remove/rotate operations.
     *
     * @param curr - the current AVLNode to update
     */
    private void update(AVLNode<T> curr) {
        int leftHeight = (curr.getLeft() == null) ? -1
            : curr.getLeft().getHeight();
        int rightHeight = (curr.getRight() == null) ? -1
            : curr.getRight().getHeight();
        curr.setHeight(Math.max(leftHeight, rightHeight) + 1);
        curr.setBalanceFactor(leftHeight - rightHeight);
    }

    /**
     * A method that checks a node's balance factor to see if a rotation
     * is necessary or not for balancing the tree.
     *
     * @param curr - the current AVLNode being checked
     * @return the subtree after checked/rotated
     */
    private AVLNode<T> rotateCheck(AVLNode<T> curr) {
        int bf = curr.getBalanceFactor();
        if (bf < -1) { //curr is right-heavy
            if (curr.getRight().getBalanceFactor() > 0) { //right-left rotate
                curr.setRight(rightRotate(curr.getRight())); //rotate right 1st
            }
            return leftRotate(curr); //rotate left
        } else if (bf > 1) { //curr is left-heavy
            if (curr.getLeft().getBalanceFactor() < 0) { //left-right rotate
                curr.setLeft(leftRotate(curr.getLeft())); //rotate left 1st
            }
            return rightRotate(curr); //rotate right
        }
        return curr;
    }

    /**
     * Given a node as a root, performs a right rotation on the node's subtree.
     *
     * @param curr - the current root of the subtree
     * @return the updated root node of the subtree
     */
    private AVLNode<T> rightRotate(AVLNode<T> curr) {
        AVLNode<T> leftChild = curr.getLeft();
        curr.setLeft(leftChild.getRight());
        leftChild.setRight(curr);
        update(curr);
        update(leftChild);
        return leftChild;
    }

    /**
     * Given a node as a root, performs a left rotation on the node's subtree.
     *
     * @param curr - the current root of the subtree
     * @return the updated root node of the subtree
     */
    private AVLNode<T> leftRotate(AVLNode<T> curr) {
        AVLNode<T> rightChild = curr.getRight();
        curr.setRight(rightChild.getLeft());
        rightChild.setLeft(curr);
        update(curr);
        update(rightChild);
        return rightChild;
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
            throw new IllegalArgumentException("Cannot remove null data.");
        }
        AVLNode<T> temp = new AVLNode<T>(data);
        root = removeHelper(root, temp); //NoSuchElementException can be thrown
        size--;
        return temp.getData();
    }

    /**
     * A recursive remove helper method to find and remove a node from tree.
     *
     * @throws java.util.NoSuchElementException if data is not found in tree
     * @param curr - the current subtree to search
     * @param temp - a node object to store the data to be returned in remove
     * method.
     * @return the subtree after removal
     */
    private AVLNode<T> removeHelper(AVLNode<T> curr, AVLNode<T> temp) {
        if (curr == null) {
            throw new java.util.NoSuchElementException(
                "Attempt to remove nonexistent data from tree.");
        } else {
            if (temp.getData().compareTo(curr.getData()) < 0) {
                curr.setLeft(removeHelper(curr.getLeft(), temp));
            } else if (temp.getData().compareTo(curr.getData()) > 0) {
                curr.setRight(removeHelper(curr.getRight(), temp));
            } else {
                temp.setData(curr.getData());
                return removeChildren(curr);
            }
            update(curr);
            return rotateCheck(curr);
        }
    }

    /**
     * An additional remove helper to help with removing a node once found.
     *
     * @param curr - the node to be removed from the tree
     * @return null if no children, the child of a node with 1 child only, or
     * if the node had 2 children, the node stored in the removed node's place
     * after, found from the predecessor of the node.
     */
    private AVLNode<T> removeChildren(AVLNode<T> curr) {
        if (curr.getLeft() == null && curr.getRight() == null) {
            return null;
        } else if (curr.getLeft() != null && curr.getRight() == null) {
            return curr.getLeft(); //return only child
        } else if (curr.getLeft() == null && curr.getRight() != null) {
            return curr.getRight(); //return only child
        } else { //2 children
            AVLNode<T> predecessor = findMax(curr.getLeft());
            curr.setData(predecessor.getData());
            curr.setLeft(removeHelper(curr.getLeft(), predecessor));
            update(curr);
            return rotateCheck(curr);
        }
    }

    /**
     * Method that finds the predecessor of a node by locating the maximum
     * valued node in its left subtree.
     *
     * @param curr - the current left subtree of the node
     * @return the predecessor node
     */
    private AVLNode<T> findMax(AVLNode<T> curr) {
        if (curr.getRight() != null) {
            return findMax(curr.getRight());
        }
        return curr;
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
            throw new IllegalArgumentException("Cannot use get() with null.");
        }
        AVLNode<T> node = getHelper(root, data);
        if (node == null || node.getData().compareTo(data) != 0) {
            throw new java.util.NoSuchElementException(
                "Cannot use get() - data not found in tree.");
        }
        return node.getData();
    }

    /**
     * Get helper method to retrieve the node with inputted data.
     *
     * @param curr - current subtree to traverse through
     * @param data - the data of the node we wish to get
     * @return found node (or null if not found)
     */
    private AVLNode<T> getHelper(AVLNode<T> curr, T data) {
        if (curr == null) {
            return null;
        } else {
            if (data.compareTo(curr.getData()) < 0) {
                return getHelper(curr.getLeft(), data);
            } else if (data.compareTo(curr.getData()) > 0) {
                return getHelper(curr.getRight(), data);
            }
            return curr;
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
            throw new IllegalArgumentException(
                "Cannot use null for argument in contains().");
        }
        AVLNode<T> node = getHelper(root, data);
        if (node != null && node.getData().compareTo(data) == 0) {
            return true;
        }
        return false; //node is either null or data doesn't match
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
            throw new IllegalArgumentException("Cannot use null data.");
        }
        if (root == null) {
            throw new java.util.NoSuchElementException(
                "Element with data not found in tree.");
        }
        AVLNode<T> successor = findSuccessor(root, data, null);
        return (successor != null) ? successor.getData() : null;
    }

    /**
     * A recursive method to find the successor. The successor variable is only
     * updated if the data is < curr.data, so in the case that we have the
     * have the rightmost node as with our data, it would return null b/c it
     * would not have one. If the node with data isn't found, throws error.
     * This traverses the tree in-order.
     * 
     * @throws java.util.NoSuchElementException if data isn't found in tree
     * @param curr - the current subtree to traverse
     * @param data - the data we are trying to find
     * @param successor - the ancestor to node with data (or null if none)
     * @return the successor node, or null if there isn't one for the node
     */
    private AVLNode<T> findSuccessor(AVLNode<T> curr, T data,
        AVLNode<T> successor) {
        if (curr == null) {
            throw new java.util.NoSuchElementException(
                "Element with data not found in tree.");
        } else if (curr.getData().compareTo(data) == 0) {
            if (curr.getRight() != null) {
                return findMin(curr.getRight());
            } else {
                return successor;
            }
        } else {
            if (data.compareTo(curr.getData()) < 0) {
                if (curr.getLeft() != null) {
                    return findSuccessor(curr.getLeft(), data, curr);
                } else { //no more elements, not found
                    throw new java.util.NoSuchElementException(
                        "Element with data not found in tree.");
                }
            } else { // data > curr.data
                if (curr.getRight() != null) {
                    return findSuccessor(curr.getRight(), data, successor);
                } else { //no more elements, not found
                    throw new java.util.NoSuchElementException(
                        "Element with data not found in tree.");
                }
            }
        }
    }

    /**
     * A recursive method to find the mimimum node of a subtree.
     *
     * @param curr - the current subtree to traverse
     * @return the node with smallest value in subtree
     */

    private AVLNode<T> findMin(AVLNode<T> curr) {
        if (curr.getLeft() != null) {
            return findMin(curr.getLeft());
        }
        return curr;
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
        } else {
            return root.getHeight();
        }
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
