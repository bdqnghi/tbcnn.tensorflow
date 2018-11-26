// Ben Liepert & Gezim Saciri
// source file for RedBlackTree class
#include <iostream>
#include <sstream>
#include <cassert>
#include "rbt.h"
using namespace std;

//=====================================
// default constructor
template <class KeyType>
RedBlackTree<KeyType>::RedBlackTree(){
  nil = new Node<KeyType>;
  root = nil;
}

//=====================================
// destructor
template <class KeyType>
RedBlackTree<KeyType>::~RedBlackTree(){
  destroy(root); //I think this is all we need as opposed to the above
}

//=====================================
// copy constructor
// pre condition: A RedBlackTree that we will copy into this
// post condition: A new RedBlackTree that is a copy of the one passed in
template <class KeyType>
RedBlackTree<KeyType>::RedBlackTree(const RedBlackTree<KeyType>& rbt){
  nil = new Node<KeyType>;
  root = copy(rbt.root, nil, rbt.nil); //need to pass in the other tree's nil to know when to stop traversing
}

//=====================================
// get
// pre condition: A RedBlackTree and a KeyType k that it will search for
// post condition: The RedBlackTree(unchanged) and will return value key or nil
template <class KeyType>
KeyType*  RedBlackTree<KeyType>::get(const KeyType& k) {
  Node<KeyType>* found = search(k);
  return (found == nil) ? NULL : found->key; //NULL if not in rbt, key otherwise
}

