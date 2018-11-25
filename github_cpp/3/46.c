



#ifndef TREEAVL_CPP
#define TREEAVL_CPP

#include <stddef.h>
#include <iostream>

#include "TreeAVL.hpp"
#include "NodeAVL.cpp"

template <class T>
TreeAVL<T>::TreeAVL() {
    root=NULL;
}


template <class T>
TreeAVL<T>::TreeAVL(const TreeAVL& orig) {
}

template <class T>
TreeAVL<T>::~TreeAVL() {
}

template<class T>
bool TreeAVL<T>::isEmpty() {
    return (root==NULL);
}

template<class T>
int TreeAVL<T>::getSize() {
    size=0;
    getSize(root);
    return size;
}

template<class T>
int TreeAVL<T>::getHeight() {
    return getHeight(root);
}

template<class T>
int TreeAVL<T>::getHeight(NodeAVL<T>* node) {
    if (node==NULL) {return 0;}
    if (node->isSheet()){return 1;}
    return calculateHigher(getHeight(node->getLeft()),getHeight(node->getRight()))+1;
}

template<class T>
int TreeAVL<T>::getSwing() {
    getSwing(root);
    return root->getSwing();
}

template<class T>
int TreeAVL<T>::getSwing(NodeAVL<T>* node) {
    if (node==NULL) {return 0;}
    if (node->isSheet()) {
        node->setSwing(0);
        return 1;
    }else{
        node->setSwing(getSwing(node->getRight())- getSwing(node->getLeft()));
        return getHeight(node);
    }
}




template<class T>
int TreeAVL<T>::calculateHigher(int numberOne, int numberTwo) {
    return (numberOne>numberTwo?numberOne:numberTwo);
}



template<class T>
void TreeAVL<T>::getSize(NodeAVL<T>* node) {
    if (node==NULL) {
        return;
    }else{
        getSize(node->getLeft());
        size++;
        getSize(node->getRight());
    }
}

template<class T>
void TreeAVL<T>::balanced() {
    this->balanced(root);
}

template<class T>
NodeAVL<T>* TreeAVL<T>::balanced(NodeAVL<T>* node) {
    if (node==NULL) {
        if (getHeight(node->getRight()-getHeight(node->getLeft()))>1) {

        }

    return node;
    }
}

template<class T>
NodeAVL<T>* TreeAVL<T>::rotateLeft(NodeAVL<T>* node) {
    NodeAVL<T> *aux=node->getLeft();
    node->setLeft(aux->getRight());
    aux->setRight(aux);
    return node=aux;
}

template<class T>
NodeAVL<T>* TreeAVL<T>::rotateRight(NodeAVL<T>* node) {
   NodeAVL<T> *aux=node->getRight();
    node->setRight(aux->getLeft());
    aux->setLeft(node);
    return node=aux; 
}


template<class T>
void TreeAVL<T>::add(T *info) {
    NodeAVL<T> *node=new NodeAVL<T>(info);
    if (isEmpty()) {
        this->root=node;
    }else{
        NodeAVL<T> *aux=root;
        NodeAVL<T> *previus=root;
        while (aux!=NULL) {
            previus=aux;
            if (info->compareTo(aux->getInfo())==-1) {
                aux=aux->getLeft();
            }else{
                aux=aux->getRight();
            }
        }
        if (info->compareTo(previus->getInfo())==-1) {
            previus->setLeft(node);
        }else{
            previus->setRight(node);
        }
    }
}

#include "TreeAVL.hpp"
#include "NodeAVL.cpp"
#endif 