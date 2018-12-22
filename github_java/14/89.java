package org.praveen.treeOperations;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

public class TreeOperations {

    //Operations
    //PreOrder Traversal - Recursive
    //PreOrder Traversal - Iterative
    //InOrder Traversal - Recursive
    //InOrder Traversal - Iterative
    //postOrder Traversal - Recursive
    //postOrder Traversal - Iterative - 2 stacks
    //postOrder Traversal - Iterative - 2 stacks Custom
    //postOrder Traversal - Iterative - 1 stacks  -> //In A loop Check If the current is right of the top of the stack then pop the top of the stack too!!
    //LevelOrder Traversal
    //Maximum in a BTree - Recursive
    //Maximum in BTree - Iterative
    //Searching an Element in BTree - Recursive
    //Searching an Element in BTree - Iterative
    //Insert Element in BTree - Recursive - BST
    //Insert Element in BTree - Iterative
    //Sizeof BTree - Recursive
    //Sizeof BTree - Iterative
    //PreOrder Traversal - Recursive
    //PreOrder Traversal - Special Case Level order 1,2,3,4,5,6,7 (Simple), Order should be 4,5,6,7,2,3,1
    //Height of BTree - Recursive
    //Height of BTree - Iterative
    //Minimum Height of BTree

    public static void preOrderRecursive(BTree bTree) {

        if (bTree != null) {
            System.out.print(bTree.getData() + " -- ");
            preOrderRecursive(bTree.getLeft());
            preOrderRecursive(bTree.getRight());
        }
    }

    //PreOrder Traversal - Iterative
    public static void preOrderIterative(BTree bTree) {

        Stack<BTree> bTreeStack = new Stack<>();
        bTreeStack.push(bTree);

        while (!bTreeStack.isEmpty()) {

            BTree node = bTreeStack.pop();
            System.out.print(node.getData() + " -- ");

            if (node.getRight() != null) {
                bTreeStack.push(node.getRight());
            }
            if (node.getLeft() != null) {
                bTreeStack.push(node.getLeft());
            }
        }
    }

    //InOrder Traversal - Recursive
    public static void inOrderRecursive(BTree bTree) {

        if (bTree != null) {
            inOrderRecursive(bTree.getLeft());
            System.out.print(bTree.getData() + " -- ");
            inOrderRecursive(bTree.getRight());
        }
    }

    //InOrder Traversal - Iterative
    public static void inOrderIterative(BTree bTree) {

        Stack<BTree> bTreeStack = new Stack<>();
        pushCurrentNodeAndAllLeftNodes(bTree, bTreeStack);

        while (!bTreeStack.isEmpty()) {

            BTree node = bTreeStack.pop();
            System.out.print(node.getData() + " -- ");

            if (node.getRight() != null) {
                pushCurrentNodeAndAllLeftNodes(node.getRight(), bTreeStack);
            }
        }
    }

    //postOrder Traversal - Recursive
    public static void postOrderRecursive(BTree bTree) {

        if (bTree != null) {
            postOrderRecursive(bTree.getLeft());
            postOrderRecursive(bTree.getRight());
            System.out.print(bTree.getData() + " -- ");
        }
    }

    //postOrder Traversal - Iterative - 2 stacks
    public static void postOrderIterative2Stacks(BTree bTree) {

        Stack<BTree> stack1 = new Stack<>();
        Stack<BTree> stack2 = new Stack<>();

        stack1.push(bTree);

        while (!stack1.isEmpty()) {

            BTree node = stack1.pop();
            stack2.push(node);

            if (node.getLeft() != null) {
                stack1.push(node.getLeft());
            }
            if (node.getRight() != null) {
                stack1.push(node.getRight());
            }
        }

        while (!stack2.isEmpty()) {
            System.out.print(stack2.pop().getData() + " -- ");
        }
    }

    //postOrder Traversal - Iterative - 2 Stacks Custom
    public static void postOrderIterative2StacksCustom(BTree bTree) {

        Stack<BTree> stack1 = new Stack<>();
        Stack<BTree> stack2 = new Stack<>();

        pushCurrentNodeAndAllLeftNodes(bTree, stack1);

        while (!stack1.isEmpty()) {

            BTree node = stack1.peek();

            //Make sure we are not going in circles
            if (!stack2.isEmpty() && stack2.peek().equals(node)) {
                stack1.pop();
                stack2.pop();
                System.out.print(node.getData() + " -- ");
            } else if (node.getRight() == null) {
                stack1.pop();
                System.out.print(node.getData() + " -- ");
            } else {
                stack2.push(node); //This is to remember that we we have visited the right node,
                pushCurrentNodeAndAllLeftNodes(node.getRight(), stack1);
            }
        }
    }

