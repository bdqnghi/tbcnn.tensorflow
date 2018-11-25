
#pragma once








#include <vector>

enum class RedBlackTreeNodeColor {
	RED,
	BLACK
};

class RedBlackTreeNode {
public:
	RedBlackTreeNode(int value, RedBlackTreeNodeColor color, 
		RedBlackTreeNode* parent, RedBlackTreeNode* left, RedBlackTreeNode* right)
	: mValue(value)
	, mColor(color)
	, mParent(parent)
	, mLeft(left)
	, mRight(right) {
	}
	int mValue;
	RedBlackTreeNodeColor mColor;
	RedBlackTreeNode* mParent;
	RedBlackTreeNode* mLeft;
	RedBlackTreeNode* mRight;
};

class RedBlackTree {
public:
	RedBlackTree()
	: mNil(0, RedBlackTreeNodeColor::BLACK, nullptr, nullptr, nullptr)
	, mRoot(&mNil) {
	}

	~RedBlackTree() {
		freeNode(mRoot);
	}

	RedBlackTreeNode* root() {
		return mRoot;
	}

	RedBlackTreeNode* nil() {
		return &mNil;
	}

	void insert(int value) {
		if (mRoot == &mNil) {
			mRoot = new RedBlackTreeNode(value, RedBlackTreeNodeColor::BLACK, &mNil, &mNil, &mNil);
			return;
		}
		RedBlackTreeNode* p = mRoot;
		RedBlackTreeNode* n = new RedBlackTreeNode(value, RedBlackTreeNodeColor::RED, p, &mNil, &mNil);
		while (true) {
			if (value <= p->mValue) {
				if (p->mLeft == &mNil) {
					p->mLeft = n;
					n->mParent = p;
					break;
				}
				else {
					p = p->mLeft;
				}
			}
			else {
				if (p->mRight == &mNil) {
					p->mRight = n;
					n->mParent = p;
					break;
				}
				else {
					p = p->mRight;
				}
			}
		}
		insertFixup(n);
	}

	void remove(RedBlackTreeNode* node) {
		RedBlackTreeNode* y = node;
		auto yColor = y->mColor;
		RedBlackTreeNode* x = &mNil;
		
		if (node->mLeft == &mNil) {
			x = node->mRight;
			transplant(node, node->mRight);
		}
		
		else if (node->mRight == &mNil) {
			x = node->mLeft;
			transplant(node, node->mLeft);
		}
		
		else {
			
			y = successor(node);
			yColor = y->mColor;
			x = y->mRight;
			if (y->mParent == node) {
				x->mParent = y;
			}
			else {
				transplant(y, y->mRight);
				y->mRight = node->mRight;
				y->mRight->mParent = y;
			}
			transplant(node, y);
			y->mLeft = node->mLeft;
			y->mLeft->mParent = y;
			y->mColor = node->mColor;
		}
		if (yColor == RedBlackTreeNodeColor::BLACK) {
			removeFixup(x);
		}
		delete node;
	}

	RedBlackTreeNode* search(int v) {
		RedBlackTreeNode* p = mRoot;
		while (p != &mNil && p->mValue != v) {
			if (v < p->mValue) {
				p = p->mLeft;
			}
			else {
				p = p->mRight;
			}
		}
		return p;
	}

	
	void inorderWalk(RedBlackTreeNode* node, std::vector<int>& v) {
		if (node == &mNil) {
			return;
		}
		inorderWalk(node->mLeft, v);
		v.push_back(node->mValue);
		inorderWalk(node->mRight, v);
	}

	
	RedBlackTreeNode* minimum(RedBlackTreeNode* p) {
		while (p->mLeft != &mNil) {
			p = p->mLeft;
		}
		return p;
	}

	
	RedBlackTreeNode* maximum(RedBlackTreeNode* p) {
		while (p->mRight != &mNil) {
			p = p->mRight;
		}
		return p;
	}

	
	RedBlackTreeNode* predecessor(RedBlackTreeNode* node) {
		if (node->mLeft != &mNil) {
			return maximum(node->mLeft);
		}
		RedBlackTreeNode* parent = node->mParent;
		while (parent != &mNil && node == parent->mLeft) {
			node = parent;
			parent = node->mParent;
		}
		return parent;
	}

	
	RedBlackTreeNode* successor(RedBlackTreeNode* node) {
		if (node->mRight != &mNil) {
			return minimum(node->mRight);
		}
		
		
		
		
		RedBlackTreeNode* parent = node->mParent;
		while (parent != &mNil && node == parent->mRight) {
			node = parent;
			parent = node->mParent;
		}
		return parent;
	}

private:
	
