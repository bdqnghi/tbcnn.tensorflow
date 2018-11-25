


#include "stdafx.h"
#include "BTree.h"
#include <iostream>
#include <stack>
#include <queue>

using namespace std;


BTreeNode* BTree::createBTree()
{
	BTreeNode* current = 0;
	int val = 0;
	cin >> val;
	
	if (val == -1)
	{
		return NULL;
	}
	else
	{
		current = new BTreeNode;
		current->data = val;
		current->lChild = createBTree();
		current->rChild = createBTree();
		return current;
	}
}


void BTree::inOrder()
{
	inOrder(root);
	cout << endl;
}


void BTree::inOrder(BTreeNode* r)
{
	if (r != 0)  
	{
		inOrder(r->lChild);  
		cout << r->data << " ";
		inOrder(r->rChild);  
	}
}


void BTree::NotReInOrder()
{
	stack<BTreeNode*> s;  
	BTreeNode* r = getRoot();
	
	while (!s.empty() || r != 0)
	{
		while (r != 0)
		{
			s.push(r);   
			r = r->lChild;   
		}
		if (!s.empty())
		{
			r = s.top();  
			s.pop();      
			cout << r->data << " ";  
			r = r->rChild;  
		}
	}
}


void BTree::preOrder()
{
	preOrder(root);
	cout << endl;
}



void BTree::preOrder(BTreeNode* r)
{
	if (r != 0) 
	{
		cout << r->data << " ";
		preOrder(r->lChild); 
		preOrder(r->rChild); 
	}
}




void BTree::NotRePreOrder()
{
	stack<BTreeNode*> s;
	BTreeNode* r = getRoot();  
	s.push(r);     

	while (!s.empty())  
	{
		r = s.top();
		s.pop();

		cout << r->data << " ";

		if (r->rChild != 0)
			s.push(r->rChild);
		if (r->lChild != 0)
			s.push(r->lChild);
	}
}



void BTree::postOrder()
{
	postOrder(root);
	cout << endl;
}



void BTree::postOrder(BTreeNode* r)
{
	if (r != 0) 
	{
		postOrder(r->lChild); 
		postOrder(r->rChild); 
		cout << r->data << " ";
	}
}



struct Node
{
	BTreeNode* tp;
	bool flag;
};


void BTree::NotRePostOrder()
{
	Node node; 
	stack<Node> s;

	BTreeNode* r = getRoot();
	while (!s.empty() || r != 0)
	{
		while (r != 0)
		{
			node.tp = r;
			node.flag = 0;
			s.push(node);
			r = r->lChild;
		}

		if (!s.empty())
		{
			node = s.top();
			s.pop();
			r = node.tp; 
			if (node.flag == 1)
			{
				cout << r->data << " ";
				r = 0; 
			}
			else
			{
				node.flag = 1;
				s.push(node);
				r = r->rChild;
			}
		}
	}
}



int BTree::BTreeSize()
{
	return BTreeSize(root);
}


int BTree::BTreeSize(BTreeNode* r)
{
	
	if (r == 0) return 0;
	else
		return 1 + BTreeSize(r->lChild) + BTreeSize(r->rChild);
}


int BTree::BTreeLeaves()
{
	return BTreeLeaves(root);
}


int BTree::BTreeLeaves(BTreeNode* r)
{
	
	if (r == 0) return 0;
	else
		if (r->lChild == 0 && r->rChild == 0)
			return 1;
		else
			return BTreeLeaves(r->lChild) + BTreeLeaves(r->rChild);
}


int BTree::BTreeHeight()
{
	return BTreeHeight(root);
}


int BTree::BTreeHeight(BTreeNode* r)
{
	if (r == 0) return 0;
	else
	{
		
		int lHei = BTreeHeight(r->lChild);
		int rHei = BTreeHeight(r->rChild);
		return (lHei>rHei) ? lHei + 1 : rHei + 1;
	}
}




struct LayerBTreeNode
{
	BTreeNode* ptr;
	int height;
};


int BTree::layerHeight()
{
	queue<LayerBTreeNode> que;
	LayerBTreeNode temp, lTemp, rTemp; 

	BTreeNode* r = getRoot();

	int hei = 1;
	temp.ptr = r;
	temp.height = 1;
	que.push(temp); 

	
	while (!que.empty())
	{
		

		temp = que.front(); 
		que.pop();

		r = temp.ptr;

		
		if (hei<temp.height)
			hei = temp.height;

		if (r->lChild != 0 || r->rChild != 0)
		{
			
			if (r->lChild != 0)
			{
				lTemp.ptr = r->lChild;
				lTemp.height = temp.height + 1; 
				que.push(lTemp);
			}
			if (r->rChild != 0)
			{
				rTemp.ptr = r->rChild;
				rTemp.height = temp.height + 1;
				que.push(rTemp);
			}

		}
	}
	return hei;
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

