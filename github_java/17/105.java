package com.dokyme.alg4.searching.balanced;


import com.dokyme.alg4.searching.st.SymbolTable;

import java.util.LinkedList;
import java.util.List;

/**
 * Created by intellij IDEA.But customed by hand of Dokyme.
 *
 * @author dokym
 * @date 2018/6/20-12:30
 * Description:
 */
public class RedBlackTree<Key extends Comparable<Key>, Value> implements SymbolTable<Key, Value> {

    private static final boolean RED = true;
    private static final boolean BLACK = false;
    private Node root;

    private boolean isRed(Node x) {
        if (x == null) {
            return false;
        }
        return x.color == RED;
    }

    private Node rotateLeft(Node h) {
        Node x = h.right;
        h.right = x.left;
        x.left = h;
        x.color = h.color;
        h.color = RED;
        x.n = h.n;
        h.n = size(h.left) + size(h.right) + 1;
        return x;
    }

    private Node rotateRight(Node h) {
        Node x = h.left;
        h.left = x.right;
        x.right = h;
        x.color = h.color;
        h.color = RED;
        x.n = h.n;
        h.n = size(h.left) + size(h.right) + 1;
        return x;
    }

    private void flipColors(Node h) {
        h.color = RED;
        h.left.color = BLACK;
        h.right.color = BLACK;
    }

    @Override
    public void put(Key key, Value val) {
        root = put(root, key, val);
        root.color = BLACK;
    }

    private Node put(Node h, Key key, Value val) {
        if (h == null) {
            return new Node(key, val, 1, RED);
        }
        int cmp = key.compareTo(h.key);
        if (cmp < 0) {
            h.left = put(h.left, key, val);
        } else if (cmp > 0) {
            h.right = put(h.right, key, val);
        } else {
            h.val = val;
        }

        if (isRed(h.right) && !isRed(h.left)) {
            h = rotateLeft(h);
        }
        if (isRed(h.left) && isRed(h.left.left)) {
            h = rotateRight(h);
        }
        if (isRed(h.left) && isRed(h.right)) {
            flipColors(h);
        }

        //更新以h为根节点的子树的大小
        h.n = size(h.left) + size(h.right) + 1;
        return h;
    }

    @Override
    public Value get(Key key) {
        if (root == null) {
            return null;
        }
        return get(root, key);
    }

    private Value get(Node h, Key key) {
        if (h == null) {
            return null;
        }
        int cmp = key.compareTo(h.key);
        if (cmp < 0) {
            return get(h.left, key);
        } else if (cmp > 0) {
            return get(h.right, key);
        } else {
            return h.val;
        }
    }

    @Override
    public void delete(Key key) {

    }

    @Override
    public boolean contains(Key key) {
        return get(key) == null;
    }

    @Override
    public boolean isEmpty() {
        return root == null;
    }

    @Override
    public int size() {
        return size(root);
    }

    @Override
    public Key min() {
        if (root == null) {
            return null;
        }
        Node x = root;
        while (x.left != null) {
            x = x.left;
        }
        return x.key;
    }

    @Override
    public Key max() {
        if (root == null) {
            return null;
        }
        Node x = root;
        while (x.right != null) {
            x = x.right;
        }
        return x.key;
    }

    @Override
    public Key floor(Key key) {
        Node x = root;
        Key t = null;
        while (x != null) {
            int cmp = x.key.compareTo(key);
            if (cmp < 0) {
                t = x.key;
                x = x.right;
            } else if (cmp > 0) {
                x = x.left;
            } else {
                t = x.key;
                break;
            }
        }
        return t;
    }

    @Override
    public Key ceiling(Key key) {
        Node x = root;
        Key t = null;
        while (x != null) {
            int cmp = x.key.compareTo(key);
            if (cmp > 0) {
                t = x.key;
                x = x.left;
            } else if (cmp < 0) {
                x = x.right;
            } else {
                t = x.key;
                break;
            }
        }
        return t;
    }

    @Override
    public int rank(Key key) {
        int c = 0;
        Node x = root;
        while (x != null) {
            int cmp = key.compareTo(x.key);
            if (cmp < 0) {
                x = x.left;
            } else if (cmp > 0) {
                c++;
                if (x.left != null) {
                    c += x.left.n;
                }
                x = x.right;
            } else {
                if (x.left != null) {
                    c += x.left.n;
                }
                break;
            }
        }
        return c;
    }

    @Override
    public Key select(int n) {
        Node x = root;
        while (x != null) {
            int leftSubSize = 0;
            if (x.left != null) {
                leftSubSize = x.left.n;
            }
            if (n > leftSubSize) {
                n -= leftSubSize + 1;
                x = x.right;
            } else if (n < leftSubSize) {
                x = x.left;
            } else {
                return x.key;
            }
        }
        return null;
    }

    @Override
    public void deleteMin() {

    }

    @Override
    public void deleteMax() {

    }

    @Override
    public int size(Key lo, Key hi) {
        return 0;
    }

    private int size(Node h) {
        if (h == null) {
            return 0;
        }
        return h.n;
    }

    @Override
    public Iterable<Key> keys(Key lo, Key hi) {
        List<Key> list = new LinkedList<>();
        keys(list, root, lo, hi);
        return list;
    }

    private void keys(List<Key> list, Node h, Key lo, Key hi) {
        if (h == null) {
            return;
        }
        int clo = lo.compareTo(h.key);
        int chi = hi.compareTo(h.key);
        if (clo < 0) {
            //如果lo<key，说明h的左子树还存在可能符合要求的节点
            keys(list, h.left, lo, hi);
        }
        if (clo <= 0 && chi >= 0) {
            list.add(h.key);
        }
        if (chi > 0) {
            keys(list, h.right, lo, hi);
        }
    }

    @Override
    public Iterable<Key> keys() {
        return keys(min(), max());
    }

    private class Node {
        Key key;
        Value val;
        Node left, right;
        int n;
        boolean color;

        public Node(Key key, Value val, int n, boolean color) {
            this.key = key;
            this.val = val;
            this.n = n;
            this.color = color;
        }
    }
}
