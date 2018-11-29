package exercise.java.datastructure.b_tree;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

/**
 * Created by hanbing on 2017/3/27.
 */
public class BTree<K extends Comparable<K>> {
    private BNode<K> root;
    private int height;
    private int minDegree = 2;

    public static class BNode<K extends Comparable<K>> {
        private List<K> keys;
        private List<BNode<K>> children;
        private boolean leaf;
        private int size;

        public BNode() {
        }

        public BNode(List<K> keys, List<BNode<K>> children, boolean leaf) {
            this.keys = keys;
            this.children = children;
            this.leaf = leaf;
        }

        public List<K> getKeys() {
            return keys;
        }

        public void setKeys(List<K> keys) {
            this.keys = keys;
        }

        public List<BNode<K>> getChildren() {
            return children;
        }

        public void setChildren(List<BNode<K>> children) {
            this.children = children;
        }

        public boolean isLeaf() {
            return children.size() == 0;
        }

        public void setLeaf(boolean leaf) {
            this.leaf = leaf;
        }

        public int getSize() {
            return keys.size();
        }

        public void setSize(int size) {
            this.size = size;
        }

        public int position(K key) {
            int index = 0;
            for (K k : keys) {
                if (k.compareTo(key) >= 0) {
                    return index;
                }
                index++;
            }
            return index;
        }
    }


    //search key k in B-Tree
    public SearchResult search(BNode<K> current, K k) {
        int i = 0;
        while (i < current.size && k.compareTo(current.keys.get(i)) > 0) {
            i++;
        }
        if (i < current.size && 0 == k.compareTo(current.keys.get(i))) {
            return new SearchResult(i, current);
        }
        if (current.isLeaf()) {
            return null;
        }
        return search(current.getChildren().get(i), k);
    }

    public BNode<K> CreateTree() {
        root = new BNode<K>(new LinkedList<K>(), new LinkedList<BNode<K>>(), true);
        return root;
    }

    public static class SearchResult<K extends Comparable<K>> {
        private int index;
        private BNode node;

        public SearchResult(int index, BNode node) {
            this.index = index;
            this.node = node;
        }
    }


    public void insert(K key) {
        if (2 * minDegree - 1 == root.getSize()) {
            LinkedList<K> newRootKeys = new LinkedList<K>();
            LinkedList<BNode<K>> newRootChildren = new LinkedList<>();
            newRootChildren.add(root);
            root = new BNode<K>(newRootKeys, newRootChildren, false);
            splitNode(root, 0);
            height++;
        }
        insertNotFull(root, key);
    }

    /**
     * 拆分节点
     *
     * @param node  未满的拆分节点的父节点
     * @param index 拆分节点在父节点中的位置
     */
    public void splitNode(BNode<K> node, int index) {
        BNode<K> current = node.getChildren().get(index);
        //待拆分节点的键值数量
        int splitNodeKeysCount = current.getSize();
        //待拆分节点的子节点个数
        int splitNodeChildrenCount = current.getChildren().size();

        LinkedList<K> rightNodeKeys = new LinkedList<K>(current.getKeys().subList(splitNodeKeysCount / 2 + 1, splitNodeKeysCount));

        LinkedList<BNode<K>> rightNodeChildren = current.getChildren().isEmpty() ?
                new LinkedList<>() : new LinkedList<>(current.getChildren().subList((splitNodeChildrenCount + 1) / 2, splitNodeChildrenCount));

        BNode<K> rightNode = new BNode<K>(rightNodeKeys, rightNodeChildren, current.isLeaf());

        LinkedList<K> leftNodeKeys = new LinkedList<K>(current.getKeys().subList(0, splitNodeKeysCount / 2));
        LinkedList<BNode<K>> leftNodeChildren = current.getChildren().isEmpty() ?
                new LinkedList<>() : new LinkedList<>(current.getChildren().subList(0, (splitNodeChildrenCount + 1) / 2));

        BNode<K> leftNode = new BNode<K>(leftNodeKeys, leftNodeChildren, current.isLeaf());

        node.getChildren().set(index, leftNode);

        K mid = current.getKeys().get(splitNodeKeysCount / 2);
        node.getKeys().add(index, mid);
        node.getChildren().add(index + 1, rightNode);
    }


    public void insertNotFull(BNode<K> node, K key) {
        int index = node.getKeys().size() - 1;

        while (index > -1 && key.compareTo(node.getKeys().get(index)) < 0) {
            index--;
        }
        //if the node is a leaf , insert directly
        if (node.isLeaf()) {
            node.getKeys().add(index + 1, key);
            return;
        }

        //if the node is not a leaf, we need to find the leaf of the node first, then find the position
        index++;
        if (2 * minDegree - 1 == node.getChildren().get(index).getSize()) {
            splitNode(node, index);
            if (key.compareTo(node.getKeys().get(index)) > 0) {
                index++;
            }
        }
        insertNotFull(node.getChildren().get(index), key);
    }

