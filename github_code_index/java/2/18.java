package org.learnless.chap04;

import java.util.NoSuchElementException;

/**
 * AVL树
 * Created by learnless on 18.3.2.
 */
public class AvlTree<K extends Comparable<? super K>> {
    class Node {
        K k;
        Node left;
        Node right;
        int height;

        public Node(K k) {
            this(k, null, null);
        }

        public Node(K k, Node left, Node right) {
            this.k = k;
            this.left = left;
            this.right = right;
            this.height = 0;
        }
    }

    //avl控制平衡条件变量
    private static final int  ALLOWED_IMBALANCE = 1;
    private Node root;

    public void insert(K k) {
        root = insert(k, root);
    }

    private Node insert(K k, Node n) {
        if (n == null) {
            return new Node(k);
        }
        int comp = k.compareTo(n.k);
        if (comp < 0) {
            n.left = insert(k, n.left);
        } else if (comp > 0) {
            n.right = insert(k, n.right);
        } else {
            ;
        }
        return balance(n);
    }

    public void remove(K k) {
        check(k);
        root = remove(k, root);
    }

    private Node remove(K k, Node n) {
        if (n == null) {
            return n;
        }
        int comp = k.compareTo(n.k);
        if (comp < 0) {
            n.left = remove(k, n.left);
        } else if (comp > 0) {
            n.right = remove(k, n.right);
        } else {
            if (n.left != null && n.right != null) {
                Node min = findMin(n.right);
                n.k = min.k;
                n.right = remove(n.k, n.right);
            } else {
                n = n.left == null ? n.right : n.left;
            }
        }

        return balance(n);
    }

    private Node balance(Node n) {
        if (n == null) {
            return n;
        }
        if (height(n.left) - height(n.right) > ALLOWED_IMBALANCE) {
            //是否需要双旋转
            if (height(n.left.left) >= height(n.left.right)) {  //否
                n = rotateLeft(n);
            } else {
                n = rotateDoubleLeft(n);
            }
        } else if (height(n.right) - height(n.left) > ALLOWED_IMBALANCE) {
            if (height(n.right.right) >= height(n.right.left)) {
                n = rotateRight(n);
            } else {
                n = rotateDoubleRight(n);
            }
        }

        n.height = reheight(n);
        return n;
    }

    public Node rotateLeft(Node n) {
        Node left = n.left;
        n.left = left.right;
        left.right = n;

        n.height = reheight(n);
        left.height = reheight(left);

        return left;
    }

    public Node rotateRight(Node n) {
        Node right = n.right;
        n.right = right.left;
        right.left = n;

        n.height = reheight(n);
        right.height = reheight(right);

        return right;
    }

    public Node rotateDoubleLeft(Node n) {
        n.left = rotateRight(n.left);
        return rotateLeft(n);
    }

    public Node rotateDoubleRight(Node n) {
        n.right = rotateLeft(n.right);
        return rotateRight(n);
    }

    public Node findMin() {
        check();
        return findMin(root);
    }

    private Node findMin(Node n) {
        if (n == null) {
            return null;
        }
        if (n.left == null) {
            return n;
        }
        return findMin(n.left);
    }

    public boolean contains(K k) {
        check(k);
        return contains(k, root);
    }

    private boolean contains(K k, Node n) {
        if (n == null) {
            return false;
        }
        int comp = k.compareTo(n.k);
        if (comp < 0) {
            return contains(k, n.left);
        } else if (comp > 0) {
            return contains(k, n.right);
        } else {
            return true;
        }
    }

    public int height(Node n) {
        return n == null ? - 1 : n.height;
    }

    public int reheight(Node n) {
        return Math.max(height(n.left), height(n.right)) + 1;
    }

    public void check() {
        if (root == null) {
            throw new NoSuchElementException("tree is empty");
        }
    }

    public void check(K k) {
        if (root == null) {
            throw new NoSuchElementException("tree is empty");
        }
        if (k == null) {
            throw new IllegalArgumentException("element is empty");
        }
    }

    private void run() {
        AvlTree tree = new AvlTree();
        tree.insert(12);
        tree.insert(1);
        tree.insert(32);
        tree.insert(83);
        tree.insert(4);
        tree.insert(2);
        tree.insert(85);
        tree.insert(7);

        tree.remove(12);

        System.out.println();
    }

    public static void main(String[] args) {
        AvlTree tree = new AvlTree();
        tree.run();
    }

}
