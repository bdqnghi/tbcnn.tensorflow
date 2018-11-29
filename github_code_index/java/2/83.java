import java.util.Collection;
import java.util.NoSuchElementException;

/**
 * Your implementation of an AVL Tree.
 *
 * @author Zack Vogel
 * @userid dvogel3
 * @GTID 903208462
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
            throw new IllegalArgumentException("AVL cannot be created with "
                    + "null data");
        }
        for (T element : data) {
            add(element);
        }
    }

    /**
     * This is a private height method that I created to deal with null nodes.
     * When getting the height of a null node, it will return -1 for correct
     * calculation of balanceHelper factors for balancing purposes of the tree.
     * @param node node that will have height checked for null
     * @return height of node passed in
     */
    private int getHeightRevise(AVLNode<T> node) {
        if (node == null) {
            return -1;
        }
        return node.getHeight();
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
            throw new IllegalArgumentException("Cannot add null data to tree.");
        } else {
            root = addHelper(root, data);
        }
    }

    /**
     *
     * @param temp creates temporary node in order to add to AVL
     * @param data data to be added to the new part of the AVL
     * @return node with data
     */
    private AVLNode<T> addHelper(AVLNode<T> temp, T data) {
        if (temp == null) {
            size++;
            return new AVLNode<T>(data);
        }
        if (data.compareTo(temp.getData()) == 0) {
            return temp;
        }
        if (data.compareTo(temp.getData()) < 0) {
            temp.setLeft(addHelper(temp.getLeft(), data));
            temp.setBalanceFactor(getHeightRevise(temp.getLeft())
                    - getHeightRevise(temp.getRight()));
            temp = balanceHelper(temp);
        } else {
            temp.setRight(addHelper(temp.getRight(), data));
            temp.setBalanceFactor(getHeightRevise(temp.getLeft())
                - getHeightRevise(temp.getRight()));
            temp = balanceHelper(temp);
        }
        temp.setHeight(Math.max(getHeightRevise(temp.getLeft()),
                getHeightRevise(temp.getRight())) + 1);
        temp.setBalanceFactor(getHeightRevise(temp.getLeft())
                - getHeightRevise(temp.getRight()));
        return temp;
    }
    /**
     * description: private balanceHelper method that is used in the add method
     * to make the code look cleaner in each method for readability.
     * @param node the node that we are balancing at.
     * @return the node we are working with
     *
     */
    private AVLNode<T> balanceHelper(AVLNode<T> node) {
        if (node.getBalanceFactor() > 1) {
            if (node.getLeft() != null
                    && node.getLeft().getBalanceFactor() >= 0) {
                node = rightRotate(node);
            } else {
                node = leftRightRotate(node);
            }
        } else if (node.getBalanceFactor() < -1) {
            if (node.getRight() != null
                    && node.getRight().getBalanceFactor() <= 0) {
                node = leftRotate(node);
            } else {
                node = rightLeftRotate(node);
            }
        }
        return node;
    }
    /**
     * Right rotation helper method that will help balanceHelper the AVL if
     * left heavy
     * @param temp the node to rotate at
     * @return the rotated node
     */
    private AVLNode<T> rightRotate(AVLNode<T> temp) {
        AVLNode<T> newP = temp.getLeft();
        temp.setLeft(newP.getRight());
        newP.setRight(temp);
        temp.setHeight(Math.max(getHeightRevise(temp.getRight()),
                getHeightRevise(temp.getLeft())) + 1);
        newP.setHeight(Math.max(getHeightRevise(newP.getLeft()),
                getHeightRevise(newP.getRight())) + 1);
        temp.setBalanceFactor(getHeightRevise(temp.getLeft())
                - getHeightRevise(temp.getRight()));
        newP.setBalanceFactor(getHeightRevise(temp.getLeft())
                - getHeightRevise(temp.getRight()));
        return newP;
    }

    /**
     * Left rotation helper method that will help balanceHelper the AVL if
     * right heavy
     * @param node node to rotate at
     * @return the rotated node
     */
    private AVLNode<T> leftRotate(AVLNode<T> node) {
        AVLNode<T> newP = node.getRight();
        node.setRight(newP.getLeft());
        newP.setLeft(node);
        node.setHeight(Math.max(getHeightRevise(node.getRight()),
                getHeightRevise(node.getLeft())) + 1);
        newP.setHeight(Math.max(getHeightRevise(newP.getLeft()),
                getHeightRevise(newP.getRight())) + 1);
        node.setBalanceFactor(getHeightRevise(node.getLeft())
                - getHeightRevise(node.getRight()));
        newP.setBalanceFactor(getHeightRevise(newP.getLeft())
                - getHeightRevise(newP.getRight()));
        return newP;
    }


    /**
     * Private Double rotation (right then left) helper method
     * that corrects a bend in the AVL and then proceeds to complete the
     * opposite required single rotation.
     * @param node is the node to rotate
     * @return the rotated node
     */
    private AVLNode<T> rightLeftRotate(AVLNode<T> node) {
        node.setRight(rightRotate(node.getRight()));
        return leftRotate(node);
    }

    /**
     * Private Double rotation (left then right) helper method
     * that corrects a bend in the AVL and then proceeds to complete the
     * opposite required single rotation.
     * @param node is the node to rotate
     * @return the rotated node
     */
    private AVLNode<T> leftRightRotate(AVLNode<T> node) {
        node.setLeft(leftRotate(node.getLeft()));
        return rightRotate(node);
    }


    /** Removes the data from the tree. There are 3 cases to consider:
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
        AVLNode<T> node = new AVLNode<T>(null);
        root = removeHelper(root, data, node);
        size--;
        return node.getData();
    }
    /**
     * This is a remove helper function that I created in order to make
     * the main code for the remove function cleaner and easier to read.
     * This is a recursive helper that removes and rebalances as necessary.
     * @param root stores node to be removed in temp
     * @param data data to be removed
     * @param node a holder for the node that will later be returned as the
     *             removed node from the AVL
     * @return returns temporary node
     */
    private AVLNode<T> removeHelper(AVLNode<T> root, T data,
                                    AVLNode<T> node) {
        AVLNode<T> none = new AVLNode<T>(null);
        if (root == null) {
            throw new java.util.NoSuchElementException("Element not in AVL");
        } else if (data.compareTo(root.getData()) < 0) {
            root.setLeft(removeHelper(root.getLeft(), data, node));
        } else if (data.compareTo(root.getData()) > 0) {
            root.setRight(removeHelper(root.getRight(), data, node));
        } else {
            if (node != null) {
                node.setData(root.getData());
            }
            if (root.getLeft() == null && root.getRight() == null) {
                root = null;
            }
            if (root.getLeft() == null) {
                node.setData(root.getData());
                root.setBalanceFactor(getHeightRevise(root.getLeft())
                        - getHeightRevise(root.getRight()));
                return root.getRight();
            } else if (root.getRight() == null) {
                node.setData(root.getData());
                root.setBalanceFactor(getHeightRevise(root.getLeft())
                        - getHeightRevise(root.getRight()));
                return root.getLeft();
            } else {
                node.setData(root.getData());
                root.setData(nodeSearch(root.getLeft()));
                root.setLeft(removeHelper(root.getLeft(),
                        root.getData(), none));
                root.setHeight(Math.max(getHeightRevise(root.getRight()),
                        getHeightRevise(root.getLeft())) + 1);
                root.setBalanceFactor(getHeightRevise(root.getLeft())
                        - getHeightRevise(root.getRight()));
                root = balanceHelper(root);
            }
        }
        root.setHeight(Math.max(getHeightRevise(root.getRight()),
                getHeightRevise(root.getLeft())) + 1);
        root = balanceHelper(root);
        root.setBalanceFactor(getHeightRevise(root.getLeft())
                - getHeightRevise(root.getRight()));

        return root;

    }
    /**
     *This is my node search helper method that uses a while loop to look
     * for the predecessor when removing from the AVL.
     * @param search takes in the previously looked at node to find the
     * predecessor
     * @return data from node
     */
    private T nodeSearch(AVLNode<T> search) {
        if (search.getRight() == null) {
            return search.getData();
        }
        T search = nodeSearch(search.getRight());
        return search.getData();
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
            throw new IllegalArgumentException("Cannot retrieve null data.");
        }
        return getHelper(root, data);
    }

    /**
     * This is a helper get method that uses recursion to find the requested
     * element in the tree. Used to make the main function cleaner and easier
     * to read.
     * @param temp temporary node to store the node in
     * @param data the data to be searched for
     * @return data sought
     */
    private T getHelper(AVLNode<T> temp, T data) {
        if (temp == null) {
            throw new NoSuchElementException("Data not in tree.");
        }
        if (data.compareTo(temp.getData()) == 0) {
            return temp.getData();
        } else if (data.compareTo(temp.getData()) < 0) {
            return getHelper(temp.getLeft(), data);
        } else {
            return getHelper(temp.getRight(), data);
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
            throw new IllegalArgumentException("Tree will not have null data");
        }
        return containsHelper(root, data);
    }

    /**
     * This is my contains helper method which uses recursion to determine if
     * the tree contains the requested element. The same idea is applied to my
     * get helper method from above.
     * @param temp creates a node to store the node
     * @param data data being sought
     * @return boolean of whether BST contains data
     */
    private boolean containsHelper(AVLNode<T> temp, T data) {
        if (temp == null) {
            return false;
        }
        if (data.compareTo(temp.getData()) == 0) {
            return true;
        } else if (data.compareTo(temp.getData()) < 0) {
            return containsHelper(temp.getLeft(), data);
        } else {
            return containsHelper(temp.getRight(), data);
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
            throw new IllegalArgumentException("Data cannot be null.");
        }
        if (root.getData() == data) {
            AVLNode<T> node = root;
            return successorHelperTwo(node);
        } else {
            AVLNode<T> node = successorHelperOne(root, data);
            return successorHelperTwo(node);
        }
    }

    /**
     * This is my first successor helper method that recursively traverses the
     * AVL to find where in the tree the data is to then be used to find its
     * successor
     * @throws NoSuchElementException if data is not found in tree
     * @param temp a node that is passed into the method to help find the node
     * with the passed in data
     * @param data the data that the method is looking for.
     * @return an AVL node where the data passed in is located in the tree
     */
    private AVLNode<T> successorHelperOne(AVLNode<T> temp, T data) {
        if (temp == null) {
            throw new NoSuchElementException("Data is not in tree.");
        }
        if (data.compareTo(temp.getData()) == 0) {
            AVLNode<T> found = temp;
            return found;
        } else if (data.compareTo(temp.getData()) < 0) {
            return successorHelperOne(temp.getLeft(), data);
        } else {
            return successorHelperOne(temp.getRight(), data);
        }
    }

    /**
     * A second helper method to find the successor from the node where the data
     * is located in the tree.
     * @param temp the node where the data in the tree is located
     * @return the data of the successor node or null if no successor can be
     * found
     */
    private T successorHelperTwo(AVLNode<T> temp) {
        if (temp == null) {
            throw new NoSuchElementException("Data not in tree");
        }
        AVLNode<T> p = temp;
        if (p.getData().compareTo(root.getData()) > 0 && p.getLeft() == null
                && p.getRight() == null) {
            return root.getData();
        }
        if (p.getRight() != null) {
            p = p.getRight();
            while (p.getLeft().getLeft() != null) {
                p = p.getLeft();
            }
            return p.getLeft().getData();
        }
        return root.getData();
    }

    /**
     * Return the height of the root of the tree.
     * 
     * This method does not need to traverse the tree since this is an AVL.
     *
     * @return the height of the root of the tree, -1 if the tree is empty
     */
    public int height() {
        return heightHelp(root);
    }

    /**
     * A height helper method to assist in finding the height of a node;
     * @param temp the node we wish to find the height of in the AVL
     * @return an int representing the height of the node in the AVL
     */
    private int heightHelp(AVLNode<T> temp) {
        if (temp == null) {
            return -1;
        } else {
            return 1 + Math.max(heightHelp(temp.getLeft()),
                    heightHelp(temp.getRight()));
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
