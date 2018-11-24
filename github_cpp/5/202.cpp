#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

template <class T> class Node;
template <class T> class AVLTree;

template <class T>
class Node {

  friend class AVLTree<T>;

private:
  T data;
  Node<T>* parent;
  Node<T>* left;
  Node<T>* right;
  int balanceFactor;

public:
  Node(T d = T(), Node<T>* p = nullptr, Node<T>* l = nullptr, Node<T>* r = nullptr);

};

template <class T>
Node<T>::Node(T d, Node<T>* p, Node<T>* l, Node<T>* r){
  data = d;
  parent = p;
  left = l;
  right = r;
  balanceFactor = 0;
}

template <class T>
class AVLTree {

private:
  Node<T>* root;
  int size;
  int setBalance(Node<T>* node);
  int getHeight(Node<T>* node) const;
  void rebalance(Node<T>* node);
  void rotate(Node<T>* parent);
  void LLR(Node<T>* parent, Node<T>* node, Node<T>* child);
  void LRR(Node<T>* parent, Node<T>* node, Node<T>* child);
  void RRR(Node<T>* parent, Node<T>* node, Node<T>* child);
  void RLR(Node<T>* parent, Node<T>* node, Node<T>* child);
  void printInOrder(Node<T>* node) const;
  void printPostOrder(Node<T>* node) const;
  void printPreOrder(Node<T>* node) const;
  void printLevelOrder(Node<T>* node) const;
  Node<T>* copy(Node<T>* rhs) const;
  void remove(Node<T>* node);

public:
  AVLTree(): root(nullptr), size(0){}
  AVLTree(const AVLTree<T>& rhs): root(nullptr) { *this = rhs; }
  ~AVLTree();
  AVLTree<T>& operator =(const AVLTree<T>& rhs);

  bool contains(const T& data) const;
  bool isEmpty() const { return size == 0; }
  void clear();
  void insert(T data);
  Node<T>* search(const T& data) const;
  void remove(const T& data) { remove(search(data)); }
  void printInOrder() const;
  void printPostOrder() const;
  void printPreOrder() const;
  void printLevelOrder() const { printLevelOrder(root); }
  int getHeight() const { return getHeight(root); }
  int getSize() const { return size; }

};

template <class T>
int AVLTree<T>::setBalance(Node<T>* node){
  if (node == nullptr) return 0;
  int leftHeight = getHeight(node->left);
  int rightHeight = getHeight(node->right);
  node->balanceFactor = rightHeight - leftHeight;
  return node->balanceFactor;
}

template <class T>
int AVLTree<T>::getHeight(Node<T>* node) const{
  if (node == nullptr) return -1;
  return 1 + max(getHeight(node->left), getHeight(node->right));
}

template <class T>
void AVLTree<T>::rebalance(Node<T>* node){
  while (node != nullptr){
    setBalance(node);
    if (node->balanceFactor >= 2 || node->balanceFactor <= -2)
      rotate(node);
    node = node->parent;
  }
}

template <class T>
void AVLTree<T>::rotate(Node<T>* node){
  Node<T>* child;
  //node is heavier on the left side
  if (node->balanceFactor < -1){
    child = node->left;
    setBalance(child);
    //child is heavier on the right side
    if (child->balanceFactor == 1)
      LRR(node, child, child->right);
    //child is heavier on the left side
    else
      LLR(node, child, child->left);
  }
  //node is heavier on the right side
  else {
    child = node->right;
    setBalance(child);
    //child is heavier on the left side
    if (child->balanceFactor == -1)
      RLR(node, child, child->left);
    //child heavier on the right side
    else
      RRR(node, child, child->right);
  }
}

//left left rotation where parent node is the node with a bad balance factor (>= 1 || <= -1)
template <class T>
void AVLTree<T>::LLR(Node<T>* parent, Node<T>* node, Node<T>* child){
  Node<T>* grandParent = parent->parent;
  node->parent = grandParent;
  Node<T>* nodeRight = node->right;
  if (nodeRight != nullptr) nodeRight->parent = parent;
  node->right = parent;
  parent->parent = node;
  parent->left = nodeRight;
  if (grandParent == nullptr)
    root = node;
  else if (grandParent->left == parent)
    grandParent->left = node;
  else 
    grandParent->right = node;
}

//left right rotation where parent node is the node with a bad balance factor (>= 1 || <= -1)
template <class T>
void AVLTree<T>::LRR(Node<T>* parent, Node<T>* node, Node<T>* child){
  RRR(node, child, child->right);
  LLR(parent, child, node);
}

//right right rotation where parent node is the node with a bad balance factor (>= 1 || <= -1)
template <class T>
void AVLTree<T>::RRR(Node<T>* parent, Node<T>* node, Node<T>* child){
  Node<T>* grandParent = parent->parent;
  node->parent = grandParent;
  Node<T>* nodeLeft = node->left;
  if (nodeLeft != nullptr) nodeLeft->parent = parent;
  node->left = parent;
  parent->parent = node;
  parent->right = nodeLeft;
  if (grandParent == nullptr)
    root = node;
  else if (grandParent->left == parent)
    grandParent->left = node;
  else
    grandParent->right = node;
}

//right left rotation where parent node is the node with a bad balance factor (>= 1 || <= -1)
template <class T>
void AVLTree<T>::RLR(Node<T>* parent, Node<T>* node, Node<T>* child){
  LLR(node, child, child->left);
  RRR(parent, child, node);
}

