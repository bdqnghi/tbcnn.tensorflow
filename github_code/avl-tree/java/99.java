package tcss342;
//File: AVL.java

import java.io.*;
import java.util.*;

/**
 * CSC B63 Assignment #2 Programming component Provides command line access to
 * the AVL tree class
 *
 * This file has been provided to make it easier to test your AVL tree code.
 *
 * DO NOT SUBMIT THIS FILE
 **/

public class AVL {
	
	public static void main(String... args) {
		AVLTree tree = new AVLTree();

		tree.insert(41);
		tree.insert(31);
		tree.insert(50);
		tree.insert(45);
		tree.insert(47);
//		tree.insert(23);
//		tree.insert(71);
//		tree.insert(5);
//		
		tree.print();
//		tree.deleteKey(5);
//		tree.deleteKey(15);
//		tree.deleteKey(50);
//		tree.deleteKey(7);
//		tree.print();
//		tree.printInOrder();
		
		
		//RedBlack rb = new RedBlack();
		
		//left - right 
//		rb.add(41);
//		rb.add(50);
//		rb.add(31);
//		rb.add(38);
		
		//single right
//		rb.add(41);
//		rb.add(38);
//		rb.add(31);
		
		//single left
//		rb.add(31);
//		rb.add(20);
//		rb.add(38);
//		rb.add(41);
		
		
	//	rb.print();
	}
} // AVL
