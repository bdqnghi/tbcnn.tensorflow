#pragma once
#include "AVLTreeNode.h"
#include <queue>
#include <stack>

template<typename type>
class iterator{
public:
	iterator(AVLTreeNode<type>* n){
		node = n;
	}
	~iterator(){
		node = nullptr;
	}
	iterator<type> operator--(){ //pre-increment
		if (!node) return *this;
		parents.push(node);
		node = node->left();
		return *this;
	}
	iterator<type> operator++(){ //pre-increment
		if (!node) return *this;
		parents.push(node);
		node = node->right();
		return *this;
	}
	iterator<type> operator~(){
		if (parents.empty()) return false;
		node = parents.top();
		parents.pop();
		return *this;
	}
	iterator<type> operator--(int){ //post-increment
		return operator--();
	}
	iterator<type> operator++(int){ //post-increment
		return operator++();
	}
	bool operator+= (std::size_t i){
		while (i-- > 0) if (!(operator++().node)) return false;
		return true;
	}
	bool operator-= (std::size_t i){
		while (i-- > 0) if (!(operator--().node)) return false;
		return true;
	}
	friend iterator<type> operator+ (iterator<type> lhs, const std::size_t& rhs){
		iterator<type> ret = iterator<type>(lhs.operator->());
		ret += rhs;
		return ret;
	}
	friend iterator<type> operator- (iterator<type> lhs, const std::size_t& rhs){
		iterator<type> ret = iterator<type>(lhs.operator->());
		ret -= rhs;
		return ret;
	}
	bool operator== (const iterator<type>& o) const{
		if (!o.operator->() || !node) return !o.operator->() && !node;
		return *(node) == *(o);
	}
	bool operator< (const iterator<type>& o) const{
		if (!o.operator->() || !node) return !o.operator->() && node;
		return *(node) < *(o);
	}
	bool operator> (const iterator<type>& o){ return o.operator<(*this); }
	bool operator<= (const iterator<type>& o){ return !(operator>(o)); }
	bool operator>= (const iterator<type>& o){ return !(operator<(o)); }
	AVLTreeNode<type>* operator->() const{
		return node;
	}
	AVLTreeNode<type>& operator*() const{
		return *node;
	}
	friend std::ostream& operator<< (std::ostream& out, iterator<type>& o){
		out << '[';
		if (o->left()) out << o - 1 << "";
		out << o->getData();
		if (o->right()) out << "" << o + 1;
		out << ']';
		return out;
	};
protected:
	AVLTreeNode<type>* node;
	std::stack<AVLTreeNode<type>*> parents = std::stack<AVLTreeNode<type>*>();
};

template<typename type>
class AVLTree
{
public:
	//Constructors & Destructor
	AVLTree();
	AVLTree(type);
	AVLTree(AVLTreeNode<type>*);
	~AVLTree();

	//Iterator functions
	iterator<type> before_begin();
	iterator<type> begin();
	iterator<type> end();

	//Capacity functions
	std::size_t height(iterator<type>);
	std::size_t height();
	std::size_t count(iterator<type>);
	std::size_t count();
	bool empty();

	//Element access
	AVLTreeNode<type>* root();
	AVLTreeNode<type>* at(iterator<type>);

	//Modifiers
	void clear();
	AVLTreeNode<type>* insert(iterator<type>, AVLTreeNode<type>*);
	//iterator<type> emplace(iterator<type>, AVLTreeNode<type>*);
	AVLTreeNode<type>* remove(iterator<type>, AVLTreeNode<type>*);
	void insert(AVLTreeNode<type>*);
	void insert(type);
	void remove(AVLTreeNode<type>*);
	void remove(type);
	AVLTreeNode<type>* pop_root();
	AVLTreeNode<type>* rotateRight(iterator<type>);
	AVLTreeNode<type>* rotateLeft(iterator<type>);
	void copy(AVLTree<type>*);
	void unique(iterator<type>);
	void unique();
	void merge(AVLTree<type>&);

	//List Operations
	void swap(AVLTree<type>&);

	//Lookup
	AVLTreeNode<type>* find(type);

	//Operator Overloads
	bool operator+= (AVLTreeNode<type>* n){
		insert(n);
		return true;
	}
	friend std::ostream& operator<< (std::ostream& out, AVLTree& o){
		out << o.begin();
		return out;
	};

protected:
	AVLTreeNode<type>* rootNode;
};

template<typename type>
AVLTree<type>::AVLTree(){
	rootNode = new AVLTreeNode<type>();
}

template<typename type>
AVLTree<type>::~AVLTree(){
	if (rootNode) rootNode->~AVLTreeNode();
	rootNode = nullptr;
}

//Creates an iterator to the root data node
template<typename type>
iterator<type> AVLTree<type>::before_begin(){
	return iterator<type>(rootNode);
}

//Creates an iterator to the root data node
template<typename type>
iterator<type> AVLTree<type>::begin(){
	iterator<type> it = iterator<type>(rootNode);
	it++;
	return it;
}

//Creates an iterator to a nullptr, which represents the tail
template<typename type>
iterator<type> AVLTree<type>::end(){
	return iterator<type>(nullptr);
}

template<typename type>
AVLTreeNode<type>* AVLTree<type>::root(){
	return rootNode->right();
}

