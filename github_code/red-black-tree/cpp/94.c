// Created by Buwenjie
#pragma once

// 红黑树的性质
// 1、每个节点是红色或黑色
// 2、根节点是黑色
// 3、叶节点都是NIL，且都是黑色
// 4、如果一个节点是红色，则它的2个子节点都是黑色
// 5、每个节点，到它后代叶节点的简单路径上，黑色节点数目相同

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
		// 如果node没有左孩子，则用右孩子代替node的位置
		if (node->mLeft == &mNil) {
			x = node->mRight;
			transplant(node, node->mRight);
		}
		// 如果node没有右孩子，则用左孩子代替node的位置
		else if (node->mRight == &mNil) {
			x = node->mLeft;
			transplant(node, node->mLeft);
		}
		// 如果有2个孩子
		else {
			// node的后继y（y一定在node的右子树中，且y是右子树的最小值，所以y肯定没有左孩子）
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

	// 中序遍历
	void inorderWalk(RedBlackTreeNode* node, std::vector<int>& v) {
		if (node == &mNil) {
			return;
		}
		inorderWalk(node->mLeft, v);
		v.push_back(node->mValue);
		inorderWalk(node->mRight, v);
	}

	// 最小值
	RedBlackTreeNode* minimum(RedBlackTreeNode* p) {
		while (p->mLeft != &mNil) {
			p = p->mLeft;
		}
		return p;
	}

	// 最大值
	RedBlackTreeNode* maximum(RedBlackTreeNode* p) {
		while (p->mRight != &mNil) {
			p = p->mRight;
		}
		return p;
	}

	// 前驱
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

	// 后继
	RedBlackTreeNode* successor(RedBlackTreeNode* node) {
		if (node->mRight != &mNil) {
			return minimum(node->mRight);
		}
		// node没有右子树，说明在当前子树中，node是最大值，这时需要沿着parent向上找
		// 直到node是parent的左孩子，这时parent就是后继
		// 设最终的结果为R，因为R的右子树都大于R，R的左子树都小于R，且node为当前子树的最大值
		// 所以当前子树的根节点是R的左孩子
		RedBlackTreeNode* parent = node->mParent;
		while (parent != &mNil && node == parent->mRight) {
			node = parent;
			parent = node->mParent;
		}
		return parent;
	}

private:
	// 释放
	void freeNode(RedBlackTreeNode* node) {
		if (node == &mNil) {
			return;
		}
		freeNode(node->mLeft);
		freeNode(node->mRight);
		delete node;
	}

	//       |
	//       x
	//      / \
	//     a   y
	//        / \
	//       b   c
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

	//       |
	//       y
	//      / \
	//     x   c
	//    / \
	//   a   b
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
			// case A: 父节点是祖父节点的左孩子
			if (node->mParent == node->mParent->mParent->mLeft) {
				auto uncle = node->mParent->mParent->mRight;
				// case 1: 叔节点是红色
				// 对父、叔、祖父节点着色，变为与以前相反的颜色
				// 祖父节点处可能会破坏性质，继续检查祖父节点
				if (uncle->mColor == RedBlackTreeNodeColor::RED) {
					node->mParent->mColor = RedBlackTreeNodeColor::BLACK;
					uncle->mColor = RedBlackTreeNodeColor::BLACK;
					node->mParent->mParent->mColor = RedBlackTreeNodeColor::RED;
					node = node->mParent->mParent;
				}
				else {
					// case 2: 叔节点是黑色，且当前节点是右孩子
					// 左旋一次会转化为case 3
					if (node == node->mParent->mRight) {
						node = node->mParent;
						leftRotate(node);
					}
					// case 3: 叔节点是黑色，且当前节点是左孩子
					node->mParent->mColor = RedBlackTreeNodeColor::BLACK;
					node->mParent->mParent->mColor = RedBlackTreeNodeColor::RED;
					rightRotate(node->mParent->mParent);
				}
			}
			// case B: 父节点是祖父节点的右孩子
			// 与case A做类似的操作，把单词"right"和"left"交换一下就可以
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
		// 根节点是黑色
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
			// case A: node是父节点的左孩子
			if (node == node->mParent->mLeft) {
				RedBlackTreeNode* brother = node->mParent->mRight;
				// case 1: 兄弟节点为红色
				if (brother->mColor == RedBlackTreeNodeColor::RED) {
					brother->mColor = RedBlackTreeNodeColor::BLACK;
					node->mParent->mColor = RedBlackTreeNodeColor::RED;
					leftRotate(node->mParent);
					brother = node->mParent->mRight;
				}
				// case 2: 兄弟节点是黑色，且兄弟节点的2个子节点都是黑色
				if (brother->mLeft->mColor == RedBlackTreeNodeColor::BLACK && brother->mRight->mColor == RedBlackTreeNodeColor::BLACK) {
					brother->mColor = RedBlackTreeNodeColor::RED;
					node = node->mParent;
				}
				// case 3: 兄弟节点是黑色，且兄弟节点的左孩子是红色，右孩子是黑色
				else {
					if (brother->mRight->mColor == RedBlackTreeNodeColor::BLACK) {
						brother->mLeft->mColor = RedBlackTreeNodeColor::BLACK;
						brother->mColor = RedBlackTreeNodeColor::RED;
						rightRotate(brother);
						brother = node->mParent->mRight;
					}
					// case 4: 兄弟节点是黑色，且兄弟节点的右孩子是红色
					brother->mColor = node->mParent->mColor;
					node->mParent->mColor = RedBlackTreeNodeColor::BLACK;
					brother->mRight->mColor = RedBlackTreeNodeColor::BLACK;
					leftRotate(node->mParent);
					node = mRoot;
				}
			}
			// case B: node是父节点的右孩子
			// 与case A做类似的操作，把单词"right"和"left"交换一下就可以
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
	// inorder
	std::vector<int> res;
	tree.inorderWalk(tree.root(), res);
	for (auto v : res) {
		printf("%d ", v);
	}
	printf("\n");
	// search
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
	// min max
	printf("minimum %d\n", tree.minimum(tree.root())->mValue);
	printf("maximum %d\n", tree.maximum(tree.root())->mValue);
	// predecessor
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
	// successor
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
	// remove
	for (auto v : data) {
		tree.remove(tree.search(v));
		res.clear();
		tree.inorderWalk(tree.root(), res);
		for (auto v : res) {
			printf("%d ", v);
		}
		printf("\n");
		//tree.insert(v);
	}
}
