package ifrn.tads.estruturadedados.tree.b;

import java.util.List;

public class BTree<T extends Comparable<T>> implements BTreeInterface<T> {

    private BTreeNode<T> root;
    private int
            minimumNumberOfChildren,
            maximumNumberOfChildren,
            minimumNumberOfKeys,
            maximumNumberOfKeys;

    public BTree(int order) {
        minimumNumberOfChildren = order;
        maximumNumberOfChildren = (2 * order);
        minimumNumberOfKeys = minimumNumberOfChildren - 1;
        maximumNumberOfKeys = maximumNumberOfChildren - 1;
    }

    public BTreeNode<T> root() {
        return root;
    }

    public BTreeNode<T> root(BTreeNodeInterface<T> node) {
        root = (BTreeNode<T>) node;

        return root;
    }

    public void add(List<T> keys) {
        for (T key : keys) {
            add(key);
        }
    }

    public void add(T key) {
        if (root() == null) {
            root(new BTreeNode<T>(key, maximumNumberOfKeys, maximumNumberOfChildren));
        } else {
            add(root(), key);
        }
    }

    private void add(BTreeNode<T> node, T key) {
        // Performs a binary search on the array of keys
        // to discover the place to insert
        int lo = 0;
        int hi = node.getKeys().size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            if (lessThan(key, node.getKey(mid))) hi = mid - 1;
            else if (greaterThan(key, node.getKey(mid))) lo = mid + 1;

            // found a possible place to insert
            if (hi - lo == 1) {
                if (node.isLeaf()) {
                    // just add the key to the node
                    node.setKey(key);

                    // TODO: try to fix the invalid tree
                } else {
                    // try to add to the child node
                    add(node.getChild(hi), key);
                }

                break;
            }

            // special cases (first and last key)
            else if (lo == hi) {
                if (node.isLeaf()) {
                    // just add the key to the node
                    node.setKey(key);

                    // TODO: try to fix the invalid tree
                } else {
                    if (lessThan(key, node.getKey(lo))) add(node.getFirstChild(), key);
                    else add(node.getLastChild(), key);
                }

                break;
            }
        }
    }

    public BTreeNode<T> find(T key) {
        return find(root(), key);
    }

    public BTreeNode<T> find(BTreeNode<T> node, T key) {
        if (node == null) return null;

        // Performs a binary search on the array of keys
        int lo = 0;
        int hi = node.getKeys().size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            if (lessThan(key, node.getKey(mid))) hi = mid - 1;
            else if (greaterThan(key, node.getKey(mid))) lo = mid + 1;
            else return node;

            // the key is not in the list but is in the range of two keys
            if (hi - lo == 1) {
                if (node.isLeaf()) return null;

                return find(node.getChild(hi), key);
            }

            // special cases (first and last key)
            else if (lo == hi) {
                if (node.isLeaf()) return null;

                return lessThan(key, node.getKey(lo)) ? find(node.getFirstChild(), key) : find(node.getLastChild(), key);
            }
        }

        return null;
    }

    public boolean remove(T key) {
        return false;
    }

    public boolean lessThan(T key, T comparedKey) {
        return key.compareTo(comparedKey) < 0;
    }

    public boolean greaterThan(T key, T comparedKey) {
        return key.compareTo(comparedKey) > 0;
    }
}
