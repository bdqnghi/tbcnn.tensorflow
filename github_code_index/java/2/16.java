import java.util.Collection;
import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

/**
 * Your implementation of an AVL Tree.
 *
 * @author MADDIE RAVICHANDRAN
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
        this.root = null;
        this.size = 0;
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
            throw new IllegalArgumentException("data cant be null");
        }
        for (T d : data) {
            add(d);
        }
    }

    @Override
    public void add(T data) throws IllegalArgumentException {
        if (data == null) {
            throw new IllegalArgumentException("Data to add can't be null");
        }
        root = add(root, data);
    }
    /**
     * adds the data to the current node then calls balanceTree
     * @param data the data to be added
     * @param node the node where we are adding
     * @return node that is updated with the element added
     */
    private AVLNode<T> add(AVLNode<T> node, T data) {
        if (node == null) {
            size++;
            AVLNode<T> newNode = new AVLNode<>(data);
            node = newNode;
        } else if (data.compareTo(node.getData()) < 0) {
            node.setLeft(add(node.getLeft(), data));
            calculateBF(node);
            if (node.getBalanceFactor() > 1) {
                AVLNode<T> left = node.getLeft();
                if (left != null) {
                    if (height(left.getLeft()) >= height(left.getRight())) {
                        node = rotateWithLeftChild(node);
                    } else {
                        node = doubleWithLeftChild(node); //L then R
                    }
                }
            }
        } else if (data.compareTo(node.getData()) > 0) {
            node.setRight(add(node.getRight(), data));
            calculateBF(node);
            if (node.getBalanceFactor() < -1) {
                AVLNode<T> right = node.getRight();
                if (right != null) {
                    if (height(right.getRight()) >= height(right.getLeft())) {
                        node = rotateWithRightChild(node);
                    } else {
                        node = doubleWithRightChild(node); //R then L
                    }
                }
            }
        }
        int h = Math.max(height(node.getLeft()), height(node.getRight()));
        node.setHeight(h + 1);
        calculateBF(node);
        return node;
    }
    /**
    * Internal method to calculate balance factor of current node
    * @param node to be calculated
    */
    private void calculateBF(AVLNode<T> node) {
        if (node.getLeft() == null && node.getRight() == null) {
            node.setBalanceFactor(0);
        } else if (node.getLeft() != null) {
            calculateBF(node.getLeft());
        } else if (node.getRight() != null) {
            calculateBF(node.getRight());
        }
        if (node != null) {
            node.setBalanceFactor(
                  height(node.getLeft()) - height(node.getRight()));
        }
    }

    /**
    * Rotate AVL tree node with left child.
    * Update heights, then return new root.
    * @param current node to be rotated
    * @return root after rotation is done
    */
    private AVLNode<T> rotateWithLeftChild(AVLNode<T> current) {
        AVLNode<T> tempNode = current.getLeft();
        current.setLeft(tempNode.getRight());
        tempNode.setRight(current);
        current.setHeight(Math.max(
                height(current.getLeft()), height(current.getRight())) + 1);
        tempNode.setHeight(Math.max(
                height(tempNode.getLeft()), height(tempNode.getRight())) + 1);
        calculateBF(current);
        return tempNode;
    }
    /**
    * Rotate AVL tree node with right child.
    * Update heights, then return new root.
    * @param current node to be rotated
    * @return root after rotation is done
    */
    private AVLNode<T> rotateWithRightChild(AVLNode<T> current) {
        AVLNode<T> node = current.getRight();
        current.setRight(node.getLeft());
        node.setLeft(current);
        current.setHeight(Math.max(
              height(current.getLeft()), height(current.getRight())) + 1);
        node.setHeight(Math.max(
              height(node.getLeft()), height(node.getRight())) + 1);
        calculateBF(current);
        return node;
    }
    /**
    * Rotate AVL tree node with left child then right
    * Update heights, then return new root.
    * @param node to be rotated
    * @return root after rotation is done
    */
    private AVLNode<T> doubleWithLeftChild(AVLNode<T> node) {
        AVLNode<T> temp;
        node.setLeft(rotateWithRightChild(node.getLeft()));
        temp = rotateWithLeftChild(node);
        return temp;
    }
    /**
    * Rotate AVL tree node with right child then with left.
    * Update heights, then return new root.
    * @param node to be rotated right then left
    * @return root after rotation is done
    */
    private AVLNode<T> doubleWithRightChild(AVLNode<T> node) {
        AVLNode<T> temp;
        node.setRight(rotateWithLeftChild(node.getRight()));
        temp = rotateWithRightChild(node);
        return temp;
    }

    @Override
    public T remove(T data) throws IllegalArgumentException {
        if (data == null) {
            throw new IllegalArgumentException("data to remove can't be null");
        }
        AVLNode<T> dummy = new AVLNode<>(null);
        root = remove(root, data, dummy);
        return dummy.getData();
    }

    /**
     * removes the data in the current node, dummy node is what will be returned
     * @param data the data to be removed
     * @param node the node where we are removing
     * @param dummy node where removed data will be stored
     * @return node that has updated removal
     * @throws java.util.NoSuchElementException if data not in tree
     */
    private AVLNode<T> remove(AVLNode<T> node, T data, AVLNode<T> dummy)
        throws java.util.NoSuchElementException {
        if (node == null) {
            throw new java.util.NoSuchElementException("Data not in tree");
        }
        int compare = data.compareTo(node.getData());
        if (compare == 0) {
            dummy.setData(node.getData());
            size--;
            if (node.getLeft() != null && node.getRight() != null) {
                AVLNode<T> left = node.getLeft();
                AVLNode<T> right = node.getRight();
                node = removeMin(right, node);
                AVLNode<T> newRight = node.getRight();
                node.setLeft(left);
                node.setRight(right);
                if (node.getRight().getData() == node.getData()) {
                    node.setRight(newRight);
                }
            } else if (node.getLeft() == null && node.getRight() == null) {
                node = null;
            } else if (node.getLeft() != null) {
                node = node.getLeft();
            } else {
                node = node.getRight();
            }
        } else if (compare > 0) {
            node.setRight(remove(node.getRight(), data, dummy));
        } else {
            node.setLeft(remove(node.getLeft(), data, dummy));
        }

        //balance since youve removed
        if (node == null) {
            return node;
        }

        int h = Math.max(height(node.getLeft()), height(node.getRight()));
        node.setHeight(h + 1);
        calculateBF(node);

        if (node.getBalanceFactor() > 1) {
            AVLNode<T> left = node.getLeft();
            if (left != null) {
                if (height(left.getLeft()) >= height(left.getRight())) {
                    node = rotateWithLeftChild(node);
                } else {
                    node = doubleWithLeftChild(node); //L then R
                }
            }
        } else if (node.getBalanceFactor() < -1) {
            AVLNode<T> right = node.getRight();
            if (right != null) {
                if (height(right.getRight()) >= height(right.getLeft())) {
                    node = rotateWithRightChild(node);
                } else {
                    node = doubleWithRightChild(node); //R then L
                }
            }
        }
        int newH = Math.max(height(node.getLeft()), height(node.getRight()));
        node.setHeight(newH + 1);
        calculateBF(node);

        return node;
    }

    /**
     * removes the min of current subtree, goes right first, then all left
     * @param parent the parent of the subtree
     * @param current the current subree
     * @return node that has updated removal
     */
    private AVLNode<T> removeMin(AVLNode<T> current, AVLNode<T> parent) {
        if (current == null) {
            return null;
        } else if (current.getLeft() == null) {
            if (parent != root) {
                parent.setLeft(current.getRight());
            }
            return current;
        }
        return removeMin(current.getLeft(), current);
    }

    @Override
    public T get(T data) throws IllegalArgumentException {
        if (data == null) {
            throw new java.lang.IllegalArgumentException("Data can't be null");
        }
        return get(root, data);
    }
    /**
     * gets the node holding the data
     * @param data the data to be got
     * @param node the node where we are getting
     * @return node that has the data to get
     * @throws java.util.NoSuchElementException if data not in tree
     */
    private T get(AVLNode<T> node, T data)
        throws java.util.NoSuchElementException {
        if (node == null) {
            throw new java.util.NoSuchElementException("Data not found");
        } else if (data.compareTo(node.getData()) == 0) {
            return node.getData();
        } else if (data.compareTo(node.getData()) > 0) {
            return get(node.getRight(), data);
        } else if (data.compareTo(node.getData()) < 0) {
            return get(node.getLeft(), data);
        }
        return node.getData();
    }

    @Override
    public boolean contains(T data) throws IllegalArgumentException {
        if (data == null) {
            throw new java.lang.IllegalArgumentException("Data can't be null");
        }
        return contains(data, root);
    }
    /**
     * returns boolean whether data is in tree
     * @param data the data we are looking for in tree
     * @param node the node we are starting traversal in
     * @return true if data is in tree, false otherwise
     */
    private boolean contains(T data, AVLNode<T> node) {
        if (node == null) {
            return false;
        } else if (data.compareTo(node.getData()) == 0) {
            return true;
        } else if (data.compareTo(node.getData()) > 0) {
            return contains(data, node.getRight());
        } else if (data.compareTo(node.getData()) < 0) {
            return contains(data, node.getLeft());
        }
        return false;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public List<T> preorder() {
        List<T> list = new ArrayList<T>();
        preorder(root, list);
        return list;
    }
    /**
    * Helper for preorder
    * @param node where to start traversal
    * @param list to be returned holding traversal
    */
    private void preorder(AVLNode<T> node, List<T> list) {
        if (node != null) {
            list.add(node.getData());
            preorder(node.getLeft(), list);
            preorder(node.getRight(), list);
        }
    }

    @Override
    public List<T> postorder() {
        List<T> list = new ArrayList<T>();
        postorder(root, list);
        return list;
    }
    /**
    * Helper for postorder
    * @param node where to start traversal
    * @param list to be returned holding traversal
    */
    private void postorder(AVLNode<T> node, List<T> list) {
        if (node != null) {
            postorder(node.getLeft(), list);
            postorder(node.getRight(), list);
            list.add(node.getData());
        }
    }

    @Override
    public List<T> inorder() {
        List<T> list = new ArrayList<T>();
        inorder(root, list);
        return list;
    }
    /**
    * Helper for inorder
    * @param node where to start traversal
    * @param list to be returned holding traversal
    */
    private void inorder(AVLNode<T> node, List<T> list) {
        if (node != null) {
            inorder(node.getLeft(), list);
            list.add(node.getData());
            inorder(node.getRight(), list);
        }
    }

    @Override
    public List<T> levelorder() {
        List<T> list = new LinkedList<>();
        Queue<AVLNode<T>> queue = new LinkedList<>();
        if (root == null) {
            return list;
        }
        queue.add(root);
        while (!queue.isEmpty()) {
            AVLNode<T> tempNode = queue.poll();
            list.add(tempNode.getData());
            if (tempNode.getLeft() != null) {
                queue.add(tempNode.getLeft());
            }
            if (tempNode.getRight() != null) {
                queue.add(tempNode.getRight());
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
        return height(root);
    }

    /**
    * helper for height that takes in a node
    * @param node is current node
    * @return int height of current node
    */
    private int height(AVLNode<T> node) {
        if (node == null) {
            return -1;
        } else {
            return node.getHeight();
        }
    }


    @Override
    public AVLNode<T> getRoot() {
        // DO NOT EDIT THIS METHOD!
        return root;
    }
}
