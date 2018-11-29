package com.alltej.apps.rbtreeapp;

/**
 * @author Allan Tejano
 * 4/29/2018
 */
public class RedBlackTreeApp {

    public static void main(String args[]) {
        //RedBlackNode root = null;
        RedBlackTree redBlackTree = new RedBlackTree();

        redBlackTree.insertData(10);
        redBlackTree.insertData( 15);
        redBlackTree.insertData( -10);
        redBlackTree.insertData( 20);
        redBlackTree.insertData( 30);
        redBlackTree.insertData( 40);
        redBlackTree.insertData( 50);
        redBlackTree.insertData( -15);
        redBlackTree.insertData( 25);
        redBlackTree.insertData( 17);
        redBlackTree.insertData( 21);
        redBlackTree.insertData( 24);
        redBlackTree.insertData( 28);
        redBlackTree.insertData( 34);
        redBlackTree.insertData( 32);
        redBlackTree.insertData( 26);
        redBlackTree.insertData( 35);
        redBlackTree.insertData( 19);

        redBlackTree.printFromRoot();

        redBlackTree.removeData(50);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
        redBlackTree.removeData(40);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
        redBlackTree.removeData(-10);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
        redBlackTree.removeData(15);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
        redBlackTree.removeData(17);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
        redBlackTree.removeData(24);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
        redBlackTree.removeData(21);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
        redBlackTree.removeData(32);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
        redBlackTree.removeData(26);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
        redBlackTree.removeData(19);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
        redBlackTree.removeData(25);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
        redBlackTree.removeData(17);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
        redBlackTree.removeData(-15);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
        redBlackTree.removeData(20);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
        redBlackTree.removeData(35);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
        redBlackTree.removeData(34);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
        redBlackTree.removeData(30);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
        redBlackTree.removeData(28);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
        redBlackTree.removeData(10);
        System.out.println(redBlackTree.validateRedBlackTreeDefault());
    }
}