template<typename type>
AVLTreeNode<type>* AVLTree<type>::at(iterator<type> it){
	return it.operator->();
}

template<typename type>
std::size_t AVLTree<type>::height(){
	return rootNode->balance();
	//return height(begin());
}

template<typename type>
std::size_t AVLTree<type>::height(iterator<type> it){
	if (it == end()) return 0;
	std::size_t ret;
	if (it->balance() > 0)  ret = height(it++);
	else ret = height(it--);
	~it;
	return ret + 1;
}

template <typename type>
bool AVLTree<type>::empty(){
	return rootNode->right() == nullptr;
}

template <typename type>
AVLTreeNode<type>* AVLTree<type>::rotateRight(iterator<type> it){
	AVLTreeNode<type>* ret = it->left();
	it->setLeft(ret->right());
	ret->setRight(it.operator->());
	return ret;
}

template <typename type>
AVLTreeNode<type>* AVLTree<type>::rotateLeft(iterator<type> it){
	AVLTreeNode<type>* ret = it->right();
	it->setRight(ret->left());
	ret->setLeft(it.operator->());
	return ret;
}

template <typename type>
AVLTreeNode<type>* AVLTree<type>::insert(iterator<type> it, AVLTreeNode<type>* n){
	if (it == end()) return n;
	if (*n < *it){
		(~it)->setLeft(insert(it--, n));
		if (it->balance() < -1){
			if ((it - 1)->balance() > 0) (~it)->setLeft(rotateLeft(it--));
			return rotateRight(it);
		}
	}
	else{
		(~it)->setRight(insert(it++, n));
		if (it->balance() > 1){
			if ((it + 1)->balance() < 0) (~it)->setRight(rotateRight(it++));
			return rotateLeft(it);
		}
	}
	return it.operator->();
}

template <typename type>
AVLTreeNode<type>* AVLTree<type>::remove(iterator<type> it, AVLTreeNode<type>* n){ //TODO improve simplicity, make more elagant if possible
	if (it == end()) return nullptr;
	if (*n == *it){
		if (!(it->left())) return it->right(); //Case 1, 2
		if (!(it->right())) return it->left(); //Case 2
		AVLTreeNode<type>* ret = it->right();
		while (ret->left()) ret = ret->left();
		(~it)->setRight(remove(it++, ret)); //Case 3, 4, 5
		ret->setLeft(it->left());
		ret->setRight(it->right());
		if (ret->balance() < -1){
			if (ret->left()->balance() > 0) ret->setLeft(rotateLeft(iterator<type>(ret->left()))); //Double Rotation Case
			return rotateRight(iterator<type>(ret)); //Rotation Cases
		}
		return ret;
	}
	if (*n < *it){
		(~it)->setLeft(remove(it--, n));
		if (it->balance() > 1){ //Balance Violation Cases
			if ((it + 1)->balance() < 0) (~it)->setRight(rotateRight(it++)); //Double Rotation Case
			return rotateLeft(it); //Rotation Cases
		}
	}
	else{
		(~it)->setRight(remove(it++, n));
		if (it->balance() < -1){ //Balance Violation Cases
			if ((it - 1)->balance() > 0) (~it)->setLeft(rotateLeft(it--)); //Double Rotation Case
			return rotateRight(it); //Rotation Cases
		}
	}
	return it.operator->();
}

template <typename type>
void AVLTree<type>::insert(AVLTreeNode<type>* n){
	rootNode->setRight(insert(begin(), n));
}

template <typename type>
void AVLTree<type>::insert(type d){
	insert(new AVLTreeNode<type>(d));
}

template <typename type>
void AVLTree<type>::remove(AVLTreeNode<type>* n){
	remove(before_begin(), n);
}

template <typename type>
void AVLTree<type>::remove(type d){
	remove(new AVLTreeNode<type>(d));
}

template <typename type>
AVLTreeNode<type>* AVLTree<type>::pop_root(){
	AVLTreeNode<type>* ret = remove(begin(), at(begin()));
	//TODO
	return ret;
}

template <typename type>
void AVLTree<type>::unique(iterator<type> it){
	if (it == end() || (it + 1 == end())) return;
	(~it)->setRight(remove(it++, it.operator->()));
	unique(it++);
	~it;
	unique(it--);
	~it;
}

template <typename type>
void AVLTree<type>::unique(){
	return unique(begin());
}

template <typename type>
void AVLTree<type>::swap(AVLTree<type>& o){
	AVLTreeNode<type>* n = rootNode->right();
	iterator<type> o_it = o.before_begin();
	rootNode->setRight(o_it->right());
	o_it->setRight(n);
}

template <typename type>
std::size_t AVLTree<type>::count(iterator<type> it){
	if (it == end()) return 0;
	std::size_t ret = count(it++);
	~it;
	ret += count(it--);
	~it;
	return ret + 1;
}

template <typename type>
std::size_t AVLTree<type>::count(){
	return count(begin())
}

template<typename type>
AVLTreeNode<type>* AVLTree<type>::find(type d){
	iterator<type> it = begin();
	AVLTreeNode<type>* n = new AVLTreeNode<type>(d);
	while (!(it == end() || *it == *n)){
		if (*n < *it) it--;
		else it++;
	}
	return at(it);
}