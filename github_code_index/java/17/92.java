package com.kimmin.datastructure.tree.binary;

import java.util.Comparator;

/**
 * Created by kimmin on 15/11/2016.
 */
public class SimpleRedBlackTree<T> {

    //1）每个结点要么是红的，要么是黑的。
    //2）根结点是黑的。
    //3）每个叶结点，即空结点（NIL）是黑的。
    //4）如果一个结点是红的，那么它的俩个儿子都是黑的。
    //5）对每个结点，从该结点到其子孙结点的所有路径上包含相同数目的黑结点。

    // According to : https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
    private enum RedBlackTreeNodeColor {
        RED(false), BLACK(true);
        private boolean color;
        RedBlackTreeNodeColor(boolean color){
            this.color = color;
        }
        public static RedBlackTreeNodeColor getColor(RedBlackTreeNode node){
            if(node == null) return BLACK;
            else return node.color;
        }
    }

    public static class RedBlackTreeNode<T> extends BinaryTreeNode<T> {


        public RedBlackTreeNodeColor color;
        public RedBlackTreeNode(T val, RedBlackTreeNodeColor color){
            super(val);
            this.color = color;
        }
        public RedBlackTreeNode(T val, RedBlackTreeNodeColor color, RedBlackTreeNode<T> parent){
            this(val, color);
            this.parent = parent;
        }
        public RedBlackTreeNode(T val, RedBlackTreeNodeColor color,
                                RedBlackTreeNode<T> parent, RedBlackTreeNode<T> leftChild, RedBlackTreeNode<T> rightChild){
            this(val, color, parent);
            this.leftChild = leftChild;
            this.rightChild = rightChild;
        }

        @Override
        public RedBlackTreeNode<T> getRootNode(){
            return (RedBlackTreeNode<T>) super.getRootNode();
        }

        public RedBlackTreeNode<T> getLeftChild(){
            return (RedBlackTreeNode<T>) this.leftChild;
        }

        public RedBlackTreeNode<T> getRightChild(){
            return (RedBlackTreeNode<T>) this.rightChild;
        }

        public RedBlackTreeNode<T> getParent(){
            return (RedBlackTreeNode<T>) this.parent;
        }

        public RedBlackTreeNode<T> getSibling(){
            if(this.parent != null){
                if(this.getParent().getLeftChild() == this){
                    return this.getParent().getRightChild();
                }else{
                    return this.getParent().getLeftChild();
                }
            }else{
                System.err.println("ERROR: Accessing sibling from a root node!");
                return null;
            }
        }

        private RedBlackTreeNode<T> getSuccessorNode(){
            // Maximum element from left-subtree
            if(this.leftChild == null){
                //System.err.println("ERROR: Getting successor from a leaf node!");
                return null;
            }
            RedBlackTreeNode<T> p = this.getLeftChild().getRightChild();
            if(p == null){
                return this.getLeftChild();
            }else{
                while(p.getRightChild() != null){
                    p = p.getRightChild();
                }
                return p;
            }
        }


    }

    /* Fields */
    private RedBlackTreeNode<T> root = null;
    private int size = 0;
    private Comparator<T> comparator = null;

    public SimpleRedBlackTree(Comparator<T> comparator){
        this.comparator = comparator;
    }

    public RedBlackTreeNode<T> find(T val){
        RedBlackTreeNode<T> p = root;
        while(p != null){
            if(comparator.compare(p.val, val) == 0){
                return p;
            }else if(comparator.compare(val, p.val) < 0){
                p = p.getLeftChild();
            }else{
                p = p.getRightChild();
            }
        }
        return null;
    }


    public void insert(T val){
        // Insert a red node and do the fix-up
        RedBlackTreeNode<T> newNode = new RedBlackTreeNode<T>(val, RedBlackTreeNodeColor.RED);
        if(root == null || size == 0){
            this.root = newNode;
        }else{
            RedBlackTreeNode<T> y = null;
            RedBlackTreeNode<T> x = this.root;
            while(x != null){
                y = x;
                if(comparator.compare(newNode.val, x.val) == 0){
                    System.err.println("ERROR: inserting a duplicated element!");
                    return;
                }
                else if(comparator.compare(newNode.val, x.val) < 0){
                    x = x.getLeftChild();
                }else{
                    x = x.getRightChild();
                }
            }
            newNode.parent = y;
            if(comparator.compare(newNode.val, y.val) < 0){
                y.leftChild = newNode;
            }else{
                y.rightChild = newNode;
            }
        }
        size++;
        insertFixUp(newNode);
        root = root.getRootNode();
    }


