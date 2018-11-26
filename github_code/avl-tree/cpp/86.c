#ifndef AVL_H
#define AVL_H

#include "BST.h"
#include "BST.cpp"

template <class K, class D>
class AVL : public BST<K, D>{
public:
	AVL();
	void Insert(const K&, const D&);
	void Remove(const K&);
private:
	int GetHeight(TreeNode<K, D>*);
	int BF(TreeNode<K, D>*);
	void Insert(TreeNode<K, D>*&, const K&, const D&);
    void Rotate(TreeNode<K,D> *&);
	void RotateSingle(TreeNode<K, D> *&);
	void RotateDouble(TreeNode<K, D> *&);
	void Remove(TreeNode<K, D>*&, const K&);
};

#endif