template <class T>
void AVLTree<T>::printInOrder(Node<T>* node) const {
  if (node == nullptr) return;
  printInOrder(node->left);
  cout << node->data << ' ';
  printInOrder(node->right);
}

template <class T>
void AVLTree<T>::printPostOrder(Node<T>* node) const {
  if (node == nullptr) return;
  printPostOrder(node->left);
  printPostOrder(node->right);
  cout << node->data << ' ';
}

template <class T>
void AVLTree<T>::printPreOrder(Node<T>* node) const {
  if (node == nullptr) return;
  cout << node->data << ' ';
  printPreOrder(node->left);
  printPreOrder(node->right);
}

template <class T>
void AVLTree<T>::printLevelOrder(Node<T>* node) const {
  if (node == nullptr) return;
  list<Node<T>*> nodeQueue;
  list<int> levelQueue;
  nodeQueue.push_back(node);
  levelQueue.push_back(0);
  while (!nodeQueue.empty()){
    Node<T>* currNode = nodeQueue.front();
    int currLevel = levelQueue.front();
    nodeQueue.pop_front();
    levelQueue.pop_front();
    if (currNode->left != nullptr){ 
      nodeQueue.push_back(currNode->left);
      levelQueue.push_back(currLevel + 1);
    }
    if (currNode->right != nullptr){
      nodeQueue.push_back(currNode->right);
      levelQueue.push_back(currLevel + 1);
    } 
    for (int i = 0; i < currLevel; i++)
      cout << '\t';
    cout << currNode->data << endl;
  }
}

template <class T>
Node<T>* AVLTree<T>::copy(Node<T>* rhs) const {
  if (rhs == nullptr) return nullptr;
  Node<T>* ret = new Node<T>(rhs->data, nullptr, copy(rhs->left), copy(rhs->right));
  if (ret->left != nullptr)
    ret->left->parent = ret;
  if (ret->right != nullptr)
    ret->right->parent = ret;
  return ret;
}

template <class T>
void AVLTree<T>::remove(Node<T>* node){
  if (node == nullptr) return;
  if (root == nullptr) return;

  Node<T>* parent = node->parent;

  //removing a leaf
  if (node->left == nullptr && node->right == nullptr){
    if (parent == nullptr) 
      root = nullptr;
    else if (parent->left == node) 
      parent->left = nullptr;
    else
      parent->right = nullptr;
    delete node;
    rebalance(parent);
    size--;
  }

  //removing a node with only a left child
  else if (node->right == nullptr){
    if (parent == nullptr){
      root = node->left;
      root->parent = nullptr;
    }
    else if (parent->left == node){
      parent->left = node->left;
      node->left->parent = parent;
    }
    else {
      parent->right = node->left;
      node->left->parent = parent;
    }
    delete node;
    rebalance(parent);
    size--;
  }

  //removing a node with only a right child
  else if (node->left == nullptr){
    if (parent == nullptr){
      root = node->right;
      root->parent = nullptr;
    }
    else if (parent->left == node){
      parent->left = node->right;
      node->right->parent = parent;
    }
    else {
      parent->right = node->right;
      node->right->parent = parent;
    }
    delete node;
    rebalance(parent);
    size--;
  }

  //removing a node with two children
  //swap data with the sucessor (right child's left most child) 
  //and make a recursive call to remove the sucessor node
  else {
    Node<T>* temp = node->right;
    while (temp->left != nullptr)
      temp = temp->left;
    node->data = temp->data;
    remove(temp);
  }
}

template <class T>
AVLTree<T>::~AVLTree(){
  clear();
}

template <class T>
AVLTree<T>& AVLTree<T>::operator =(const AVLTree<T>& rhs){
  if (this == &rhs) return *this;
  clear();
  root = copy(rhs.root);
  size = rhs.size;
  return *this;
}

template <class T>
bool AVLTree<T>::contains(const T& data) const {
  if (search(data) == nullptr) return false;
  return true;
}

template <class T>
void AVLTree<T>::clear(){
  while (root != nullptr)
    remove(root);
}

template <class T>
void AVLTree<T>::insert(T data){
  if (root == nullptr){
    root = new Node<T>(data);
    return;
  }
  Node<T>* curr = root;
  Node<T>* prev = curr;
  while (curr != nullptr){
    prev = curr;
    if (data < curr->data)
      curr = curr->left;
    else if (data > curr->data)
      curr = curr->right;
    else
      return;
  }
  size++;
  Node<T>* newNode = new Node<T>(data, prev);
  if (data < prev->data)
    prev->left = newNode;
  else
    prev->right = newNode;

  rebalance(newNode);
}

template <class T>
Node<T>* AVLTree<T>::search(const T& data) const {
  Node<T>* temp = root;
  while (temp != nullptr){
    if (temp->data == data) return temp;
    if (temp->data < data) temp = temp->right;
    else temp = temp->left;
  }
  return nullptr;
}

template <class T>
void AVLTree<T>::printInOrder() const {
  printInOrder(root);
  cout << endl;
}

template <class T>
void AVLTree<T>::printPostOrder() const {
  printPostOrder(root);
  cout << endl;
}

template <class T>
void AVLTree<T>::printPreOrder() const {
  printPreOrder(root);
  cout << endl;
}

