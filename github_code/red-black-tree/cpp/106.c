#include "BinarySearchTree.h"
#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>

using namespace std;

enum Color {Red,Black};

struct RedBlackTreeNode : public TreeNode
{
	Color color;
	RedBlackTreeNode(int key,int val,Color color):TreeNode(key,val),color(color)
	{	
	}
};

class RedBlackBST : public BinarySearchTree
{
	// Assuming that node is red and both node.left and node.left.left
    // are black, make node.left or one of its children red.
	TreeNode* MoveRedLeft(TreeNode* node)
	{
		FlipColors(node);
		if(IsRed(node->right->left))
		{
			node->right = RightRotate(node->right);
			node = LeftRotate(node);
			FlipColors(node);	
		}
		return node;
	}
	
	TreeNode* MoveRedRight(TreeNode* node)
	{
		FlipColors(node);
		if(IsRed(node->left->left))
		{
			node = RightRotate(node);
			FlipColors(node);
		}
		return node;
	}
	
	//restore red/black tree inviriant
	TreeNode* Balance(TreeNode* node)
	{
		if(IsRed(node->right))
			node = LeftRotate(node);
		if(IsRed(node->left) && IsRed(node->left->left))
			node = RightRotate(node);
		if(IsRed(node->left) && IsRed(node->right))
			FlipColors(node);
		return node;
	}
		
	TreeNode* DeleteHelper(TreeNode* node,int key)
	{
		if(key < node->key)
		{
			if(IsRed(node->left) == false && IsRed(node->left->left) == false)
			{
				node = MoveRedLeft(node);
			}
			node->left = DeleteHelper(node->left,key);
		}
		else
		{
			if(IsRed(node->left))
			{
				node = RightRotate(node);
			}
			if(node->key == key && node->right == 0)
			{
				delete node;
				return 0;
			}
			
			if(IsRed(node->right) == false && IsRed(node->right->left) == false)
			{
				node = MoveRedRight(node);
			}
			
			if(node->key == key)
			{
				TreeNode* min = MinHelper(node->right);
				node->key = min->key;
				node->val = min->val;
				node->right = DeleteMinHelper(node->right);
			}
			else
			{
				node->right = DeleteHelper(node->right,key);
			}
		}
		
		return Balance(node);
	}
	
	TreeNode* DeleteMinHelper(TreeNode* node)
	{
		if(node->left == 0)
		{
			delete node;
			return 0;
		}
		
		if(IsRed(node->left) == false && IsRed(node->left->left) == false)
		{
			node = MoveRedLeft(node);
		}
		
		node->left = DeleteMinHelper(node->left);
		
		return Balance(node);
		
	}
	
	TreeNode* InsertHelper(TreeNode* node,int key,int val)
	{
		if(node == 0)
		{
			size++;
			return new RedBlackTreeNode(key,val,Red);
		}
		
		if(node->key == key)
		{
			node->val = val;
		}
		else if(node->key > key)
		{
			node->left = InsertHelper(node->left,key,val);
		}
		else
		{
			node->right = InsertHelper(node->right,key,val);
		}
		
		//fix up right-leaning links
		if(IsRed(node->right) && IsRed(node->left) == false)
		{
			node = LeftRotate(node);
		}
		//two reds in a row
		if(IsRed(node->left) && IsRed(node->left->left))
		{
			node = RightRotate(node);
		}
		if(IsRed(node->left) && IsRed(node->right))
		{
			FlipColors(node);
		}
		
		return node;
	}
	
	void FlipColors(TreeNode* node)
	{
		//assert(IsRed(node) == false && IsRed(node->left) && IsRed(node->right));
		((RedBlackTreeNode*)node)->color = ((RedBlackTreeNode*)node)->color == Red? Black:Red;
		((RedBlackTreeNode*)(node->left))->color = ((RedBlackTreeNode*)(node->left))->color == Red? Black:Red;
		((RedBlackTreeNode*)(node->right))->color = ((RedBlackTreeNode*)(node->right))->color == Red? Black:Red;
	}
	
	TreeNode* LeftRotate(TreeNode* node)
	{
		assert(node != 0 && IsRed(node->right));
		RedBlackTreeNode* tmp = (RedBlackTreeNode*)(node->right);
		node->right = tmp->left;
		tmp->left = node;
		tmp->color = ((RedBlackTreeNode*)(tmp->left))->color;
		((RedBlackTreeNode*)(tmp->left))->color = Red;
		return tmp;
	}
	
	TreeNode* RightRotate(TreeNode* node)
	{
		assert(node != 0 && IsRed(node->left));
		RedBlackTreeNode* tmp = (RedBlackTreeNode*)(node->left);
		node->left = tmp->right;
		tmp->right = node;
		tmp->color = ((RedBlackTreeNode*)(tmp->right))->color;
		((RedBlackTreeNode*)(tmp->right))->color = Red;
		return tmp;
	}
	
	bool IsRed(TreeNode* node)
	{
		return (node == 0)? false : ((RedBlackTreeNode*)node)->color == Red;
	}
	
public:
	
	RedBlackBST():BinarySearchTree(){}
			
	void Delete(int key)
	{
		if(Contain(key) == false)
		{
			cout << "key: " << key << " doesn't exist" << endl;
			return;
		}
		
		if(IsRed(mRoot->left) == false && IsRed(mRoot->right) == false)
		{
			((RedBlackTreeNode*)mRoot)->color = Red;
		}
		
		mRoot = DeleteHelper(mRoot,key);
		size--;
		if(IsEmpty() == false)
		{
			((RedBlackTreeNode*)mRoot)->color = Black;
		}
	}
	
	void Insert(int key,int val = 0)
	{
		mRoot = InsertHelper(mRoot,key,val);
		((RedBlackTreeNode*)mRoot)->color = Black;
	}
			
};

int main()
{
	int n = 10;
	vector<int> keys;
	
	for(int i = 0; i < n; i++)
	{
		keys.push_back(rand() % n);
	}
		
	RedBlackBST tree;

	for(int i = 0; i < keys.size(); i++)
	{
		tree.Insert(keys[i]);
	}
	
	tree.PrintTreeInOrder();
	
	
	for(int i = 0; i < keys.size(); i++)
	{
		cout << "deleting " << keys[i] << endl;
		tree.Delete(keys[i]);
	}
	
	for(int i = 0; i < keys.size(); i++)
	{
		tree.Contain(i);
	}
	
	
	/*
	int t0 = time(0);
	int t1 = time(0);
	cout << "searching a red/black tree took " << t1 - t0 << " seconds" << endl;
		
		
	*/
}