    //PostOrder Traversal - Iterative - 1 Stack
    public static void postOrderIterative1Stack(BTree bTree) {

        Stack<BTree> bTreeStack = new Stack<>();
        pushCurrentNodeAndAllLeftNodes(bTree, bTreeStack);
        while (!bTreeStack.isEmpty()) {

            BTree current = bTreeStack.peek();

            if (current.getRight() == null) {
                bTreeStack.pop();
                System.out.print(current.getData() + " -- ");

                while (!bTreeStack.isEmpty() && bTreeStack.peek().getRight() != null && bTreeStack.peek().getRight().equals(current)) { //In A loop Check If the current is right of the top of the stack then pop the top of the stack too!!
                    current = bTreeStack.pop();
                    System.out.print(current.getData() + " -- ");
                }
            } else {
                pushCurrentNodeAndAllLeftNodes(current.getRight(), bTreeStack);
            }
        }

    }

    //LevelOrder Traversal
    public static void levelOrderTraversal(BTree bTree) {

        Queue<BTree> bTreeQueue = new LinkedList<>();
        bTreeQueue.offer(bTree);

        while (!bTreeQueue.isEmpty()) {
            BTree node = bTreeQueue.poll();
            System.out.print(node.getData() + " -- ");

            if (node.getLeft() != null) {
                bTreeQueue.offer(node.getLeft());
            }

            if (node.getRight() != null) {
                bTreeQueue.offer(node.getRight());
            }
        }
    }

    //Maximum in a BTree - Recursive
    public static int maximumInBTreeRecursive(BTree bTree) {

        int max = Integer.MIN_VALUE;
        if (bTree != null) {
            int leftMax = maximumInBTreeRecursive(bTree.getLeft());
            int rightMax = maximumInBTreeRecursive(bTree.getRight());

            if (leftMax > max) {
                max = leftMax;
            }
            if (rightMax > max) {
                max = rightMax;
            }
            if (bTree.getData() > max) {
                max = bTree.getData();
            }
        }
        return max;
    }

    //Maximum in a BTree - Iterative
    public static int maximumInBTreeIterative(BTree bTree) {

        int max = Integer.MIN_VALUE;
        Queue<BTree> bTreeQueue = new LinkedList<>();
        bTreeQueue.offer(bTree);
        while (!bTreeQueue.isEmpty()) {

            BTree node = bTreeQueue.poll();
            if (node.getData() > max) {
                max = node.getData();
            }

            if (node.getLeft() != null) {
                bTreeQueue.offer(node.getLeft());
            }
            if (node.getRight() != null) {
                bTreeQueue.offer(node.getRight());
            }
        }
        return max;
    }

    //Searching an Element in BTree - Recursive
    public static boolean searchingElementRecursive(BTree bTree, int element) {

        boolean found = false;
        if (bTree != null) {
            boolean foundLeftTree = searchingElementRecursive(bTree.getLeft(), element);
            boolean foundRightTree = searchingElementRecursive(bTree.getRight(), element);
            if (foundLeftTree) {
                found = true;
            }
            if (foundRightTree) {
                found = true;
            }
            if (bTree.getData() == element) {
                found = true;
            }
        }
        return found;
    }

    //Searching an Element in BTree - Iterative
    public static boolean searchingElementIterative(BTree bTree, int element) {

        boolean found = false;
        Queue<BTree> bTreeQueue = new LinkedList<>();
        while (!bTreeQueue.isEmpty()) {
            BTree node = bTreeQueue.poll();
            if (node.getData() == element) {
                found = true;
                break;
            }

            if (node.getLeft() != null) {
                bTreeQueue.offer(node.getLeft());
            }
            if (node.getRight() != null) {
                bTreeQueue.offer(node.getRight());
            }
        }
        return found;
    }

    //Insert Element in BTree - Iterative
    public static void insertElementBTree(BTree bTree, int element) {

        Queue<BTree> bTreeQueue = new LinkedList<>();
        bTreeQueue.offer(bTree);

        while (!bTreeQueue.isEmpty()) {
            BTree node = bTreeQueue.poll();
            if (node.getLeft() == null) {
                node.setLeft(new BTree(element));
                break;
            } else {
                bTreeQueue.offer(node.getLeft());
            }

            if (node.getRight() == null) {
                node.setLeft(new BTree(element));
                break;
            } else {
                bTreeQueue.offer(node.getRight());
            }
        }
    }

