/***
 * File Name 				: 		AVLTree.java
 * Author Name 			: 		Aditya Shrotri
 * Date 						:		October 13,2012
 * Version					:		1.0
 * Purpose					:       The class implements functions for insert and search 
 * 									in the AVL tree. Insert functions in turn, checks for the 
 * 									height and balance factor of the AVL tree and calls the functions 
 * 									which perform LL, LR, RL, RR rotations accordingly. The search functions 
 * 									checks if the given key is present in the AVL tree. 
 * 									The class also has display functions for inorder and postorder walk of the AVL tree.
 */

package ufl.ads.datastructures;

import java.util.*;

class AVLTree {

	private AVLNode root; // first node of tree
	private static AVLNode newNode; // for new node to be inserted.
	private static AVLNode current;
	private static AVLNode parent; // parent node required for the fixing.

	/*
	 * Constructor of AVLTree
	 */
	public AVLTree() {
		root = null;
	}

	/*
	 * find node with given key
	 */
	public AVLNode find(AVLNode root1, int key) {
		AVLNode current = root1; // start at root
		try {

			if (root1 == null) {
				return null;
			}

			while (current.iKey != key) // while no match,
			{
				if (key < current.iKey)
					current = current.leftChild;// left subtree to be traversed.
				else
					current = current.rightChild;
				if (current == null) // right subtree to be traversed.
					return null; // didn't find it
			}
			return current; // found it
		} catch (Exception e) {
			e.printStackTrace();
		}
		return current;
	}

	/*
	 * Inserts key into AVLTree if imbalance is detected then rotations are
	 * performed.
	 */
	public boolean insert(int key, int value) {
		try {
			// rotation flag for checking whether rotations are required to
			// performed or not
			boolean rotateFlag = false;

			newNode = new AVLNode(); // make new node

			// Fill in the fields of the newly created AVLNode
			newNode.iKey = key; // insert key
			newNode.iValue = value;
			newNode.balance = 0;
			newNode.height = 1;

			if (root == null)
				root = newNode;
			else // root occupied
			{
				current = root; // start at root and walk down the tree
				parent = null;

				// An AVLStack is a stack that stores AVLNodes. It will be used
				// to store the search path

				Stack<AVLNode> S = new Stack<AVLNode>();

				// Loop to walk down the tree, until current becomes null
				// The nodes visited in this walk are stored in S

				while (current != null) {
					S.push(current);
					parent = current;
					if (key < current.iKey)
						current = current.leftChild;// left subtree to be
													// traversed.
					else if (key > current.iKey)
						current = current.rightChild;// right subtree to be
														// traversed.
					else
						return false;
				} // end while

				// assignment of the node to it's parent.
				if (key < parent.iKey)
					parent.leftChild = newNode;
				else
					parent.rightChild = newNode;

				S.push(newNode);
				// Walk back up the tree, by popping items from the AVLStack S
				int leftHeight, rightHeight;
				AVLNode pathNode;
				while (!S.isEmpty()) {
					// This is the current node of the search path
					pathNode = S.pop();

					// Compute its height and balance
					// First find the height of the left subtree
					if (pathNode.leftChild == null)
						leftHeight = 0;
					else
						leftHeight = pathNode.leftChild.height;

					// find the height of the right subtree
					if (pathNode.rightChild == null)
						rightHeight = 0;
					else
						rightHeight = pathNode.rightChild.height;

					// balance of the node
					pathNode.balance = leftHeight - rightHeight;

					// Set the height of the subtree rooted at the node
					pathNode.height = 1 + max(leftHeight, rightHeight);

					// Check if balance is 2 or -2
					AVLNode av = null;
					if (pathNode.balance > 1) {
						// System.out.println("Tree is Rebalancing on Left Rotate.");
						rotateFlag = true;
						if (key < pathNode.leftChild.iKey) {
							// perform LL rotation
							pathNode = rotateLeft(pathNode);

						} else {
							// perform LR rotation
							pathNode = doubleRotateLeft(pathNode);
						}

					} else if (pathNode.balance < -1) {
						// System.out.println("Tree is Rebalancing on Right Rotate.");
						rotateFlag = true;
						if (key > pathNode.rightChild.iKey) {
							// perform RR rotation
							pathNode = rotateRight(pathNode);

						} else {
							// perform RL rotation
							pathNode = doubleRotateRight(pathNode);
						}
					}

					if (rotateFlag == true) {
						rotateFlag = false;
						if (S.isEmpty()) {
							root = pathNode;
						} else {
							// Pop the parent
							av = S.pop();
							// fix the children
							if (av.iKey < pathNode.iKey) {
								av.rightChild = pathNode;
							} else {
								av.leftChild = pathNode;
							}
						}

					}

				}

			}
		} catch (Exception e) {
			e.printStackTrace();

		}
		return true;
	}

