

#include <string>
#ifndef AVL_TREE_H
#define AVL_TREE_H


struct BinaryNode {
  BinaryNode(const int key) : key(key), left(NULL), right(NULL) {}

  ~BinaryNode() {
    delete left;
    delete right;
    left = right = NULL;
  }

  int key;
  BinaryNode *left, *right;
  int bfactor = 0;
};

class AVLTree {

public:
  
  AVLTree() : root(NULL) {}
  
  ~AVLTree() { delete root; }

  
  void insert(const int key);

  
  void remove(const int key);

  
  void print(const char c);

  
private:
  
  BinaryNode* insert(const int key, BinaryNode* node);

  
  BinaryNode* remove(const int key, BinaryNode* node);

  
  void balanceUpdate(BinaryNode* &node);

  
  void single_left_rotate(BinaryNode* &node);

  
  void single_right_rotate(BinaryNode* &node);

  
  void double_left_rotate(BinaryNode* &node);

  
  void double_right_rotate(BinaryNode* &node);

  
  void inorder(BinaryNode* node);

  
  void inorder_height(BinaryNode* node);

  
  int height(BinaryNode* node);

  
  int max(int i, int j);

  
  int successor(BinaryNode* node);

  
  BinaryNode* minNode(BinaryNode* node);


  BinaryNode* root;
};

#endif
