



#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_BINARYSEARCHTREE_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_BINARYSEARCHTREE_H

#include <algorithm>
#include <iostream>

template <typename Comparable>
class BinarySearchTree {
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree & rhs);
    BinarySearchTree(BinarySearchTree && rhs);
    ~BinarySearchTree();

    const Comparable & findMin() const;
    const Comparable & findMax() const;
    bool contains(const Comparable & x) const;
    bool isEmpty() const;
    void printTree(std::ostream & out = std::cout) const;

    void makeEmpty();
    void insert(const Comparable & x);
    void insert(Comparable && x);
    void remove(const Comparable & x);

    BinarySearchTree & operator= (const BinarySearchTree & rhs);
    BinarySearchTree & operator= (BinarySearchTree && rhs);

private:
    struct BinaryNode {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt)
                : element{theElement}, left{lt}, right{rt} {}
        BinaryNode(Comparable && theElement, BinaryNode *lt, BinaryNode *rt)
                : element{std::move(theElement)}, left{lt}, right{rt} {}
    };

    BinaryNode *root;

    void insert(const Comparable & x, BinaryNode * & t);
    void insert(Comparable && x, BinaryNode * & t);
    void remove(const Comparable & x, BinaryNode * & t);
    BinaryNode * findMin(BinaryNode *t) const;
    BinaryNode * findMax(BinaryNode *t) const;
    bool contains(const Comparable & x, BinaryNode *t) const;
    void makeEmpty(BinaryNode * & t);
    void printTree(BinaryNode *t, std::ostream & out, int indent = 0) const;
    BinaryNode *clone(BinaryNode *t) const;

};

#include "BinarySearchTree.cpp"

#endif 
