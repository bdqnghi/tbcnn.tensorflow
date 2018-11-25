

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
  
  
  
  RedBlackTree();
  ~RedBlackTree();

  
  
  
  bool isEmpty() const;
  int getHeight() const;
  int getNumberOfNodes() const;
  ItemType getRootData() const; 
  void setRootData(ItemType &newEntry);
  bool add(const ItemType &newData);
  bool remove(const ItemType &target); 
  void clear();
  ItemType getEntry(const ItemType &anEntry) const; 

  
  
  
  void preorderTrav(void visit(ItemType&)) const;
  void inorderTrav(ItemType&) const;
  void postorderTrav(void visit(ItemType&)) const;
}; 

#include "RedBlackTree.cpp"
#endif
