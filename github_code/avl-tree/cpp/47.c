#ifndef AVL_H
#define AVL_H

#include <string>

using namespace std;

#include "BinaryNode.h"
#include "DuplicateException.h"

template <class ItemType>
class AvlTree
{
private:
	const int LH = 1;	// Left High
	const int EH = 0;	// Even High
	const int RH = -1;	// Right High
	int count;
	BinaryNode<ItemType>  *tree;


	BinaryNode<ItemType>* insert(BinaryNode<ItemType> *rootPtr, BinaryNode<ItemType> *newPtr, bool& taller) throw(DuplicateException);
	BinaryNode<ItemType>* leftBalance(BinaryNode<ItemType> *rootPtr, bool& taller);
	BinaryNode<ItemType>* rotateLeft(BinaryNode<ItemType> *rootPtr);
	BinaryNode<ItemType>* rightBalance(BinaryNode<ItemType> *rootPtr, bool& taller);
	BinaryNode<ItemType>* rotateRight(BinaryNode<ItemType> *rootPtr);
	BinaryNode<ItemType>* removeValue(BinaryNode<ItemType> *rootPtr, const ItemType& searchKey, bool& shorter, bool& success);
	BinaryNode<ItemType>* dltLeftBalance(BinaryNode<ItemType> *rootPtr, bool& smaller);
	BinaryNode<ItemType>* dltRightBalance(BinaryNode<ItemType> *rootPtr, bool& shorter);
	BinaryNode<ItemType>* findNode(const ItemType& key, BinaryNode<ItemType> *rootPtr) const;
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* treePtr) const;

	// Recursive traversal helper methods:
	void preorder(void visit(ItemType&), BinaryNode<ItemType>* rootPtr) const;
	void inorder(void visit(ItemType&), BinaryNode<ItemType>* rootPtr) const;
	void postorder(void visit(ItemType&), BinaryNode<ItemType>* rootPtr) const;

	// Recursively deletes all nodes from the tree.
	void destroyTree(BinaryNode<ItemType>* rootPtr);

	//  	The following function is used for debugging.
	void _print(BinaryNode<ItemType> *rootPtr, int level) const;

public:
	AvlTree();
	AvlTree(const AvlTree<ItemType>& treePtr);
	
	~AvlTree();
	
	AvlTree& operator=(const AvlTree& rightTree);

	bool add(const ItemType& newData);
	bool remove(const ItemType& searchKey);
	bool get(ItemType& searchKey) const;


	void preorderTraverse(void visit(ItemType&)) const;
	void inorderTraverse(void visit(ItemType&)) const;
	void postorderTraverse(void visit(ItemType&)) const;;

	bool isEmpty() const;
	bool isFull() const;
	int  getNumberOfNodes() const;

	//      The following function is used for debugging.
	void AVL_Print() const;
}; // class AvlTree

#include "AVL.cpp"
#endif