    public boolean delete(BNode<K> node, K key) {

        if (node.isLeaf()) {
            return node.getKeys().remove(key);
        }
        int pos = node.position(key);
        //key is not existed in node
        if (pos == node.getSize() || node.getKeys().get(pos).compareTo(key) != 0) {
            BNode<K> childNode = node.getChildren().get(pos);
            //because the num of key must > minDegree - 1, so if childNode.size() < minDegree, we must add the num of key
            if (childNode.getSize() < minDegree) {
                BNode<K> leftSibling = null;
                BNode<K> rightSibling = null;
                if (pos > 0 && (leftSibling = node.getChildren().get(pos - 1)).getSize() > minDegree - 1) {
                    K leftMax = leftSibling.getKeys().remove(leftSibling.getSize() - 1);
                    K temp = node.getKeys().set(pos, leftMax);
                    childNode.getKeys().add(0, temp);
                    if (leftSibling.getChildren() != null) {
                        BNode<K> leftMaxChild = leftSibling.getChildren().remove(leftSibling.getChildren().size() - 1);
                        childNode.getChildren().add(0, leftMaxChild);
                    }
                } else if (pos < childNode.getSize() && (rightSibling = node.getChildren().get(pos + 1)).getSize() > minDegree - 1) {
                    K rightMin = rightSibling.getKeys().remove(0);
                    K temp = node.getKeys().set(pos, rightMin);
                    childNode.getKeys().add(childNode.getSize(), temp);
                    if (rightSibling.getChildren() != null) {
                        BNode<K> rightMinChild = rightSibling.getChildren().remove(0);
                        childNode.getChildren().add(childNode.getChildren().size(), rightMinChild);
                    }
                } else {
                    if (leftSibling != null) {
                        childNode.getKeys().add(0, node.getKeys().get(pos - 1));
                        childNode.getKeys().addAll(0, leftSibling.getKeys());
                        childNode.getChildren().addAll(0, leftSibling.getChildren());
                        node.getKeys().remove(pos - 1);
                        node.getChildren().remove(pos - 1);
                    } else if (rightSibling != null) {
                        childNode.getKeys().add(childNode.getSize() - 1, node.getKeys().get(pos + 1));
                        childNode.getKeys().addAll(childNode.getSize() - 1, rightSibling.getKeys());
                        childNode.getChildren().addAll(childNode.getChildren().size(), rightSibling.getChildren());
                        node.getKeys().remove(pos);
                        node.getChildren().remove(pos + 1);
                    }
                    if (root.getKeys() == null) {
                        height--;
                        root.getChildren().set(0, root.getChildren().get(0).getChildren().get(0));
                    }
                }
            }
                return delete(childNode, key);
            }

            BNode<K> leftChild = node.getChildren().get(pos);
            if (leftChild.getSize() > minDegree - 1) {
                K lefMaxKey = leftChild.getKeys().get(leftChild.getSize() - 1);
                node.getKeys().set(pos, lefMaxKey);
                return delete(leftChild, lefMaxKey);
            }

            BNode<K> rightChild = node.getChildren().get(pos + 1);
            if (rightChild.getSize() > minDegree - 1) {
                K rightMInKey = rightChild.getKeys().get(0);
                node.getKeys().set(pos, rightMInKey);
                return delete(rightChild, rightMInKey);
            }

            leftChild.getKeys().add(node.getKeys().get(pos));
            leftChild.getKeys().addAll(rightChild.getKeys());
            leftChild.getChildren().addAll(rightChild.getChildren());
            node.getKeys().remove(pos);
            node.getChildren().remove(pos + 1);
            return delete(leftChild, key);

    }

    public void print(BNode<K> node) {
        if (node == null)
            return;
        int index = 0;
        for (K k : node.getKeys()) {
            print(node.getChildren().get(index));
            System.out.print(k + " ");
            print(node.getChildren().get(index + 1));
        }
    }

    public void output()
    {
        Queue<BNode> queue = new LinkedList<>();
        queue.offer(root);
        while(!queue.isEmpty())
        {
            BNode node = queue.poll();
            for(int i = 0; i < node.getSize(); ++ i)
                System.out.print(node.getKeys().get(i) + " ");
            System.out.println();
            if(!node.isLeaf())
            {
                for(int i = 0; i <= node.getSize(); ++ i)
                    queue.offer((BNode) node.getChildren().get(i));
            }
        }
    }


    public static void main(String[] args) {
        BTree<Integer> bTree = new BTree<>();
        BNode<Integer> root = bTree.CreateTree();
        for (int i = 0; i < 10; i++) {
            bTree.insert(10 - i);
        }
        //bTree.print(bTree.root);
        bTree.output();

        System.out.println(bTree.height);
    }

}
