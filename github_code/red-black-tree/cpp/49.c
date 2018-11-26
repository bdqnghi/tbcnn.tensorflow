#ifndef B
#define B

#include <string>
#include <iostream>
#include <iomanip>// - for setw>
#include <fstream>
#include <cstdlib>
#include <stdexcept>

/*
This is header file for RedBlackTree.cpp
*** Please include�� 

	using RBTree::RedBlackTree; 

	to test this RedBlackTree.h and RedBlackTree.cpp
	This header file contains Node class, and RedBlackTree class
	Both of them are in template classes, the RedBlackTree header 
	file is seperate from RedBlackTree.cpp file
*/
namespace RBTree{
	/*
	Node class is implement out side of RedBlackTree class; 
	however, it's under RBTee namespace
	*/
	template<class T>
	class Node {
	public:
		T data; //a template type parameter
		char color; /*color*/ // besides isBlack, the color is impliment for checking purpose
		Node *left, *right, *parent; /*lelf, right, parent*/
		bool isBlack;//the colour of the node, either black or red but represented as a bool 

		/*copy constructor*/
		Node(T x) {
			data = x;
			left = NULL;
			right = NULL;
			parent = NULL;
			color = 'X';
			isBlack = true;
		}

		/*constructor*/
		Node() {
		//	data = 0;
			color = 'X';
			left = NULL;
			right = NULL;
			parent = NULL;
			isBlack = true;
		}
	};


	/*
	RedBlackTree class is separate from Node class
	The main task of is to insert and delete data into Red Black Tree form
	The file can handle integer, numbers, and strings which is in template class.
	*/
	template<class T>
	class RedBlackTree {
	public:
		
		RedBlackTree(); //default constructor �C creates an empty tree whose root is null
		RedBlackTree(const RedBlackTree& old);//copy constructor - deep copy, simply call void delete_all function
		RedBlackTree& operator=(const RedBlackTree& old);//assignment operator
		~RedBlackTree();//destructor - creates a deep copy of the parameter
		void load(T* arr, int size);//loads the contents of the array parameter 
		bool insert(T value);//inserts value and returns true;
		bool remove(T value);// removes value from the tree and returns true; 
		bool search(T value);//searches the tree for value and returns true if it is found 
		T* search(T valueMin, T valueMax,int &iCount);//search the value in between of minimum and maximum values
		void deleteAll();//empties the tree, and de-allocates dynamic memory 
		T* dump(int& n) const; //return all the values in the tree in dynmic memory
		

		/*statistic part*/
		int size() const;//return the number of item in the tree
		int height() const;//return the height of the tree
		int b_height() const;//return black height of the tree

		/*following function are given in Assignment 4*/
		void redProperty(Node<T>* nd, bool & ok) const; 
		bool redCheck() const; 
		
		/*following function are helper functions*/
		/*The functions' specifications are include in RedBlackTree.cpp*/
		void dump_help(Node<T> *node, int& n) const;//dump helper function
		void insertfixup(Node<T> *node);
		void removefixup(Node<T> *node);
		Node<T>* deleteNode(Node<T>* node);
		void deletefixup(Node<T>* node,Node<T>* nodeParent, bool nodeIsLeft);
		//void deletefixupRight(Node<T>* w, Node<T>* node,Node<T>* nodeParent,bool nodeIsLeft);

		
		Node<T>* TreeSuccessor(Node<T>* target);//find the target's successor	
		void delete_all(Node<T>* p);//destructor and deleteAll() call this function to empties the tree, and de-allocates dynamic memory 
		void LeftRotate(Node<T>* x);
		void RightRotate(Node<T>* x);
		bool RedBlackTree<T>::isEmpty() const;

		
		void deleteNode(Node<T>* target, Node<T>* parent, bool isLeft);




		/*for debug*/
    ////////////////////////////////
		//void debugPrint(Node<T>* n) {
		//	if (n == NULL) {
		//		return;
		//	}

		//	cout << "node " << n << " data " << n->data << " " << n->color << endl;
		//	cout << "\tleft=" << n->left << endl;
		//	cout << "\tright=" << n->right << endl;
		//	if (n->left != NULL) {
		//		debugPrint(n->left);
		//	}
		//	if (n->right != NULL) {
		//		debugPrint(n->right);
		//	}
		//}

		//void debugPrint() {
		//	cout << "root = " << root << endl;
		//	debugPrint(root);
		//}

	private:
		Node<T>* root;//pointer to the root of the tree
		int n; //the number of items in the tree
		T* arr;

		
	};
}
#endif