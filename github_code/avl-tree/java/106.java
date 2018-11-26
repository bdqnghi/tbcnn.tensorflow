import java.util.ArrayList;
import java.util.Collection;
import java.util.LinkedList;
import java.util.List;

/**
 * Your implementation of an AVL Tree.
 *
 * @author Yue Gu
 * @userid ygu65
 * @GTID 903055355
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
            throw new java.lang.IllegalArgumentException("Collection cannot be"
                    + " null");
        } else  {
            for (T inputData : data) {
                if (inputData == null) {
                    throw new java.lang.IllegalArgumentException("Null"
                            + " element cannot be added");
                } else {
                    add(inputData);
                }
            }
        }
    }

    @Override
    public void add(T data) {
        if (data == null) {
            throw new java.lang.IllegalArgumentException("Inserted"
                    + "data is null");
        } else {
            root = addHelper(data, root);
        }
    }

    /**
     * helper method for add
     *
     * @param data the data to add to the tree
     * @param parent the node that traverses through the tree
     * @throws java.lang.IllegalArgumentException if data or any element
     * in data is null
     * @return parent node that part of the tree
     */
    private AVLNode<T> addHelper(T data, AVLNode<T> parent) {
        if (parent == null) {
            size++;
            return new AVLNode<>(data);
        } else if (data.compareTo(parent.getData()) < 0) {
            parent.setLeft(addHelper(data, parent.getLeft()));
        } else if (data.compareTo(parent.getData()) > 0) {
            parent.setRight(addHelper(data, parent.getRight()));
        }
        updateHeight(parent);
        updateBalance(parent);
        parent = balance(parent);
        return parent;
    }

    /**
     * balances the AVL tree
     *
     * @param a the node to balance
     * @return a node that is balanced
     */
    private AVLNode<T> balance(AVLNode<T> a) {
        if (a.getBalanceFactor() < -1) {
            if (a.getRight().getBalanceFactor() > 0) {
                a = rotateRightLeft(a);
            } else {
                a = rotateLeft(a);
            }
        } else if (a.getBalanceFactor() > 1) {
            if (a.getLeft().getBalanceFactor() < 0) {
                a = rotateLeftRight(a);
            } else {
                a = rotateRight(a);
            }
        }
        return a;
    }

    /**
     * rotates the part of tree left
     *
     * @param a the node to rotate
     * @return a node that is rotated left
     */
    private AVLNode<T> rotateLeft(AVLNode a) {
        AVLNode b = a.getRight();
        a.setRight(b.getLeft());
        b.setLeft(a);
        updateHeight(a);
        updateBalance(a);
        updateHeight(b);
        updateBalance(b);
        return b;
    }

    /**
     * rotates the part of tree right
     *
     * @param a the node to rotate
     * @return a node that is rotated right
     */
    private AVLNode<T> rotateRight(AVLNode a) {
        AVLNode b = a.getLeft();
        a.setLeft(b.getRight());
        b.setRight(a);
        updateHeight(a);
        updateBalance(a);
        updateHeight(b);
        updateBalance(b);
        return b;
    }

    /**
     * rotates the part of tree right then left
     *
     * @param a the node to rotate
     * @return rotateLeft(a) root node of rotated subtree
     */
    private AVLNode<T> rotateRightLeft(AVLNode a) {
        AVLNode b = a.getRight();
        a.setRight(rotateRight(b));
        return rotateLeft(a);
    }

    /**
     * rotates the part of tree left then right
     *
     * @param a the node to rotate
     * @return rotateRight(a) root node of rotated subtree
     */
    private AVLNode<T> rotateLeftRight(AVLNode a) {
        AVLNode b = a.getLeft();
        a.setLeft(rotateLeft(b));
        return rotateRight(a);
    }

    /**
     * updates the balance factor of a node
     *
     * @param a the node to update balance factor
     */
    private void updateBalance(AVLNode a) {
        AVLNode left = a.getLeft();
        AVLNode right = a.getRight();
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
        a.setBalanceFactor(leftHeight - rightHeight);
    }

    /**
     * updates the height of a node
     *
     * @param a the node to update height
     */
    private void updateHeight(AVLNode a) {
        AVLNode left = a.getLeft();
        AVLNode right = a.getRight();
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
        if (rightHeight > leftHeight) {
            a.setHeight(++rightHeight);
        } else {
            a.setHeight(++leftHeight);
        }
    }

    @Override
    public T remove(T data) {
        AVLNode<T> dummy = new AVLNode<>(null);
        if (data == null) {
            throw new java.lang.IllegalArgumentException("Inserted"
                    + "data is null");
        } else {
            root = removeHelper(data, root, dummy);
            size--;
            return dummy.getData();
        }
    }

    /**
     * helper method for remove
     *
     * @param data the data to add to the tree
     * @param current node that traverses through the tree
     * @param dummy node that has the return data
     * @throws java.util.NoSuchElementException if data is not found
     * in data is null
     * @return current node that traverses through the tree
     */
    public AVLNode<T> removeHelper(T data,
                                   AVLNode<T> current, AVLNode<T> dummy) {
        AVLNode<T> random = new AVLNode<>(null);
        if (current == null) {
            throw new java.util.NoSuchElementException("Data was not found in"
                    + "BST");
        } else if (data.compareTo(current.getData()) < 0) {
            current.setLeft(removeHelper(data, current.getLeft(), dummy));
        } else if (data.compareTo(current.getData()) > 0) {
            current.setRight(removeHelper(data, current.getRight(), dummy));
        } else {
            dummy.setData(current.getData());
            if (current.getLeft() != null && current.getRight() != null) {
                AVLNode<T> temp = current.getLeft();
                while (temp.getRight() != null) {
                    temp = temp.getRight();
                }
                AVLNode<T> predecessor = temp;
                current.setData(predecessor.getData());
                current.setLeft(removeHelper(predecessor.getData(),
                        current.getLeft(), random));
                updateHeight(current);
                updateBalance(current);
                current = balance(current);
            } else if (current.getLeft() != null) {
                return current.getLeft();
            } else if (current.getRight() != null) {
                return current.getRight();
            } else {
                return null;
            }
        }
        updateHeight(current);
        updateBalance(current);
        current = balance(current);
        return current;
    }

    @Override
    public T get(T data) {
        if (data == null) {
            throw new java.lang.IllegalArgumentException("Inserted"
                    + "data is null");
        } else {
            return getHelper(data, root);
        }
    }

    /**
     * helper method for get
     *
     * @param data to search for in the tree
     * @param parent node that traverses through the tree
     * @throws java.util.NoSuchElementException if data is not found
     * in data is null
     * @return data that is found in the tree
     */
    public T getHelper(T data, AVLNode<T> parent) {
        if (parent == null) {
            throw new java.util.NoSuchElementException("Node"
                    + "with inserted data was not found");
        }
        if (data.compareTo(parent.getData()) < 0) {
            return getHelper(data, parent.getLeft());
        } else if (data.compareTo(parent.getData()) > 0) {
            return getHelper(data, parent.getRight());
        }
        return parent.getData();
    }

    @Override
    public boolean contains(T data) {
        if (data == null) {
            throw new java.lang.IllegalArgumentException("Inserted"
                    + "data is null");
        }
        if (size == 0) {
            return false;
        } else {
            return containsHelper(data, root);
        }
    }

    /**
     * helper method for contains
     *
     * @param data to search for in tree
     * @param parent node that traverses through the tree
     * @return boolean to check if data is in the tree
     */
    public boolean containsHelper(T data, AVLNode<T> parent) {
        if (data.compareTo(parent.getData()) < 0) {
            if (parent.getLeft() == null) {
                return false;
            } else {
                return containsHelper(data, parent.getLeft());
            }
        } else if (data.compareTo(parent.getData()) > 0) {
            if (parent.getRight() == null) {
                return false;
            } else {
                return containsHelper(data, parent.getRight());
            }
        } else {
            return true;
        }
    }

    @Override
    public int size() {
        // DO NOT MODIFY THIS METHOD!
        return size;
    }

    @Override
    public List<T> preorder() {
        ArrayList<T> list = new ArrayList<>();
        preorderHelper(root, list);
        return list;
    }

    /**
     * helper method for preorder
     *
     * @param node pointer that traverses through the tree
     * @param list to return and add to
     */
    public void preorderHelper(AVLNode<T> node, ArrayList<T> list) {
        if (node != null) {
            list.add(node.getData());
            preorderHelper(node.getLeft(), list);
            preorderHelper(node.getRight(), list);
        }
    }

    @Override
    public List<T> postorder() {
        ArrayList<T> list = new ArrayList<>();
        postorderHelper(root, list);
        return list;
    }

    /**
     * helper method for postorder
     *
     * @param node pointer that traverses through the tree
     * @param list to return and add to
     */
    public void postorderHelper(AVLNode<T> node, ArrayList<T> list) {
        if (node != null) {
            postorderHelper(node.getLeft(), list);
            postorderHelper(node.getRight(), list);
            list.add(node.getData());
        }
    }

    @Override
    public List<T> inorder() {
        ArrayList<T> list = new ArrayList<>();
        inorderHelper(root, list);
        return list;
    }

    /**
     * helper method for inorder
     *
     * @param node pointer that traverses through the tree
     * @param list to return and add to
     */
    public void inorderHelper(AVLNode<T> node, ArrayList<T> list) {
        if (node != null) {
            inorderHelper(node.getLeft(), list);
            list.add(node.getData());
            inorderHelper(node.getRight(), list);
        }
    }

    @Override
    public List<T> levelorder() {
        ArrayList<T> list = new ArrayList<>();
        LinkedList<AVLNode<T>> queue = new LinkedList<>();
        if (root == null) {
            return list;
        }
        queue.add(root);
        AVLNode<T> temp;
        while (!queue.isEmpty()) {
            temp = queue.get(0);
            if (temp.getLeft() != null) {
                queue.add(temp.getLeft());
            }
            if (temp.getRight() != null) {
                queue.add(temp.getRight());
            }
            list.add(temp.getData());
            queue.remove(0);
        }
        return list;
    }

    @Override
    public List<T> listLeavesDescending() {
        ArrayList<T> result = new ArrayList<>();
        descendingHelper(root, result);
        return result;
    }

    /**
     * helper method for listLeavesDescending
     *
     * @param node pointer that traverses through the tree
     * @param list to return and add to
     */
    private void descendingHelper(AVLNode<T> node, ArrayList<T> list) {
        if (node != null)   {
            descendingHelper(node.getLeft(), list);
            if (node.getLeft() == null && node.getRight() == null)  {
                list.add(0, node.getData());
            }
            descendingHelper(node.getRight(), list);
        }
    }

    @Override
    public void clear() {
        root = null;
        size = 0;
    }

    @Override
    public int height() {
        return heightHelper(root);
    }

    /**
     * helper method for height
     *
     * @param parent node that traverses through the tree
     * @return height of tree
     */
    public int heightHelper(AVLNode<T> parent) {
        int height;
        if (parent == null) {
            return -1;
        } else {
            height = Math.max(heightHelper(parent.getLeft()),
                    heightHelper(parent.getRight())) + 1;
            return height;
        }
    }

    @Override
    public AVLNode<T> getRoot() {
        // DO NOT MODIFY THIS METHOD!
        return root;
    }
}
