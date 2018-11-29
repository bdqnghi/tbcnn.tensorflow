import java.util.Collection;
import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

/**
 * Your implementation of an AVL Tree.
 *
 * @author Michael Troughton
 * @version 1.0
 */
public class AVL<T extends Comparable<? super T>> implements AVLInterface<T> {
    // DO NOT ADD OR MODIFY INSTANCE VARIABLES.
    private AVLNode<T> root;
    private int size;

    /**
     * I wanted to use compare() instead of compareTo()
     * @param x data being compared
     * @param y data being compared
     * @return Comparison between x and y data
     */
    private int compare(T x, T y) {
        return x.compareTo(y);
    }

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
        String error = "None of the data elements you add can be null";
        if (data == null) {
            throw new IllegalArgumentException(error);
        }
        for (T x : data) {
            if (x == null) {
                throw new IllegalArgumentException(error);
            }
            add(x);
        }
    }

    /**
     * Updates height and balance factor of node
     * @param node The node whose values are to be calculated and updated
     * @return The node passed in with updated values
     */
    private AVLNode<T> update(AVLNode<T> node) {
        if (node != null) {
            AVLNode<T> left = node.getLeft();
            AVLNode<T> right = node.getRight();
            int leftHeight;
            int rightHeight;
            if (left == null) {
                leftHeight = -1;
            } else {
                leftHeight = left.getHeight();
            }
            if (right == null) {
                rightHeight = -1;
            } else {
                rightHeight = right.getHeight();
            }
            node.setHeight(1 + Math.max(leftHeight, rightHeight));
            node.setBalanceFactor(leftHeight - rightHeight);
        }
        return node;
    }

    /**
     * Determines what rotation needs to be done if any and also executes
     * rotation
     *
     * @param node The node to potentially be rotated
     * @return The new root of the subtree that is now balanced due to the
     *          rotation
     */
    private AVLNode<T> rotate(AVLNode<T> node) {
        if (node == null) {
            return null;
        }
        node = update(node);
        int balanceFactor = node.getBalanceFactor();
        // System.out.println("PreRotatedNode:" + node);
        if (balanceFactor > 1) {
            AVLNode<T> left = update(node.getLeft());
            if (left == null) {
                return node;
            }
            int leftBalanceFactor = left.getBalanceFactor();
            if (leftBalanceFactor < 0) {
                node = leftRight(node);
            } else if (leftBalanceFactor > 0) {
                // System.out.println("I NEED TO RIGHT ROTATE!");
                node = right(node);
            }
        } else if (balanceFactor < -1) {
            AVLNode<T> right = update(node.getRight());
            if (right == null) {
                return node;
            }
            int rightBalanceFactor = right.getBalanceFactor();
            if (rightBalanceFactor < 0) {
                node = left(node);
            } else if (rightBalanceFactor > 0) {
                // System.out.println("I NEED TO RIGHTLEFT");
                node = rightLeft(node);
            }
        }
        node = update(node);
        // System.out.println("RotatedNode:" + node);
        return node;
    }

    /**
     * Performs a left rotation on a node
     *
     * @param node The node to have the left rotation performed on
     * @return The new tree that is now balanced
     */
    private AVLNode<T> left(AVLNode<T> node) {
        AVLNode<T> left = node;
        AVLNode<T> rightLeft;
        if (node.getRight() != null && node.getRight().getLeft() != null) {
            rightLeft = node.getRight().getLeft();
        } else {
            rightLeft = null;
        }
        if (node.getRight() != null) {
            node = node.getRight();
        } else {
            return node;
        }
        node.setLeft(left);
        node.getLeft().setRight(rightLeft);
        update(node);
        update(node.getLeft());
        return node;
    }

    /**
     * Performs a right rotation on a node
     *
     * @param node The node to have the right rotation performed on
     * @return The new tree that is now balanced
     */
    private AVLNode<T> right(AVLNode<T> node) {
        AVLNode<T> right = node;
        AVLNode<T> leftRight;
        if (node.getLeft() != null && node.getLeft().getRight() != null) {
            leftRight = node.getLeft().getRight();
        } else {
            leftRight = null;
        }
        if (node.getLeft() != null) {
            node = node.getLeft();
        } else {
            return node;
        }
        node.setRight(right);
        node.getRight().setLeft(leftRight);
        update(node);
        update(node.getRight());
        return node;
    }

    /**
     * Performs a left right rotation on a node
     *
     * @param node The node to have the left right rotation performed on
     * @return The new tree that is now balanced
     */
    private AVLNode<T> leftRight(AVLNode<T> node) {
        node.setLeft(left(node.getLeft()));
        return right(node);
    }

    /**
     * Performs a right left rotation on a node
     *
     * @param node The node to have the right left rotation performed on
     * @return The new tree that is now balanced
     */
    private AVLNode<T> rightLeft(AVLNode<T> node) {
        node.setRight(right(node.getRight()));
        return left(node);
    }


    @Override
    public void add(T data) {
        if (data == null) {
            String error = "The data you are trying to add is null.";
            throw new IllegalArgumentException(error);
        }
        root = addHelper(root, data);
        // System.out.println("Root:" + root);
        // System.out.println("Left:" + root.getLeft());
        // System.out.println("Right:" + root.getRight());
        // List<T> list = levelorder();
        // for (T x:list) {
        //     System.out.print(x + " ");
        // }
        // System.out.println();
    }

    /**
     * Recursive helper to add
     * @param tree the tree that you are trying to add to
     * @param data the value being added
     * @return the tree that was modified - Data added if wasn't already in tree
     */
    private AVLNode<T> addHelper(AVLNode<T> tree, T data) {
        if (tree == null) {
            tree = new AVLNode<T>(data);
            size++;
        } else {
            int compare = data.compareTo(tree.getData());
            if (compare > 0 || data == null) {
                // if data is null or data > node
                tree.setRight(addHelper(tree.getRight(), data));
            } else if (data != null && compare < 0) {
                // if data is !null and data <= node
                tree.setLeft(addHelper(tree.getLeft(), data));
            } else {
                return tree;
            }
        }
        return rotate(tree);
    }

    @Override
    public T remove(T data) {
        if (data == null) {
            String error = "The data you are trying to remove is null.";
            throw new IllegalArgumentException(error);
        }
        AVLNode<T> dummy = new AVLNode<T>(null);
        root = removeHelper(root, data, dummy);
        size--;
        // System.out.println("---- REMOVING ----");
        // System.out.println("Root:" + root);
        // System.out.println("Left:" + root.getLeft());
        // System.out.println("Right:" + root.getRight());
        // List<T> list = levelorder();
        // for (T x:list) {
        //     System.out.print(x + " ");
        // }
        // System.out.println();
        return dummy.getData();
    }

    /**
     * Recursive helper to remove
     * @param tree the tree you are trying to remove from
     * @param data the value being removed
     * @param dummy dummy node used to return value after removing from tree
     * @return tree the tree that has been removed from if found in tree
     */
    private AVLNode<T> removeHelper(AVLNode<T> tree, T data, AVLNode<T> dummy) {
        if (tree == null) {
            String error = "The data you are trying to remove is null.";
            throw new java.util.NoSuchElementException(error);
        } else if (compare(data, tree.getData()) < 0) {
            tree.setLeft(removeHelper(tree.getLeft(), data, dummy));
        } else if (compare(data, tree.getData()) > 0) {
            tree.setRight(removeHelper(tree.getRight(), data, dummy));
        } else { // FOUND DATA TO DELETE
            dummy.setData(tree.getData());
            if (tree.getLeft() == null) {
                return tree.getRight();
            } else if (tree.getRight() == null) {
                return tree.getLeft();
            } else { // CASE OF 2 CHILDREN NODE
                AVLNode<T> dummy2 = new AVLNode<T>(null);
                AVLNode<T> right = tree.getRight();
                tree.setRight(getSuccessor(right, dummy2));
                tree.setData(dummy2.getData());
            }
        }
        return rotate(tree);
    }

    /**
     * Recursive function to find successor
     * @param node the tree you are looking for the successor in
     * @param dummy the dummy node used to store temp data before deleting
     * @return the tree in which the successor was deleted
     */
    private AVLNode<T> getSuccessor(AVLNode<T> node, AVLNode<T> dummy) {
        if (node == null) {
            return null;
        } else if (node.getLeft() == null) { // found data?
            dummy.setData(node.getData());
            return null;
        } else {
            node.setLeft(getSuccessor(node.getLeft(), dummy));
        }
        return rotate(node);
    }

    @Override
    public T get(T data) {
        T out;
        if (data == null) {
            throw new IllegalArgumentException("Not allowed to"
                + " pass in Null data to get");
        } else if (root == null) {
            throw new java.util.NoSuchElementException("AVL is empty, "
                + "no element to get");
        } else {
            out = getHelper(root, data);
        }
        if (out != null) {
            return out;
        } else {
            throw new java.util.NoSuchElementException("Data "
                + "passed in was not found in the AVL");
        }
    }

    /**
     * Helper function for Get
     * @param tree the tree you are trying to get the data from
     * @param data the data you are trying to find within the tree
     * @return return the data if found within tree
     */
    private T getHelper(AVLNode<T> tree, T data) {
        T out;
        if (compare(data, tree.getData()) < 0) {
            if (tree.getLeft() == null) {
                out = null;
            } else {
                out = getHelper(tree.getLeft(), data);
            }
        } else if (compare(data, tree.getData()) > 0) {
            if (tree.getRight() == null) {
                out = null;
            } else {
                out = getHelper(tree.getRight(), data);
            }
        } else {
            out = tree.getData();
        }
        return out;
    }

    @Override
    public boolean contains(T data) {
        if (data == null) {
            String error = "The data you are trying to check for is null";
            throw new IllegalArgumentException(error);
        }
        return containsHelper(root, data);
    }

    /**
     * Helper function for contains
     * @param tree the tree in which you are trying to check for a data
     * @param data the data you are trying to check
     * @return returns true if found, false otherwise
     */
    private boolean containsHelper(AVLNode<T> tree, T data) {
        if (tree == null) {
            return false;
        }
        T treeData = tree.getData();
        if (compare(data, treeData) == 0) {
            return true;
        } else if (compare(data, treeData) < 0) { // data < treeData
            return containsHelper(tree.getLeft(), data);
        } else { // data == null, or data > treeData
            return containsHelper(tree.getRight(), data);
        }
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public List<T> preorder() {
        List<T> list = new ArrayList<T>();
        return preorder(root, list);
    }

    /**
     * Recursive helper for preorder
     * @param tree the tree you are performing preorder on
     * @param list the list in which you want to store the traversal
     * @return the order in which the tree was traversed
     */
    private List<T> preorder(AVLNode<T> tree, List<T> list) {
        if (tree != null) {
            list.add(tree.getData());
            preorder(tree.getLeft(), list);
            preorder(tree.getRight(), list);
        }
        return list;
    }

    @Override
    public List<T> postorder() {
        List<T> list = new ArrayList<T>();
        return postorder(root, list);
    }

    /**
     * Recursive helper for postorder
     * @param tree the tree you are performing postorder on
     * @param list the list in which you want to store the traversal
     * @return the order in which the tree was traversed
     */
    private List<T> postorder(AVLNode<T> tree, List<T> list) {
        if (tree != null) {
            postorder(tree.getLeft(), list);
            postorder(tree.getRight(), list);
            list.add(tree.getData());
        }
        return list;
    }

    @Override
    public List<T> inorder() {
        List<T> list = new ArrayList<T>();
        return inorder(root, list);
    }

    /**
     * Recursive helper for inorder traversal
     * @param tree the tree you are performing in order on
     * @param list the list in which you want to store the traversal
     * @return the order in which the tree was traversed
     */
    private List<T> inorder(AVLNode<T> tree, List<T> list) {
        if (tree != null) {
            inorder(tree.getLeft(), list);
            list.add(tree.getData());
            inorder(tree.getRight(), list);
        }
        return list;
    }

    @Override
    public List<T> levelorder() {
        List<T> list = new ArrayList<T>();
        Queue<AVLNode<T>> queue = new LinkedList<AVLNode<T>>();
        if (root == null) {
            return list;
        }
        queue.add(root);
        while (!queue.isEmpty()) {
            AVLNode<T> temp = queue.poll();
            list.add(temp.getData());
            if (temp.getLeft() != null) {
                queue.add(temp.getLeft());
            }
            if (temp.getRight() != null) {
                queue.add(temp.getRight());
            }
        }
        return list;
    }

    @Override
    public void clear() {
        root = null;
        size = 0;
    }

    @Override
    public int height() {
        if (root != null) {
            return root.getHeight();
        } else {
            return -1;
        }
    }

    @Override
    public AVLNode<T> getRoot() {
        // DO NOT EDIT THIS METHOD!
        return root;
    }
}
