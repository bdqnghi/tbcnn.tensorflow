/**
 * Program Name: CS 3610 Project #2 Fall 2017
 * Author: Joshua Wright
 * Date: 10/10/2017
 * Purpose: Implements the AVL Tree data type with nodes of type int.
 * Note: AVL Tree Class Header File
**/

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
  // Constructor
  AVLTree() : root(NULL) {}
  // Deconstructor
  ~AVLTree() { delete root; }

  /* *
   * Function Name: insert
   * Description: Call the private insertion function.
   * Parameters: key - The node key to be inserted
   * */
  void insert(const int key);

  /* *
   * Function Name: remove
   * Description: Delete a key-specified node in the AVL Tree.
   * Parameters: key - The key of the node to be deleted.
   * */
  void remove(const int key);

  /* *
   * Function Name: print
   * Description: Print AVL Tree node keys.
   * Parameters: c - 'p' will print the keys, 'h' will print the (sub)tree height
   * */
  void print(const char c);

  
private:
  /* *
   * Function Name: insert
   * Description: Insert a new node into the AVL-Tree
   * Parameters: key - number to be inserted, node - root of AVL Tree
   * */
  BinaryNode* insert(const int key, BinaryNode* node);

  /* *
   * Function Name: remove
   * Description: Delete a specific node from the AVL-Tree
   * Parameters: key - The key of the node to be deleted, node - The AVL Tree's root node
   * */
  BinaryNode* remove(const int key, BinaryNode* node);

  /* *
   * Function Name: balanceUpdate
   * Description: Update the balance factors of the AVL-Tree's nodes
   * Parameters: node - Root of AVL Tree.
   * */
  void balanceUpdate(BinaryNode* &node);

  /* *
   * Function Name: single_left_rotate
   * Description: Rotate the specified node and its left subtree to the left.
   * Parameters: node - The node to be rotated on.
   * */
  void single_left_rotate(BinaryNode* &node);

  /* *
   * Function Name: single_right_rotate
   * Description: Rotate the specified node and its right subtree to the right.
   * Parameters: node - The node to be rotated on.
   * */
  void single_right_rotate(BinaryNode* &node);

  /* *
   * Function Name: double_left_rotate
   * Description: Rotate the specified node's left child to the left
   *  and the node itself subtree to the right.
   * Parameters: node - The node to be rotated on.
   * */
  void double_left_rotate(BinaryNode* &node);

  /* *
   * Function Name: double_right_rotate
   * Description: Rotate the specified node's left child to the left
   *  and the node itself to the right.
   * Parameters: node - The node to be rotated on.
   * */
  void double_right_rotate(BinaryNode* &node);

  /* *
   * Function Name: inorder
   * Description: Traverse the AVL-Tree in ascending
   * order of node keys, while outputing the key.
   * Parameters: node - Root of the AVL Tree.
   * */
  void inorder(BinaryNode* node);

  /* *
   * Function Name: inorder_height
   * Description: Traverse the AVL-Tree in ascending
   * order of node keys, while outputing the (sub)tree height.
   * Parameters: node - Root of the AVL Tree.
   * */
  void inorder_height(BinaryNode* node);

  /* *
   * Function Name: height
   * Description: Determine the longest path within the AVL-Tree
   * from root to leaf(NULL).
   * Parameters: node - Root of the AVL Tree.
   * */
  int height(BinaryNode* node);

  /* *
   * Function Name: max
   * Description: Determine the greater of two integers.
   * Parameters: i - 1st node's key, j - 2nd node's key
   * */
  int max(int i, int j);

  /* *
   * Function Name: successor
   * Description: Find the next inorder node's key.
   * Parameters: node - The root of the AVL Tree to be traversed.
   * */
  int successor(BinaryNode* node);

  /* *
   * Function Name: minNode
   * Description: Find the node of least value in the AVL Tree.
   * Parameters: node - The root of the AVL Tree where the minimum is wanted.
   * */
  BinaryNode* minNode(BinaryNode* node);


  BinaryNode* root;
};

#endif
