import java.nio.channels.IllegalChannelGroupException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.NoSuchElementException;

/**
 * Your implementation of an AVL Tree.
 *
 * @author Hao Zhang
 * @version 1.0
 */
public class AVL<T extends Comparable<? super T>> implements AVLInterface<T> {

    // Do not make any new instance variables.
    private AVLNode<T> root;
    private int size;

    /**
     * A no argument constructor that should initialize an empty AVL tree.
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
            throw new IllegalArgumentException("data cannot be null");
        }
        for (T datum : data) {
            add(datum);
        }
    }

    /**
     * Add the data as a leaf in the AVL.  Should traverse the tree to find the
     * appropriate location. If the data being added already exists in the
     * tree, do nothing. The tree has to be balanced after each adding
     * operation.
     *
     * Rotations are performed as necessary.
     *
     * @throws java.lang.IllegalArgumentException if the data is null
     * @param data the data to be added
     */
    @Override
    public void add(T data) {
        root = Add(root, data);
    }

    private AVLNode<T> Add(AVLNode<T> node, T data) {
        if (data == null) {
            throw new IllegalArgumentException();
        } else if (node == null) {
            node = new AVLNode<>(data);
            size += 1;
            return node;
        } else if (node.getData().compareTo(data) > 0) {
            node.setLeft(Add(node.getLeft(), data));
        } else if (node.getData().compareTo(data) < 0) {
            node.setRight(Add(node.getRight(), data));
        }

        node.setHeight(Height(node));
        node.setBalanceFactor(findBF(node));

        if (node.getBalanceFactor() > 1 && node.getLeft().getBalanceFactor() > 0) {
            return rightRotation(node);
        } else if (node.getBalanceFactor() > 1 && node.getLeft().getBalanceFactor() < 0) {
            node.setLeft(leftRotation(node.getLeft()));
            return rightRotation(node);
        } else if (node.getBalanceFactor() < -1 && node.getRight().getBalanceFactor() < 0) {
            return leftRotation(node);
        } else if (node.getBalanceFactor() < -1 && node.getRight().getBalanceFactor() > 0) {
            node.setRight(rightRotation(node.getRight()));
            return leftRotation(node);
        }
        return node;
    }

    private int findBF(AVLNode<T> node){
        if (node == null) {
            return 0;
        } else {
            return Height(node.getLeft()) - Height(node.getRight());
        }
    }

    @SuppressWarnings("unchecked")
    private AVLNode<T> rightRotation(AVLNode<T> b) {
        AVLNode a = b.getLeft();
        b.setLeft(a.getRight());
        a.setRight(b);
        b.setHeight(Height(b));
        a.setHeight(Height(a));
        b.setBalanceFactor(findBF(b));
        a.setBalanceFactor(findBF(a));
        return a;
    }

    @SuppressWarnings("unchecked")
    private AVLNode<T> leftRotation(AVLNode<T> a) {
        AVLNode b = a.getRight();
        a.setRight(b.getLeft());
        b.setLeft(a);
        a.setHeight(Height(a));
        b.setHeight(Height(b));
        a.setBalanceFactor(findBF(a));
        b.setBalanceFactor(findBF(b));
        return b;
    }

    /**
     * Removes the data from the tree.  There are 3 cases to consider:
     * 1: the node containing the data is a leaf node.
     *  In this case, simply remove it.
     * 2: the node containing the data has one child.  In this case, simply
     *  replace the node with the child node.
     * 3: the data has 2 children.  There are generally two approaches:
     *  replacing the data with either the largest element in the left subtree
     *  (commonly called the predecessor), or replacing it with the smallest
     *  element in the right subtree (commonly called the successor). For this
     *  assignment, use the successor.
     *
     * This method must run in O(2 log n) or better.
     *
     * Rotations are performed as necessary.
     *
     * @throws java.lang.IllegalArgumentException if the data is null
     * @throws java.util.NoSuchElementException if the data is not in the AVL
     * @param data data to remove from the tree
     * @return the data removed from the tree.  Do not return the same data
     * that was passed in.  Return the data that was stored in the tree.
     */
    @Override
    public T remove(T data) {
        AVLNode<T> dummy = new AVLNode<>(null);
        root = removePrivate(root, dummy, data);
    	return dummy.getData();
    }

