import java.util.Collection;
import java.util.List;
import java.util.LinkedList;
import java.util.Queue;
import java.util.ArrayList;

/**
 * Your implementation of an AVL Tree.
 *
 * @author Rares Cristian
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
            throw new IllegalArgumentException("Cannot add null element");
        }
        for (T d : data) {
            if (d == null) {
                throw new IllegalArgumentException("Cannot add null element");
            }
        }

        for (T d : data) {
            add(d);
        }
    }

    /**
    * helper function to find height of a node. If the node is null,
    * we say that it has a height of -1.
    *
    * @param node the node whose height we want to find.
    * @return height of node or -1 if node is null
    */
    private int height(AVLNode<T> node) {
        if (node == null) {
            return -1;
        }
        return node.getHeight();
    }

    /**
    * Given a node, we want to update its height. We can do this by looking
    * at the heights of its children.
    *
    * @param node The node whose height we want to update.
    */
    private void updateHeight(AVLNode<T> node) {
        node.setHeight(Math.max(height(node.getLeft()), height(node.getRight()))
            + 1);
    }

    /**
    * Given a node, we want to update its balance factor.
    * Balance factor is defined to be height of the left child minus height of
    * right child
    *
    * @param node The node whose balance factor we want to update.
    */
    private void updateBalance(AVLNode<T> node) {
        node.setBalanceFactor(height(node.getLeft()) - height(node.getRight()));
    }

    /**
    * Will rotate node to the left about its right child.
    *
    * @param node The node to rotate
    * @return the root of the new subtree
    */
    private AVLNode<T> leftRotate(AVLNode<T> node) {
        AVLNode<T> child = node.getRight();
        AVLNode<T> subTree = child.getLeft();

        // Perform rotation
        child.setLeft(node);
        node.setRight(subTree);

        updateHeight(node);
        updateHeight(child);

        updateBalance(node);
        updateBalance(child);

        // Return new root
        return child;
    }

    /**
    * Will rotate node to the right about its left child.
    *
    * @param node The node to rotate
    * @return the root of the new subtree
    */
    private AVLNode<T> rightRotate(AVLNode<T> node) {
        AVLNode<T> child = node.getLeft();
        AVLNode<T> subTree = child.getRight();

        // Perform rotation
        child.setRight(node);
        node.setLeft(subTree);

        updateHeight(node);
        updateHeight(child);
        updateBalance(node);
        updateBalance(child);

        return child;
    }


    /**
    * Given a node, we will balance it if needed and update heights, balance
    * factors. Performs left, right, left-right, right-left rotations as
    * needed.
    *
    * @param node a node we want to balance
    * @return the root of the subtree after rotations.
    */
    private AVLNode<T> handleRotations(AVLNode<T> node) {
        if (node == null) {
            return node;
        }

        updateHeight(node);
        updateBalance(node);

        if (node.getBalanceFactor() == -2) {
            if (node.getRight().getBalanceFactor() <= 0) {
                // left rotation
                return leftRotate(node);
            } else {
                // right left rotation
                node.setRight(rightRotate(node.getRight()));
                return leftRotate(node);
            }
        }
        if (node.getBalanceFactor() == 2) {
            if (node.getLeft().getBalanceFactor() >= 0) {
                // right rotation
                return rightRotate(node);
            } else {
                // left right rotation
                node.setLeft(leftRotate(node.getLeft()));
                return rightRotate(node);
            }
        }

        return node;
    }

    /**
    * helper function for add(T data). Recursively finds the position to add
    * data as a leaf node. Then, when going back up the recursive stack, will
    * rotate nodes as needed to balance them. Will also update heights, and
    * balance factors.
    *
    * @param data The data we want to insert into tree
    * @param node Current node in the recursion
    * @return Node that is the root of the current subtree.
    */
    private AVLNode<T> add(T data, AVLNode<T> node) {
        if (node == null) {
            size++;
            return new AVLNode<T>(data);
        }

        if (node.equals(data)) {
            size--;
            return node;
        }

        if (data.compareTo(node.getData()) < 0) {
            node.setLeft(add(data, node.getLeft()));
        } else if (data.compareTo(node.getData()) > 0) {
            node.setRight(add(data, node.getRight()));
        }

        return handleRotations(node);
    }

    @Override
    public void add(T data) {
        if (data == null) {
            throw new IllegalArgumentException("Cannot add null data");
        }

        if (size == 0) {
            root = new AVLNode<T>(data);
            updateHeight(root);
            size++;
            return;
        }

        root = add(data, root);
    }

    /**
    * A recursive function to remove the successor. Going back up the
    * recursive stack, will update heights, balance factors, and perform
    * rotations as needed.
    *
    * @param ans Will store the data of the succesor.
    * @param node The current node we are inspecting in the recursion.
    * @return new root of the current subtree we're in.
    */
    private AVLNode<T> removeSuccessor(AVLNode<T> node, AVLNode<T> ans) {
        if (node == null) {
            return node;
        }

        if (node.getLeft() == null) {
            // found what we need to remove
            ans.setData(node.getData());

            // since it's a successor, it must be one of these.s
            if (node.getLeft() == null && node.getRight() == null) {
                node = null;
            } else if (node.getLeft() != null && node.getRight() == null) {
                node = node.getLeft();
            } else if (node.getLeft() == null && node.getRight() != null) {
                node = node.getRight();
            }
        } else {
            node.setLeft(removeSuccessor(node.getLeft(), ans));
        }

        // only one node in tree initially.
        if (node == null) {
            return node;
        }

        return handleRotations(node);
    }

    /**
    * A helper function to remove data from the tree. It recursively searches
    * for the data, and and as it goes back up the recursive calls will
    * update heights, balance Factors, and perform rotations as needed.
    *
    * @param data The data we want to remove from the tree.
    * @param node Current node we are inspectinvg in the recursion.
    * @param ans Will store the node that we have just deleted, or null if
    *       data wanted to remove does not exist in the tree.
    * @return the root of the current subtree after all rotations, or null if
    *       the subtree is empty.
    */
    private AVLNode<T> remove(T data, AVLNode<T> node, AVLNode<T> ans) {
        if (node == null) {
            return node;
        }

        if (data.compareTo(node.getData()) < 0) {
            node.setLeft(remove(data, node.getLeft(), ans));
        } else if (data.compareTo(node.getData()) > 0) {
            node.setRight(remove(data, node.getRight(), ans));
        } else {
            // found what we need to remove
            ans.setData(node.getData());

            if (node.getLeft() == null && node.getRight() == null) {
                node = null;
            } else if (node.getLeft() != null && node.getRight() == null) {
                node = node.getLeft();
            } else if (node.getLeft() == null && node.getRight() != null) {
                node = node.getRight();
            } else {
                node.setRight(removeSuccessor(node.getRight(), node));
            }
        }

        return handleRotations(node);
    }

    @Override
    public T remove(T data) {
        if (data == null) {
            throw new IllegalArgumentException("Null data does not exist "
                                                + "in tree");
        }

        if (size == 0) {
            throw new java.util.NoSuchElementException("Empty tree, nothing "
                                                        + "to remove.");
        }

        AVLNode<T> ans = new AVLNode<>(null);
        root = remove(data, root, ans);
        if (ans.getData() == null) {
            throw new java.util.NoSuchElementException("Empty tree, "
                                                    + "nothing to remove.");
        }

        size--;
        return ans.getData();
    }

    /**
    * Helper function for get(T data). Recursive function that searches for
    * data by moving into left subtree if current node it is inspecting is
    * greater than target data or into right subtree if smaller.
    *
    *
    * @param data The data to check if inside tree
    * @param node The current node we are inspecting in recusion
    * @return node which contains data, or null otherwise.
    */
    private T get(T data, AVLNode<T> node) {
        if (node == null) {
            throw new java.util.NoSuchElementException("Data not "
                                                        + "found in tree");
        }

        if (node.getData().equals(data)) {
            return node.getData();
        }

        if (data.compareTo(node.getData()) < 0) {
            return get(data, node.getLeft());
        } else {
            return get(data, node.getRight());
        }
    }

    @Override
    public T get(T data) {
        if (data == null) {
            throw new IllegalArgumentException("Null data does "
                                                    + "not exist in tree");
        }

        if (size == 0) {
            throw new java.util.NoSuchElementException("Empty tree, "
                                                + "nothing to remove.");
        }

        return get(data, root);
    }

    /**
    * Helper function for contains(T data). Recursive function that searches for
    * data by moving into left subtree if current node it is inspecting is
    * greater than target data or into right subtree if smaller.
    *
    * @param data The data to check if inside tree
    * @param node The current node we are inspecting in recusion
    * @return true if parameter 'data' is inside the tree. False otherwise.
    */
    private boolean contains(T data, AVLNode<T> node) {
        if (node == null) {
            return false;
        }

        if (node.getData().equals(data)) {
            return true;
        }

        if (data.compareTo(node.getData()) < 0) {
            return contains(data, node.getLeft());
        } else {
            return contains(data, node.getRight());
        }
    }

    @Override
    public boolean contains(T data) {
        if (data == null) {
            throw new IllegalArgumentException("Null data does "
                                                + "not exist in tree");
        }

        if (size == 0) {
            throw new java.util.NoSuchElementException("Empty tree, "
                                                    + "nothing to remove.");
        }

        return contains(data, root);
    }

    @Override
    public int size() {
        return size;
    }

    /**
    * Helper functin which performs preorder traversal of a tree
    *
    * @param node current node in recursion
    * @param list current list of nodes put in 'pre-order'
    */
    private void preorder(AVLNode<T> node, List<T> list) {
        if (node == null) {
            return;
        }
        list.add(node.getData());
        preorder(node.getLeft(), list);
        preorder(node.getRight(), list);
    }

    @Override
    public List<T> preorder() {
        List<T> list = new ArrayList<T>();
        preorder(root, list);
        return list;
    }

    /**
    * Helper functin which performs postorder traversal of a tree
    *
    * @param node current node in recursion
    * @param list current list of nodes put in 'post-order'
    */
    private void postorder(AVLNode<T> node, List<T> list) {
        if (node == null) {
            return;
        }
        postorder(node.getLeft(), list);
        postorder(node.getRight(), list);
        list.add(node.getData());
    }

    @Override
    public List<T> postorder() {
        List<T> list = new ArrayList<T>();
        postorder(root, list);
        return list;
    }

    /**
    * Helper functin which performs inorder traversal of a tree
    *
    * @param node current node in recursion
    * @param list current list of nodes put in 'in-order'
    */
    private void inorder(AVLNode<T> node, List<T> list) {
        if (node == null) {
            return;
        }
        inorder(node.getLeft(), list);
        list.add(node.getData());
        inorder(node.getRight(), list);
    }

    @Override
    public List<T> inorder() {
        List<T> list = new ArrayList<T>();
        inorder(root, list);
        return list;
    }

    @Override
    public List<T> levelorder() {
        List<T> list = new ArrayList<T>();
        if (size == 0) {
            return list;
        }
        Queue<AVLNode<T>> q = new LinkedList<AVLNode<T>>();
        q.add(root);
        while (q.size() != 0) {
            AVLNode<T> cur = q.remove();

            if (cur.getLeft() != null) {
                q.add(cur.getLeft());
            }
            if (cur.getRight() != null) {
                q.add(cur.getRight());
            }

            list.add(cur.getData());

        }
        return list;
    }

    @Override
    public void clear() {
        size = 0;
        root = null;
    }

    @Override
    public int height() {
        return height(root);
    }

    @Override
    public AVLNode<T> getRoot() {
        // DO NOT EDIT THIS METHOD!
        return root;
    }
}