    //Sizeof BTree - Recursive
    public static int sizOfBTreeRecursive(BTree bTree) {

        int size = 0;
        if (bTree != null) {

            int sizeOfLeft = sizOfBTreeRecursive(bTree.getLeft());
            int sizeOfRight = sizOfBTreeRecursive(bTree.getRight());
            size = sizeOfLeft + sizeOfRight + 1;
        }

        return size;
    }

    //Size of Btree - Iterative
    public static int sizeOfBTreeIterative(BTree bTree) {

        int size = 0;
        Queue<BTree> bTreeQueue = new LinkedList<>();
        bTreeQueue.offer(bTree);

        while (!bTreeQueue.isEmpty()) {

            BTree node = bTreeQueue.poll();
            size++;

            if (node.getLeft() != null) {
                bTreeQueue.offer(node.getLeft());
            }
            if (node.getRight() != null) {
                bTreeQueue.offer(node.getRight());
            }
        }
        return size;
    }

    //Level Order Traversal - Reverse order
    public static void levelOrderReverseOrder(BTree bTree) {

        Stack<BTree> bTreeStack = new Stack<>();
        Queue<BTree> bTreeQueue = new LinkedList<>();

        bTreeQueue.offer(bTree);
        while (!bTreeQueue.isEmpty()) {

            BTree node = bTreeQueue.poll();
            if (node.getLeft() != null) {
                bTreeQueue.offer(node.getLeft());
            }
            if (node.getRight() != null) {
                bTreeQueue.offer(node.getRight());
            }

            bTreeStack.push(node);
        }

        while (!bTreeStack.isEmpty()) {
            System.out.print(bTreeStack.pop().getData() + " -- ");
        }
    }

    //Height of BTree - Recursive
    public static int heightOfBTreeRecursive(BTree bTree) {

        int height = 0;
        if (bTree != null) {

            int heightLeft = heightOfBTreeRecursive(bTree.getLeft());
            int heightRight = heightOfBTreeRecursive(bTree.getRight());
            height = heightLeft > heightRight ? heightLeft + 1 : heightRight + 1;
        }
        return height;

    }

    //Height of BTree - Iterative - End of a level insert an null and while iterating check for null (if null add 1 to height)
    public static int heightOfBTreeIterative(BTree bTree) {

        int height = 1;
        Queue<BTree> bTreeQueue = new LinkedList<>();
        bTreeQueue.offer(bTree);
        bTreeQueue.offer(null);
        while (!bTreeQueue.isEmpty()) {

            BTree node = bTreeQueue.poll();
            if (node != null) {
                if (node.getLeft() != null) {
                    bTreeQueue.offer(node.getLeft());
                }
                if (node.getRight() != null) {
                    bTreeQueue.offer(node.getRight());
                }
            } else {
                if (!bTreeQueue.isEmpty()) {
                    height++;
                    bTreeQueue.offer(null);
                }
            }
        }
        return height;
    }

    //Minimum Height of BTree
    public static int minimumHeightBTree(BTree bTree) {

        Queue<BTree> bTreeQueue = new LinkedList<>();
        bTreeQueue.offer(bTree);
        bTreeQueue.offer(null);
        int height = 1;

        while (!bTreeQueue.isEmpty()) {

            BTree node = bTreeQueue.poll();
            if (node != null) {
                if (node.getLeft() == null || node.getRight() == null) {
                    return height;
                }
                bTreeQueue.offer(node.getLeft());
                bTreeQueue.offer(node.getRight());
            } else {
                if (!bTreeQueue.isEmpty()) { //If node is null and you have only null left
                    height++;
                    bTreeQueue.offer(null);
                }
            }
        }
        return height;
    }

    //Utility - Push Node and all its Left Nodes (if exist)
    public static void pushCurrentNodeAndAllLeftNodes(BTree bTree, Stack<BTree> bTreeStack) {

        while (bTree != null) {
            bTreeStack.push(bTree);
            bTree = bTree.getLeft();
        }
    }


    public static BTree constructBTree() {

        BTree node1 = new BTree(1);
        BTree node2 = new BTree(2);
        BTree node3 = new BTree(3);
        BTree node4 = new BTree(4);
        BTree node5 = new BTree(5);
        BTree node6 = new BTree(6);
        BTree node7 = new BTree(7);
        BTree node8 = new BTree(8);
        BTree node9 = new BTree(9);
        BTree node10 = new BTree(10);

        node1.setLeft(node2);
        node1.setRight(node3);
        node2.setLeft(node4);
        node2.setRight(node5);
        node4.setLeft(node6);
        node5.setLeft(node7);
        node5.setRight(node8);
        node3.setLeft(node9);
        node9.setRight(node10);

        return node1;
    }

