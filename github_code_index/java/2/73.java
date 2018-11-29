package com.example.searchtree;

import com.example.tree.BinaryTree;


/**
 * Created by debasishc on 1/11/16.
 */
public class AVLTree<E extends Comparable<E>> extends BinarySearchTree<E>{
    public static class Node<E extends Comparable<E>> extends BinaryTree.Node{
        protected int height = 0;
        public Node(BinaryTree.Node parent,
                    BinaryTree containerTree, E value) {
            super(parent, containerTree, value);
        }
    }

    @Override
    protected BinaryTree.Node<E> newNode(
            BinaryTree.Node<E> parent, BinaryTree<E> containerTree,
            E value) {
        return new Node(parent, containerTree, value);
    }

    @Override
    protected void rotate(BinaryTree.Node<E> node, boolean left) {
        Node<E> n = (Node<E>) node;
        Node<E> child;
        if(left){
            child = (Node<E>) n.getRight();
        }else{
            child = (Node<E>) n.getLeft();
        }
        super.rotate(node, left);
        if(node!=null){
            nullSafeComputeHeight(n);
        }
        if(child!=null){
            nullSafeComputeHeight(child);
        }
    }

    protected void rebalance(Node<E> node){
        if(node==null){
            return;
        }
        nullSafeComputeHeight(node);
        int leftHeight = nullSafeHeight((Node<E>) node.getLeft());
        int rightHeight = nullSafeHeight((Node<E>) node.getRight());
        switch (leftHeight-rightHeight){
            case -1:
            case 0:
            case 1:
                rebalance((Node<E>) node.getParent());
                break;
            case 2:
                int childLeftHeight = nullSafeHeight(
                        (Node<E>) node.getLeft().getLeft());
                int childRightHeight = nullSafeHeight(
                        (Node<E>) node.getLeft().getRight());
                if(childRightHeight > childLeftHeight){
                    rotate(node.getLeft(), true);
                }
                Node<E> oldParent = (Node<E>) node.getParent();
                rotate(node, false);
                rebalance(oldParent);
                break;
            case -2:
                childLeftHeight = nullSafeHeight(
                        (Node<E>) node.getRight().getLeft());
                childRightHeight = nullSafeHeight(
                        (Node<E>) node.getRight().getRight());
                if(childLeftHeight > childRightHeight){
                    rotate(node.getRight(), false);
                }
                oldParent = (Node<E>) node.getParent();
                rotate(node, true);
                rebalance(oldParent);
                break;
        }
    }

    @Override
    public BinaryTree.Node<E> insertValue(E value) {
        Node<E> node = (Node<E>) super.insertValue(value);
        if(node!=null)
            rebalance(node);
        return node;
    }

    @Override
    public BinaryTree.Node<E> deleteValue(E value) {
        Node<E> node = (Node<E>) super.deleteValue(value);
        if(node==null){
            return null;
        }
        Node<E> parentNode = (Node<E>) node.getParent();
        rebalance(parentNode);
        return node;
    }

    private int nullSafeHeight(Node<E> node){
        if(node==null){
            return 0;
        }else{
            return node.height;
        }
    }

    private void nullSafeComputeHeight(Node<E> node){
        Node<E> left = (Node<E>) node.getLeft();
        Node<E> right = (Node<E>) node.getRight();
        int leftHeight = left==null? 0 : left.height;
        int rightHeight = right==null? 0 :right.height;
        node.height =  Math.max(leftHeight, rightHeight)+1;
    }

    protected void testSanity(Node<E> n){
        if(n==null){
            return;
        }else{
            int leftHeight = nullSafeHeight((Node<E>) n.getLeft());
            int rightHeight = nullSafeHeight((Node<E>) n.getRight());
            if(n.height != Math.max(leftHeight, rightHeight)+1){
                throw new IllegalStateException("Height computation don't match");
            }else if(Math.abs(leftHeight-rightHeight)>1){
                throw new IllegalStateException("Unbalanced tree");
            }
            testSanity((Node<E>) n.getLeft());
            testSanity((Node<E>) n.getRight());
        }
    }

    public static void main(String [] args){
        AVLTree<Integer> tree = new AVLTree<>();
        for(int i=0;i<20;i++){
            tree.insertValue(i);
        }
        //tree.displayText();
        tree.insertValue(9);
        //tree.displayText();
        tree.deleteValue(12);
        tree.deleteValue(14);
        tree.displayText();
        //testSanity((Node<Integer>) tree.getRoot());
        for(int i=0;i<2000000;i++){
            tree.insertValue((int)(Math.random()*10000000));
        }
        //tree.testSanity((Node<Integer>) tree.getRoot());
        for(int i=0;i<2000;i++){
            tree.deleteValue((int)(Math.random()*10000000));
        }

        tree.testSanity((Node<Integer>) tree.getRoot());
    }
}
