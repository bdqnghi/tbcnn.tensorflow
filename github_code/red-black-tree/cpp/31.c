/*
 * binsearchtree.cpp
 *
 *  Created on: 2015?11?12?
 *      Author: xuqji
 */

#include "RedBlackTree.h"

namespace cpp {

RedBlackTree::RedBlackTree():root_(NULL)
{

}

int RedBlackTree::Size()
{
	return Size(root_);
}

int RedBlackTree::Size(Node* root)
{
	if(root) {
		return root->count_;
	}
	return 0;
}

bool RedBlackTree::IsEmpty()
{
	return !Size(root_);
}

bool RedBlackTree::IsRed(Node* node)
{
	if(!node) return false;

	return node->red_;
}

NODE* RedBlackTree::DoLeftRotate(Node* root)
{
	root = LeftRotate(root);
	return root;
}

NODE* RedBlackTree::LeftRotate(Node* root)
{
	//adjust the pointer
	NODE* x = root->right_;
	root->right_ = x->left_;
	x->left_ = root;

	//change the color after the rotation
	x->red_ = root->red_;
	root->red_ = true;

	//recaculate the root node count
	root->count_ = Size(root->left_) + Size(root->right_) + 1;

	return x;
}

NODE* RedBlackTree::DoRightRotate(Node* root)
{
	root = RightRotate(root);
	return root;
}

NODE* RedBlackTree::RightRotate(Node* root)
{
	NODE* x = root->left_;
	root->left_ = x->right_;
	x->right_ = root;

	x->red_ = root->red_;
	root->red_ = true;

	root->count_ = Size(root->left_) + Size(root->right_) + 1;
	return x;
}

NODE* RedBlackTree::DoFlipColor(Node* root)
{
	root = FlipColor(root);
	return root;
}

NODE* RedBlackTree::FlipColor(Node* root)
{
	root->left_->red_ = false;
	root->right_->red_ = false;
	root->red_ = true;
	return root;

}
void RedBlackTree::Put(KeyType key, ValueType value)
{
	this->root_ = Put(this->root_, key, value);
}

NODE* RedBlackTree::Put(Node* root, KeyType key, ValueType value)
{
	if(!root) {
		Node* node = new Node(key, value);
		return node;
	}

	if(key < root-> key_) {
		root->left_ = Put(root->left_, key, value);
	}
	else if(key > root->key_){//data >root->item
		root->right_ = Put(root->right_, key, value);
	}
	else { //key == root->key_
		root->value_ = value;
	}

	if(!IsRed(root->left_) && IsRed(root->right_)) {
		root = LeftRotate(root);
	}

	if(IsRed(root->left_) && IsRed(root->left_->left_)) {
		root = RightRotate(root);
	}

	if(IsRed(root->left_) && IsRed(root->right_)) {
		root = FlipColor(root);
	}

	root->count_ = Size(root->left_) + Size(root->right_) + 1;
	return root;
}

RedBlackTree::ValueType RedBlackTree::Get(const KeyType& key) const
{
	return Get(root_, key);
}

RedBlackTree::ValueType RedBlackTree::Get(Node* root, const KeyType& key) const
{
	if(!root) {
		return 0;
	}

	if(key < root->key_) {
		return Get(root->left_, key);
	}
	else if(key > root->key_) {
		return Get(root->right_, key);
	}
	else {
		return root->value_;
	}
}

bool RedBlackTree::Contains(KeyType key)
{
	if(ValueType(0) != Get(key)) {
		return true;
	}

	return false;
}
RedBlackTree::KeyType RedBlackTree::Min()
{
	return Min(root_)->key_;
}

NODE* RedBlackTree::Min(Node* root)
{
	if(!root) return NULL;

	if(!(root->left_)) return root;

	return Min(root->left_);
}

RedBlackTree::KeyType RedBlackTree::Max()
{
	return Max(root_)->key_;
}

NODE* RedBlackTree::Max(Node* root)
{
	if(!root) return NULL;

	if(!(root->right_)) return root;

	return Max(root->right_);
}

void RedBlackTree::Travers(Node* tree, OperateType& operate)
{

	if(!tree) {
		return ;
	}
	Travers(tree->left_, operate);
	operate.Do(tree);
	Travers(tree->right_, operate);
}

void RedBlackTree::TraversTree(OperateType& operate)
{
	Travers(this->root_, operate);
}

void RedBlackTree::Destroy()
{
	DestroyNode destroy_node;
	Travers(this->root_, destroy_node);
	root_ = NULL;
}

RedBlackTree::~RedBlackTree()
{
	Destroy();
}

void RedBlackTree::Dump()
{
	DumpNode dump_node;
	Travers(this->root_, dump_node);
	cout<<endl;
}

void RedBlackTree::DeleteMin()
{
	if(root_) {
		root_ = DeleteMin(root_);
	}
}

NODE* RedBlackTree::DeleteMin(Node* root)
{
	if(!(root->left_)) {
		Node* right = root->right_;
		delete root;
		return right;
	}

	root->left_ = DeleteMin(root->left_);
	root->count_ = Size(root->left_) + Size(root->right_) + 1;

	return root;
}

void RedBlackTree::DeleteMax()
{
	if(root_) {
		root_ = DeleteMax(root_);
	}
}


NODE* RedBlackTree::DeleteMax(Node* root)
{
	if(!(root->right_)) {
		Node* left = root->left_;
		delete root;
		return left;
	}

	root->right_ = DeleteMax(root->right_);
	root->count_ = Size(root->left_) + Size(root->right_) + 1;

	return root;
}

void RedBlackTree::Delete(KeyType key)
{
	root_ = Delete(root_, key);
}

NODE* RedBlackTree::Delete(Node* root, KeyType key)
{
	if(!root)	return root;

	if(key < root->key_) {
		root->left_ = Delete(root->left_, key);
	}
	else if(key >root->key_) {
		root->right_ = Delete(root->right_, key);
	}
	else {//equal
		if(!root->left_) {
			Node* t = root->right_;
			delete root;
			return t;
		}
		if(!root->right_) {
			Node* t = root->left_;
			delete root;
			return t;
		}

		Node* t = Min(root->right_);
		root->right_ = DeleteMin(root->right_);
		root->value_ = t->value_;
	}

	root->count_ = Size(root->left_) + Size(root->right_);
	return root;
}

RedBlackTree::KeyType RedBlackTree::Select(int index)
{
	assert(index >= 0);
	assert(index <= Size(root_));

	return Select(root_, index)->key_;
}

NODE* RedBlackTree::Select(Node* root, int index)
{
	if(!root) return NULL;

	int size = Size(root->left_);

	if(index < size) {
		return Select(root->left_, index);
	}
	else if(index > size) {
		return Select(root->right_, index -size -1);
	}
	else {
		return root;
	}
}

int RedBlackTree::Rank(KeyType key)
{
	return Rank(root_, key);
}

int RedBlackTree::Rank(NODE* root, KeyType key)
{
	if(!root) return 0;

	if(key < root->key_) {
		return Rank(root->left_, key);
	}
	else if(key > root->key_) {
		return Rank(root->right_, key) + Size(root->left_) + 1;
	}
	else {
		return Size(root->left_);
	}
}

std::queue<RedBlackTree::KeyType> RedBlackTree::Keys()
{
	std::queue<RedBlackTree::KeyType> q;
	Keys(q, root_, Min(), Max());
	return q;
}

void RedBlackTree::Keys(std::queue<RedBlackTree::KeyType>& q, NODE* root, RedBlackTree::KeyType lo, RedBlackTree::KeyType hi)
{
	if(!root) return;

	if((lo <= root->key_) && (root->key_ <= hi)) {
		q.push(root->key_);
		Keys(q, root->left_, lo, hi);
		Keys(q, root->right_, lo, hi);

	}
	else if(root->key_ > hi) {
		Keys(q, root->left_, lo, hi);
	}
	else if(root->key_ < lo) {
		Keys(q, root->right_, lo, hi);
	}
}










} /* namespace datastruct */
