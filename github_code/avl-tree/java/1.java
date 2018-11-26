package com.company.tree;

/**
 * Created by jbpark on 2016-12-06.
 */
public class AvlTree<T extends Comparable<T>> implements Tree<T> {

    private Node<T> root;

    @Override
    public void insert(T data) {
        root = insert(root, data);
    }

    private Node<T> insert(Node n, T data) {
        if (n == null) {
            return new Node(data);
        }

        if (n.getData().compareTo(data) == 1) {
            n.setLeftChild(insert(n.getLeftChild(), data));
        } else {
            n.setRightChild(insert(n.getRightChild(), data));
        }

        n.setHeight(Math.max(height(n.getLeftChild()), height(n.getRightChild())) + 1);

        n = settleViolation(n);

        return n;
    }

    @Override
    public boolean remove(T data) {
        remove(root, data);
        return true;
    }

    private Node<T> remove(Node n, T data) {
        if (n == null) {
            return n;
        }
        int result = n.getData().compareTo(data);
        if (result > 0) {
            n.setLeftChild(remove(n.getLeftChild(), data));
        } else if (result < 0) {
            n.setRightChild(remove(n.getRightChild(), data));
        } else {

            if (n.getLeftChild() == null && n.getRightChild() == null) {
                // Removing leaf node
                return null;
            } else if (n.getLeftChild() == null) {
                // Removing node with right child only
                return n.getRightChild();
            } else if (n.getRightChild() == null) {
                // Removing node with left child only
                return n.getLeftChild();
            } else {
                // Removing node with two children
                Node<T> predecessor = getPredecessor(n.getLeftChild());
                n.setData(predecessor.getData());
                n.setLeftChild(remove(n.getLeftChild(), predecessor.getData()));
            }

            n.setHeight(Math.max(height(n.getLeftChild()), height(n.getRightChild())) + 1);

            return settleViolation(n);

        }
        return n;
    }

    private Node<T> getPredecessor(Node<T> n) {
        if (n.getRightChild() == null) {
            return n;
        }
        return getPredecessor(n.getRightChild());
    }

    private Node<T> settleViolation(Node<T> n) {
        int balance = getBalance(n);
        if (balance > 1) {
            if (getBalance(n.getLeftChild()) < 0) {
                n.setLeftChild(leftRotation(n.getLeftChild()));
            }
            return rightRotation(n);
        } else if (balance < -1) {
            if (getBalance(n.getRightChild()) > 0) {
                n.setRightChild(rightRotation(n.getRightChild()));
            }
            return leftRotation(n);
        }
        return n;
    }

    private Node<T> rightRotation(Node n) {
        System.out.println("Rotating to the right...");

        Node tempLeftChild = n.getLeftChild();
        Node t = tempLeftChild.getRightChild();

        tempLeftChild.setRightChild(n);
        n.setLeftChild(t);

        n.setHeight(Math.max(height(n.getLeftChild()), height(n.getRightChild())) + 1);
        tempLeftChild.setHeight(Math.max(height(tempLeftChild.getLeftChild()),
                height(tempLeftChild.getRightChild())) + 1);

        return tempLeftChild;
    }

    private Node<T> leftRotation(Node n) {
        System.out.println("Rotating to the left...");

        Node tempRightChild = n.getRightChild();
        Node t = tempRightChild.getLeftChild();

        tempRightChild.setLeftChild(n);
        n.setRightChild(t);

        n.setHeight(Math.max(height(n.getLeftChild()), height(n.getRightChild())) + 1);
        tempRightChild.setHeight(Math.max(height(tempRightChild.getLeftChild()),
                height(tempRightChild.getRightChild())) + 1);

        return tempRightChild;
    }

    private int height(Node<T> n) {
        if (n == null) {
            return -1;
        }
        return n.getHeight();
    }

    private int getBalance(Node<T> n) {
        if (n == null) {
            return 0;
        }
        return height(n.getLeftChild()) - height(n.getRightChild());
    }

    @Override
    public boolean search(T data) {
        return search(data, root) != null;
    }

    private Node<T> search(T data, Node<T> node) {
        if (node == null) {
            return null;
        }
        int compareResult = node.getData().compareTo(data);
        switch (compareResult) {
            case 0:
                return node;
            case 1:
                return search(data, node.getLeftChild());
            case -1:
                return search(data, node.getRightChild());
            default:
                return null;
        }
    }

    @Override
    public void traversal() {
        if (root == null) return;
        inOrderTraversal(root);
    }

    private void inOrderTraversal(Node n) {
        if (n == null) {
            return;
        }
        inOrderTraversal(n.getLeftChild());
        System.out.println(n);
        inOrderTraversal(n.getRightChild());
    }

    @Override
    public T getMax() {
        return getMax(root);
    }

    private T getMax(Node<T> n) {
        if (n.getRightChild() == null) {
            return n.getData();
        }
        return getMax(n.getRightChild());
    }

    @Override
    public T getMin() {
        return getMin(root);
    }

    private T getMin(Node<T> n) {
        if (n.getRightChild() == null) {
            return n.getData();
        }
        return getMax(n.getLeftChild());
    }

}
