package com.anuragkapur.ds.tree;

/**
 * @author: anuragkapur
 * @since: 09/05/2014
 */

public class TreeFactory {

    /**
     * @return Root node of a balanced binary tree. The tree may/may not be 'complete'.
     */
    public static TreeNode getBalancedBinaryTree() {

        /*
                       4
                 1           3
              2     4     5     7
                  2          6
         */

        TreeNode rootNode = new TreeNode(4);
        TreeNode node1 = new TreeNode(1);
        TreeNode node2 = new TreeNode(3);
        TreeNode node3 = new TreeNode(2);
        TreeNode node4 = new TreeNode(4);
        TreeNode node5 = new TreeNode(5);
        TreeNode node6 = new TreeNode(7);
        TreeNode node7 = new TreeNode(2);
        TreeNode node8 = new TreeNode(6);

        rootNode.setLeft(node1);
        rootNode.setRight(node2);

        node1.setLeft(node3);
        node1.setRight(node4);

        node2.setLeft(node5);
        node2.setRight(node6);

        node4.setLeft(node7);

        node6.setLeft(node8);

        return rootNode;
    }

    /**
     * @return Root node of a un-balanced binary tree. The tree may/may not be 'complete'.
     */
    public static TreeNode getUnBalancedBinaryTree() {

        /*
                       4
                 1           3
              2     4
                  2
         */

        TreeNode rootNode = new TreeNode(4);
        TreeNode node1 = new TreeNode(1);
        TreeNode node2 = new TreeNode(3);
        TreeNode node3 = new TreeNode(2);
        TreeNode node4 = new TreeNode(4);
        TreeNode node5 = new TreeNode(2);


        rootNode.setLeft(node1);
        rootNode.setRight(node2);

        node1.setLeft(node3);
        node1.setRight(node4);

        node4.setLeft(node5);

        return rootNode;
    }

    public static TreeNode getBinarySearchTree() {

        /*
                       6
                 3           8
              2     5     7     10
                  4           9
         */

        TreeNode rootNode = new TreeNode(6);
        TreeNode node1 = new TreeNode(3);
        TreeNode node2 = new TreeNode(8);
        TreeNode node3 = new TreeNode(2);
        TreeNode node4 = new TreeNode(5);
        TreeNode node5 = new TreeNode(7);
        TreeNode node6 = new TreeNode(10);
        TreeNode node7 = new TreeNode(4);
        TreeNode node8 = new TreeNode(9);

        rootNode.setLeft(node1);
        rootNode.setRight(node2);

        node1.setLeft(node3);
        node1.setRight(node4);
        node1.setParent(rootNode);

        node2.setLeft(node5);
        node2.setRight(node6);
        node2.setParent(rootNode);

        node3.setParent(node1);

        node4.setLeft(node7);
        node4.setParent(node1);

        node5.setParent(node2);

        node6.setLeft(node8);
        node6.setParent(node2);

        node7.setParent(node4);

        node8.setParent(node6);

        return rootNode;
    }

    public static TreeNode getBinarySearchTreeForInsertionTest1() {

        /*
                       6
                 4           8
              2     5     7     10
                              9
         */

        TreeNode rootNode = new TreeNode(6);
        TreeNode node1 = new TreeNode(4);
        TreeNode node2 = new TreeNode(8);
        TreeNode node3 = new TreeNode(2);
        TreeNode node4 = new TreeNode(5);
        TreeNode node5 = new TreeNode(7);
        TreeNode node6 = new TreeNode(10);
        TreeNode node8 = new TreeNode(9);

        rootNode.setLeft(node1);
        rootNode.setRight(node2);

        node1.setLeft(node3);
        node1.setRight(node4);
        node1.setParent(rootNode);

        node2.setLeft(node5);
        node2.setRight(node6);
        node2.setParent(rootNode);

        node3.setParent(node1);

        node4.setParent(node1);

        node5.setParent(node2);

        node6.setLeft(node8);
        node6.setParent(node2);

        node8.setParent(node6);

        return rootNode;
    }

    public static TreeNode getInvalidBinarySearchTree() {

        /*
                       4
                 3           6
              2     6     5     7
                  3           6
         */

        TreeNode rootNode = new TreeNode(4);
        TreeNode node1 = new TreeNode(3);
        TreeNode node2 = new TreeNode(6);
        TreeNode node3 = new TreeNode(2);
        TreeNode node4 = new TreeNode(6);
        TreeNode node5 = new TreeNode(5);
        TreeNode node6 = new TreeNode(7);
        TreeNode node7 = new TreeNode(3);
        TreeNode node8 = new TreeNode(6);

        rootNode.setLeft(node1);
        rootNode.setRight(node2);

        node1.setLeft(node3);
        node1.setRight(node4);

        node2.setLeft(node5);
        node2.setRight(node6);

        node4.setLeft(node7);

        node6.setLeft(node8);

        return rootNode;
    }
}