    private AVLNode<T> removePrivate(AVLNode<T> node, AVLNode<T> dummy, T data) {
        if (data == null) {
            throw new IllegalArgumentException();
        } else if (node == null) {
            throw new NoSuchElementException();
        } else if (node.getData().compareTo(data) > 0) {
            node.setLeft(removePrivate(node.getLeft(), dummy, data));
        } else if (node.getData().compareTo(data) < 0) {
            node.setRight(removePrivate(node.getRight(), dummy, data));
        } else {
            dummy.setData(node.getData());
            if (node.getRight() == null && node.getLeft() == null) {
                size -= 1;
                return null;
            } else if (node.getRight() == null) {
                size -= 1;
                return node.getLeft();
            } else if (node.getLeft() == null) {
                size -= 1;
                return node.getRight();
            } else {
                AVLNode<T> temp = new AVLNode<>(null);
                node.setRight(getSuccessor(node.getRight(), temp));
                node.setData(temp.getData());
                size -= 1;
            }
        }

        node.setHeight(Height(node));
        node.setBalanceFactor(findBF(node));

        if (node.getBalanceFactor() > 1 && node.getLeft().getBalanceFactor() >= 0) {
            return rightRotation(node);
        } else if (node.getBalanceFactor() > 1 && node.getLeft().getBalanceFactor() < 0) {
            node.setLeft(leftRotation(node.getLeft()));
            return rightRotation(node);
        } else if (node.getBalanceFactor() < -1 && node.getRight().getBalanceFactor() <= 0) {
            return leftRotation(node);
        } else if (node.getBalanceFactor() < -1 && node.getRight().getBalanceFactor() > 0) {
            node.setRight(rightRotation(node.getRight()));
            return leftRotation(node);
        }
        return node;
    }

    private AVLNode<T> getSuccessor(AVLNode<T> node, AVLNode<T> dummy) {
        if (node.getLeft() != null) {
            node.setLeft(getSuccessor(node.getLeft(), dummy));
        } else {
            dummy.setData(node.getData());
            node = node.getRight();
        }
        return node;
    }

    /**
     * Adds values of each vertex (node) which lie in between the node
     * containing data equals to {@code start}, and the node containing
     * data equals to {@code end}, inclusive and in sequence (nodes closest to
     * start have to be added first). {@code start} and {@code end} have
     * to added to the list as well.
     *
     * There are 3 cases to consider:
     * 1. Start and End are of the same node. In this case, if the value exists
     *    in the tree, return a list of one element, ie. the value itself
     * 2. Either node is an ancestor of the other node
     * 3. Both nodes share at least one common ancestor
     *
     *          50
     *        /    \
     *      25      75
     *     /  \
     *    12   37
     *   /  \    \
     *  10  15    40
     *     /
     *    13
     *
     * For example, the path between 13 and 40 is
     *   [13, 15, 12, 25, 37, 40]
     * On the other hand, the path between 40 and 13 is
     *   [40, 37, 25, 12, 15, 13]
     * The path between 25 and 13 is
     *   [25, 12, 15, 13]
     * The path between 10 and 10 is
     *   [10]
     *
     * @throws java.lang.IllegalArgumentException if either start or end is
     * null
     * @throws java.util.NoSuchElementException if either start or end is not
     * in the AVL tree
     * @param start value of the starting node
     * @param end value of the ending node
     * @return the list of values representing the path between two nodes
     */
    @Override
    public List<T> findPathBetween(T start, T end) {
        List<T> list = new ArrayList<>();
        LCA(root, start, end, list);
        return list;
    }

    private void LCA(AVLNode<T> node, T start, T end, List<T> list) {
        try {
            if (start == null || end == null) {
                throw new IllegalArgumentException();
            } else if (node == null) {
                throw new NoSuchElementException();
            } else if (node.getData().compareTo(start) > 0 && node.getData().compareTo(end) > 0) {
                LCA(node.getLeft(), start, end, list);
            } else if (node.getData().compareTo(start) < 0 && node.getData().compareTo(end) < 0) {
                LCA(node.getRight(), start, end, list);
            } else {
                list.add(node.getData());
                pathToStart(node, start, list);
                pathToEnd(node, end, list);
            }
        } catch (NullPointerException e) {
            throw new NoSuchElementException("start or end cannot be found");
        }
    }

    private void pathToStart(AVLNode<T> node, T start, List<T> list) {
        if (node.getData().compareTo(start) > 0) {
            list.add(0, node.getLeft().getData());
            pathToStart(node.getLeft(), start, list);
        } else if (node.getData().compareTo(start) < 0) {
            list.add(0, node.getRight().getData());
            pathToStart(node.getRight(), start, list);
        }
    }

