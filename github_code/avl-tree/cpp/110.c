#pragma once
#include "TreeNode.h"

template <typename type>
class AVLTreeNode :
	public TreeNode<type>
{
public:
	AVLTreeNode();
	AVLTreeNode(type);
	~AVLTreeNode();
	AVLTreeNode<type>* left();
	AVLTreeNode<type>* right();
	int balance();
	void setLeft(AVLTreeNode<type>*);
	void setRight(AVLTreeNode<type>*);
	/*friend std::ostream& operator<< (std::ostream& out, AVLTreeNode& o){
		out << "|" << o.getData() << "|";
		return out;
	};*/

	static std::size_t height(AVLTreeNode<type>*);

protected:
	//AVLTreeNode<type>* leftChild;
	//AVLTreeNode<type>* rightChild;
	int subBalance;
	bool modified;
};

template <typename type>
AVLTreeNode<type>::AVLTreeNode() : TreeNode(){
	subBalance = 0;
	modified = false;
}

template <typename type>
AVLTreeNode<type>::AVLTreeNode(type d) : TreeNode(d){
	subBalance = 0;
	modified = false;
}

template <typename type>
AVLTreeNode<type>::~AVLTreeNode(){
	subBalance = 0;
	modified = false;
}

template <typename type>
AVLTreeNode<type>* AVLTreeNode<type>::left(){
	return static_cast<AVLTreeNode<type>*>(leftChild);
}

template <typename type>
AVLTreeNode<type>* AVLTreeNode<type>::right(){
	return static_cast<AVLTreeNode<type>*>(rightChild);
}

template <typename type>
int AVLTreeNode<type>::balance(){
	if (modified) subBalance = AVLTreeNode::height(right()) - AVLTreeNode::height(left());
	modified = false;
	return subBalance;
}

template <typename type>
void AVLTreeNode<type>::setLeft(AVLTreeNode<type>* n){
	leftChild = n;
	modified = true;
}

template <typename type>
void AVLTreeNode<type>::setRight(AVLTreeNode<type>* n){
	rightChild = n;
	modified = true;
}

template <typename type>
std::size_t AVLTreeNode<type>::height(AVLTreeNode<type>* n){
	if (!n) return 0;
	else if (n->balance() > 0) return AVLTreeNode::height(n->right()) + 1;
	else return AVLTreeNode::height(n->left()) + 1;
}