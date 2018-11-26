import java.util.Collection;
import java.util.List;
import java.util.Set;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Queue;
import java.util.LinkedList;
import java.util.HashSet;

/**
 * Your implementation of an AVL Tree.
 *
 * @author Vaibhav Dedhia 903117055
 * @version 1.0
 */
public class AVL<T extends Comparable<? super T>> implements AVLInterface<T> {
    // DO NOT ADD OR MODIFY INSTANCE VARIABLES.
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
            throw new IllegalArgumentException("data cannot be null");
        }
        Iterator itr = data.iterator();
        T val;
        while (itr.hasNext()) {
            val = (T) itr.next();
            add(val);
        }
    }


    /**
     * Initializes the AVL tree with the data in the Collection. The data
     * should be added in the same order it is in the Collection.
     *
     * @param y the node for rotation
     * @return the updated node
     */
    private AVLNode<T> rightRotate(AVLNode<T> y) {
        if (y == null) {
            return y;
        }

        AVLNode<T> x = y.getLeft();
        AVLNode<T> newT = x.getRight();
        x.setRight(y);   // Rotation
        y.setLeft(newT);

        int leftHeight  = y.getLeft()  == null ? -1 : y.getLeft().getHeight();
        int rightHeight = y.getRight() == null ? -1 : y.getRight().getHeight();
        y.setHeight(Math.max(leftHeight, rightHeight) + 1);
        y.setBalanceFactor(leftHeight - rightHeight);

        leftHeight  = x.getLeft()  == null ? -1 : x.getLeft().getHeight();
        rightHeight = x.getRight() == null ? -1 : x.getRight().getHeight();
        x.setHeight(Math.max(leftHeight, rightHeight) + 1);
        x.setBalanceFactor(leftHeight - rightHeight);
        return x;
    }
    /**
     * Initializes the AVL tree with the data in the Collection. The data
     * should be added in the same order it is in the Collection.
     *
     * @param x the node for rotation
     * @return the updated node
     */
    private AVLNode<T> leftRotate(AVLNode<T> x) {
        if (x == null) {
            return x;
        }
        AVLNode<T> y = x.getRight();
        AVLNode<T> newN = y.getLeft();
        y.setLeft(x);   // Rotation
        x.setRight(newN);

        int leftHeight  = x.getLeft()  == null ? -1 : x.getLeft().getHeight();
        int rightHeight = x.getRight() == null ? -1 : x.getRight().getHeight();
        x.setHeight(Math.max(leftHeight, rightHeight) + 1);
        x.setBalanceFactor(leftHeight - rightHeight);

        leftHeight  = y.getLeft()  == null ? -1 : y.getLeft().getHeight();
        rightHeight = y.getRight() == null ? -1 : y.getRight().getHeight();
        y.setHeight(Math.max(leftHeight, rightHeight) + 1);
        y.setBalanceFactor(leftHeight - rightHeight);
        return y;
    }


    /**
     * Initializes the AVL tree with the data in the Collection. The data
     * should be added in the same order it is in the Collection.
     *
     * @param data the data to be added
     * @param current the node
     * @return the updated node
     */
    private AVLNode<T> addHelper(T data, AVLNode<T> current) {
        if (current == null) {
            size = size + 1;
            return new AVLNode<T>(data);
        } else if (data.compareTo(current.getData()) < 0) {
            current.setLeft(addHelper(data, current.getLeft()));
        } else if (data.compareTo(current.getData()) > 0) {
            current.setRight(addHelper(data, current.getRight()));
        }

        int leftHeight  = current.getLeft()  == null ? -1
                : current.getLeft().getHeight();
        int rightHeight = current.getRight() == null ? -1
                : current.getRight().getHeight();
        current.setHeight(Math.max(leftHeight, rightHeight) + 1);
        current.setBalanceFactor(leftHeight - rightHeight);
        int balDiff = leftHeight - rightHeight;

        if (balDiff > 1 && data.compareTo(current.getLeft().getData()) < 0) {
            return rightRotate(current);
        } else if (balDiff < -1
                && data.compareTo(current.getRight().getData()) > 0) {
            return leftRotate(current);
        } else if (balDiff > 1
                && data.compareTo(current.getLeft().getData()) > 0) {
            current.setLeft(leftRotate(current.getLeft()));
            return rightRotate(current);
        } else if (balDiff < -1
                && data.compareTo(current.getRight().getData()) < 0) {
            current.setRight(rightRotate(current.getRight()));
            return leftRotate(current);
        }
        return current;
    }


    @Override
    public void add(T data) {
        if (data == null) {
            throw new IllegalArgumentException("data to be added"
                    +  " cannot be null");
        }
        this.root = addHelper(data, root); // adds like BST
    }




    /**
     * A helper method to remove a new Node to AVL tree
     *
     * @param data the data to add to the tree
     * @param current the node
     * @param val the node to hold the data of the node removed
     * @throws java.util.NoSuchElementException if data doesnt exist
     * @return it returns the node.
     */
    private AVLNode<T> removeHelper(T data, AVLNode<T> current,
                                    AVLNode<T> val) {
        if (current == null) {
            throw new java.util.NoSuchElementException("data does not exist "
                    + "in binary search tree ");
        }
        if (current.getData().equals(data)) {
            if (current.getRight() == null) {
                val.setData(current.getData());
                this.size = this.size - 1;
                return current.getLeft();
            } else if (current.getLeft() == null) {
                val.setData(current.getData());
                this.size = this.size - 1;
                return current.getRight();
            } else {
                val.setData(current.getData());
                AVLNode<T> explore = current.getRight();
                while (explore.getLeft() != null) {
                    explore = explore.getLeft();
                }
                current.setData(explore.getData());
                AVLNode<T> del = new AVLNode<T>(null);
                current.setRight(removeHelper(explore.getData(),
                        current.getRight(), del));
            }
        } else if (data.compareTo(current.getData()) > 0) {
            current.setRight(removeHelper(data, current.getRight(), val));
        } else {
            current.setLeft(removeHelper(data, current.getLeft(), val));
        }


        if (current == null) {
            return current;
        }

        int leftHeight  = current.getLeft()  == null ? -1
                : current.getLeft().getHeight();
        int rightHeight = current.getRight() == null ? -1
                : current.getRight().getHeight();
        current.setHeight(Math.max(leftHeight, rightHeight) + 1);
        current.setBalanceFactor(leftHeight - rightHeight);
        int balDiff = leftHeight - rightHeight;


        if (balDiff > 1 && current.getLeft().getBalanceFactor() >= 0) {
            return rightRotate(current);
        } else if (balDiff < -1
                && current.getRight().getBalanceFactor() <= 0) {
            return leftRotate(current);
        } else if (balDiff > 1 && current.getLeft().getBalanceFactor() < 0) {
            current.setLeft(leftRotate(current.getLeft()));
            return rightRotate(current);
        } else if (balDiff < -1 && current.getRight().getBalanceFactor() > 0) {
            current.setRight(rightRotate(current.getRight()));
            return leftRotate(current);
        }
        return current;
    }
    @Override
    public T remove(T data) {
        if (data == null) {
            throw new IllegalArgumentException("data to be deleted"
                    + " cannot be null");
        }
        AVLNode<T> val = new AVLNode<T>(null);
        root = removeHelper(data, root, val);
        return val.getData();
    }


    /**
     * Initializes the AVL tree with the data in the Collection. The data
     * should be added in the same order it is in the Collection.
     *
     * @param data to be added
     * @param current the node
     * @return the updated node
     */
    private T getHelper(T data, AVLNode<T> current) {
        if (current == null) {
            throw new java.util.NoSuchElementException("data does not "
                    +  "exist in binary search tree ");
        }
        if (current.getData().equals(data)) {
            return current.getData();
        } else if (data.compareTo(current.getData()) > 0) {
            return getHelper(data, current.getRight());
        } else {
            return getHelper(data, current.getLeft());
        }
    }
    @Override
    public T get(T data) {
        if (data == null) {
            throw new IllegalArgumentException("data to be searched "
                    + "for cannot be null");
        }
        T val = getHelper(data, root);
        return val;
    }


    /**
     * Initializes the AVL tree with the data in the Collection. The data
     * should be added in the same order it is in the Collection.
     *
     * @param data to be searched for
     * @param current the node
     * @return the updated node
     */
    private boolean containsHelper(T data, AVLNode<T> current) {
        if (current == null) {
            return false;
        }
        if (current.getData().equals(data)) {
            return true;
        } else if (data.compareTo(current.getData()) > 0) {
            return containsHelper(data, current.getRight());
        } else {
            return containsHelper(data, current.getLeft());
        }
    }
    @Override
    public boolean contains(T data) {
        if (data == null) {
            throw new java.lang.IllegalArgumentException("cannot "
                    + "search for data with null");
        }
        return containsHelper(data, root);
    }



    @Override
    public int size() {
        return this.size;
    }


    /**
     * Initializes the AVL tree with the data in the Collection. The data
     * should be added in the same order it is in the Collection.
     *
     * @param current the node
     * @return the updated node
     */
    private List<T> preorderHelper(AVLNode<T> current) {
        List<T> myList = new ArrayList<T>();
        if (current != null) {
            myList.add(current.getData());
            myList.addAll(preorderHelper(current.getLeft()));
            myList.addAll(preorderHelper(current.getRight()));
        }
        return myList;
    }
    @Override
    public List<T> preorder() {
        return preorderHelper(root);
    }



    /**
     * Initializes the AVL tree with the data in the Collection. The data
     * should be added in the same order it is in the Collection.
     *
     * @param current the node for rotation
     * @return the updated node
     */
    private List<T> postorderHelper(AVLNode<T> current) {
        List<T> myList = new ArrayList<T>();
        if (current != null) {
            myList.addAll(postorderHelper(current.getLeft()));
            myList.addAll(postorderHelper(current.getRight()));
            myList.add(current.getData());
        }
        return myList;
    }
    @Override
    public List<T> postorder() {
        return postorderHelper(root);
    }



    /**
     * Initializes the AVL tree with the data in the Collection. The data
     * should be added in the same order it is in the Collection.
     *
     * @param set the set
     * @param current the node
     * @param lower the lower limit
     * @param upper the upper limit
     * @return the updated node
     */
    public Set<T> thresholdHelper(Set<T> set, AVLNode<T> current,
                                  T lower, T upper) {
        if (current == null) {
            return set;
        }
        if (current.getData().compareTo(lower) > 0) {
            thresholdHelper(set, current.getLeft(), lower, upper);
        }
        if (current.getData().compareTo(lower) > 0
                && current.getData().compareTo(upper) < 0) {
            set.add(current.getData());
        }
        if (current.getData().compareTo(upper) < 0) {
            thresholdHelper(set, current.getRight(), lower, upper);
        }
        return set;
    }
    @Override
    public Set<T> threshold(T lower, T upper) {
        if (lower == null) {
            throw new java.lang.IllegalArgumentException("Lower "
                    + "threshold cannot be null");
        } else if (upper == null) {
            throw new java.lang.IllegalArgumentException("Upper "
                    + "threshold cannot be null");
        } else {
            Set<T> set = new HashSet<T>();
            return thresholdHelper(set, root, lower, upper);
        }
    }



    /**
     * Initializes the AVL tree with the data in the Collection. The data
     * should be added in the same order it is in the Collection.
     *
     * @param list the list
     * @param current the node
     */
    void levelOrderhelper(LinkedList<T> list, AVLNode<T> current) {
        Queue<AVLNode<T>> queue = new LinkedList<AVLNode<T>>();
        queue.add(current);
        while (!queue.isEmpty()) {
            AVLNode<T> tempNode = queue.poll();
            list.addLast(tempNode.getData());

            /*Enqueue left child */
            if (tempNode.getLeft() != null) {
                queue.add(tempNode.getLeft());
            }

            /*Enqueue right child */
            if (tempNode.getRight() != null) {
                queue.add(tempNode.getRight());
            }
        }
    }
    @Override
    public List<T> levelorder() {
        LinkedList<T> list = new LinkedList<T>();
        levelOrderhelper(list, root);
        return list;
    }




    @Override
    public void clear() {
        this.root = null;
        this.size = 0;

    }

    @Override
    public int height() {
        if (root == null) {
            return -1;
        }
        return root.getHeight();
    }

    @Override
    public AVLNode<T> getRoot() {
        // DO NOT EDIT THIS METHOD!
        return root;
    }
}
