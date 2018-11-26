/**
 * RedBlackTree.hpp
 *
 * Copyright (c) 2017, Denis Kovalchuk <deniskk25@gmail.com>
 *
 * This code is licensed under a MIT-style license.
 */

#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <iostream>

enum Color { red, black };

template <typename T>
class RedBlackTree
{
public:
    RedBlackTree();
    virtual ~RedBlackTree();

    void add(const T& key);
    void remove(const T& key);
    void postorder();
    
private:
    class Node {
    public:
        T key;
        Color color;
        Node *left;
        Node *right;
        Node *parent;
    };

    Node *root;
    
    Node *grandparent(Node *node) const;
    Node *sibling(Node *node) const;
    Node *uncle(Node *node) const;
    Node *create_node(Node *parent, const T& key, const Color color);
    void insert_case1(Node *node);
    void insert_case2(Node *node);
    void insert_case3(Node *node);
    void insert_case4(Node *node);
    void insert_case5(Node *node);
    void rotate_right(Node *node);
    void rotate_left(Node *node);
    void postorder(Node *node);
    bool node_color(Node *node);
    void delete_tree(Node *node);
};

template<typename T>
RedBlackTree<T>::RedBlackTree() {
    root = nullptr;
}

template<typename T>
RedBlackTree<T>::~RedBlackTree() {
    delete_tree(root);
}

template<typename T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::grandparent(Node *node) const {
    if (node->parent != nullptr) {
        return node->parent->parent;
    }
    return nullptr;
}

template<typename T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::sibling(Node *node) const {
    if (node->parent != nullptr) {
        if (node == node->parent->left) {
            return node->parent->right;
        }
        if (node == node->parent->right) {
            return node->parent->left;
        }
    }
    return nullptr;
}

template<typename T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::uncle(Node *node) const {
    if (node->parent != nullptr) {
        return sibling(node->parent);
    }
    return nullptr;
}

template<typename T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::create_node(Node *parent, const T& key, const Color color) {
    Node *node = new Node();
    node->key = key;
    node->color = color;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

template<typename T>
void RedBlackTree<T>::add(const T& key) {
    if (root == nullptr) {
        root = create_node(nullptr, key, black);
        return;
    }
    
    Node *node = root;
    Node *added_node;
    while (true) {
        if (key < node->key) {
            if (node->left == nullptr) {
                added_node = node->left = create_node(node, key, red);
                break;
            }
            node = node->left;
        } else {
            if (node->right == nullptr) {
                added_node = node->right = create_node(node, key, red);
                break;
            }
            node = node->right;
        }
    }
    insert_case1(added_node);    
}

template<typename T>
void RedBlackTree<T>::insert_case1(Node *node) {
    if (node->parent == nullptr) {
        node->color = black;
    } else {
        insert_case2(node);
    }
}

template<typename T>
void RedBlackTree<T>::insert_case2(Node *node) {
    if (node_color(node->parent) == black) {
        return;
    }
    insert_case3(node);
}

template<typename T>
void RedBlackTree<T>::insert_case3(Node *node) {
    Node *uncle = this->uncle(node);
    Node *grandparent = this->grandparent(node);
    
    if (uncle != nullptr && node_color(uncle) == red && node_color(node->parent) == red) {
        uncle->color = black;
        node->parent->color = black;
        grandparent->color = red;
        insert_case1(grandparent);
    } else {
        insert_case4(node);
    }
}

template<typename T>
void RedBlackTree<T>::insert_case4(Node *node) {
    Node *grandparent;
    grandparent = this->grandparent(node);
    
    if (node == node->parent->right && node->parent == grandparent->left) {
        rotate_left(node->parent);
        node = node->left;
    } else if (node == node->parent->left && node->parent == grandparent->right) {
        rotate_right(node->parent);
        node = node->right;
    }
    insert_case5(node);
}

template<typename T>
void RedBlackTree<T>::insert_case5(Node *node) {
	Node *grandparent = this->grandparent(node);

	node->parent->color = black;
	grandparent->color = red;
	if ((node == node->parent->left) && (node->parent == grandparent->left)) {
		rotate_right(grandparent);
	} else {
		rotate_left(grandparent);
	}
}

template<typename T>
void RedBlackTree<T>::rotate_right(Node *node) {
    Node *pivot = node->left;

    pivot->parent = node->parent;
    if (node->parent == nullptr) {
        root = pivot;
    } else {
        if (node->parent->left == node)
            node->parent->left = pivot;
        else
            node->parent->right = pivot;
    }		
	
    node->left = pivot->right;
    if (pivot->right != NULL)
        pivot->right->parent = node;

    node->parent = pivot;
    pivot->right = node;
}

template<typename T>
void RedBlackTree<T>::rotate_left(Node *node) {
    Node *pivot = node->right;

    pivot->parent = node->parent;
    if (node->parent == nullptr) {
        root = pivot;
    } else {
        if (node->parent->left == node)
            node->parent->left = pivot;
        else
            node->parent->right = pivot;
    }		
	
    node->right = pivot->left;
    if (pivot->left != NULL)
        pivot->left->parent = node;

    node->parent = pivot;
    pivot->left = node;
}

template<typename T>
void RedBlackTree<T>::postorder() {
    std::cout << "postorder: " << std::endl;
    postorder(root);
}

template<typename T>
void RedBlackTree<T>::postorder(Node *node) {
    if (node == nullptr) {
        return;
    }
    postorder(node->left);
    postorder(node->right);
    std::cout << node->key << " ";
    if (node->color == red) {
        std::cout << "red" << std::endl;   
    } else {
        std::cout << "black" << std::endl;
    }
}

template<typename T>
bool RedBlackTree<T>::node_color(Node *node) {
    return node == nullptr ? black : node->color;
}

template<typename T>
void RedBlackTree<T>::delete_tree(Node *node) {
    if (node != nullptr) {
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
    }
}

#endif // RED_BLACK_TREE_HPP
