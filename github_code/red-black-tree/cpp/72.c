/*
 * redblacktree.cpp
 *
 *  Created on: Apr 27, 2017
 *      Author: Benjamin Kleinberg
 */

#include"redblacktree.h"
#include"redblacknode.h"

using namespace RedBlack;
using std::bad_alloc;

RedBlackNode* RedBlackTree::makeNode(Int val, int color) {
	RedBlackNode* node;

	try {
		node = new RedBlackNode(val, color);
		//node->left = &NULL_NODE;
		//node->right = &NULL_NODE;

	} catch(bad_alloc &ex) {
		node = 0;
	}

	return node;
}

RedBlackTree::RedBlackTree() {
	// TODO Auto-generated constructor stub

}

RedBlackTree::~RedBlackTree() {
	// TODO Auto-generated destructor stub
}

/**
 * Rotates the subtree rooted at the given node to the left.
 * The right child of the given node will be the new root.
 *
 * @param root a pointer to the root of the subtree
 *
 * @return a pointer to the new root of the subtree
 * @return 0 if the rotation failed
 */
RedBlackNode* RedBlackTree::rotateLeft(RedBlackNode* root) {
	BinaryTreeNode* newParent = root->right;

	if(newParent) {
		root->right = newParent->left;

		if(newParent->left)
			newParent->left->parent = root;
		newParent->parent = root->parent;

		if(root->parent == 0)
			_root = newParent;
		else if(root == root->parent->left)
			root->parent->left = newParent;
		else
			root->parent->right = newParent;

		newParent->left = root;
		root->parent = newParent;
	}

	return dynamic_cast<RedBlackNode*>(newParent);
}

/**
 * Rotates the subtree rooted at the given node to the right.
 * The left child of the given node will be the new root.
 *
 * @param root a pointer to the root of the subtree
 *
 * @return a pointer to the new root of the subtree
 * @return 0 if the rotation failed
 */
RedBlackNode* RedBlackTree::rotateRight(RedBlackNode* root) {
	BinaryTreeNode* newParent = root->left;

	if(newParent) {
		root->left = newParent->right;

		if(newParent->right)
			newParent->right->parent = root;
		newParent->parent = root->parent;

		if(root->parent == 0)
			_root = newParent;
		else if(root == root->parent->right)
			root->parent->right = newParent;
		else
			root->parent->left = newParent;

		newParent->right = root;
		root->parent = newParent;
	}

	return dynamic_cast<RedBlackNode*>(newParent);
}

/**
 * Rotates the tree along the given edge and switches the colors of the nodes.
 * The tree will be rotated away from the child.
 *
 * @param parent a pointer to the parent node of the edge
 * @param child a pointer to the child node of the edge
 */
void RedBlackTree::rotateEdge(RedBlackNode* parent, RedBlackNode* child) {
	int tempColor = 0;

	//Swap the colors as long as this is a valid edge
	if(child->parent == parent) {
		tempColor = child->color;
		child->color = parent->color;
		parent->color = tempColor;
	}

	//Call the appropriate rotate, but do not assume the edge is valid
	if(child == parent->right)
		rotateLeft(parent);
	else if(child == parent->left)
		rotateRight(parent);
}

/**
 * Inserts the given value into the tree and returns whether it succeeds.
 *
 * @param val the key value to insert into the tree
 *
 * @return boolean value for whether the value was successfully inserted
 * 		0 is failure, 1 is success
 */
int RedBlackTree::insertVal(Int val) {
	int success = 0;

	RedBlackNode* node = makeNode(val, RED);

	if(node) {
		insertNode(node);
		success = 1;
	}

	return success;
}

/**
 * Inserts the given node into the tree.
 * Uses a standard binary tree insertion to enter the node as red, then fixes
 * the tree to maintain the red black tree properties.
 *
 * @param node a pointer to the node to be inserted
 */
void RedBlackTree::insertNode(RedBlackNode* node) {
	RedBlackNode* parent = 0;

	BinaryTree::insertNode(node);
	parent = dynamic_cast<RedBlackNode*>(node->parent);
	if(parent == 0)
		node->color = BLACK;
	else if(parent->color == RED)
		insertFixup(parent, node);
}


void RedBlackTree::insertFixup(RedBlackNode* parent, RedBlackNode* error) {
	//Fixup is needed when parent is red
	RedBlackNode* grandparent = 0;
	RedBlackNode* uncle = 0;

	grandparent = dynamic_cast<RedBlackNode*>(parent->parent);
	if(parent == grandparent->left)
		uncle = dynamic_cast<RedBlackNode*>(grandparent->right);
	else
		uncle = dynamic_cast<RedBlackNode*>(grandparent->left);

	//If the uncle is red then pull a black down from the grandparent
	//If the grandparent is the root, leave it to black and stop
	//Otherwise, change it to red and move up the tree
	//This is case 1
	while(uncle && uncle->color == RED) {
		parent->color = BLACK;
		uncle->color = BLACK;

		if(grandparent != _root) {
			grandparent->color = RED;

			//Update the family pointers
			error = grandparent;
			parent = dynamic_cast<RedBlackNode*>(error->parent);
			grandparent = dynamic_cast<RedBlackNode*>(parent->parent);
			if(grandparent) {
				if(parent == grandparent->left)
					uncle = dynamic_cast<RedBlackNode*>(grandparent->right);
				else
					uncle = dynamic_cast<RedBlackNode*>(grandparent->left);
			}
			else
				uncle = 0;
		}
	}

	//If the parent is still red, more fixing is needed
	if(parent->color == RED) {
		//If the error node is close to the uncle, rotate the parent away from the uncle
		//This is case 2
		if((parent->right == error && grandparent->right == uncle) ||
				(parent->left == error && grandparent->left == uncle)) {
			rotateEdge(parent, error);
			RedBlackNode* temp = parent;
			parent = error;
			error = temp;
		}

		//If the error node is far from the uncle, rotate the grandparent towards the uncle
		//This is case 3
		rotateEdge(grandparent, parent);
	}
}

