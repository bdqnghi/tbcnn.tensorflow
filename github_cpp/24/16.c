#pragma once
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include<iostream>

template<typename T>
class BinarySearchTree
{
public:
	BinarySearchTree() :root(nullptr) {};
	BinarySearchTree(const BinarySearchTree &rhs);
	~BinarySearchTree();
	const BinarySearchTree &operator=(const BinarySearchTree &rhs);

	const T &findMin() const;
	const T &findMax() const;
	bool contains(const T &x) const; 
	bool isEmpty() const;

	void printTree() const;
	void preorderPrintTree() const;
	void postorderPrintTree() const;

	void makeEmpty();
	void insert(const T &x);
	void remove(const T &x);

private:
	struct BinaryNode
	{
		T element;
		BinaryNode *left;
		BinaryNode *right;

		BinaryNode(const T &theElement, BinaryNode *lt, BinaryNode *rt)
			:element(theElement), left(lt), right(rt) {}
	};

	BinaryNode *root;

	void insert(const T &x, BinaryNode *&t);
	void remove(const T &x, BinaryNode *&t);

	BinaryNode *findMin(BinaryNode *t) const;
	BinaryNode *findMax(BinaryNode *t) const;

	void makeEmpty(BinaryNode *&t);
	BinaryNode *clone(BinaryNode *t) const;
	
    void printTree(BinaryNode *t) const;
	void preorderPrintTree(BinaryNode *t) const;
	void postorderPrintTree(BinaryNode *t) const;

	bool contains(const T &x, BinaryNode *t) const;

};

template<typename T>
bool BinarySearchTree<T>::contains(const T &x, BinaryNode *t) const
{
	if (t == nullptr)
		return false;
	else if (x < t->element)
		return contains(x, t->left);
	else if (t->element < x)
		return contains(x, t->right);
	else
		return true;
}

template<typename T>
bool BinarySearchTree<T>::contains(const T &x) const
{
	return contains(x, root);
}

template<typename T>                   
typename BinarySearchTree<T>::BinaryNode *BinarySearchTree<T>::findMin(BinaryNode *t) const
{
	if (t == nullptr)
		return false;
	else if (t->left == nullptr)
		return t;
	return findMin(t->left);
}

template<typename T>
const T &BinarySearchTree<T>::findMin() const
{
	return findMin(root)->element;
}

template<typename T>
typename BinarySearchTree<T>::BinaryNode *BinarySearchTree<T>::findMax(BinaryNode *t) const
{
	if (t != nullptr)
		while (t->right != nullptr)
			t = t->right;
	return t;
}

template<typename T>
const T &BinarySearchTree<T>::findMax() const
{
	return findMax(root)->element;
}

template<typename T>
void BinarySearchTree<T>::insert(const T &x, BinaryNode *&t)
{
	if (t == nullptr)
		t = new BinaryNode(x, nullptr, nullptr);
	else if (x < t->element)
		insert(x, t->left);
	else if (t->element < x)
		insert(x, t->right);
	else
		return;
}

template<typename T>
void BinarySearchTree<T>::insert(const T &x)
{
	insert(x, root);
}

template<typename T>
void BinarySearchTree<T>::remove(const T &x, BinaryNode *&t)
{
	if (t == nullptr)
		return;
	else if (x < t->element)
		remove(x, t->left);
	else if (t->element < x)
		remove(x, t->right);
	else if (t->left != nullptr && t->right != nullptr)
	{
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else
	{
		BinaryNode *oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
	}
}

template<typename T>
void BinarySearchTree<T>::remove(const T &x)
{
	remove(x, root);
}

template<typename T>
void BinarySearchTree<T>::makeEmpty(BinaryNode *&t)
{
	if (t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = nullptr;
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree &rhs)
{
	*this = rhs;
}

template<typename T>
void BinarySearchTree<T>::makeEmpty()
{
	makeEmpty(root);
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	makeEmpty();
}

template<typename T>
bool BinarySearchTree<T>::isEmpty() const
{
	if (this != nullptr)
		return false;
	return true;
}

template<typename T>
void BinarySearchTree<T>::printTree(BinaryNode *t) const
{
	if (t)
	{
		printTree(t->left);
		std::cout << t->element << " ";
		printTree(t->right);
	}
}

template<typename T>
void BinarySearchTree<T>::printTree() const
{
	printTree(root);
}

template<typename T>
void BinarySearchTree<T>::preorderPrintTree(BinaryNode *t) const
{
	if (t)
	{
		std::cout << t->element << " ";
		preorderPrintTree(t->left);
		preorderPrintTree(t->right);
	}
}

template<typename T>
void BinarySearchTree<T>::preorderPrintTree() const
{
	preorderPrintTree(root);
}

template<typename T>
void BinarySearchTree<T>::postorderPrintTree(BinaryNode *t) const
{
	if (t)
	{
		postorderPrintTree(t->left);
		postorderPrintTree(t->right);
		std::cout << t->element << " ";
	}
}

template<typename T>
void BinarySearchTree<T>::postorderPrintTree() const
{
	postorderPrintTree(root);
}

template<typename T>
typename BinarySearchTree<T>::BinaryNode *BinarySearchTree<T>::clone(BinaryNode *t) const
{
	if (t == nullptr)
		return nullptr;
	return new BinaryNode(t->element, clone(t->left), clone(t->right));
}

template<typename T>
const BinarySearchTree<T> &BinarySearchTree<T>::operator=(const BinarySearchTree &rhs)
{
	if (this != &rhs)
	{
		makeEmpty();
		root = clone(rhs.root);
	}
	return *this;
}

#endif 