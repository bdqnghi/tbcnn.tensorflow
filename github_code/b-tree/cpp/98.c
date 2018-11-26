// �������Ļ�������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "BTree.h"
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

//�������������㷨
BTreeNode* BTree::createBTree()
{
	BTreeNode* current = 0;
	int val = 0;
	cin >> val;
	//-1�ĸ�������ֵ�ĸ�����1
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

//�������صķ���
void BTree::inOrder()
{
	inOrder(root);
	cout << endl;
}

//������ʶ��������ݹ飩
void BTree::inOrder(BTreeNode* r)
{
	if (r != 0)  //��if��������while
	{
		inOrder(r->lChild);  //�ݹ����
		cout << r->data << " ";
		inOrder(r->rChild);  //�ݹ����
	}
}

//����������ǵݹ�not recursion��
void BTree::NotReInOrder()
{
	stack<BTreeNode*> s;  //����һ��ջs
	BTreeNode* r = getRoot();
	//���ջs��Ϊ�ջ�ڵ㲻Ϊ0
	while (!s.empty() || r != 0)
	{
		while (r != 0)
		{
			s.push(r);   //ѹ��
			r = r->lChild;   //������
		}
		if (!s.empty())
		{
			r = s.top();  //ȡջ��Ԫ��
			s.pop();      //��ջ��Ԫ��
			cout << r->data << " ";  //��ӡ
			r = r->rChild;  //������
		}
	}
}

//������ʽ  
void BTree::preOrder()
{
	preOrder(root);
	cout << endl;
}


//ǰ��ݹ���ʶ�����(�ݹ�)  
void BTree::preOrder(BTreeNode* r)
{
	if (r != 0) //��if��������while  
	{
		cout << r->data << " ";
		preOrder(r->lChild); //�ݹ����  
		preOrder(r->rChild); //�ݹ����  
	}
}


//ǰ�����(�ǵݹ�)  
//�ڵ�-������-������
void BTree::NotRePreOrder()
{
	stack<BTreeNode*> s;
	BTreeNode* r = getRoot();  //Ҫ��������
	s.push(r);     //ѹ��s

	while (!s.empty())  //��һ����Ϊ��
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


//������ʽ  
void BTree::postOrder()
{
	postOrder(root);
	cout << endl;
}

//�������(�ݹ�)  
//��-��-�ڵ�
void BTree::postOrder(BTreeNode* r)
{
	if (r != 0) //��if��������while  
	{
		postOrder(r->lChild); //�ݹ����  
		postOrder(r->rChild); //�ݹ����  
		cout << r->data << " ";
	}
}


//����ǵݹ����Ҫ�����µĽṹ������  
struct Node
{
	BTreeNode* tp;
	bool flag;
};

//�������(�ǵݹ�)  
void BTree::NotRePostOrder()
{
	Node node; //����Node�ṹ���һ�����  
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
			r = node.tp; //��ջ����BTreeNode*���ָ���r  
			if (node.flag == 1)
			{
				cout << r->data << " ";
				r = 0; //��ʾ�Ѿ������˸ý��  
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


//������ʽ  
int BTree::BTreeSize()
{
	return BTreeSize(root);
}

//��������������ĺ���  
int BTree::BTreeSize(BTreeNode* r)
{
	//�������Ľ�����Ϊ���������ĸ߶�֮����+1  
	if (r == 0) return 0;
	else
		return 1 + BTreeSize(r->lChild) + BTreeSize(r->rChild);
}

//������ʽ  
int BTree::BTreeLeaves()
{
	return BTreeLeaves(root);
}

//�������Ҷ�ӽ������ĺ���  
int BTree::BTreeLeaves(BTreeNode* r)
{
	//��Ϊ��ʱ������0�����ҵ�Ҷ��ʱ����1  
	if (r == 0) return 0;
	else
		if (r->lChild == 0 && r->rChild == 0)
			return 1;
		else
			return BTreeLeaves(r->lChild) + BTreeLeaves(r->rChild);
}

//������ʽ  
int BTree::BTreeHeight()
{
	return BTreeHeight(root);
}

//��������߶ȵĺ���  
int BTree::BTreeHeight(BTreeNode* r)
{
	if (r == 0) return 0;
	else
	{
		//�������ĸ߶�Ϊ���������������+1  
		int lHei = BTreeHeight(r->lChild);
		int rHei = BTreeHeight(r->rChild);
		return (lHei>rHei) ? lHei + 1 : rHei + 1;
	}
}



//��α�����������Ҫ���õ��½ṹ  
struct LayerBTreeNode
{
	BTreeNode* ptr;
	int height;
};

//��α�����߶�  
int BTree::layerHeight()
{
	queue<LayerBTreeNode> que;
	LayerBTreeNode temp, lTemp, rTemp; //�����ռ�������㷨��������  

	BTreeNode* r = getRoot();

	int hei = 1;
	temp.ptr = r;
	temp.height = 1;
	que.push(temp); //�Ƚ�����Ӧ��LayerBTreeNode�������  

	//��Ϊ��ʱ  
	while (!que.empty())
	{
		//BTreeNode* btreePtr=0;  

		temp = que.front(); //ȡ������Ԫ��  
		que.pop();

		r = temp.ptr;

		//�õ�ǰ�ĸ߶ȸ�ȡ���Ķ��׽��бȽ�  
		if (hei<temp.height)
			hei = temp.height;

		if (r->lChild != 0 || r->rChild != 0)
		{
			//�����������������Ϊ�գ��������  
			if (r->lChild != 0)
			{
				lTemp.ptr = r->lChild;
				lTemp.height = temp.height + 1; //��ԭ���߶Ȼ����ϼ�1,�������  
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

