/*
Jensen_A2.cpp
9/16/13
Bryan Jensen

A library containing three binary tree classes: the binaryTree, binarySearchTree and most importantly 
the balancedBST class, a Balanced Binary Search Tree using the AVL balancing method with single and double
rotations, which supports insertion and searching.

Description: This file contains the prototypes for the three classes in this mini-library, the binaryTree, 
			 binarySearchTree and balancedBST, each of which subclasses the previous one.

			 (note: private methods are not available to the programmer and therefore not fully documented)

			binaryTree:
			 Methods:
			 	treeNodeCount:      A method to return the total number of nodes in the tree.
			 	treeHeight:         A method to return the height of the tree, defined as the number of transitions from the
			 				        root to the farthest node.
			 	postorderTraversal: A method to output the data contents of the tree to the console, traversing
			 						in a postorder fashion.
			 	inorderTraversal:   A method to output the data contents of the tree to the console, traversing
			 					    in an inorder fashion.
			 	preorderTraversal:  A method to output the data contents of the tree to the console, traversing
			 					    in a preorder fashion.
			 	treeDisplay:        A method to graphically output the data contents of the tree to the console. Returns void.

			binarySearchTree:
			 Methods:
			 	searchItem:         Searches the binary tree for the given key, returning a boolean representing whether it was found.
			 	insertItem:         Inserts an item into the binary tree according to the rules of a binary search tree, where
			 				        each data item is inserted to the left of a parent node which is greater than it, and right of
			 				        a value which is smaller.

			balancedBST:
			 Methods:
			 	insertItem:         A method to insert an item into the binary tree while maintaining the AVL-tree balancing rules,
			 				        where every node's two subtrees (right and left) have heights that do not differ by more than 1.
			 				        To achieve this, right and left, single and double rotations are performed on the binary tree.
			 	balanceFactors:     A method to output the data contents and corresponding node's balance factors, traversing over
			 					    the tree in a preorder fashion.

Input:       binarySearchTree and balancedBST can store characters, which are inserted via their respective insertItem methods.
Output:      All three tree classes are capable of output via pre-, in- and post-order traversals, as well as a command-line graphical
			 output for a given binary tree.

*/

#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

typedef char elemType;	// "placeholder" for data type

// Binary Tree Node struct
struct nodeType {
	elemType data;		// store data
	nodeType* left;		// link to left subtree
	nodeType* right;	// link to right subtree
	int balanceFactor;	// AVL-Tree balance factor
};

// Binary Tree class
class binaryTree {
protected:
	nodeType* root; // Pointer to root node
	int nodecount(nodeType*) const;                        // finds number of nodes in subtree rooted at node
	int height(nodeType*) const;                           // finds height of subtree rooted at node

	void inorder(nodeType*) const;                         // Iterates over subtree rooted at node in inorder fashion
	void preorder(nodeType*) const;                        // Iterates over subtree rooted at node in preorder fashion
	void postorder(nodeType*) const;                       // Iterates over subtree rooted at node in postorder fashion

	void display(nodeType*) const;                         // Provides a graphical output of the subtree rooted at node
public: 
	// constructor
	binaryTree() { root = NULL; }; // Default CTOR

	// some tree information methods
	int treeNodeCount() const { return nodecount(root); }; // Public method for counting num nodes in entire tree
	int treeHeight() const { return height(root); };       // Public method for finding height of entire tree
		  
	// tree traversals
	void postorderTraversal() const { postorder(root); };  // Traverses entire tree in postorder fashion
	void inorderTraversal() const { inorder(root); };      // Traverses entire tree in inorder fashion
	void preorderTraversal() const { preorder(root); };    // Traverses entire tree in preorder fashion

	// tree outputs
	void treeDisplay() const { cout << endl; display( root ); }; // Graphically displays entire tree
};


// Binary Search Tree class
class binarySearchTree : public binaryTree {
protected:
	bool search(const elemType, const nodeType*) const;    // Searches subtree rooted at node for key value
	void insert(const elemType, nodeType*&);               // Inserts key value into subtree rooted at node
public:
	bool searchItem(const elemType key) const { return search(key, root); };  // Searches entire tree for key
	void insertItem(const elemType key) { insert(key, root); }; // Inserts key into tree
};


// Balanced Binary Search Tree class
class balancedBST : public binarySearchTree {
protected:
	void rotateLeft(nodeType*&);                           // Performs a left rotation of the subtree rooted at node
	void rotateRight(nodeType*&);                          // Performs a left rotation of the subtree rooted at node

	void rotateSubtree(nodeType*&);                        // Performs the correct rotation on an unbalanced subtree rooted at node

	void insert(const elemType, nodeType*&);               // Inserts an item into the subtree rooted at node, updating balance factors

	void bFactors(const nodeType*) const;                  // Displays the balance factors the subtree rooted at node, displayed in preorder fashion
	int calcBalanceFactor(nodeType*) const;                // Helper method to calculate balance factor of a certain node
public:
	balancedBST() {};                                      // Default CTOR

	// AVL-Tree methods
	void insertItem(const elemType key) { insert(key, root); }; // Insert item into AVL tree and balance
	void balanceFactors() const { bFactors(root); };       // Display balance factors of entire tree in preorder fashion
};
