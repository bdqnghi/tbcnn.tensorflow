#pragma once

#include <iostream>

enum LinkColor
{
    RED = 0,
    BLACK
};

class RedBlackTreeNode
{
public:
    RedBlackTreeNode(int key, int val) : key(key), val(val), color(RED){
        left = NULL;
        right = NULL;
    }
    ~RedBlackTreeNode() {}

    int getkey() { return key; }
    int getVal() { return val; }
    void setVal(int inval) { val = inval; }

    RedBlackTreeNode* left;
    RedBlackTreeNode* right;
    LinkColor         color;
private:
    RedBlackTreeNode() {}
    int key;
    int val;
};

class RedBlackTree
{
public:
    RedBlackTree() { tree_root = NULL; };
    ~RedBlackTree() {};

    bool IsRed(RedBlackTreeNode* inNode);
    RedBlackTreeNode* rightRotate(RedBlackTreeNode*& inNode);
    RedBlackTreeNode* leftRotate(RedBlackTreeNode*& inNode);
    void flipColors(RedBlackTreeNode* inNode);

    void insert(RedBlackTreeNode*& root, RedBlackTreeNode* node);

    RedBlackTreeNode* find(RedBlackTreeNode* root, int key);

    int maxDepth(RedBlackTreeNode* node);
    void printGivenLevel(RedBlackTreeNode* root, int level);
    void printLevelOrder(RedBlackTreeNode* root);

    RedBlackTreeNode* getTreeRoot() { return tree_root; }

private:
    RedBlackTreeNode* tree_root;
};

void RedBlackTreeTest();

