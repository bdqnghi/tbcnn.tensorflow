#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <class T> struct Node {
    T key;
    bool red;
    Node *left;
    Node *right;
    Node *parent;
};

template <class T> class RedBlackTree {
private:
    Node<T> *root;
    Node<T> *nil;
public:
    RedBlackTree() {
        root = NULL;
        nil = new Node<T>;
        nil->left = nil->right = nil->parent = nil;
        nil->red = false;
        nil->key = MIN_INT;
    }

    void left_rotate(Node<T> *x) {
        Node<T> *y = x->right;
        x->right = y->left;
        if (y->left != nil) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nil) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // incomplete... IntroToAlgo p308
};