//=====================================
// insert
// pre condition: A RedBlackTree to insert values into, and a KeyType pointer k to insert
// post condition: The RedBlackTree with the KeyType pointer k inserted into the tree
template <class KeyType>
void  RedBlackTree<KeyType>::insert(KeyType *k){

  Node<KeyType> *par = nil; //keep track of parent w/this
  Node<KeyType> *c = root;
  while (c != nil){
    par = c;
    if (k == NULL){
      cout << "k is NULL\n";
      exit(1);
    }
    if (*k < *c->key){ //need to deref to compare vals
      c = c->leftChild;
    }else{
      c = c->rightChild;
    }
  }
  Node<KeyType> *i = new Node<KeyType>; //create node to insert
  i->color = RED;
  i->key = k; //key stores a pointer, k is a ptr
  i->parent = par;
  i->leftChild = nil;
  i->rightChild = nil;
  if (par == nil){ //empty tree
    root = i;
  }else if(*i->key < *par->key){
    par->leftChild = i;
  }else{
    par->rightChild = i;
  }
  insertFixup(i);
}
//=====================================
// insertFixup
// pre condition: A RBT that is not following the properties of the RBT after an insertion
// post condition: A RBT that follows all properties of RBT's
template <class KeyType>
void RedBlackTree<KeyType>::insertFixup(Node<KeyType> *current){
  while(current->parent->color == RED){
    if(current->parent == current->parent->parent->leftChild){
      Node<KeyType> *uncle = current->parent->parent->rightChild;
      if(uncle->color == RED){          // case 1
        current->parent->color = BLACK;
        uncle->color = BLACK;
        current->parent->parent->color = RED;
        current = current->parent->parent;
      }
      else{
        if(current == current->parent->rightChild){ // case 2
          current = current->parent;
          leftRotate(current);
        }
        current->parent->color = BLACK;   // case 2 cont. and 3
        current->parent->parent->color = RED;
        rightRotate(current->parent->parent);
      }
    }
    else{
      Node<KeyType> *uncle = current->parent->parent->leftChild;
      if(uncle->color == RED){         // case 4
        current->parent->color = BLACK;
        uncle->color = BLACK;
        current->parent->parent->color = RED;
        current = current->parent->parent;
      }
      else{
        if(current == current->parent->leftChild){   // case 5
          current = current->parent;
          rightRotate(current);
        }
        current->parent->color = BLACK;        // case 5 cont. and 6
        current->parent->parent->color = RED;
        leftRotate(current->parent->parent);
      }
    }
  }
  root->color = BLACK;
}
//=====================================
// leftRotate
// pre condition: Takes an unbalanced RBT and given node and preforms a left rotation
// post condition: Balances out the RBT to fufill the RBT property
template <class KeyType>
void RedBlackTree<KeyType>::leftRotate(Node<KeyType> *node){
  Node<KeyType> *right = node->rightChild;
  node->rightChild = right->leftChild;
  if(right->leftChild != nil){
    right->leftChild->parent = node;
  }
  right->parent = node->parent;
  if(node->parent == nil){
    root = right;
  }
  else if(node == node->parent->leftChild){
    node->parent->leftChild = right;
  }
  else{
    node->parent->rightChild = right;
  }
  right->leftChild = node;
  node->parent = right;
}
//=====================================
// rightRotate
// pre condition: Takes an unbalanced RBT and given node and preforms a right rotation
// post condition: Balances out the RBT to fufill the RBT property
template <class KeyType>
void RedBlackTree<KeyType>::rightRotate(Node<KeyType> *node){
  Node<KeyType> *left = node->leftChild;
  node->leftChild = left->rightChild;
  if(left->rightChild != nil){
    left->rightChild->parent = node;
  }
  left->parent = node->parent;
  if(node->parent == nil){
    root = left;
  }
  else if(node == node->parent->rightChild){
    node->parent->rightChild = left;
  }
  else{
    node->parent->leftChild = left;
  }
  left->rightChild = node;
  node->parent = left;
}
//=====================================
// remove
// pre condition: A RedBlackTree that contains values(else EmptyError) and a value k to remove
// post condition: The RedBlackTree with the value k removed from it
template <class KeyType>
void  RedBlackTree<KeyType>::remove(const KeyType& k){
  if(root == nil){ //can't remove if empty
    throw EmptyError();
  }
  Node<KeyType>* par = nil;
  Node<KeyType>* n = root;
  while (k != *n->key){ //get node to be removed
    par = n;
    if (k < *n->key){
      n = n->leftChild;
    }else{
      n = n->rightChild;
    }
  }
  if(n->leftChild == nil){
    transplant(n, n->rightChild);
  }else if(n->rightChild == nil){
    transplant(n, n->leftChild);
  }else{
    Node<KeyType>* successor = search(*min(n->rightChild));
    if(successor->parent != n){
      transplant(successor, successor->rightChild);
      successor->rightChild = n->rightChild;
      successor->rightChild->parent = successor;
    }
    transplant(n, successor);
    successor->leftChild = n->leftChild;
    successor->leftChild->parent = successor;
    delete n;
  }
}
//=====================================
// maximum
// pre condition: A RedBlackTree with at least one value
// post condition: The RedBlackTree(unchanged) and returns the maximum key
template <class KeyType>
KeyType*  RedBlackTree<KeyType>::maximum() const{
  if (root == nil){
    throw EmptyError();
  }
  Node<KeyType>* n = root;
  while(n->rightChild != nil){
    n = n->rightChild;
  }
  return n->key;
}
//=====================================
// max (private)
// pre condition: A RedBlackTree with at least one value
// post condition: The RedBlackTree and returns the minimum value
template <class KeyType>
KeyType*  RedBlackTree<KeyType>::min(Node<KeyType>* node) const{
  if (node == nil){
    throw EmptyError();
  }
  Node<KeyType>* n = node;
  while(n->leftChild != nil){
    n = n->leftChild;
  }
  return n->key;
}
//=====================================
// minimum
// pre condition: A RedBlackTree with at least one value
// post condition: The RedBlackTree and returns the minimum value
template <class KeyType>
KeyType*  RedBlackTree<KeyType>::minimum()const{
  if (root == nil){ //root shouldn't be NULL either
    throw EmptyError();
  }
  Node<KeyType>* n = root;
  while(n->leftChild != nil){
    n = n->leftChild;
  }
  return n->key;
}
//=====================================
// min (private)
// pre condition: A RedBlackTree with at least one value
// post condition: The RedBlackTree and returns the minimum value
template <class KeyType>
KeyType*  RedBlackTree<KeyType>::max(Node<KeyType> *node) const{
  if (node == nil){
    throw EmptyError();
  }
  Node<KeyType>* n = node;
  while(n->rightChild != nil){
    n = n->rightChild;
  }
  return n->key;
}
//=====================================
// successor
// pre condition: A RedBlackTree with at least one value
// post condition: The RedBlackTree(uchanged) and returns the successor
template <class KeyType>
KeyType*  RedBlackTree<KeyType>::successor(const KeyType& k){
  if (root == nil){
    throw EmptyError();
  }
  if(k == *maximum()){ // max has no successor
    return NULL;
  }
  Node<KeyType>* n = search(k); //get the node whose value is k
  if(n == nil){
    return NULL;
  }
  Node<KeyType> *nRC = n->rightChild;
  if(nRC != nil){
    return (min(nRC)); //make a private one now;
  }
  Node<KeyType>* par = n->parent;
  while(par != nil && n == par->rightChild){
    n = par;
    par = par->parent;
  }
  return par->key;
}

//=====================================
// predecessor
// pre condition: A RedBlackTree with at least one value
// post condition: The RedBlackTree(uchanged) and returns the predecessor
template <class KeyType>
KeyType*  RedBlackTree<KeyType>::predecessor(const KeyType& k){
  if (root == nil){
    throw EmptyError();
  }
  if(k == *minimum()){ //min has no predecessor
    return NULL;
  }
  Node<KeyType>* n = search(k); //get the node whose value is k
  if(n == nil){
    return NULL;
  }
  Node<KeyType> *nLC = n->leftChild;
  if(nLC != nil){
    return (max(nLC));
  }
  Node<KeyType>* par = n->parent;
  while(par != nil && n == par->leftChild){
    n = par;
    par = par->parent;
  }
  return par->key;
}

