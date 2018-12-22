package ru.home.pii.hexlet.lesson3;

public class BTree<T extends Comparable<T>> implements IBTree<T> {

    private final T value;
    private IBTree<T> leftNode = null;
    private IBTree<T> rightNode = null;
    private int count = 1;

    public BTree(T value) {
        this.value = value;
    }

    @Override
    public IBTree<T> getLeftNode() {
        return leftNode;
    }

    @Override
    public IBTree<T> getRightNode() {
        return rightNode;
    }

    @Override
    public T getValue() {
        return value;
    }

    @Override
    public int getCount() {
        return count;
    }

    @Override
    public void add(T value) {
        if (value.equals(getValue())) {
            increment();
        } else if (value.compareTo(getValue()) < 0) {
            addValueToLeft(value);
        } else {
            addValueToRight(value);
        }
    }

    private synchronized void increment() {
        int oldCount = getCount();
        int count = getCount();
        count++;
        if (count > 1000)
            count = 0;
        Thread.yield();
        if (getCount() != oldCount)
            System.out.println("!=");
        setCount(count);
    }

    private void setCount(int count) {
        this.count = count;
    }

    private void setLeftNode(IBTree<T> leftNode) {
        this.leftNode = leftNode;
    }

    private void setRightNode(IBTree<T> rightNode) {
        this.rightNode = rightNode;
    }

    private void addValueToLeft(T value) {
        if (getLeftNode() == null)
            setLeftNode(new BTree<>(value));
        else
            getLeftNode().add(value);
    }

    private void addValueToRight(T value) {
        if (getRightNode() == null)
            setRightNode(new BTree<>(value));
        else
            getRightNode().add(value);
    }

}
