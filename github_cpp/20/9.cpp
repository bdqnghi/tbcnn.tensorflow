

#include <iostream>
#include <sstream>
#include <cassert>
#include "rbt.h"
using namespace std;



template <class KeyType>
RedBlackTree<KeyType>::RedBlackTree(){
  nil = new Node<KeyType>;
  root = nil;
}



template <class KeyType>
RedBlackTree<KeyType>::~RedBlackTree(){
  destroy(root); 
}





template <class KeyType>
RedBlackTree<KeyType>::RedBlackTree(const RedBlackTree<KeyType>& rbt){
  nil = new Node<KeyType>;
  root = copy(rbt.root, nil, rbt.nil); 
}





template <class KeyType>
KeyType*  RedBlackTree<KeyType>::get(const KeyType& k) {
  Node<KeyType>* found = search(k);
  return (found == nil) ? NULL : found->key; 
}





template <class KeyType>
void  RedBlackTree<KeyType>::insert(KeyType *k){

  Node<KeyType> *par = nil; 
  Node<KeyType> *c = root;
  while (c != nil){
    par = c;
    if (k == NULL){
      cout << "k is NULL\n";
      exit(1);
    }
    if (*k < *c->key){ 
      c = c->leftChild;
    }else{
      c = c->rightChild;
    }
  }
  Node<KeyType> *i = new Node<KeyType>; 
  i->color = RED;
  i->key = k; 
  i->parent = par;
  i->leftChild = nil;
  i->rightChild = nil;
  if (par == nil){ 
    root = i;
  }else if(*i->key < *par->key){
    par->leftChild = i;
  }else{
    par->rightChild = i;
  }
  insertFixup(i);
}




template <class KeyType>
void RedBlackTree<KeyType>::insertFixup(Node<KeyType> *current){
  while(current->parent->color == RED){
    if(current->parent == current->parent->parent->leftChild){
      Node<KeyType> *uncle = current->parent->parent->rightChild;
      if(uncle->color == RED){          
        current->parent->color = BLACK;
        uncle->color = BLACK;
        current->parent->parent->color = RED;
        current = current->parent->parent;
      }
      else{
        if(current == current->parent->rightChild){ 
          current = current->parent;
          leftRotate(current);
        }
        current->parent->color = BLACK;   
        current->parent->parent->color = RED;
        rightRotate(current->parent->parent);
      }
    }
    else{
      Node<KeyType> *uncle = current->parent->parent->leftChild;
      if(uncle->color == RED){         
        current->parent->color = BLACK;
        uncle->color = BLACK;
        current->parent->parent->color = RED;
        current = current->parent->parent;
      }
      else{
        if(current == current->parent->leftChild){   
          current = current->parent;
          rightRotate(current);
        }
        current->parent->color = BLACK;        
        current->parent->parent->color = RED;
        leftRotate(current->parent->parent);
      }
    }
  }
  root->color = BLACK;
}




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




template <class KeyType>
void  RedBlackTree<KeyType>::remove(const KeyType& k){
  if(root == nil){ 
    throw EmptyError();
  }
  Node<KeyType>* par = nil;
  Node<KeyType>* n = root;
  while (k != *n->key){ 
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




template <class KeyType>
KeyType*  RedBlackTree<KeyType>::minimum()const{
  if (root == nil){ 
    throw EmptyError();
  }
  Node<KeyType>* n = root;
  while(n->leftChild != nil){
    n = n->leftChild;
  }
  return n->key;
}




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




template <class KeyType>
KeyType*  RedBlackTree<KeyType>::successor(const KeyType& k){
  if (root == nil){
    throw EmptyError();
  }
  if(k == *maximum()){ 
    return NULL;
  }
  Node<KeyType>* n = search(k); 
  if(n == nil){
    return NULL;
  }
  Node<KeyType> *nRC = n->rightChild;
  if(nRC != nil){
    return (min(nRC)); 
  }
  Node<KeyType>* par = n->parent;
  while(par != nil && n == par->rightChild){
    n = par;
    par = par->parent;
  }
  return par->key;
}





template <class KeyType>
KeyType*  RedBlackTree<KeyType>::predecessor(const KeyType& k){
  if (root == nil){
    throw EmptyError();
  }
  if(k == *minimum()){ 
    return NULL;
  }
  Node<KeyType>* n = search(k); 
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





template <class KeyType>
RedBlackTree<KeyType>&  RedBlackTree<KeyType>::operator=(const RedBlackTree<KeyType> &rbt){
  destroy(root);
  Node<KeyType>* traverse = rbt.root;
  root = copy(traverse, nil, rbt.nil);
}





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





template <class KeyType>
string  RedBlackTree<KeyType>::preOrd(Node<KeyType> *node, std::string& tree)const{
  if (node != nil){
    tree += (" " + node->toString());
    inOrd(node->leftChild, tree);
    inOrd(node->rightChild, tree);
  }
  return tree;
}





template <class KeyType>
string  RedBlackTree<KeyType>::postOrd(Node<KeyType> *node, std::string& tree)const{
  if (node != nil){
    inOrd(node->leftChild, tree);
    inOrd(node->rightChild, tree);
    tree += (" " + node->toString());
  }
  return tree;
}





template <class KeyType>
Node<KeyType>* RedBlackTree<KeyType>::copy(Node<KeyType>* traverse, Node<KeyType>* parent,  Node<KeyType>* NIL){
  if(traverse == NIL){ 
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





template <class KeyType>
void RedBlackTree<KeyType>::destroy(Node<KeyType>* traverse){
  if(traverse == nil){
    return;
  }
  destroy(traverse->leftChild);
  destroy(traverse->rightChild);
  delete traverse; 
}