/**
 * Deletes the given key value from the tree and returns whether it was found.
 *
 * @param val the key value of the node to delete
 *
 * @return boolean value for whether a node was found and deleted
 * 		0 is failure, 1 is success
 */
int RedBlackTree::deleteVal(Int val) {
	int success = 0;
	RedBlackNode* node = dynamic_cast<RedBlackNode*>(search(val));
	RedBlackNode* removed = 0;
	RedBlackNode* error = 0;

	if(node) {
		removed = dynamic_cast<RedBlackNode*>(BinaryTree::deleteNode(node));

		if(_root && removed->color == BLACK) {
			//There error node is whichever node replaced the removed node
			if(removed->left)
				error = dynamic_cast<RedBlackNode*>(removed->left);
			else
				error = dynamic_cast<RedBlackNode*>(removed->right);
			//Add the removed node's color to the error node
			if(error)
				error->color += 1;
			deleteFixup(dynamic_cast<RedBlackNode*>(removed->parent), error);
		}

		success = 1;
	}

	return success;
}

void RedBlackTree::deleteFixup(RedBlackNode* parent, RedBlackNode* error) {
	RedBlackNode* sibling = 0;
	RedBlackNode* far = 0;
	RedBlackNode* close = 0;

	if(error == _root)
		error->color = BLACK;

	else {

		//Find the sibling
		if(parent->left == error)
			sibling = dynamic_cast<RedBlackNode*>(parent->right);
		else
			sibling = dynamic_cast<RedBlackNode*>(parent->left);

		//If the sibling is red then rotate towards the error node
		//This is case 1
		if(sibling->color == RED) {
			rotateEdge(parent, sibling);
			if(parent->left == error)
				sibling = dynamic_cast<RedBlackNode*>(parent->right);
			else
				sibling = dynamic_cast<RedBlackNode*>(parent->left);
		}

		//If the sibling is black and its children are black then pull a black up one level
		//If the parent becomes double black, move up the tree
		//If the parent is the root, set it to black and stop
		//This is case 2
		while(sibling->color == BLACK &&
				(!sibling->left || dynamic_cast<RedBlackNode*>(sibling->left)->color == BLACK) &&
				(!sibling->right || dynamic_cast<RedBlackNode*>(sibling->right)->color == BLACK)) {
			parent->color++;
			sibling->color--;
			if(error)
				error->color--;

			//If the parent is the root, set it to black and stop
			if(parent == _root)
				parent->color = BLACK;

			//Otherwise, move up one level and change family pointers
			else if(parent->color == BLACK_BLACK) {
				error = parent;
				parent = dynamic_cast<RedBlackNode*>(error->parent);
				if(error == parent->left)
					sibling = dynamic_cast<RedBlackNode*>(parent->right);
				else
					sibling = dynamic_cast<RedBlackNode*>(parent->left);
			}
		}

		//The sibling is black and one or more children is red
		//Find the near and far children
		if(error == parent->left) {
			far = dynamic_cast<RedBlackNode*>(sibling->right);
			close = dynamic_cast<RedBlackNode*>(sibling->left);
		}
		else {
			far = dynamic_cast<RedBlackNode*>(sibling->left);
			close = dynamic_cast<RedBlackNode*>(sibling->right);
		}

		//If the sibling is black and its farther child is black then rotate
		//the sibling towards the far child
		//Closer child can be assumed red due to case 2 not firing
		//This is case 3
		if(sibling->color == BLACK && (!far || far->color == BLACK)) {
			rotateEdge(sibling, close);
			sibling = close;
			//Update the near and far children
			if(error == parent->left) {
				far = dynamic_cast<RedBlackNode*>(sibling->right);
				close = dynamic_cast<RedBlackNode*>(sibling->left);
			}
			else {
				far = dynamic_cast<RedBlackNode*>(sibling->left);
				close = dynamic_cast<RedBlackNode*>(sibling->right);
			}
		}

		//If the sibling is black and its far child is red then change the
		//far child black and rotate the parent towards the error
		//The issue is now resolved
		//This is case 4
		if(sibling->color == BLACK && (!close || close->color == BLACK)) {
			far->color = BLACK;
			rotateEdge(parent, sibling);
		}
	}
}
