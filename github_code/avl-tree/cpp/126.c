//
// Created by 涂金戈 on 01/11/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_AVLTREE_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_AVLTREE_H

#include <algorithm>
#include <iostream>

template <typename Comparable>
class AvlTree {
public:
    AvlTree();
    AvlTree(const AvlTree & rhs);
    AvlTree(AvlTree && rhs);
    ~AvlTree();

    const Comparable & findMin() const;
    const Comparable & findMax() const;
    bool contains(const Comparable & x) const;
    bool isEmpty() const;

    void makeEmpty();
    void insert(const Comparable & x);
    void insert(Comparable && x);
    void remove(const Comparable & x);
    void printTree(std::ostream &out = std::cout) const;

    AvlTree & operator= (const Comparable & rhs);
    AvlTree & operator= (Comparable && rhs);

private:
    struct AvlNode {
        Comparable element;
        AvlNode* left;
        AvlNode* right;
        int height;

        AvlNode(const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0)
                : element{ele}, left{lt}, right{rt}, height{h} {}
        AvlNode(Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0)
                : element{std::move(ele)}, left{lt}, right{rt}, height{h} {}
    };

    AvlNode* root;

    static const int ALLOWED_IMBALANCE = 1;

    void insert(const Comparable & x, AvlNode * & t);
    void insert(Comparable && x, AvlNode * & t);
    void remove(const Comparable & x, AvlNode * & t);
    AvlNode * findMin(const AvlNode * t) const;
    AvlNode * findMax(const AvlNode * t) const;
    bool contains(const Comparable & x, AvlNode * t) const;
    void makeEmpty(AvlNode * & t);
    AvlNode * clone(AvlNode * t) const;
    int height(AvlNode * t) const;
    void balance(AvlNode * & t);
    void rotateWithLeftChild(AvlNode * & k2);
    void doubleWithLeftChild(AvlNode * & k3);
    void rotateWithRightChild(AvlNode * & k2);
    void doubleWithRightChild(AvlNode * & k3);
    void printTree(AvlNode *t, std::ostream &out, int indent = 0) const;
};

#include "AvlTree.cpp"

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_AVLTREE_H