    public static BTree constructBTreeSimple() {

        BTree node1 = new BTree(1);
        BTree node2 = new BTree(2);
        BTree node3 = new BTree(3);
        BTree node4 = new BTree(4);
        BTree node5 = new BTree(5);
        BTree node6 = new BTree(6);
        BTree node7 = new BTree(7);

        node1.setLeft(node2);
        node1.setRight(node3);
        node2.setLeft(node4);
        node2.setRight(node5);
        node3.setLeft(node6);
        node3.setRight(node7);


        return node1;
    }

    public static BTree constructBTreeComplex() {

        BTree node1 = new BTree(1);
        BTree node2 = new BTree(2);
        BTree node3 = new BTree(3);
        BTree node4 = new BTree(4);
        BTree node5 = new BTree(5);
        BTree node6 = new BTree(6);
        BTree node7 = new BTree(7);
        BTree node8 = new BTree(8);
        BTree node9 = new BTree(9);
        BTree node10 = new BTree(10);
        BTree node11 = new BTree(11);

        node1.setLeft(node2);
        node1.setRight(node11);
        node2.setLeft(node3);
        node2.setRight(node8);
        node3.setLeft(node4);
        node3.setRight(node5);
        node5.setLeft(node6);
        node6.setRight(node7);
        node8.setRight(node9);
        node9.setLeft(node10);


        return node1;
    }

    public static void main(String[] args) {

        BTree simpleBTree = TreeOperations.constructBTreeSimple();
        TreeOperations.treeOperations(simpleBTree);

        BTree normalBTree = TreeOperations.constructBTree();
        TreeOperations.treeOperations(normalBTree);

        BTree complexBTree = TreeOperations.constructBTreeComplex();
        TreeOperations.treeOperations(complexBTree);
    }

    public static void treeOperations(BTree bTree) {

        TreeOperations.insertElementBTree(bTree, 25);
        System.out.println("Pre Order Traversals");
        TreeOperations.preOrderRecursive(bTree);
        System.out.println();
        TreeOperations.preOrderIterative(bTree);
        System.out.println();

        System.out.println("In Order Traversals");
        TreeOperations.inOrderRecursive(bTree);
        System.out.println();
        TreeOperations.inOrderIterative(bTree);
        System.out.println();

        System.out.println("Post Order Traversals");
        TreeOperations.postOrderRecursive(bTree);
        System.out.println();
        TreeOperations.postOrderIterative2Stacks(bTree);
        System.out.println();
        TreeOperations.postOrderIterative2StacksCustom(bTree);
        System.out.println();
        TreeOperations.postOrderIterative1Stack(bTree);
        System.out.println();

        System.out.println("Level Order Traversal");
        TreeOperations.levelOrderTraversal(bTree);
        System.out.println();

        System.out.println("Level Order Traversal Reverse");
        TreeOperations.levelOrderReverseOrder(bTree);
        System.out.println();

        System.out.println("Maximum in BTree Recursive " + TreeOperations.maximumInBTreeRecursive(bTree));
        System.out.println("Maximum in BTree Iterative " + TreeOperations.maximumInBTreeIterative(bTree));

        System.out.println("is element 16 in  BTree Recursive ? " + TreeOperations.searchingElementRecursive(bTree, 16));
        System.out.println("is element 7 in  BTree Recursive ? " + TreeOperations.searchingElementRecursive(bTree, 7));

        System.out.println("Size of BTree Recursive " + TreeOperations.sizOfBTreeRecursive(bTree));
        System.out.println("Size of BTree Iterative " + TreeOperations.sizeOfBTreeIterative(bTree));
        System.out.println("Height of BTree Iterative " + TreeOperations.heightOfBTreeIterative(bTree));

        System.out.println("Minimum Height of BTree " + TreeOperations.minimumHeightBTree(bTree));
    }

    public static class BTree {

        private int data;
        private BTree left;
        private BTree right;

        public BTree(int data) {
            this.data = data;
        }

        public int getData() {
            return data;
        }

        public void setData(int data) {
            this.data = data;
        }

        public BTree getLeft() {
            return left;
        }

        public void setLeft(BTree left) {
            this.left = left;
        }

        public BTree getRight() {
            return right;
        }

        public void setRight(BTree right) {
            this.right = right;
        }
    }
}