    private void pathToEnd(AVLNode<T> node, T end, List<T> list) {
        if (node.getData().compareTo(end) > 0) {
            list.add(list.size(), node.getLeft().getData());
            pathToEnd(node.getLeft(), end, list);
        } else if (node.getData().compareTo(end) < 0) {
            list.add(list.size(), node.getRight().getData());
            pathToEnd(node.getRight(), end, list);
        }
    }

    /**
     * Returns the data in the tree matching the parameter passed in.
     *
     * @throws java.lang.IllegalArgumentException if the data is null
     * @throws java.util.NoSuchElementException if the data is not in the tree
     * @param data data to get in the AVL tree
     * @return the data in the tree equal to the parameter.  Do not return the
     * same data that was passed in.  Return the data that was stored in the
     * tree.
     */
    @Override
    public T get(T data) {
    	return Get(root, data);
    }

    private T Get(AVLNode<T> node, T data) {
        if (data == null) {
            throw new IllegalArgumentException();
        } else if (node == null) {
            throw new NoSuchElementException();
        } else if (node.getData().compareTo(data) == 0) {
            return node.getData();
        } else if (node.getData().compareTo(data) > 0) {
            return Get(node.getLeft(), data);
        } else {
            return Get(node.getRight(), data);
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
        return Contains(root, data);
    }

    private boolean Contains(AVLNode<T> node, T data) {
        if (data == null) {
            throw new IllegalArgumentException();
        } else if (node == null) {
            return false;
        } else if (node.getData().compareTo(data) == 0) {
            return true;
        } else if (node.getData().compareTo(data) > 0) {
            return Contains(node.getLeft(), data);
        } else {
            return Contains(node.getRight(), data);
        }
    }

    /**
     * Get the number of elements in the tree.
     *
     * @return the number of elements in the tree
     */
    @Override
    public int size() {
    	return size;
    }

    /**
     * Clear the tree.
     */
    @Override
    public void clear() {
        size = 0;
        root = null;
    }

    /**
     * Calculate and return the height of the root of the tree. A node's
     * height is defined as max(left.height, right.height) + 1. A leaf node has
     * a height of 0.
     *
     * @return the height of the root of the tree, -1 if the tree is empty
     */
    @Override
    public int height() {
    	return Height(root);
    }

    private int Height(AVLNode<T> node) {
        if (node == null) {
            return -1;
        } else {
            return 1 + Math.max(Height(node.getLeft()), Height(node.getRight()));
        }
    }

    /**
     * Calculate the depth of the node containing the data.
     * The depth of the node is defined as (parent node's depth)+1.
     * The depth of the root node is 1.
     *
     * @throws java.lang.IllegalArgumentException if data is null
     * @throws java.util.NoSuchElementException if the data is not in the tree.
     * @param data data to calculate the depth of
     * @return the depth of the node containing the data if it is in the tree
     */
    @Override
    public int depth(T data) {
    	return Depth(root, data);
    }

    private int Depth(AVLNode<T> node, T data) {
        if (data == null) {
            throw new IllegalArgumentException();
        } else if (node == null) {
            throw new NoSuchElementException();
        } else if (node.getData().compareTo(data) == 0) {
            return 1;
        } else if (node.getData().compareTo(data) > 0) {
            return Depth(node.getLeft(), data) + 1;
        } else {
            return Depth(node.getRight(), data) + 1;
        }
    }

    /**
     * THIS METHOD IS ONLY FOR TESTING PURPOSES.
     * DO NOT USE IT IN YOUR CODE
     * DO NOT CHANGE THIS METHOD
     *
     * @return the root of the tree
     */
    public AVLNode<T> getRoot() {
        return root;
    }
    
    /**
     * THIS METHOD IS ONLY FOR TESTING PURPOSES.
     * DO NOT USE IT IN YOUR CODE
     * DO NOT CHANGE THIS METHOD
     *
     * @param node the root of the tree
     */
    public void setRoot(AVLNode<T> node) {
        this.root = node; 
    }

    /**
     * THIS METHOD IS ONLY FOR TESTING PURPOSES.
     * DO NOT USE IT IN YOUR CODE
     * DO NOT CHANGE THIS METHOD
     *
     * @param size the size of the tree
     */
    public void setSize(int size) {
        this.size = size;
    }

}
