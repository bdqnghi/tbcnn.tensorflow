#include<iostream>
const int rbBlack = 0;
const int rbRed = 1;
class RedBlackTreeNode{
public:
	RedBlackTreeNode() :color(0), left(nullptr), right(nullptr), parent(nullptr), key(0){};
	RedBlackTreeNode(int color) :color(rbBlack){};
	int color;
	int key;
	RedBlackTreeNode *left, *right, *parent;
};
class RedBlackTree{
public:
	typedef RedBlackTreeNode rbtNode;
	typedef rbtNode* rbtPtr;

	rbtPtr root;
	rbtPtr nil;
	RedBlackTree()
	{
		nil = new rbtNode(rbBlack);
		root = nil;
	}
	void insert(rbtPtr z)
	{
		rbtPtr x = root;
		rbtPtr y = nil;
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
			root = z;
		else
		{
			if (z->key < y->key)
				y->left = z;
			else
				y->right = z;
		}
		z->color = rbRed;
		z->left = nil;
		z->right = nil;
		insertFix(z);
	}
	void rbtDelete(rbtPtr z)
	{
		rbtPtr y = z;
		rbtPtr x;
		int yOringnalColor = y->color;
		if (z->left == nil)
		{
			x = z->right;
			transPlant(z, z->right);
		}
		else if (z->right == nil)
		{
			x = z->left;
			transPlant(z, z->left);
		}
		else
		{
			y = mimum(z->right);
			yOringnalColor = y->color;
			x = y->right;
			//if (y->parent != z)
			//{
			//	transPlant(y, x);
			//	y->right = z->right;
			//	z->right->parent = y;
			//}
			//transPlant(z, y);
			//y->left = z->left;
			//z->left->parent = y;
			//y->color = z->color;
			if (y->parent == z)
				x->parent = y;
			else
			{
				transPlant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transPlant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;

		}
		//����������������������ʵ��ɾ���˽���y������ռλ�õĽ��㣬������������y������ռλ�õĽ�������ɫ�Ǻ�ɫ��
		//��ô���н����ĵ�����5���Ӹý��㵽����������������·���Ͼ����ĺ�ɫ������Ŀ��ͬ����Ϊɾ�����Ǻ�ɫ���㣬����������Ŀ��û����
		//��Ȼy������ռ��λ���Ǻ�ɫ�ģ���ôy�Ͳ������Ǹ�����
		if (yOringnalColor == rbBlack)
			rbtDeleteFix(x);
	}
	void orderPrint(rbtPtr node)
	{
		//if (node->left != nil)
		//	orderPrint(node->left);
		//std::cout << node->key << ',';
		//if (node->right != nil)
		//	orderPrint(node->right);
		if (node != nil)
		{
			orderPrint(node->left);
			std::cout << node->key << ',';
			orderPrint(node->right);
		}
	}
	void show()
	{
		orderPrint(root);
	}
private:
	void leftRotation(rbtPtr x)
	{
		rbtPtr y = x->right;
		x->right = y->left;
		if (y->left != nil)
			y->left->parent = x;
		y->parent = x->parent;
		if (x->parent == nil)
			root = y;
		else if (x == x->parent->left)
			x->parent->left=y;
		else
			x->parent->right=y;
		y->left = x;
		x->parent = y;
	}
	void rightRotation(rbtPtr x)
	{
		rbtPtr y = x->left;
		x->left = y->right;
		if (y->right != nil)
			y->right->parent = x;
		y->parent = x->parent;
		if (x->parent == nil)
			root = y;
		else if (x == x->parent->left)
			x->parent->left=y;
		else
			x->parent->right=y;
		y->right = x;
		x->parent = y;
	}
	void insertFix(rbtPtr z)
	{
		while (z->parent->color == rbRed)
		{
			if (z->parent == z->parent->parent->left)
			{
				if (z->parent->parent->right->color == rbRed)
				{
					z->parent->color = rbBlack;
					z->parent->parent->color = rbRed;
					z->parent->parent->right->color = rbBlack;
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->right)
					{
						z = z->parent;
						leftRotation(z);
					}
					z->parent->color = rbBlack;
					z->parent->parent->color = rbRed;
					rightRotation(z->parent->parent);
				}
			}
			else
			{
				if (z->parent->parent->left->color == rbRed)
				{
					z->parent->color = rbBlack;
					z->parent->parent->color = rbRed;
					z->parent->parent->left->color = rbBlack;
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->left)
					{
						z = z->parent;
						rightRotation(z);
					}
					z->parent->color = rbBlack;
					z->parent->parent->color = rbRed;
					leftRotation(z->parent->parent);
				}
			}
		}
		root->color = rbBlack;
	}
	void rbtDeleteFix(rbtPtr x)
	{
		while (x != root&&x->color == rbBlack)
		{
			//x��������
			if (x == x->parent->left)
			{
				rbtPtr w = x->parent->right;//w:x�常����
				if (w->color == rbRed)
				{
					x->parent->color = rbRed;
					w->color = rbBlack;
					leftRotation(x->parent);
					w = x->parent->right;
				}
				if (w->right->color == rbBlack&&w->left->color == rbBlack)
				{
					w->color = rbRed;
					x = x->parent;
				}
				else
				{
					if (w->right->color == rbBlack)
					{
						w->color = rbRed;
						w->left->color = rbBlack;
						rightRotation(w);
						w = x->parent->right;
					}
					w->right->color = rbBlack;
					w->color = x->parent->color;
					x->parent->color = rbBlack;
					leftRotation(x->parent);
					x = root;
				}
				
			}
			else
			{
				//x�����ӽ���
				rbtPtr w = x->parent->left;
				if (w->color == rbRed)
				{
					w->color = rbBlack;
					x->parent->color = rbRed;
					rightRotation(x->parent);
					w = x->parent->left;
				}
				if (w->left->color == rbBlack&&w->right->color == rbBlack)
				{
					w->color = rbRed;
					x = x->parent;
				}
				else
				{
					if (w->left->color == rbBlack)
					{
						w->color = rbRed;
						w->right->color = rbBlack;
						leftRotation(w);
						w = x->parent->left;
					}
					w->left->color = rbBlack;
					w->color = x->parent->color;
					x->parent->color = rbBlack;
					rightRotation(x->parent);
					x = root;
				}
			}
		}
		x->color = rbBlack;
	}
	void transPlant(rbtPtr u, rbtPtr v)
	{
		if (u->parent == nil)
			root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}
	rbtPtr mimum(rbtPtr node)
	{
		while (node->left != nil)
			node = node->left;
		return node;
	}
};

