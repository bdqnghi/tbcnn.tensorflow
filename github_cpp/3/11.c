
#ifndef AVLT_CPP
#define AVLT_CPP
#include <iostream>
#include "AVLTree.h"
#include "BinarySearchTree.h"

using namespace std;



template<class T>
AVLTree<T>::AVLTree(int (*ptr)(T, T)) :
		BinarySearchTree<T>(ptr) {
}


template<class T>
AVLTree<T>::~AVLTree() {
}


template<class T>
void AVLTree<T>::add(T data) {
	this->root = this->insert(data, this->root);
}


template<class T>
Node<T>* AVLTree<T>::balance(Node<T>* node) {
	int balance_factor = this->heightDifference(node);
	if (balance_factor > 1) {
		if (heightDifference(node->getLeft()) > 0)
			node = this->leftLeftRotation(node);
		else
			node = this->leftRightRotation(node);
	} else if (balance_factor < -1) {
		if (heightDifference(node->getRight()) > 0)
			node = this->rightLeftRotation(node);
		else
			node = this->rightRightRotation(node);
	}
	return node;
}


template<class T>
Node<T>* AVLTree<T>::leftLeftRotation(Node<T>* node) {
	Node<T>* aux;
	aux = node->getLeft();
	node->setLeft(aux->getRight());
	aux->setRight(node);
	return aux;
}


template<class T>
Node<T>* AVLTree<T>::leftRightRotation(Node<T>* node) {
	Node<T>* aux;
	aux = node->getLeft();
	node->setLeft(this->rightRightRotation(aux));
	return this->leftLeftRotation(node);
}


template<class T>
Node<T>* AVLTree<T>::rightLeftRotation(Node<T>* node) {
	Node<T>* aux;
	aux = node->getRight();
	node->setRight(this->leftLeftRotation(aux));
	return this->rightRightRotation(node);
}


template<class T>
Node<T>* AVLTree<T>::rightRightRotation(Node<T>* node) {
	Node<T>* aux;
	aux = node->getRight();
	node->setRight(aux->getLeft());
	aux->setLeft(node);
	return aux;
}


template<class T>
int AVLTree<T>::heightDifference(Node<T>* node) {
	if (node == null)
		return 0;
	return this->height(node->getLeft()) - this->height(node->getRight());
}


template<class T>
int AVLTree<T>::height(Node<T>* node) {
	if (node != null) {
		return max(this->height(node->getLeft()),
				this->height(node->getRight())) + 1;
	}
	return 0;
}


template<class T>
Node<T>* AVLTree<T>::insert(T data, Node<T>* node) {
	if (node == null) {
		node = new Node<T>(data);
	} else if (this->ptr(node->getData(), data) > 0) {
		node->setLeft(this->insert(data, node->getLeft()));
		node = this->balance(node);
	} else if (this->ptr(node->getData(), data) < 0) {
		node->setRight(this->insert(data, node->getRight()));
		node = this->balance(node);
	}
	return node;
}


template<class T>
void AVLTree<T>::remove(T data) {
	this->root = this->remove(data, this->root);
}


template<class T>
Node<T>* AVLTree<T>::remove(T data, Node<T>* node) {
	Node<T>* aux;
	if (node == null)
		return null;
	else if (this->ptr(node->getData(), data) > 0) {
		node->setLeft(this->remove(data, node->getLeft()));
	} else if (this->ptr(node->getData(), data) < 0) {
		node->setRight(this->remove(data, node->getRight()));
	} else if (node->getLeft() && node->getRight()) {
		aux = this->findMax(node->getLeft());
		node->setData(aux->getData());
		node->setLeft(this->remove(node->getData(), node->getLeft()));
	} else {
		aux = node;
		if (node->getRight() == null) {
			node = node->getLeft();
		} else if (node->getLeft() == null) {
			node = node->getRight();
		}
		delete aux;
	}

	if (node == null)
		return node;
	int balance_factor = this->heightDifference(node);
	if (balance_factor > 1) {
		if (heightDifference(node->getLeft()) >= 0)
			node = this->leftLeftRotation(node);
		else
			node = this->leftRightRotation(node);
	} else if (balance_factor < -1) {
		if (heightDifference(node->getRight()) <= 0)
			node = this->rightRightRotation(node);
		else
			node = this->rightLeftRotation(node);
	}

	return node;
}

#endif 
