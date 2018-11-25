

#include"redblacktree.h"
#include"redblacknode.h"

using namespace RedBlack;
using std::bad_alloc;

RedBlackNode* RedBlackTree::makeNode(Int val, int color) {
	RedBlackNode* node;

	try {
		node = new RedBlackNode(val, color);
		
		

	} catch(bad_alloc &ex) {
		node = 0;
	}

	return node;
}

RedBlackTree::RedBlackTree() {
	

}

RedBlackTree::~RedBlackTree() {
	
}


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


void RedBlackTree::rotateEdge(RedBlackNode* parent, RedBlackNode* child) {
	int tempColor = 0;

	
	if(child->parent == parent) {
		tempColor = child->color;
		child->color = parent->color;
		parent->color = tempColor;
	}

	
	if(child == parent->right)
		rotateLeft(parent);
	else if(child == parent->left)
		rotateRight(parent);
}


int RedBlackTree::insertVal(Int val) {
	int success = 0;

	RedBlackNode* node = makeNode(val, RED);

	if(node) {
		insertNode(node);
		success = 1;
	}

	return success;
}


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
	
	RedBlackNode* grandparent = 0;
	RedBlackNode* uncle = 0;

	grandparent = dynamic_cast<RedBlackNode*>(parent->parent);
	if(parent == grandparent->left)
		uncle = dynamic_cast<RedBlackNode*>(grandparent->right);
	else
		uncle = dynamic_cast<RedBlackNode*>(grandparent->left);

	
	
	
	
	while(uncle && uncle->color == RED) {
		parent->color = BLACK;
		uncle->color = BLACK;

		if(grandparent != _root) {
			grandparent->color = RED;

			
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

	
	if(parent->color == RED) {
		
		
		if((parent->right == error && grandparent->right == uncle) ||
				(parent->left == error && grandparent->left == uncle)) {
			rotateEdge(parent, error);
			RedBlackNode* temp = parent;
			parent = error;
			error = temp;
		}

		
		
		rotateEdge(grandparent, parent);
	}
}


int RedBlackTree::deleteVal(Int val) {
	int success = 0;
	RedBlackNode* node = dynamic_cast<RedBlackNode*>(search(val));
	RedBlackNode* removed = 0;
	RedBlackNode* error = 0;

	if(node) {
		removed = dynamic_cast<RedBlackNode*>(BinaryTree::deleteNode(node));

		if(_root && removed->color == BLACK) {
			
			if(removed->left)
				error = dynamic_cast<RedBlackNode*>(removed->left);
			else
				error = dynamic_cast<RedBlackNode*>(removed->right);
			
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

		
		if(parent->left == error)
			sibling = dynamic_cast<RedBlackNode*>(parent->right);
		else
			sibling = dynamic_cast<RedBlackNode*>(parent->left);

		
		
		if(sibling->color == RED) {
			rotateEdge(parent, sibling);
			if(parent->left == error)
				sibling = dynamic_cast<RedBlackNode*>(parent->right);
			else
				sibling = dynamic_cast<RedBlackNode*>(parent->left);
		}

		
		
		
		
		while(sibling->color == BLACK &&
				(!sibling->left || dynamic_cast<RedBlackNode*>(sibling->left)->color == BLACK) &&
				(!sibling->right || dynamic_cast<RedBlackNode*>(sibling->right)->color == BLACK)) {
			parent->color++;
			sibling->color--;
			if(error)
				error->color--;

			
			if(parent == _root)
				parent->color = BLACK;

			
			else if(parent->color == BLACK_BLACK) {
				error = parent;
				parent = dynamic_cast<RedBlackNode*>(error->parent);
				if(error == parent->left)
					sibling = dynamic_cast<RedBlackNode*>(parent->right);
				else
					sibling = dynamic_cast<RedBlackNode*>(parent->left);
			}
		}

		
		
		if(error == parent->left) {
			far = dynamic_cast<RedBlackNode*>(sibling->right);
			close = dynamic_cast<RedBlackNode*>(sibling->left);
		}
		else {
			far = dynamic_cast<RedBlackNode*>(sibling->left);
			close = dynamic_cast<RedBlackNode*>(sibling->right);
		}

		
		
		
		
		if(sibling->color == BLACK && (!far || far->color == BLACK)) {
			rotateEdge(sibling, close);
			sibling = close;
			
			if(error == parent->left) {
				far = dynamic_cast<RedBlackNode*>(sibling->right);
				close = dynamic_cast<RedBlackNode*>(sibling->left);
			}
			else {
				far = dynamic_cast<RedBlackNode*>(sibling->left);
				close = dynamic_cast<RedBlackNode*>(sibling->right);
			}
		}

		
		
		
		
		if(sibling->color == BLACK && (!close || close->color == BLACK)) {
			far->color = BLACK;
			rotateEdge(parent, sibling);
		}
	}
}