//=====================================
//  assignment operator
// pre condition: A RedBlackTree to set equal to another passed in tree rbt
// post condition: The RedBlackTree which is equal to the passed in tree rbt
template <class KeyType>
RedBlackTree<KeyType>&  RedBlackTree<KeyType>::operator=(const RedBlackTree<KeyType> &rbt){
  destroy(root);
  Node<KeyType>* traverse = rbt.root;
  root = copy(traverse, nil, rbt.nil);
}

//=====================================
//  search
// pre condition: A RedBlackTree and a value k to search for
// post condition: The RedBlackTree(unchanged) and returns the node with the value k
template <class KeyType>
Node<KeyType>*  RedBlackTree<KeyType>::search(const KeyType& k){
  Node<KeyType>* n = root;
  while(n != nil && *n->key != k){
    if(!(*n->key < k) && (*n->key != k)){
      n = n->leftChild;
    }else{
      n = n->rightChild;
    }
  }
  return n;
}

//=====================================
//  transplant
// pre condition: A RedBlackTree and two nodes within that tree
// post condition: The RedBlackTree where the two nodes have swapped places
template <class KeyType>
void  RedBlackTree<KeyType>::transplant(Node<KeyType>* rem, Node<KeyType>* rep){
  if(rem->parent == nil){
    root = rep;
  }else if(rem == rem->parent->leftChild){
    rem->parent->leftChild = rep;
  }else{
    rem->parent->rightChild = rep;
  }
  if(rep != nil){
    rep->parent = rem->parent;
  }
}

//==========================================
// these three functions call the ones below
// this avoids exposing node pointers
template <class KeyType>
std::string  RedBlackTree<KeyType>::inOrder(){
  std::string tree = "{";
  return inOrd(root, tree) + " }";
}
template <class KeyType>
std::string  RedBlackTree<KeyType>::preOrder(){
  std::string tree = "{";
  return preOrd(root, tree) + " }";
}
template <class KeyType>
std::string  RedBlackTree<KeyType>::postOrder(){
  std::string tree = "{";
  return postOrd(root, tree) + " }";
}

//=====================================
// inOrd
// pre condition: A pointer node and a string tree
// post condition: Only returns the string tree which contains the keys of the nodes inOrd
template <class KeyType>
string  RedBlackTree<KeyType>::inOrd(Node<KeyType> *node, string& tree)const {
  if (node == NULL){
    cout << "node = NULL" << endl;
  }
  if (node != nil){
    inOrd(node->leftChild, tree);
    tree += (" " + node->toString());
    inOrd(node->rightChild, tree);
  }
  return tree;
}

//=====================================
// preOrd
// pre condition: A pointer node and a string tree
// post condition: Only returns the string tree which contains the keys of the nodes preOrd
template <class KeyType>
string  RedBlackTree<KeyType>::preOrd(Node<KeyType> *node, std::string& tree)const{
  if (node != nil){
    tree += (" " + node->toString());
    inOrd(node->leftChild, tree);
    inOrd(node->rightChild, tree);
  }
  return tree;
}

//=====================================
// postOrd
// pre condition: A pointer node and a string tree
// post condition: Only returns the string tree which contains the keys of the nodes postOrd
template <class KeyType>
string  RedBlackTree<KeyType>::postOrd(Node<KeyType> *node, std::string& tree)const{
  if (node != nil){
    inOrd(node->leftChild, tree);
    inOrd(node->rightChild, tree);
    tree += (" " + node->toString());
  }
  return tree;
}

//=====================================
// copy
// pre condition: A RedBlackTree and a node that is set to the root of the tree to copy
// post condition: The RedBlackTree that is the copy of the passed in tree
template <class KeyType>
Node<KeyType>* RedBlackTree<KeyType>::copy(Node<KeyType>* traverse, Node<KeyType>* parent,  Node<KeyType>* NIL){
  if(traverse == NIL){ //assuming we don't need to check if traverse is NULL?
    return nil;
  }
  Node<KeyType> *n = new Node<KeyType>;
  n->key = traverse->key;
  n->color = traverse->color;
  n->parent = parent;
  n->leftChild = copy(traverse->leftChild, traverse, NIL);
  n->rightChild = copy(traverse->rightChild, traverse, NIL);
  return n;
}

//=====================================
// destroy
// pre condition: A RedBlackTree and a node to the root of that tree
// post condition: Deallocates the memory of the RedBlackTree
template <class KeyType>
void RedBlackTree<KeyType>::destroy(Node<KeyType>* traverse){
  if(traverse == nil){
    return;
  }
  destroy(traverse->leftChild);
  destroy(traverse->rightChild);
  delete traverse; //get to bottom of left or right subtree, delete, recursive call
}
