
#ifndef __AVLTREE_HPP__
#define __AVLTREE_HPP__

#include "AVLNode.hpp"

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <cstddef>

template <class Type>
class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    Type minimum() const;
    Type maximum() const;

    size_t height() const;
    size_t size() const;
    bool empty() const;

    void insert(const Type& value);
    void remove(const Type& value);
    bool find(const Type& value);

    void display_tree() const;
    void display_list() const;
private:
    AVLNode<Type> *root;
};

template <class Type>
AVLTree<Type>::AVLTree() {
    root = nullptr;
}

template <class Type>
AVLTree<Type>::~AVLTree() {
    if (root)
        delete root;
}

template <class Type>
Type AVLTree<Type>::minimum() const {
    if (!root)
        throw std::domain_error("AVLTree::minimum() error: AVL-Tree is empty!");
    return root->minimum()->value;
}

template <class Type>
Type AVLTree<Type>::maximum() const {
    if (!root)
        throw std::domain_error("AVLTree::maximum() error: AVL-Tree is empty!");
    return root->maximum()->value;
}

template <class Type>
size_t AVLTree<Type>::height() const {
    return (root ? root->height : 0);
}

template <class Type>
size_t AVLTree<Type>::size() const {
    if (root)
        return root->size();
    else
        return 0;
}

template <class Type>
bool AVLTree<Type>::empty() const {
    return (!root);
}

template <class Type>
void AVLTree<Type>::insert(const Type& value) {
    if (root) {
        if (!root->search(value))
            root = root->insert(value);
    }
    else
        root = new AVLNode<Type>(value);         
}

template <class Type>
void AVLTree<Type>::remove(const Type& value) {
    if (root)
        root = root->remove(value);
}

template <class Type>
bool AVLTree<Type>::find(const Type& value) {
    if (root)
        return (bool)root->search(value);
    return false;
}

template <class Type>
void AVLTree<Type>::display_tree() const {
    if (!root) {
        std::cout << "AVL-Tree is empty" << std::endl;
        return;
    }

    std::cout << std::endl;
    size_t h = height();
    for (size_t i = 0; i < h; ++i) 
        std::cout << '\t' << i;
    std::cout << std::endl;

    std::cout << "\troot:\t";
    root->display_tree(1);

    for (size_t i = 0; i < h; ++i) 
        std::cout << '\t' << i;
    std::cout << std::endl;
}

template <class Type>
void AVLTree<Type>::display_list() const {
    if (root)
        root->display_list(); 
    else
        std::cout << "AVL-Tree is empty";
    std::cout << std::endl;
}


#endif