    public void delete(T val){
        // Do deletion and do the fix up
        RedBlackTreeNode<T> toDelete = find(val);
        if(toDelete == null){
            System.err.println("ERROR: Deleting an non-existent element!");
            return;
        }
        RedBlackTreeNode<T> successor = toDelete.getSuccessorNode();
        if(successor == null){
            // Do directly deletion
            if(toDelete.getParent() == null){
                this.root = toDelete.getRightChild();
                if(this.root != null) this.root.parent = null;
            }else{
                if(toDelete.getParent().getLeftChild() == toDelete){
                    toDelete.getParent().leftChild = toDelete.getRightChild();
                    if(toDelete.getParent().getLeftChild() != null) toDelete.getParent().getLeftChild().parent = toDelete.getParent();
                    if(RedBlackTreeNodeColor.getColor(toDelete) == RedBlackTreeNodeColor.BLACK) deleteFixUp(toDelete.getRightChild(), toDelete.getParent());
                }else{
                    toDelete.getParent().rightChild = toDelete.getRightChild();
                    if(toDelete.getParent().getRightChild() != null) toDelete.getParent().getRightChild().parent = toDelete.getParent();
                    if(RedBlackTreeNodeColor.getColor(toDelete) == RedBlackTreeNodeColor.BLACK) deleteFixUp(toDelete.getRightChild(), toDelete.getParent());
                }
            }
        }else{
            // Adjust using successor
            RedBlackTreeNode<T> n = successor.getLeftChild();
            toDelete.val = successor.val;
            if(n != null) n.parent = successor.getParent();
            if(successor.getParent().getLeftChild() == successor){
                successor.getParent().leftChild = n;
            }else{
                successor.getParent().rightChild = n;
            }
            if(RedBlackTreeNodeColor.getColor(successor) == RedBlackTreeNodeColor.BLACK) deleteFixUp(n, successor.getParent());
        }
        size--;
        if(this.root != null) this.root = this.root.getRootNode();
    }


    private void deleteFixUp(RedBlackTreeNode<T> deletedNode, RedBlackTreeNode<T> p){
        while(deletedNode != this.root && RedBlackTreeNodeColor.getColor(deletedNode) == RedBlackTreeNodeColor.BLACK){
            if(p.getLeftChild() == deletedNode){
                RedBlackTreeNode<T> w = p.getRightChild();
                if(RedBlackTreeNodeColor.getColor(w) == RedBlackTreeNodeColor.RED){
                    w.color = RedBlackTreeNodeColor.BLACK;
                    p.color = RedBlackTreeNodeColor.RED;
                    if(p.canLeftRotate()) p.leftRotate();
                    w = p.getRightChild();
                }
                if(RedBlackTreeNodeColor.getColor(w.getLeftChild()) == RedBlackTreeNodeColor.BLACK &&
                        RedBlackTreeNodeColor.getColor(w.getRightChild()) == RedBlackTreeNodeColor.BLACK){
                    w.color = RedBlackTreeNodeColor.RED;
                    deletedNode = p;
                    w = deletedNode.getSibling();
                    p = deletedNode.getParent();
                }else if(RedBlackTreeNodeColor.getColor(w.getRightChild()) == RedBlackTreeNodeColor.BLACK) {
                    w.getLeftChild().color = RedBlackTreeNodeColor.BLACK;
                    w.color = RedBlackTreeNodeColor.RED;
                    if (w.canRightRotate()) w.rightRotate();
                    w = p.getRightChild();
                }
                w.color = p.color;
                p.color = RedBlackTreeNodeColor.BLACK;
                w.getRightChild().color = RedBlackTreeNodeColor.BLACK;
                if(p.canLeftRotate()) p.leftRotate();
                this.root = p.getRootNode();
                deletedNode = p.getRootNode();
                p = deletedNode.getParent();
            }else{
                RedBlackTreeNode<T> w = p.getLeftChild();
                if(RedBlackTreeNodeColor.getColor(w) == RedBlackTreeNodeColor.RED){
                    w.color = RedBlackTreeNodeColor.BLACK;
                    p.color = RedBlackTreeNodeColor.RED;
                    if(p.canRightRotate()) p.rightRotate();
                    w = p.getLeftChild();
                }
                if(RedBlackTreeNodeColor.getColor(w.getLeftChild()) == RedBlackTreeNodeColor.BLACK &&
                        RedBlackTreeNodeColor.getColor(w.getRightChild()) == RedBlackTreeNodeColor.BLACK){
                    w.color = RedBlackTreeNodeColor.RED;
                    deletedNode = p;
                    w = deletedNode.getSibling();
                    p = deletedNode.getParent();
                }else if(RedBlackTreeNodeColor.getColor(w.getLeftChild()) == RedBlackTreeNodeColor.BLACK){
                    w.getRightChild().color = RedBlackTreeNodeColor.BLACK;
                    w.color = RedBlackTreeNodeColor.RED;
                    if(w.canLeftRotate()) w.leftRotate();
                    w = p.getLeftChild();
                }
                w.color = p.color;
                p.color = RedBlackTreeNodeColor.BLACK;
                if(RedBlackTreeNodeColor.getColor(w.getRightChild()) == RedBlackTreeNodeColor.RED) w.getRightChild().color = RedBlackTreeNodeColor.BLACK;
                if(p.canRightRotate()) p.rightRotate();
                this.root = p.getRootNode();
                deletedNode = p.getRootNode();
                p = deletedNode.getParent();
            }
            deletedNode.color = RedBlackTreeNodeColor.BLACK;
        }
    }