	void freeNode(RedBlackTreeNode* node) {
		if (node == &mNil) {
			return;
		}
		freeNode(node->mLeft);
		freeNode(node->mRight);
		delete node;
	}

	
	
	
	
	
	
	void leftRotate(RedBlackTreeNode* x) {
		RedBlackTreeNode* y = x->mRight;
		x->mRight = y->mLeft;
		if (y->mLeft != &mNil) {
			y->mLeft->mParent = x;
		}
		y->mParent = x->mParent;
		if (x->mParent == &mNil) {
			mRoot = y;
		}
		else if (x == x->mParent->mLeft) {
			x->mParent->mLeft = y;
		}
		else {
			x->mParent->mRight = y;
		}
		y->mLeft = x;
		x->mParent = y;
	}

	
	
	
	
	
	
	void rightRotate(RedBlackTreeNode* y) {
		RedBlackTreeNode* x = y->mLeft;
		y->mLeft = x->mRight;
		if (x->mRight != &mNil) {
			x->mRight->mParent = y;
		}
		x->mParent = y->mParent;
		if (y->mParent == &mNil) {
			mRoot = x;
		}
		else if (y == y->mParent->mLeft) {
			y->mParent->mLeft = x;
		}
		else {
			y->mParent->mRight = x;
		}
		x->mRight = y;
		y->mParent = x;
	}

	void insertFixup(RedBlackTreeNode* node) {
		while (node->mParent->mColor == RedBlackTreeNodeColor::RED) {
			
			if (node->mParent == node->mParent->mParent->mLeft) {
				auto uncle = node->mParent->mParent->mRight;
				
				
				
				if (uncle->mColor == RedBlackTreeNodeColor::RED) {
					node->mParent->mColor = RedBlackTreeNodeColor::BLACK;
					uncle->mColor = RedBlackTreeNodeColor::BLACK;
					node->mParent->mParent->mColor = RedBlackTreeNodeColor::RED;
					node = node->mParent->mParent;
				}
				else {
					
					
					if (node == node->mParent->mRight) {
						node = node->mParent;
						leftRotate(node);
					}
					
					node->mParent->mColor = RedBlackTreeNodeColor::BLACK;
					node->mParent->mParent->mColor = RedBlackTreeNodeColor::RED;
					rightRotate(node->mParent->mParent);
				}
			}
			
			
			else {
				auto uncle = node->mParent->mParent->mLeft;
				if (uncle->mColor == RedBlackTreeNodeColor::RED) {
					node->mParent->mColor = RedBlackTreeNodeColor::BLACK;
					uncle->mColor = RedBlackTreeNodeColor::BLACK;
					node->mParent->mParent->mColor = RedBlackTreeNodeColor::RED;
					node = node->mParent->mParent;
				}
				else {
					if (node == node->mParent->mLeft) {
						node = node->mParent;
						rightRotate(node);
					}
					node->mParent->mColor = RedBlackTreeNodeColor::BLACK;
					node->mParent->mParent->mColor = RedBlackTreeNodeColor::RED;
					leftRotate(node->mParent->mParent);
				}
			}
		}
		
		mRoot->mColor = RedBlackTreeNodeColor::BLACK;
	}

	void transplant(RedBlackTreeNode* src, RedBlackTreeNode* des) {
		if (src->mParent == &mNil) {
			mRoot = des;
		}
		else {
			if (src == src->mParent->mLeft) {
				src->mParent->mLeft = des;
			}
			else {
				src->mParent->mRight = des;
			}
		}
		des->mParent = src->mParent;
	}