	/*
	 * Helper function to give max
	 */
	int max(int x, int y) {
		if (x > y || x == y)
			return x;
		return y;
	}

	/**
	 * For AVL trees, this is a single rotation for LL. Update heights, then
	 * return new root. Rotate binary tree node with left child.
	 */
	private AVLNode rotateLeft(AVLNode k2) {
		int leftHeight;
		int rightHeight;
		AVLNode k1 = k2.leftChild;
		k2.leftChild = k1.rightChild;
		k1.rightChild = k2;

		k2.height = max(k2.leftChild == null ? 0 : k2.leftChild.height,
				k2.rightChild == null ? 0 : k2.rightChild.height) + 1;
		k1.height = max(k1.leftChild == null ? 0 : k1.leftChild.height,
				k2.height) + 1;

		// Compute its height and balance

		if (k2.leftChild == null)
			leftHeight = 0;
		else
			leftHeight = k2.leftChild.height;

		// Then find the height of the right subtree
		if (k2.rightChild == null)
			rightHeight = 0;
		else
			rightHeight = k2.rightChild.height;

		// Set the balance of the node
		k2.balance = leftHeight - rightHeight;

		// Compute its height and balance

		if (k1.leftChild == null)
			leftHeight = 0;
		else
			leftHeight = k1.leftChild.height;

		// Then find the height of the right subtree
		if (k1.rightChild == null)
			rightHeight = 0;
		else
			rightHeight = k1.rightChild.height;

		// Set the balance of the node
		k1.balance = leftHeight - rightHeight;

		return k1;

	}

	/*
	 * Inorder Tree Walk using recursion
	 */
	public void inorderTreeWalk(AVLNode k1) {
		try {
			if (k1 == null)
				return;

			inorderTreeWalk(k1.leftChild);
			Dictionary.pwAVLInorder.println(k1.iKey + " "+k1.iValue);
			// System.out.print(k1.iKey + " ");
			inorderTreeWalk(k1.rightChild);
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

	/*
	 * PostOrder Tree Walk for AVLTree
	 */
	public void postTreeWalk(AVLNode k1) {
		try {
			if (k1 == null)
				return;

			postTreeWalk(k1.leftChild);
			postTreeWalk(k1.rightChild);
			Dictionary.pwAVLPostorder.println(k1.iKey + " "+k1.iValue);
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

	/*
	 * To find the Root of the tree.
	 */
	public AVLNode getRoot() {
		return root;
	}

	/**
	 * Rotate binary tree node with right child. For AVL trees, this is a single
	 * rotation for RR. Update heights, then return new root.
	 */
	private AVLNode rotateRight(AVLNode k1) {
		int leftHeight;
		int rightHeight;
		AVLNode k2 = k1.rightChild;
		k1.rightChild = k2.leftChild;
		k2.leftChild = k1;
		k1.height = max(k1.leftChild == null ? 0 : k1.leftChild.height,
				k1.rightChild == null ? 0 : k1.rightChild.height) + 1;
		k2.height = max(k2.rightChild == null ? 0 : k2.rightChild.height,
				k1.height) + 1;

		// Compute its height and balance
		// First find the height of the left subtree
		if (k2.leftChild == null)
			leftHeight = 0;
		else
			leftHeight = k2.leftChild.height;

		// Then find the height of the right subtree
		if (k2.rightChild == null)
			rightHeight = 0;
		else
			rightHeight = k2.rightChild.height;

		// Set the balance of the node
		k2.balance = leftHeight - rightHeight;

		// Compute its height and balance
		// First find the height of the left subtree
		if (k1.leftChild == null)
			leftHeight = 0;
		else
			leftHeight = k1.leftChild.height;

		// Then find the height of the right subtree
		if (k1.rightChild == null)
			rightHeight = 0;
		else
			rightHeight = k1.rightChild.height;

		// Set the balance of the node
		k1.balance = leftHeight - rightHeight;

		return k2;
	}

	/**
	 * For AVL trees, this is a double rotation for LR. Update heights, then
	 * return new root.
	 */
	private AVLNode doubleRotateLeft(AVLNode k3) {
		k3.leftChild = rotateRight(k3.leftChild);
		return rotateLeft(k3);
	}

	/**
	 * For AVL trees, this is a double rotation for RL. Update heights, then
	 * return new root.
	 */
	private AVLNode doubleRotateRight(AVLNode k1) {
		k1.rightChild = rotateLeft(k1.rightChild);
		return rotateRight(k1);
	}

} // end of class AVLTree