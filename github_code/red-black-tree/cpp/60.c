/**
 * @file RedBlackTree.h
 *
 * @brief Header file for the Red Black Tree class
 *
 * @author Willis Allstead
 *
 * @details Specifies the members of the Red Black Tree class
 *
 * @version 0.5
 *
 */

#ifndef RED_BLACK_TREE_
#define RED_BLACK_TREE_

#include "BinaryNode.h"
#include "BinarySearchTree.h"

template<class ItemType>
class RedBlackTree : public BinarySearchTree<ItemType> {
private:
  BinaryNode<ItemType> *rootPtr;

  void rotateLeft(BinaryNode<ItemType> *x);
  void rotateRight(BinaryNode<ItemType> *x);
  void insertNode(BinaryNode<ItemType> *x);

public:
  //------------------------------------------------------------
  // Constructor and Destructor Section.
  //------------------------------------------------------------
  RedBlackTree();
  ~RedBlackTree();

  //------------------------------------------------------------
  // Public Methods Section.
  //------------------------------------------------------------
  bool isEmpty() const;
  int getHeight() const;
  int getNumberOfNodes() const;
  ItemType getRootData() const; // TODO: make this throw for safety
  void setRootData(ItemType &newEntry);
  bool add(const ItemType &newData);
  bool remove(const ItemType &target); // TODO: implement this
  void clear();
  ItemType getEntry(const ItemType &anEntry) const; // TODO: make this throw for safety

  //------------------------------------------------------------
  // Public Traversals Section.
  //------------------------------------------------------------
  void preorderTrav(void visit(ItemType&)) const;
  void inorderTrav(ItemType&) const;
  void postorderTrav(void visit(ItemType&)) const;
}; // end RedBlackTree

#include "RedBlackTree.cpp"
#endif
