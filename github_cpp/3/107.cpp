

#ifndef __AVL_H__
#define __AVL_H__

#include <iostream>
#include <string> 
#include <list> 


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

		
		Node(const Type &TypeIn, Node *lt, Node *rt, int ht)
			: NodeElement{ TypeIn }, left{ lt }, right{ rt }, height{ ht } { }

		Node(const Type &&TypeIn, Node *lt, Node *rt, int ht)
			: NodeElement{ move(TypeIn) }, left{ lt }, right{ rt }, height{ ht } { }
	};

	Node *root;
	Node* clone(Node *NodeIn) const;
	
	static const int ALLOWED_IMBALANCE = 1;

	int height(Node *NodeIn) const;
	int max(int, int); 

	void insert(const Type &TypeIn, Node *&NodeIn);
	void makeEmpty(Node *&NodeIn);
	void remove(const Type &TypeIn, Node *&NodeIn);

	
	void balance(Node *&NodeIn);
	void doubleWithLeftChild(Node *&NodeIn);
	void doubleWithRightChild(Node *&NodeIn);
	void rotateLL(Node *&NodeIn);
	void rotateRR(Node *&NodeIn);

	const Type& findMin(Node* NodeIn) const;
	
public:
	AVL();                  
	AVL(const AVL &);		
	~AVL();					

	
	void clear();					  
	void insert(const Type& typeIn);  
	void remove(const Type& typeIn);  
};

#endif 