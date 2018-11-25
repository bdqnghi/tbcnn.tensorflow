#include<iostream>
using namespace std;
template <typename T>
class AVLTreeNode {
public:
	AVLTreeNode(T t, AVLTreeNode<T>* a, AVLTreeNode<T>* c)
		:key(t), lchild(a), rchild(c) {};
	T key;
	int height;
	AVLTreeNode<T>* lchild;
	AVLTreeNode<T>* rchild;
};
template <typename T>
class AVLTree
{
public:
	AVLTree() :root(nullptr) {};
	int height();
	void insert(T key);
	void remove(T key);
	void inOrder();
	void postOrder();
	void preOrder();
private:
	AVLTreeNode<T>* root;
	int height(AVLTreeNode<T>* pnode);
	int max(int a, int b);
	void preOrder(AVLTreeNode<T>* proot);
	void inOrder(AVLTreeNode<T>* proot);
	void postOrder(AVLTreeNode<T>* proot);
	AVLTreeNode<T>* insert(AVLTreeNode<T>* &pnode, T key);
	AVLTreeNode<T>* remove(AVLTreeNode<T>* &root, T key);
	AVLTreeNode<T>* rightRotation(AVLTreeNode<T>* proot);
	AVLTreeNode<T>* leftRotation(AVLTreeNode<T>* proot);
	AVLTreeNode<T>* rlRotation(AVLTreeNode<T>* proot);
	AVLTreeNode<T>* lrRotation(AVLTreeNode<T>* proot);
};
template <typename T>
AVLTreeNode<T>* AVLTree<T>::lrRotation(AVLTreeNode<T>* proot)
{
	proot->lchild = leftRotation(proot->lchild);
	return rightRotation(proot);
}
template <typename T>
AVLTreeNode<T>* AVLTree<T>::rlRotation(AVLTreeNode<T>* proot)
{
	proot->rchild = rightRotation(proot->rchild);
	return leftRotation(proot);

}
template <typename T>
AVLTreeNode<T>* AVLTree<T>::rightRotation(AVLTreeNode<T>* proot)
{
	AVLTreeNode<T>* pnode = proot->lchild;
	proot->lchild = pnode->rchild;
	pnode->rchild = proot;
	
	proot->height = max(height(proot->lchild), height(proot->rchild))+1;
	pnode->height = max(height(pnode->lchild), height(pnode->rchild))+1;
	return pnode;
}
template <typename T>
AVLTreeNode<T>* AVLTree<T>::leftRotation(AVLTreeNode<T>* proot)
{
	AVLTreeNode<T>* pnode = proot->rchild;
	proot->rchild = pnode->lchild;
	pnode->lchild = proot;
	proot->height = max(height(proot->lchild), height(proot->rchild))+1;
	pnode->height = max(height(pnode->lchild), height(pnode->rchild))+1;
	return pnode;
}

template <typename T>
int AVLTree<T>::height()
{
	height(root);
}
template <typename T>
int AVLTree<T>::height(AVLTreeNode<T>* pnode)
{
	if(pnode!=nullptr)
	{
		return pnode->height;
	}
	return 0;
}
template <typename T>
int AVLTree<T>::max(int a, int b)
{
	return a > b ? a : b;
}
template <typename T>
void AVLTree<T>::insert(T key)
{
	insert(root,key);
}
template <typename T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &pnode, T key)
{
	if (pnode == nullptr)
	{
		pnode = new AVLTreeNode<T>(key, nullptr, nullptr);
	}
	else if (key > pnode->key)
	{
		pnode->rchild = insert(pnode->rchild, key);
		if (height(pnode->rchild) - height(pnode->lchild) == 2)
		{
			if (key > pnode->rchild->key)
				pnode->rchild = leftRotation(pnode->rchild);
			else
				pnode->rchild = rlRotation(pnode->rchild);
		}
	}
	else if (key < pnode->key)
	{
		pnode->lchild = insert(pnode->lchild,key);
		if (height(pnode->rchild) - height(pnode->lchild) == 2)
		{
			if (key < pnode->lchild->key)
				pnode->lchild = rightRotation(pnode->lchild);
			else
				pnode->lchild = lrRotation(pnode->lchild);
		}
	}
	pnode->height = max(height(pnode->lchild), height(pnode->rchild));
	return pnode;
}
template <typename T>
void AVLTree<T>::remove(T key)
{
	remove(root, key);
}
template <typename T>
void AVLTree<T>::remove(AVLTreeNode<T>* pnode, T key)
{
	if (pnode != nullptr)
	{

	}
}
template <typename T>
void AVLTree<T>::inOrder()
{
	inOrder(root);
}
template <typename T>
void AVLTree<T>::inOrder(AVLTreeNode<T>* pnode)
{
	if (pnode != nullptr)
	{
		inOrder(pnode->lchild);
		cout << pnode->key<<endl;
		inOrder(pnode->rchild);
	}
}
template<typename T>
void AVLTree<T>::postOrder(AVLTreeNode<T>* pnode)
{
	if (pnode != nullptr)
	{
		inOrder(pnode->lchild);
		inOrder(pnode->rchild);
		cout << pnode->key << endl;
	}
}
template<typename T>
void AVLTree<T>::postOrder()
{
	postOrder(root);
};
template<typename T>
void AVLTree<T>::preOrder(AVLTreeNode<T>* pnode)
{
	if (pnode != nullptr)
	{
		cout << pnode->key << endl;
		inOrder(pnode->lchild);
		inOrder(pnode->rchild);
	}
};
template<typename T>
void AVLTree<T>::preOrder()
{
	preOrder(root);
};

int main()
{
	AVLTree<int> t;
	t.insert(1);
	t.insert(2);
	t.inOrder();
}
