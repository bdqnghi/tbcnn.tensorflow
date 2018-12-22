import java.util.Collection;
import java.util.NoSuchElementException;

/**
 * Your implementation of an AVL Tree.
 *
 * @author Yuqi Cao
 * @userid ycao344
 * @GTID 903352025
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
            throw new IllegalArgumentException("data cannot be now.");
        }
        for (T datum: data) {
            if (datum == null) {
                throw new IllegalArgumentException(
                        "the data wanna be added cannot be null.");
            }
            add(datum);
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
            throw new IllegalArgumentException(
                    "the added data cannot be null.");
        }
        root = addHelper(root, data);
        update(root);
    }

    /**
     * This is the addHelper method, recursively add the data
     * @param node the node we want to add from
     * @param data data we want to add in
     * @return AVLNode/<T/> return a node for pointer reinforcement
     */
    private AVLNode<T> addHelper(AVLNode<T> node, T data) {
        if (node == null) {
            node = new AVLNode<>(data);
            update(node);
            size++;
            return node;
        }
        int i = node.getData().compareTo(data);
        if (i == 0) {
            return node;
        } else if (i < 0) {
            AVLNode<T> newNode = addHelper(node.getRight(), data);
            node.setRight(newNode);
        } else if (i > 0) {
            AVLNode<T> newNode = addHelper(node.getLeft(), data);
            node.setLeft(newNode);
        }
        update(node);
        int bF = node.getBalanceFactor();
        if (bF == 2) {
            if (node.getLeft().getBalanceFactor() == -1) {
                node.setLeft(leftRotate(node.getLeft()));
            }
            return rightRotate(node);
        } else if (bF == (-2)) {
            if (node.getRight().getBalanceFactor() == 1) {
                node.setRight(rightRotate(node.getRight()));
            }
            return leftRotate(node);
        } else {
            return node;
        }
    }

    /**
     * This method is used to update the node's height and balance factor
     * @param node set its height and BF
     */
    private void update(AVLNode<T> node) {
        //update height and balanceFactor
        int leftHeight = node.getLeft() == null ? -1
                : node.getLeft().getHeight();
        int rightHeight = node.getRight() == null ? -1
                : node.getRight().getHeight();
        int newHeight = 1 + Math.max(leftHeight, rightHeight);
        node.setHeight(newHeight);
        node.setBalanceFactor(leftHeight - rightHeight);
    }

    /**
     * This method is used to right rotate
     * @param node the node we want to rotate on
     * @return AVLNode/<T/> Return the new node after rotation
     */
    private AVLNode<T> rightRotate(AVLNode<T> node) {
        AVLNode<T> temp = node.getLeft();
        node.setLeft(temp.getRight());
        temp.setRight(node);
        update(node);
        update(temp);
        return temp;
    }

    /**
     * This method is used to left rotate
     * @param node the mode we want to rotate on
     * @return AVLNode/<T/> Return the new node after rotation
     */
    private AVLNode<T> leftRotate(AVLNode<T> node) {
        AVLNode<T> temp = node.getRight();
        node.setRight(temp.getLeft());
        temp.setLeft(node);
        update(node);
        update(temp);
        return temp;
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
            throw new IllegalArgumentException(
                    "The data passed in cannot be null");
        }
        if (root == null) {
            throw new NoSuchElementException("It's an empty tree.");
        }
        AVLNode<T> dummyNode = new AVLNode<>(null);
        root = removeHelper(root, data, dummyNode);
        return dummyNode.getData();
    }

    /**
     * This is the private helper method for removing recursively
     * @throws java.util.NoSuchElementException if the data is not in the tree
     * @param curr the node passed in to remove from
     * @param data data we want to remove
     * @param dummyNode node we used to store the removed data
     * @return the new node after removing
     */
    private AVLNode<T> removeHelper(AVLNode<T> curr,
                                    T data, AVLNode<T> dummyNode) {
        if (curr == null) {
            throw new NoSuchElementException(
                    "The data is not in the tree");
        }
        int i = curr.getData().compareTo(data);
        //AVLNode<T> dummyNode2 = new AVLNode<>(null);
        if (i < 0) {
            curr.setRight(removeHelper(curr.getRight(), data, dummyNode));
        } else if (i > 0) {
            curr.setLeft(removeHelper(curr.getLeft(), data, dummyNode));
        } else {
            dummyNode.setData(curr.getData());
            size--;
            //check how many children
            if (curr.getLeft() == null) {
                return curr.getRight();
            } else if (curr.getRight() == null) {
                return curr.getLeft();
            } else {
                AVLNode<T> d2 = new AVLNode<>(null);
                curr.setLeft(pred(curr.getLeft(), d2));
                curr.setData(d2.getData());
            }
        }
        update(curr);
        int bF = curr.getBalanceFactor();
        if (bF == 2) {
            if (curr.getLeft().getBalanceFactor() == -1) {
                curr.setLeft(leftRotate(curr.getLeft()));
            }
            return rightRotate(curr);
        } else if (bF == (-2)) {
            if (curr.getRight().getBalanceFactor() == 1) {
                curr.setRight(rightRotate(curr.getRight()));
            }
            return leftRotate(curr);
        } else {
            return curr;
        }
    }

    /**
     * This method is used to find the removed node's predecessor
     * @param currNode the node passed in
     * @param d2 used to store the predecessor
     * @return the new node after find predecessor and maybe remove it
     */
    private AVLNode<T> pred(AVLNode<T> currNode, AVLNode<T> d2) {
        if (currNode.getRight() == null) {
            d2.setData(currNode.getData());
            return currNode.getLeft();
        } else {
            currNode.setRight(pred(currNode.getRight(), d2));
            update(currNode);
            int bF = currNode.getBalanceFactor();
            if (bF == 2) {
                if (currNode.getLeft().getBalanceFactor() == -1) {
                    currNode.setLeft(leftRotate(currNode.getLeft()));
                }
                return rightRotate(currNode);
            } else if (bF == (-2)) {
                if (currNode.getRight().getBalanceFactor() == 1) {
                    currNode.setRight(rightRotate(currNode.getRight()));
                }
                return leftRotate(currNode);
            } else {
                return currNode;
            }
        }
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
            throw new IllegalArgumentException(
                    "The data you wanna retrieve cannot be null.");
        }
        return getHelp(root, data);
    }

    /**
     * This private method help get to find data recursively
     * @throws java.util.NoSuchElementException if data is not in the tree
     * @param node pass in the root we want to get from
     * @param data the data we want to get
     * @return the data stored in the tree if find
     */
    private T getHelp(AVLNode<T> node, T data) {
        if (node == null) {
            throw new NoSuchElementException(
                    "The data you want is not in the tree.");
        }
        int i = node.getData().compareTo(data);
        if (i == 0) {
            return node.getData();
        } else if (i < 0) {
            return getHelp(node.getRight(), data);
        } else {
            return getHelp(node.getLeft(), data);
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
                    "The data you want to search cannot be null.");
        }
        return containsHelper(root, data);
    }

    /**
     * This private method help contains recursively find the data we want.
     * @param node the node we want to find if contains data we want
     * @param data data we want to check if contains
     * @return whether or not the data is contained in this tree
     */
    private boolean containsHelper(AVLNode<T> node, T data) {
        if (node == null) {
            return false;
        }
        int i = node.getData().compareTo(data);
        if (i == 0) {
            return true;
        } else if (i < 0) {
            return containsHelper(node.getRight(), data);
        } else {
            return containsHelper(node.getLeft(), data);
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
            throw new IllegalArgumentException(
                    "The data passed in cannot be null");
        }
        if (root == null) {
            throw new NoSuchElementException("It's an empty tree.");
        }
        T candidate = null;
        return successorHelper(root, data, candidate);
    }

    /**
     * the private helper method to find successor recursively
     * @throws java.util.NoSuchElementException if the data is not in the tree
     * @param node the node we find through
     * @param data the data we want to find
     * @param candidate the data's presumed successor, got updated each time
     * @return return the exact successor
     */
    private T successorHelper(AVLNode<T> node, T data, T candidate) {
        if (node == null) {
            throw new NoSuchElementException("Data is not in the tree.");
        }
        int i = node.getData().compareTo(data);
        if (i < 0) {
            return successorHelper(node.getRight(), data, candidate);
        } else if (i > 0) {
            return successorHelper(node.getLeft(), data, node.getData());
        } else {
            if (node.getRight() == null) {
                return candidate;
            } else {
                return successorH(node.getRight());
            }
        }
    }

    /**
     * this successorH is used when the node has a right subtree
     * @param node the node used to keep goes left
     * @return the successor we found
     */
    private T successorH(AVLNode<T> node) {
        if (node.getLeft() == null) {
            return node.getData();
        } else {
            return successorH(node.getLeft());
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
