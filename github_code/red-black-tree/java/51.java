package lab;

import java.util.Deque;
import java.util.LinkedList;
import java.util.function.Consumer;

public class RedBlackTree<T extends Comparable<T>> {
    private static final boolean RED =  true;
    private static final boolean BLACK =  false;

    private Node root;
    private int nodesCount;

    public RedBlackTree() {
    }

    private RedBlackTree(Node root) {
        this.preOrderCopy(root);
    }

    private void preOrderCopy(Node node) {
        if (node == null) {
            return;
        }

        this.insert(node.getValue());
        this.preOrderCopy(node.getLeft());
        this.preOrderCopy(node.getRight());
    }

    private boolean isRed(Node node) {
        return node != null && node.getColor() == RED;
    }

    public Node getRoot() {
        return this.root;
    }

    public int getNodesCount() {
        return this.nodesCount;
    }

    public void insert(T value) {
        this.nodesCount++;
        this.root = this.insert(value, this.root);
        this.root.setColor(BLACK);
    }

    private Node insert(T value, Node node){
        if(node == null){
            node = new Node(value);
        }
        else if(value.compareTo(node.getValue())<0){
            node.setLeft(this.insert(value, node.getLeft()));
        }
        else if(value.compareTo(node.getValue())>0){
            node.setRight(this.insert(value, node.getRight()));
        }

        if(this.isRed(node.getRight()) && !this.isRed(node.getLeft())){
            node = this.rotateLeft(node);
        }
        if(this.isRed(node.getLeft()) && this.isRed(node.getLeft().getLeft())){
            node = this.rotateRight(node);
        }
        if(this.isRed(node.getLeft()) && this.isRed(node.getRight())){
            this.flipColors(node);
        }

        node.childrenCount = 1 + this.count(node.getLeft()) + this.count(node.getRight());
        return node;
    }

    private Node rotateLeft(Node node){
        Node temp = node.getRight();
        node.setRight(temp.getLeft());
        temp.setLeft(node);
        temp.childrenCount = node.childrenCount;
        temp.setColor(node.getColor());
        node.setColor(RED);

        node.childrenCount = 1 + this.count(node.getLeft()) + this.count(node.getRight());

        return temp;
    }

    private Node rotateRight(Node node){
        Node temp = node.getLeft();
        node.setLeft(temp.getRight());
        temp.setRight(node);
        temp.childrenCount = node.childrenCount;
        temp.setColor(node.getColor());
        node.setColor(RED);

        node.childrenCount = 1 + this.count(node.getLeft()) + this.count(node.getRight());

        return temp;
    }

    private void flipColors(Node node){
        node.setColor(RED);
        if (node.getLeft() != null){
            node.getLeft().setColor(BLACK);
        }
        if (node.getRight() != null){
            node.getRight().setColor(BLACK);
        }
    }

    private int count(Node node){
        return node == null ? 0 : node.childrenCount;
    }

    public boolean contains(T value) {
        Node current = this.root;
        while (current != null) {
            if (value.compareTo(current.getValue()) < 0) {
                current = current.getLeft();
            } else if (value.compareTo(current.getValue()) > 0) {
                current = current.getRight();
            } else {
                break;
            }
        }

        return current != null;
    }

    public RedBlackTree<T> search(T item) {
        Node current = this.root;
        while (current != null) {
            if (item.compareTo(current.getValue()) < 0) {
                current = current.getLeft();
            } else if (item.compareTo(current.getValue()) > 0) {
                current = current.getRight();
            } else {
                break;
            }
        }

        return new RedBlackTree<>(current);
    }

    public void eachInOrder(Consumer<T> consumer) {
        this.eachInOrder(this.root, consumer);
    }

    private void eachInOrder(Node node, Consumer<T> consumer) {
        if (node == null) {
            return;
        }

        this.eachInOrder(node.getLeft(), consumer);
        consumer.accept(node.getValue());
        this.eachInOrder(node.getRight(), consumer);
    }

    public Iterable<T> range(T from, T to) {
        Deque<T> queue = new LinkedList<>();
        this.range(this.root, queue, from, to);
        return queue;
    }

    private void range(Node node, Deque<T> queue, T startRange, T endRange) {
        if (node == null) {
            return;
        }

        int compareStart = startRange.compareTo(node.getValue());
        int compareEnd = endRange.compareTo(node.getValue());
        if (compareStart < 0) {
            this.range(node.getLeft(), queue, startRange, endRange);
        }
        if (compareStart <= 0 && compareEnd >= 0) {
            queue.addLast(node.getValue());
        }
        if (compareEnd > 0) {
            this.range(node.getRight(), queue, startRange, endRange);
        }
    }