    private void insertFixUp(RedBlackTreeNode<T> insertedNode){
        RedBlackTreeNode<T> x = insertedNode;
        if(insertedNode.getParent() == null){
            // This node become a root node
            insertedNode.color = RedBlackTreeNodeColor.BLACK;
        }else if(insertedNode.getParent().getParent() == null){
            // Just do nothing is okay
        }else if(insertedNode.getParent().color == RedBlackTreeNodeColor.BLACK){
            // Just do nothing is still okay
        }else{
            // The father node is RED & it does have a grandfather
            RedBlackTreeNode<T> f = x.getParent();
            RedBlackTreeNode<T> g = x.getParent().getParent();
            if(f.getLeftChild() == insertedNode){
                if(g.getLeftChild() == f){
                    RedBlackTreeNode<T> u = g.getRightChild();
                    if(u != null && u.color == RedBlackTreeNodeColor.RED){
                        u.color = RedBlackTreeNodeColor.BLACK;
                        f.color = RedBlackTreeNodeColor.BLACK;
                        g.color = RedBlackTreeNodeColor.RED;
                        insertFixUp(g);
                    }else{
                        g.color = RedBlackTreeNodeColor.RED;
                        f.color = RedBlackTreeNodeColor.BLACK;
                        if(g.canRightRotate()) g.rightRotate();
                        else System.err.println("Tree rotation error!");
                    }
                }else{
                    RedBlackTreeNode<T> u = g.getLeftChild();
                    if(u != null && u.color == RedBlackTreeNodeColor.RED){
                        u.color = RedBlackTreeNodeColor.BLACK;
                        f.color = RedBlackTreeNodeColor.BLACK;
                        g.color = RedBlackTreeNodeColor.RED;
                        insertFixUp(g);
                    }else{
                        if(f.canRightRotate()) f.rightRotate();
                        else System.err.println("Tree rotation error!");
                    }
                }
            }else{
                if(g.getLeftChild() == f){
                    RedBlackTreeNode<T> u = g.getRightChild();
                    if(u != null && u.color == RedBlackTreeNodeColor.RED){
                        u.color = RedBlackTreeNodeColor.BLACK;
                        f.color = RedBlackTreeNodeColor.BLACK;
                        g.color = RedBlackTreeNodeColor.RED;
                        insertFixUp(g);
                    }else{
                        if(f.canLeftRotate()) f.leftRotate();
                        else System.err.println("Tree rotation error!");
                    }
                }else{
                    RedBlackTreeNode<T> u = g.getLeftChild();
                    if(u != null && u.color == RedBlackTreeNodeColor.RED){
                        u.color = RedBlackTreeNodeColor.BLACK;
                        f.color = RedBlackTreeNodeColor.BLACK;
                        g.color = RedBlackTreeNodeColor.RED;
                        insertFixUp(g);
                    }else{
                        g.color = RedBlackTreeNodeColor.RED;
                        f.color = RedBlackTreeNodeColor.BLACK;
                        if(g.canLeftRotate()) g.leftRotate();
                        else System.err.println("Tree rotation error!");
                    }
                }
            }
        }
    }


    public RedBlackTreeNode<T> getRootNode(){
        return root;
    }



}
