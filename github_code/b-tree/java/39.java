package com.cwj.binarytree;

/**
 * Created by cwj on 18-3-13.
 * 二叉树的创建，插入，删除，清空，高度计算，节点数计算，父亲节点的查找，遍历
 */
public class BTree {
    private BTreeNode root;

    public BTree(){}

    public BTree(BTreeNode root){
        this.root = root;
    }

    public BTreeNode getRoot() {
        return root;
    }

    public void setRoot(BTreeNode root) {
        this.root = root;
    }

    //左孩子节点插入
    public void insertAsLeftChild(BTreeNode node){
        isEmpty();
        this.root.setLeftChild(node);
    }

    //右孩子节点插入
    public void insertAsRightChild(BTreeNode node){
        isEmpty();
        this.root.setRightChild(node);
    }

    //树是否为空
    private void isEmpty(){
        if (root == null){
            throw new IllegalStateException("Can`t insert to a null tree!");
        }
    }

    //惰性删除,只是标记为空，但是为了避免浪费无用的内存，方便 GC 及时回收，我们还需要遍历这个元素的左右子树，挨个设为空
    public void deleteNode(BTreeNode node){
        isEmpty();
        if (node == null){
            return;
        }
        deleteNode(node.getLeftChild());
        deleteNode(node.getRightChild());
        node = null;
    }

    //二叉树的清空其实就是特殊的删除元素–删除根节点
    public void clear(){
        if (this.root != null){
            deleteNode(this.root);
        }
    }

    //获取二叉树的高度
    public int getTreeHeight(){
        return getHeight(this.root);
    }

    private int getHeight(BTreeNode node){
        //递归出口
        if (node == null){
            return 0;
        }
        int leftChildHeight = getHeight(node.getLeftChild());
        int rightChildHeight = getHeight(node.getRightChild());

        int max = Math.max(leftChildHeight, rightChildHeight);
        return max + 1;
    }

    public int getSize(){
        return getChildSize(this.root);
    }

    //获得二叉树的节点数，需要遍历所有子树，然后加上总和
    private int getChildSize(BTreeNode node){
        if (node == null){
            return 0;
        }

        int leftChildSize = getChildSize(node.getLeftChild());
        int rightChildSize = getChildSize(node.getRightChild());

        return leftChildSize + rightChildSize + 1;
    }

    //由于我们使用左右子树表示的节点，不含有父亲节点引用，因此有时候可能也需要一个方法，返回二叉树中，指定节点的父亲节点。
    //需要从顶向下遍历各个子树，若该子树的根节点的孩子就是目标节点，返回该节点，否则递归遍历它的左右子树：
    public BTreeNode getParent(BTreeNode node){
        if (this.root == null || this.root == node){
            return null;
        }else{
            return getParent(this.root, node);
        }
    }

    //递归出口
    private BTreeNode getParent(BTreeNode subTree, BTreeNode node){
        if (subTree == null){
            return null;
        }

        ////正好这个根节点的左右孩子之一与目标节点一致
        if (subTree.getLeftChild() == node || subTree.getRightChild() == node){
            return subTree;
        }

        //需要遍历这个节点的左右子树
        BTreeNode parent;
        if ((parent = getParent(subTree.getLeftChild(), node)) != null){
            return parent;
        }else {
            return getParent(subTree.getRightChild(), node);
        }
    }

    //打印
    private void operate(BTreeNode node){
        if (node == null){
            return;
        }
        System.out.print(node.getData() + " ");
    }

    //先序遍历
    public void iterateFirstOrder(BTreeNode node){
        if (node == null){
            return;
        }

        operate(node);
        iterateFirstOrder(node.getLeftChild());
        iterateFirstOrder(node.getRightChild());
    }

    //中序
    public void iterateMediumOrder(BTreeNode node){
        if (node == null){
            return;
        }

        iterateMediumOrder(node.getLeftChild());
        operate(node);
        iterateMediumOrder(node.getRightChild());
    }

    //后序
    public void iterateLastOrder(BTreeNode node){
        if (node == null){
            return;
        }

        iterateLastOrder(node.getLeftChild());
        iterateLastOrder(node.getRightChild());
        operate(node);
    }


    public static void main(String[] args) {

        BTreeNode root = new BTreeNode(3, null, null);

        BTree bTree = new BTree(root);
        bTree.isEmpty();
        BTreeNode leftChild = new BTreeNode(4, null, null);
        BTreeNode rightChild = new BTreeNode(5, null, null);
        bTree.insertAsLeftChild(leftChild);
        bTree.insertAsRightChild(rightChild);

        System.out.println(bTree.getTreeHeight());
        System.out.println(bTree.getSize());
        System.out.println(bTree.getParent(leftChild).getData());
        bTree.iterateFirstOrder(root);
        System.out.println("");
        bTree.iterateMediumOrder(root);
        System.out.println("");
        bTree.iterateLastOrder(root);
    }
}