	void removeFixup(RedBlackTreeNode* node) {
		while (node != mRoot && node->mColor == RedBlackTreeNodeColor::BLACK) {
			
			if (node == node->mParent->mLeft) {
				RedBlackTreeNode* brother = node->mParent->mRight;
				
				if (brother->mColor == RedBlackTreeNodeColor::RED) {
					brother->mColor = RedBlackTreeNodeColor::BLACK;
					node->mParent->mColor = RedBlackTreeNodeColor::RED;
					leftRotate(node->mParent);
					brother = node->mParent->mRight;
				}
				
				if (brother->mLeft->mColor == RedBlackTreeNodeColor::BLACK && brother->mRight->mColor == RedBlackTreeNodeColor::BLACK) {
					brother->mColor = RedBlackTreeNodeColor::RED;
					node = node->mParent;
				}
				
				else {
					if (brother->mRight->mColor == RedBlackTreeNodeColor::BLACK) {
						brother->mLeft->mColor = RedBlackTreeNodeColor::BLACK;
						brother->mColor = RedBlackTreeNodeColor::RED;
						rightRotate(brother);
						brother = node->mParent->mRight;
					}
					
					brother->mColor = node->mParent->mColor;
					node->mParent->mColor = RedBlackTreeNodeColor::BLACK;
					brother->mRight->mColor = RedBlackTreeNodeColor::BLACK;
					leftRotate(node->mParent);
					node = mRoot;
				}
			}
			
			
			else {
				RedBlackTreeNode* brother = node->mParent->mLeft;
				if (brother->mColor == RedBlackTreeNodeColor::RED) {
					brother->mColor = RedBlackTreeNodeColor::BLACK;
					node->mParent->mColor = RedBlackTreeNodeColor::RED;
					rightRotate(node->mParent);
					brother = node->mParent->mLeft;
				}
				if (brother->mRight->mColor == RedBlackTreeNodeColor::BLACK && brother->mLeft->mColor == RedBlackTreeNodeColor::BLACK) {
					brother->mColor = RedBlackTreeNodeColor::RED;
					node = node->mParent;
				}
				else {
					if (brother->mLeft->mColor == RedBlackTreeNodeColor::BLACK) {
						brother->mRight->mColor = RedBlackTreeNodeColor::BLACK;
						brother->mColor = RedBlackTreeNodeColor::RED;
						leftRotate(brother);
						brother = node->mParent->mLeft;
					}
					brother->mColor = node->mParent->mColor;
					node->mParent->mColor = RedBlackTreeNodeColor::BLACK;
					brother->mLeft->mColor = RedBlackTreeNodeColor::BLACK;
					rightRotate(node->mParent);
					node = mRoot;
				}
			}
		}
		node->mColor = RedBlackTreeNodeColor::BLACK;
	}

	RedBlackTreeNode mNil;
	RedBlackTreeNode* mRoot;
};

#include <stdio.h>
void test_RedBlackTree() {
	std::vector<int> data = { 3, 1, 5, 7, 6, 2, 9, 4, 8 };
	RedBlackTree tree;
	for (auto v : data) {
		tree.insert(v);
	}
	
	std::vector<int> res;
	tree.inorderWalk(tree.root(), res);
	for (auto v : res) {
		printf("%d ", v);
	}
	printf("\n");
	
	std::vector<int> search = { 7, 10, 3 };
	for (auto v : search) {
		auto p = tree.search(v);
		if (p != tree.nil()) {
			printf("%d found\n", v);
		}
		else {
			printf("%d not found\n", v);
		}
	}
	
	printf("minimum %d\n", tree.minimum(tree.root())->mValue);
	printf("maximum %d\n", tree.maximum(tree.root())->mValue);
	
	printf("predecessor:\n");
	for (auto v : data) {
		auto p = tree.predecessor(tree.search(v));
		if (p == tree.nil()) {
			printf("%d null\n", v);
		}
		else {
			printf("%d %d\n", v, p->mValue);
		}
	}
	
	printf("successor:\n");
	for (auto v : data) {
		auto p = tree.successor(tree.search(v));
		if (p == tree.nil()) {
			printf("%d null\n", v);
		}
		else {
			printf("%d %d\n", v, p->mValue);
		}
	}
	
	for (auto v : data) {
		tree.remove(tree.search(v));
		res.clear();
		tree.inorderWalk(tree.root(), res);
		for (auto v : res) {
			printf("%d ", v);
		}
		printf("\n");
		
	}
}
