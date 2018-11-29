import java.util.ArrayList;
import java.util.Collection;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

/**
 * Your implementation of an AVL Tree.
 *
 * @author Naoto Abe
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
            throw new IllegalArgumentException("The collection entered"
                    + "is null");
        }
        for (T element : data) {
            if (element == null) {
                throw new IllegalArgumentException("An element in the "
                        + "collection entered is null");
            }
            add(element);
        }
    }

    @Override
    public void add(T data) {
        if (data == null) {
            throw new IllegalArgumentException("The data to cannot be null");
        }
        if (root == null) {
            root = new AVLNode<T>(data);
            size++;
        } else {
            add(root, data);
        }
    }

    @Override
    public T remove(T data) {
        T d = get(data);
        if (root.getData().equals(data)) {
            if (root.getHeight() == 0) {
                root = null;
                size--;
                return d;
            } else if (root.getLeft() != null && root.getRight() != null) {
                AVLNode<T> tem = root;
                tem = tem.getLeft();
                while (tem.getRight() != null) {
                    tem = tem.getRight();
                }
                root.setData(tem.getData());
                root.setLeft(remove(root.getLeft(), tem.getData()));
            } else if (root.getRight() == null) {
                root = root.getLeft();
                size--;
                return d;
            } else {
                root = root.getRight();
                size--;
                return d;
            }
            int bf = updateTree(root);
            if (Math.abs(bf) >= 2) {
                rotate(bf, root);
            }
        } else {
            remove(root, data);
        }
        size = size - 1;
        return d;
    }

    @Override
    public T get(T data) {
        if (data == null) {
            throw new IllegalArgumentException("The data entered cannot be"
                    + " null");
        }
        if (root == null) {
            throw new java.util.NoSuchElementException("The data you entered "
                    + "was not found");
        }
        return compare(data, root);
    }

    @Override
    public boolean contains(T data) {
        boolean contains = true;
        try {
            get(data);
        } catch (java.util.NoSuchElementException e) {
            contains = false;
        }
        return contains;

    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public List<T> preorder() {
        List<T> preorderList = new LinkedList<T>();
        if (root == null) {
            return preorderList;
        }
        return preOrderHelper(root, preorderList);
    }

    @Override
    public List<T> postorder() {
        List<T> postorderList = new LinkedList<T>();
        if (root == null) {
            return postorderList;
        }
        return postOrderHelper(root, postorderList);
    }

    @Override
    public List<T> inorder() {
        List<T> inorderList = new LinkedList<T>();
        if (root == null) {
            return inorderList;
        }
        return inOrderHelper(root, inorderList);
    }

    @Override
    public List<T> levelorder() {
        List<T> levelOrderList = new ArrayList<T>();
        if (root == null) {
            return levelOrderList;
        }
        Queue<AVLNode<T>> levelOrderQueue = new LinkedList<>();
        levelOrderQueue.add(root);
        while (!levelOrderQueue.isEmpty()) {
            AVLNode<T> tempNode = levelOrderQueue.remove();
            levelOrderList.add(tempNode.getData());
            if (tempNode.getLeft() != null) {
                levelOrderQueue.add(tempNode.getLeft());
            }
            if (tempNode.getRight() != null) {
                levelOrderQueue.add(tempNode.getRight());
            }
        }
        return levelOrderList;
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

    /**
     * private helper method for the public add method. The method traverses
     * down the tree and finds the appropriate location for the node to be
     * adde. Runs in O(log n)
     * @param node the that you want to add
     * @param data the data that you want inside the node
     * @return if the add method was successful, returns the node that was
     * successfully added
     */
    private AVLNode<T> add(AVLNode<T> node, T data) {
        if (node == null) {
            size++;
            return new AVLNode<T>(data);
        }
        if (node.getData().compareTo(data) < 0) {
            node.setRight(add(node.getRight(), data));
        } else if (node.getData().compareTo(data) > 0) {
            node.setLeft(add(node.getLeft(), data));
        } else {
            return node;
        }

        int balanceFactor = updateTree(node);
        if (Math.abs(balanceFactor) >= 2) {
            rotate(balanceFactor, node);
        }
        return node;
    }

    /**
     * private recursive helper method for the public remove method. Uses
     * CompareTo method to compare the current node that is being examined
     * with the data that you want to remove. Complexity is O(Log n)
     * @param node a node that is to be removed
     * @param data the data the you want to remove from the AVL tree
     * @return if the node with the data was found and deleted, returns the
     * data that was removed
     */
    private AVLNode<T> remove(AVLNode<T> node, T data) {
        if (node == null) {
            throw new java.util.NoSuchElementException("There is no such data");
        }
        if (node.getData().compareTo(data) < 0) {
            node.setRight(remove(node.getRight(), data));
        } else if (node.getData().compareTo(data) > 0) {
            node.setLeft(remove(node.getLeft(), data));
        } else {
            if (node.getLeft() == null && node.getRight() == null) {
                return null;
            }
            if (node.getRight() == null) {
                return node.getLeft();
            }
            if (node.getLeft() == null) {
                return node.getRight();
            } else {
                AVLNode<T> temp = node;
                temp = temp.getLeft();
                while (temp.getRight() != null) {
                    temp = temp.getRight();
                }
                node.setData(temp.getData());
                node.setLeft(remove(node.getLeft(), temp.getData()));
            }
        }
        int balanceFactor = updateTree(node);
        if (Math.abs(balanceFactor) >= 2) {
            rotate(balanceFactor, node);
        }
        return node;
    }

    /**
     * a private method that handles the rotation of the tree when needed.
     * Rotation should run approximately in O(1).
     * @param balanceFactor balance factor of the node
     * @param node node to be examined
     */
    private void rotate(int balanceFactor, AVLNode<T> node) {
        AVLNode<T> original = node;
        if (balanceFactor == 2) {
            AVLNode<T> leftChild = node.getLeft();
            int leftChildBalanceFactor = leftChild.getBalanceFactor();
            if (leftChildBalanceFactor == 1 || leftChildBalanceFactor == 0) {
                //Right Rotation
                T data = node.getData();
                node.setData(leftChild.getData());
                leftChild.setData(data);
                AVLNode<T> rightNode = node.getRight();
                node.setRight(leftChild);
                node.setLeft(leftChild.getLeft());
                leftChild.setLeft(leftChild.getRight());
                leftChild.setRight(rightNode);

                updateTree(original.getRight());
                updateTree(original.getLeft());
                updateTree(original);
            } else if (leftChildBalanceFactor == -1) {
                //LR Rotation
                T midData = node.getData();
                AVLNode<T> hidari = node.getLeft();
                AVLNode<T> migi = node.getLeft().getRight();
                node.setData(migi.getData());
                migi.setData(midData);
                AVLNode temp = node.getRight();
                node.setRight(migi);
                hidari.setRight(migi.getLeft());
                migi.setLeft(migi.getRight());
                migi.setRight(temp);

                updateTree(original.getRight());
                updateTree(original.getLeft());
                updateTree(original);

            }
        } else if (balanceFactor == -2) {
            AVLNode<T> rightChild = node.getRight();
            int rightChildBalanceFactor = node.getRight().getBalanceFactor();
            if (rightChildBalanceFactor == -1 || rightChildBalanceFactor == 0) {
                //Left Rotation
                T data = node.getData();
                node.setData(rightChild.getData());
                rightChild.setData(data);
                AVLNode<T> leftNode = node.getLeft();
                node.setLeft(rightChild);
                node.setRight(rightChild.getRight());
                rightChild.setRight(rightChild.getLeft());
                rightChild.setLeft(leftNode);

                updateTree(original.getLeft());
                updateTree(original.getRight());
                updateTree(original);

            } else if (rightChildBalanceFactor == 1) {
                T midData = node.getData();
                AVLNode<T> migi = node.getRight();
                AVLNode<T> hidari = node.getRight().getLeft();

                node.setData(hidari.getData());
                hidari.setData(midData);
                AVLNode temp = node.getLeft();
                node.setLeft(hidari);
                migi.setLeft(hidari.getRight());
                hidari.setRight(hidari.getLeft());
                hidari.setLeft(temp);

                updateTree(original.getLeft());
                updateTree(original.getRight());
                updateTree(original);
            }
        }
    }

    /**
     *  a method that visits a node and calculates height  and balance factor
     * @param node node that is to be examined.
     * @return returns a height and balance factor after rotation
     */
    private int updateTree(AVLNode<T> node) {
        int leftH;
        int rightH;
        if (node.getLeft() == null) {
            leftH = -1;
        } else {
            leftH = node.getLeft().getHeight();
        }
        if (node.getRight() == null) {
            rightH = -1;
        } else {
            rightH = node.getRight().getHeight();
        }
        int height = Math.max(leftH, rightH) + 1;
        int balanceFactor = leftH - rightH;
        node.setHeight(height);
        node.setBalanceFactor(balanceFactor);
        return balanceFactor;
    }

    /**
     *  a private implementation of compare method used in the public get
     *  method. Used to traverse down a tree to find the data.
     * @param data data you are trying to get
     * @param node the method starts from the root, and compares the data that
     *             you want to get and traverses down as necessary
     * @return returns the data if the data was found
     */
    private T compare(T data, AVLNode<T> node) {
        if (root.getData().equals(data)) {
            return root.getData();
        }
        if (node == null) {
            throw new java.util.NoSuchElementException("Data is not found.");
        }
        if (node.getData().equals(data)) {
            return node.getData();
        } else {
            if (node.getData().compareTo(data) > 0) {
                return (compare(data, node.getLeft()));
            } else if (node.getData().compareTo(data) < 0) {
                return (compare(data, node.getRight()));
            }
        }
        return null;
    }

    /**
     * a private helper method that creates a list of data in the tree
     * in a pre order. Complexity is o(n)
     * @param node a node to start the search, starts at root.
     * @param list a list that's inserted in pre order of tree
     * @return returns a list of the pre ordered tree
     *
     */
    private List<T> preOrderHelper(AVLNode node, List<T> list) {
        if (node == null) {
            return null;
        } else {
            list.add((T) node.getData());
            preOrderHelper(node.getLeft(), list);
            preOrderHelper(node.getRight(), list);
        }
        return list;
    }

    /**
     * a private helper method that creates a list of data in the tree
     * in a post order. Complexity is o(n)
     * @param node a node to start the search, starts at root.
     * @param list a list that's postOrder of tree
     * @return returns a list of the postOrdered tree
     *
     */
    private List<T> postOrderHelper(AVLNode node, List<T> list) {
        if (node == null) {
            return null;
        } else {
            postOrderHelper(node.getLeft(), list);
            postOrderHelper(node.getRight(), list);
            list.add((T) node.getData());
        }
        return list;
    }

    /**
     * a private helper method that creates a list of data in the tree
     * in an inOrder. Complexity is o(n)
     * @param node a node to start the search, starts at root.
     * @param list a list that's inorder of tree
     * @return returns a list of the inOrdered tree
     *
     */
    private List<T> inOrderHelper(AVLNode node, List<T> list) {
        if (node == null) {
            return null;
        } else {
            inOrderHelper(node.getLeft(), list);
            list.add((T) node.getData());
            inOrderHelper(node.getRight(), list);
        }
        return list;
    }
}
