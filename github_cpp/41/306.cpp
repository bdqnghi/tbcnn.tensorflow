#include"red-black-tree.h"


TreeNode* redBlackTree::nil = new TreeNode();

void redBlackTree::__LeftRotate(TreeNode*  x)
{
	TreeNode* y = x->right;
	x->right = y->left;
	if (y->left != nil)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == nil)
		_root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

void redBlackTree::__RightRotate(TreeNode*  x)
{
	TreeNode* y = x->left;
	x->left = y->right;
	if (y->right != nil)
		y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == nil)
		_root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->right = x;
	x->parent = y;
}

void  redBlackTree::__rb_insert_fix(TreeNode*  z)
{
	while (z->parent->color == TreeNode::red)
	{
		if (z->parent == z->parent->parent->left)
		{
			TreeNode* y = z->parent->parent->right;
			if (y->color == TreeNode::red)
			{
				z->parent->color = TreeNode::black;
				y->color = TreeNode::black;
				z->parent->parent->color = TreeNode::red;
				z = z->parent->parent;
			}
			else
			{
				if (z == z->parent->right)
				{
					z = z->parent;
					__LeftRotate(z);
				}
				z->parent->color = TreeNode::black;
				z->parent->parent->color = TreeNode::red;
				__RightRotate(z->parent->parent);
			}
		}
		else
		{
			TreeNode* y = z->parent->parent->left;
			if (y->color == TreeNode::red)
			{
				z->parent->color = TreeNode::black;
				y->color = TreeNode::black;
				z->parent->parent->color = TreeNode::red;
				z = z->parent->parent;
			}
			else if (z == z->parent->left)
			{
				z = z->parent;
				__RightRotate(z);
			}
			z->parent->color = TreeNode::black;
			z->parent->parent->color = TreeNode::red;
			__RightRotate(z->parent->parent);
		}	
	}
	_root->color = TreeNode::black;
}

void  redBlackTree::rb_insert(TreeNode*  z)
{
	TreeNode* y = const_cast<TreeNode*>(nil);
	TreeNode* x = _root;
	while (x != nil)
	{
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if (y == nil)
		_root = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;
	z->left = nil;
	z->right = nil;
	z->color = TreeNode::red;
	__rb_insert_fix(z);
}

void redBlackTree::__rb_transplant(TreeNode* u, TreeNode* v)
{
	if (u->parent == nil)
		_root = v;
	else if (u = u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	v->parent = u->parent;
}

void redBlackTree::__rb_delete_fix(TreeNode*  x)
{
	while (x != _root&&x->color == TreeNode::black)
	{
		if (x == x->parent->left)
		{
			TreeNode* w = x->parent->right;
			if (w->color == TreeNode::red)
			{
				w->color = TreeNode::black;
				x->parent->color = TreeNode::red;
				__LeftRotate(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == TreeNode::black&&w->right->color == TreeNode::black)
			{
				w->color = TreeNode::red;
				x = x->parent;
			}
			else
			{
				if (w->right->color == TreeNode::black)
				{
					w->left->color = TreeNode::black;
					w->color = TreeNode::red;
					__RightRotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = TreeNode::black;
				w->right->color = TreeNode::black;
				__LeftRotate(x->parent);
				x = _root;
			}
		}
		else
		{
			TreeNode* w = x->parent->left;
			if (w->color == TreeNode::red)
			{
				w->color = TreeNode::black;
				x->parent->color = TreeNode::red;
				__RightRotate(x->parent);
				w = x->parent->left;
			}
			if (w->left->color == TreeNode::black&&w->right->color == TreeNode::black)
			{
				w->color = TreeNode::red;
				x = x->parent;
			}
			else
			{
				if (w->left->color == TreeNode::black)
				{
					w->right->color = TreeNode::black;
					w->color = TreeNode::red;
					__LeftRotate(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = TreeNode::black;
				w->right->color = TreeNode::black;
				__RightRotate(x->parent);
				x = _root;
			}
		}
	}
	x->color = TreeNode::black;
}

void redBlackTree::rb_delete(TreeNode*  z)
{
	TreeNode* y = z, *x;
	TreeNode::colors y_original_color = y->color;
	if (z->left == nil)
	{
		x = z->right;
		__rb_transplant(z, z->right);
	}
	else if (z->right == nil)
	{
		x = z->left;
		__rb_transplant(z, z->left);
	}
	else
	{
		y = __tree_minimun(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z)
			x->parent = y;
		else
		{
			__rb_transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		__rb_transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if (y_original_color == TreeNode::black)
		__rb_delete_fix(x);
}

TreeNode*  redBlackTree::__tree_minimun(TreeNode*  z)
{
	TreeNode* x = z;
	while (x->left != nil)
		x = x->left;
	return x;
}
