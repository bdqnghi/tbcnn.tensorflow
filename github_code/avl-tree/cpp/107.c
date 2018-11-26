/*
Author: Cordell Hurst
Course : CSCI 335 Software Design and Analysis III
Instructor: Pavel Shostak
Assignment 02
24 October 2018
This program is tasked to take random integers and inserts into an AVL tree and a BST.
Insertions are 1k, 10k, 100k and 1m nodes. -the duration of the insertions are timed and compared.
Using C++11
Compile with g++ -o out AVL.h AVL.cpp BST.cpp BST.h Type.cpp Type.h main.cpp -std=c++11
*/

#ifndef __AVL_H__
#define __AVL_H__

#include <iostream>
#include <string> //for string handling
#include <list> //for lists

//#include "Type.h"
#include "BST.h"

using namespace std;

class AVL : public BST
{
private:
	struct Node
	{
		Type NodeElement;
		Node * left;
		Node * right;
		int height = 0;

		//Node constructors :
		Node(const Type &TypeIn, Node *lt, Node *rt, int ht)
			: NodeElement{ TypeIn }, left{ lt }, right{ rt }, height{ ht } { }

		Node(const Type &&TypeIn, Node *lt, Node *rt, int ht)
			: NodeElement{ move(TypeIn) }, left{ lt }, right{ rt }, height{ ht } { }
	};

	Node *root;
	Node* clone(Node *NodeIn) const;
	
	static const int ALLOWED_IMBALANCE = 1;

	int height(Node *NodeIn) const;
	int max(int, int); //returns greater of 2 numbers or returns either if equal

	void insert(const Type &TypeIn, Node *&NodeIn);
	void makeEmpty(Node *&NodeIn);
	void remove(const Type &TypeIn, Node *&NodeIn);

	//AVL balancing functions
	void balance(Node *&NodeIn);
	void doubleWithLeftChild(Node *&NodeIn);
	void doubleWithRightChild(Node *&NodeIn);
	void rotateLL(Node *&NodeIn);
	void rotateRR(Node *&NodeIn);

	const Type& findMin(Node* NodeIn) const;
	
public:
	AVL();                  // default
	AVL(const AVL &);		// copy constructor
	~AVL();					// destructor

	// Tree modifiers:
	void clear();					  // empty the Tree
	void insert(const Type& typeIn);  // insert element
	void remove(const Type& typeIn);  // remove element
};

#endif /* __AVL_H__ */