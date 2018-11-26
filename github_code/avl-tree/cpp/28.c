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

#include "AVL.h"

using namespace std;

//default
AVL::AVL() : root(NULL){ }
//copy constructor
AVL::AVL(const AVL &Tree)
{
	root = clone(Tree.root);
}
//destructor
AVL::~AVL()
{
	makeEmpty(root);
	delete root;
}
// Type modifiers:
//empties avl tree
void AVL::clear()// empty the tree
{
	makeEmpty(root);
}
//calls recursive insert
void AVL::insert(const Type& typeIn)// insert element typeIn
{
	//call private recursive func
	insert(typeIn, root);
}
//calls recursive remove function
void AVL::remove(const Type& typeIn)// remove element typeIn
{
	//call private recursive func
	remove(typeIn, root);
}

//PRIVATE RECURSIVE FUNCTIONS
//Copy constructor accessed by regular copy constructor
AVL::Node* AVL::clone(Node *NodeIn) const
{
	if (NodeIn == nullptr)
		return nullptr;
	else
		return new Node{ NodeIn->NodeElement, clone(NodeIn->left), clone(NodeIn->right), NodeIn->height };
}
//Internal recursive delete
void AVL::makeEmpty(Node *&NodeIn)
{
	if (NodeIn != nullptr)
	{
		makeEmpty(NodeIn->left);
		makeEmpty(NodeIn->right);
		delete NodeIn;
	}
	NodeIn = nullptr;
}
//recursive findMin(). Returns Type object if found. otherwise returns NO_Type with -1
const Type& AVL::findMin(Node *NodeIn) const
{
	if (NodeIn == nullptr)
		return NO_Type;
	if (NodeIn->left == nullptr)
		return NodeIn->NodeElement;
	return findMin(NodeIn->left);
}
//Recursive insert w/balance call
void AVL::insert(const Type &TypeIn, Node *&NodeIn)
{
	if (NodeIn == nullptr)
		NodeIn = new Node{ TypeIn, nullptr , nullptr, 0 };//insert as leaf
	else if (TypeIn < NodeIn->NodeElement)
		insert(TypeIn, NodeIn->left);
	else if (NodeIn->NodeElement < TypeIn)
		insert(TypeIn, NodeIn->right);
	else
	{
		//Duplicate; do nothing
	}
		balance(NodeIn);
}
//Recursive remove w/ balance call
void AVL::remove(const Type &TypeIn, Node *&NodeIn)
{
	if (NodeIn == nullptr)
		return; //Item not found
	if (TypeIn < NodeIn->NodeElement)
		remove(TypeIn, NodeIn->left);
	else if (NodeIn->NodeElement < TypeIn)
		remove(TypeIn, NodeIn->right);
	else if (NodeIn->left != nullptr && NodeIn->right != nullptr) //Two children
	{
		NodeIn->NodeElement = findMin(NodeIn->right);
		remove(NodeIn->NodeElement, NodeIn->right);
	}
	else
	{
		Node *oldNode = NodeIn;
		NodeIn = (NodeIn->left != nullptr) ? NodeIn->left : NodeIn->right;
		delete oldNode;
	}
	balance(NodeIn);
}
//Type Adjustment functions. All AVL nodes created with height info to facilitate
//Balances AVL tree, keeps order integrity
void AVL::balance(Node *&NodeIn)
{
	if (NodeIn == nullptr)
		return;
	if (height(NodeIn->left) - height(NodeIn->right) > ALLOWED_IMBALANCE)
	{
		if (height(NodeIn->left->left) >= height(NodeIn->left->right))
			rotateLL(NodeIn);
		else
			doubleWithLeftChild(NodeIn);
	}
	else
	{
		if (height(NodeIn->right) - height(NodeIn->left) > ALLOWED_IMBALANCE)
		{
			if (height(NodeIn->right->right) >= height(NodeIn->right->left))
				rotateRR(NodeIn);
			else
				doubleWithRightChild(NodeIn);
		}
	}
	NodeIn->height = max(height(NodeIn->left), height(NodeIn->right)) + 1;
}
//Rotate left
void AVL::rotateLL(Node *&NodeIn)//rotateWithLeftchild
{
	Node *tempnode = NodeIn->left;
	NodeIn->left = tempnode->right;
	tempnode->right = NodeIn;
	NodeIn->height = max(height(NodeIn->left), height(NodeIn->right)) + 1;
	tempnode->height = max(height(tempnode->left), NodeIn->height) + 1;
	NodeIn = tempnode;
}
//Rotate right
void AVL::rotateRR(Node *&NodeIn)//rotateWithRightchild
{
	Node *tempnode = NodeIn->right;
	NodeIn->right = tempnode->left;
	tempnode->left = NodeIn;
	NodeIn->height = max(height(NodeIn->right), height(NodeIn->left)) + 1;
	tempnode->height = max(height(tempnode->right), NodeIn->height) + 1;
	NodeIn = tempnode;
}
//Double rotation, calls RL()
void AVL::doubleWithLeftChild(Node *&NodeIn)
{
	rotateRR(NodeIn->left);
	rotateLL(NodeIn);
}
//Double Rotation, calls LR()
void AVL::doubleWithRightChild(Node *&NodeIn)
{
	rotateLL(NodeIn->right);
	rotateRR(NodeIn);
}
//Other
//Returns height of AVL node for rotations and balance
int AVL::height(Node *NodeIn) const
{
	return NodeIn == nullptr ? -1 : NodeIn->height;
}
//simple greater than, less than function
int AVL::max(int left, int right)
{
	if (left < right)
		return right;
	else if (right < left)
		return left;
	else
		return left;//both are same value
}



