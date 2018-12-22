package com.dong.learn.algorithms.btree;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

/**
 * Created by coding-dong on 2017/10/24.
 */
public class BTree<T extends String> {

    private BTreeNode<T> rootNode;

    private int counter = 0;

    public BTreeNode<T> createBTree(String treeStr){
        char nodeData = treeStr.charAt(counter++);

        if('#' == nodeData){
            return null;
        }else {
            BTreeNode<T> node = new BTreeNode<>();
            node.setData((T)String.valueOf(nodeData));

            node.setlChild(createBTree(treeStr));
            node.setrChild(createBTree(treeStr));

            return node;
        }
    }

    public void initRoot(String treeStr){
        rootNode = createBTree(treeStr);
    }

    public void preBTree(BTreeNode rootNode, int level){
        if(rootNode == null){
            return;
        }
        System.out.println("data : " + rootNode.getData() + ", level : " + level);

        preBTree(rootNode.getlChild(), level + 1);

        preBTree(rootNode.getrChild(), level + 1);
    }

    public int depthBTree(BTreeNode rootNode){
        if(rootNode == null){
            return 0;
        }

        int leftDepth = depthBTree(rootNode.getlChild());
        int rightDepth = depthBTree(rootNode.getrChild());

        return 1 + Math.max(leftDepth, rightDepth);
    }

    public void printNodeAtLevel(BTreeNode rootNode, int level){
        if(rootNode == null || level < 1){
            System.out.print("#" + "    ");
            return;
        }


        if(level == 1){
            System.out.print(rootNode.getData() + "     ");
            if(rootNode == this.rootNode){
                System.out.println();
            }
            return;
        }

        printNodeAtLevel(rootNode.getlChild(), level - 1);
        printNodeAtLevel(rootNode.getrChild(), level - 1);

        System.out.println();
    }

    public void levelTraverse(){
        int depth = depthBTree(rootNode);

        for(int i = 1; i <= depth; i++){
            printNodeAtLevel(rootNode, i);
        }
    }

    public int nodeCount(BTreeNode bTreeNode){
        if(bTreeNode == null){
            return 0;
        }

        int leftCount = nodeCount(bTreeNode.getlChild());
        int rightCount = nodeCount(bTreeNode.getrChild());

        return leftCount + rightCount + 1;
    }

    public int leafNodeCount(BTreeNode bTreeNode){
        if(bTreeNode == null){
            return 0;
        }

        if(bTreeNode.getlChild() == null && bTreeNode.getrChild() == null){
            return 1;
        }

        int leftLeafNodeCount = leafNodeCount(bTreeNode.getlChild());
        int rightLeafNodeCount = leafNodeCount(bTreeNode.getrChild());

        return leftLeafNodeCount + rightLeafNodeCount;
    }

    public BTreeNode mirror(BTreeNode bTreeNode){
        if(bTreeNode == null){
            return null;
        }

        BTreeNode leftNode = mirror(bTreeNode.getlChild());
        BTreeNode rightNode = mirror(bTreeNode.getrChild());

        bTreeNode.setlChild(rightNode);
        bTreeNode.setrChild(leftNode);

        return bTreeNode;
    }

    public void levelTraverseNoRecur(){
        Queue<BTreeNode> treeNodeQueue = new LinkedList<>();

        treeNodeQueue.offer(rootNode);

        while (!treeNodeQueue.isEmpty()){
            BTreeNode bTreeNode = treeNodeQueue.poll();
            System.out.print(bTreeNode.getData() + "  ");

            if(bTreeNode.getlChild() != null){
                treeNodeQueue.offer(bTreeNode.getlChild());
            }

            if(bTreeNode.getrChild() != null){
                treeNodeQueue.offer(bTreeNode.getrChild());
            }
        }
    }

    public void preBTreeNoRecur(){
        Stack<BTreeNode> treeNodeStack = new Stack<>();
        BTreeNode popNode = rootNode;
        while (popNode != null || !treeNodeStack.isEmpty()){

            while (popNode != null){
                System.out.print(popNode.getData() + "    ");

                treeNodeStack.push(popNode);

                popNode = popNode.getlChild();

            }

            popNode = treeNodeStack.pop();

            popNode = popNode.getrChild();
        }

        System.out.println();
    }

    public void middleBTreeNoRecur(){
        Stack<BTreeNode> treeNodeStack = new Stack<>();
        BTreeNode popNode = rootNode;

        while (popNode != null || !treeNodeStack.isEmpty()){
            while (popNode != null){
                treeNodeStack.push(popNode);

                popNode = popNode.getlChild();
            }

            popNode = treeNodeStack.pop();

            System.out.print(popNode.getData() + "  ");

            popNode = popNode.getrChild();
        }

        System.out.println();
    }

    public void postBTreeNoRecur(){
        Stack<BTreeNode> treeNodeStack = new Stack<>();
        BTreeNode popNode = rootNode;
        while (true){
            while (popNode != null){
                treeNodeStack.push(popNode);

                popNode = popNode.getlChild();
            }

            while (!treeNodeStack.isEmpty() && treeNodeStack.peek().getrChild() == popNode){
                popNode = treeNodeStack.peek();

                System.out.print(popNode.getData() + "  ");

                treeNodeStack.pop();
            }

            if(treeNodeStack.isEmpty()){
                break;
            }

            popNode = treeNodeStack.peek().getrChild();
        }

        System.out.println();
    }

    public static void main(String[] args){
        String treeStr = "abd##e##c#f##";
        BTree<String> bTree = new BTree<>();
        bTree.initRoot(treeStr);
        bTree.preBTree(bTree.rootNode, 1);

//        System.out.println("btreeDepth : " + bTree.depthBTree(bTree.rootNode));
//
//        bTree.levelTraverse();
//
//        System.out.println("<=====================>");
//        System.out.println("nodeCount : " + bTree.nodeCount(bTree.rootNode));
//
//        System.out.println("<=====================>");
//        System.out.println("leafNodeCount : " + bTree.leafNodeCount(bTree.rootNode));
//
//        System.out.println("<######################################>");
//        bTree.levelTraverseNoRecur();
//
//        System.out.println("<=====================>");
//        bTree.mirror(bTree.rootNode);
//        bTree.levelTraverse();

        System.out.println("<================================>");
        bTree.preBTreeNoRecur();
        System.out.println("<================================>");
        bTree.middleBTreeNoRecur();
        System.out.println("<================================>");
        bTree.postBTreeNoRecur();
        System.out.println("<================================>");
        bTree.levelTraverse();

    }
}