int main()
{
	RedBlackTree rbtree;
	int a[14] = { 7, 11, 18, 9, 14, 19, 12, 17, 22, 20, 4 , 6, 3, 2 };
	RedBlackTreeNode *b[14];
	for (int i=0; i<14; i++)
	{
		RedBlackTreeNode *nodePtr = new RedBlackTreeNode();
		nodePtr->key = a[i];
		rbtree.insert(nodePtr);
		b[i] = nodePtr;
	}
	rbtree.show();
	std::cout << std::endl;
	rbtree.rbtDelete(b[5]);
	rbtree.show();
	std::cout << std::endl;
	rbtree.rbtDelete(b[7]);
	rbtree.show();
	std::cout << std::endl;
	rbtree.rbtDelete(b[0]);
	rbtree.show();
	std::cout << std::endl;
	rbtree.rbtDelete(b[13]);
	rbtree.show();
	std::cout << std::endl;
	rbtree.rbtDelete(b[1]);
	rbtree.show();
	std::cout << std::endl;
	rbtree.rbtDelete(b[3]);
	rbtree.show();
	std::cout << std::endl;
	rbtree.rbtDelete(b[2]);
	rbtree.show();
	std::cout << std::endl;
	rbtree.rbtDelete(b[9]);
	rbtree.show();
	std::cout << std::endl;
	rbtree.rbtDelete(b[4]);
	rbtree.show();
	std::cout << std::endl;
	rbtree.rbtDelete(b[6]);
	rbtree.show();
	std::cout << std::endl;
	rbtree.rbtDelete(b[8]);
	rbtree.show();
	std::cout << std::endl;
	rbtree.rbtDelete(b[10]);
	rbtree.show();
	std::cout << std::endl;
	rbtree.rbtDelete(b[11]);
	rbtree.show();
	std::cout << std::endl;
	rbtree.rbtDelete(b[12]);
	rbtree.show();
	std::cout << std::endl;

	return 0;
	
}