    private T minValue(Node root) {
        T minv = root.getValue();
        while (root.getLeft() != null) {
            minv = root.getLeft().getValue();
            root = root.getLeft();
        }

        return minv;
    }

    public void deleteMin() {
        if (this.root == null) {
            throw new IllegalArgumentException("Tree is empty!");
        }

        Node min = this.root;
        Node parent = null;

        while (min.getLeft() != null) {
            parent = min;
            parent.childrenCount--;
            min = min.getLeft();
        }

        if (parent == null) {
            this.root = this.root.getRight();
        } else {
            parent.setLeft(min.getRight());
        }

        this.nodesCount--;
    }

    public void deleteMax() {
        if (this.root == null) {
            throw new IllegalArgumentException("Tree is empty!");
        }

        Node max = this.root;
        Node parent = null;

        while (max.getRight() != null) {
            parent = max;
            max = max.getRight();
        }

        if (parent == null) {
            this.root = this.root.getLeft();
        } else {
            parent.setRight(max.getLeft());
        }
    }

    public T ceil(T element) {
        return this.select(this.rank(element) + 1);
    }

    public T floor(T element) {
        return this.select(this.rank(element) - 1);
    }

    public void delete(T key) {
        this.root = deleteRecursive(this.root, key);
    }

    private Node deleteRecursive(Node root, T key) {
        if (root == null) {
            return root;
        }

        if (key.compareTo(root.getValue()) < 0) {
            root.setLeft(deleteRecursive(root.getLeft(), key));
        }
        else if (key.compareTo(root.getValue()) > 0) {
            root.setRight(deleteRecursive(root.getRight(), key));
        } else {
            if (root.getLeft() == null) {
                return root.getRight();
            } else if (root.getRight() == null) {
                return root.getLeft();
            }

            root.setValue(minValue(root.getRight()));

            root.setRight(deleteRecursive(root.getRight(), root.getValue()));
        }

        return root;
    }

    public int rank(T element) {
        return this.rank(element, this.root);
    }

    private int rank(T element, Node node) {
        if (node == null) {
            return 0;
        }

        int compare = element.compareTo(node.getValue());

        if (compare < 0) {
            return this.rank(element, node.getLeft());
        }

        if (compare > 0) {
            return 1 + this.size(node.getLeft()) + this.rank(element, node.getRight());
        }

        return this.size(node.getLeft());
    }

    public T select(int rank) {
        Node node = this.select(rank, this.root);
        if (node == null) {
            throw new IllegalArgumentException("ERROR");
        }

        return node.getValue();
    }

    private Node select(int rank, Node node) {
        if (node == null) {
            return null;
        }

        int leftCount = this.size(node.getLeft());
        if (leftCount == rank) {
            return node;
        }

        if (leftCount > rank) {
            return this.select(rank, node.getLeft());
        } else {
            return this.select(rank - (leftCount + 1), node.getRight());
        }
    }

    private int size(Node node) {
        if (node == null) {
            return 0;
        }

        return node.childrenCount;
    }

    class Node {
        private T value;
        private Node left;
        private Node right;
        private boolean color;

        private int childrenCount;

        public Node(T value) {
            this.value = value;
            this.childrenCount = 1;
            this.color = RED;
        }

        public boolean getColor() {
            return color;
        }

        public void setColor(boolean color) {
            this.color = color;
        }

        public T getValue() {
            return this.value;
        }

        public void setValue(T value) {
            this.value = value;
        }

        public Node getLeft() {
            return this.left;
        }

        public void setLeft(Node left) {
            this.left = left;
        }

        public Node getRight() {
            return this.right;
        }

        public void setRight(Node right) {
            this.right = right;
        }

        @Override
        public String toString() {
            return this.value + "";
        }
    }
}

//    public T ceil(T element) {
//        return ceil(this.root, element);
//    }
//
//    private T ceil(Node node, T input) {
//        if (node == null) {
//            return null;
//        }
//
//        if (node.getValue() == input) {
//            return node.getValue();
//        }
//
//        if (node.getValue().compareTo(input) < 0) {
//            return ceil(node.getRight(), input);
//        }
//
//        T ceil = ceil(node.getLeft(), input);
//        return (ceil != null) ? ceil : node.getValue();
//    }
//
//    public T floor(T element) {
//        return floor(this.root, element);
//    }
//
//    private T floor(Node node, T input) {
//        if (node == null) {
//            return null;
//        }
//
//        if (node.getValue() == input) {
//            return node.getValue();
//        }
//
//        if (node.getValue().compareTo(input) > 0) {
//            return floor(node.getLeft(), input);
//        }
//
//        T floor = floor(node.getRight(), input);
//        return (floor != null) ? floor : node.getValue();
//    }


