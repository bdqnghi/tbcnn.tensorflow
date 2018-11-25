#ifndef _BINARY_SEARCH_TREE_
#define _BINARY_SEARCH_TREE_

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

template<typename T>
class BinarySearchNode {
public: 
  BinarySearchNode(const T& data, BinarySearchNode* left, BinarySearchNode* right)
  : _data{data}
  , _left{left}
  , _right{right}
  {}

  BinarySearchNode(T&& data, BinarySearchNode* left, BinarySearchNode* right) 
  : _data{std::move(data)} 
  , _left{left}
  , _right{right}
  {}

  T _data; 
  BinarySearchNode* _left;
  BinarySearchNode* _right; 
}; 

template<typename T>
bool Less(const T& x, T& y) {
  return x < y; 
}

template<typename T>
bool Less(T& x, const T& y) {
  return x < y; 
}

template<typename T>
class BinarySearchTree {
public:
  BinarySearchTree(); 
  BinarySearchTree(const BinarySearchTree& rhs); 
  BinarySearchTree(BinarySearchTree&& rhs); 
  ~BinarySearchTree(); 
  
  BinarySearchTree& operator= (const BinarySearchTree& rhs); 
  BinarySearchTree& operator= (BinarySearchTree&& rhs); 
  
  void insert(const T& x); 
  void insert(T&& x); 
  void remove(const T& x); 
  void makeEmpty(); 

  const T& findMin() const; 
  const T& findMax() const; 

  bool contains(const T& x) const; 
  bool isEmpty() const; 

  void preorder(std::vector<BinarySearchNode<T>*>& nodes) const;
  void inorder(std::vector<BinarySearchNode<T>*>& nodes) const;
  void postorder(std::vector<BinarySearchNode<T>*>& nodes) const;
  void breadthFirst(std::vector<BinarySearchNode<T>*>& nodes) const; 

  void print() const; 

  BinarySearchNode<T>* convertToList(); 

private:
  BinarySearchNode<T>* clone(BinarySearchNode<T>* t) const; 

  void insert(const T& x, BinarySearchNode<T>*& t); 
  void insert(T&& x, BinarySearchNode<T>*& t); 
  
  void remove(const T& x, BinarySearchNode<T>*& t); 

  void makeEmpty(BinarySearchNode<T>*& t); 

  BinarySearchNode<T>* findMin(BinarySearchNode<T>* t) const; 
  BinarySearchNode<T>* findMax(BinarySearchNode<T>* t) const; 

  bool contains(const T& x, BinarySearchNode<T>* t) const; 

  void preorder(std::vector<BinarySearchNode<T>*>& nodes, BinarySearchNode<T>* t) const;
  void inorder(std::vector<BinarySearchNode<T>*>& nodes, BinarySearchNode<T>* t) const;
  void postorder(std::vector<BinarySearchNode<T>*>& nodes, BinarySearchNode<T>* t) const;
  void breadthFirst(std::vector<BinarySearchNode<T>*>& nodes, BinarySearchNode<T>* t) const; 

  void print(BinarySearchNode<T>* t) const; 

  void convertToList(BinarySearchNode<T>* parent); 
  void convertToList(BinarySearchNode<T>* parent, BinarySearchNode<T>*& tail); 

private: 
  BinarySearchNode<T>* _root;

}; 

template<typename T>
BinarySearchTree<T>::
BinarySearchTree()
: _root{nullptr}
{}

template<typename T>
BinarySearchTree<T>::
BinarySearchTree(const BinarySearchTree& rhs) 
: _root{nullptr}
{
  _root = clone(rhs._root); 
}

template<typename T>
BinarySearchTree<T>::
BinarySearchTree(BinarySearchTree&& rhs) 
: _root{rhs._root}
{
  rhs._root = nullptr; 
}

template<typename T>
BinarySearchTree<T>::
~BinarySearchTree() {

  makeEmpty( );
}

template<typename T>
BinarySearchTree<T>& 
BinarySearchTree<T>::
operator= (const BinarySearchTree& rhs) {
    BinarySearchTree copy = rhs;
    std::swap(*this, copy); 
    return *this;
}
    
template<typename T>
BinarySearchTree<T>& 
BinarySearchTree<T>::
operator= (BinarySearchTree&& rhs) {
    std::swap(_root, rhs._root);       
    return *this;
}

template<typename T>
void 
BinarySearchTree<T>::
insert(const T& x) {
  insert(x, _root); 
}

template<typename T>
void 
BinarySearchTree<T>::
insert(T&& x) {
  insert(x, _root); 
}

template<typename T>
void 
BinarySearchTree<T>::
remove(const T& x) {
  remove(x, _root); 
}

template<typename T>
void 
BinarySearchTree<T>::
makeEmpty() {
  makeEmpty(_root); 
}

template<typename T>
const T& 
BinarySearchTree<T>::
findMin() const {
  if (!isEmpty()) {
    return findMin(_root)->_left; 
  }
}

template<typename T>
const T& 
BinarySearchTree<T>::
findMax() const {
  if (!isEmpty()) {
    return findMax(_root)->_data; 
  }
}

template<typename T>
bool 
BinarySearchTree<T>::
contains(const T& x) const {
  return contains(x, _root); 
}

template<typename T>
bool 
BinarySearchTree<T>::
isEmpty() const {
  return _root == nullptr; 
}

template<typename T>
void 
BinarySearchTree<T>::
preorder(std::vector<BinarySearchNode<T>*>& nodes) const {
  preorder(nodes, _root); 
}

template<typename T>
void 
BinarySearchTree<T>::
inorder(std::vector<BinarySearchNode<T>*>& nodes) const {
  inorder(nodes, _root); 
}

template<typename T>
void 
BinarySearchTree<T>::
postorder(std::vector<BinarySearchNode<T>*>& nodes) const {
  postorder(nodes, _root); 
}

template<typename T>
void 
BinarySearchTree<T>::
breadthFirst(std::vector<BinarySearchNode<T>*>& nodes) const {
  breadthFirst(nodes, _root); 
}

template<typename T>
void 
BinarySearchTree<T>::
print() const { 
  print(_root); 
}

template<typename T>
BinarySearchNode<T>* 
BinarySearchTree<T>::
convertToList() {
  
  BinarySearchNode<T>* tail = nullptr; 
  convertToList(_root, tail); 

  
  

  BinarySearchNode<T>* head = _root; 
  _root = nullptr; 
  while (head->_left != nullptr) {
    head = head->_left; 
  }

  return head; 
}



template<typename T>
BinarySearchNode<T>* 
BinarySearchTree<T>::
clone(BinarySearchNode<T>* t) const {
  if (t == nullptr) {
    return nullptr; 
  } else {
    return new BinarySearchNode<T>{t->_data, clone(t->_left), clone(t->_right)}; 
  }
}

template<typename T>
void 
BinarySearchTree<T>::
insert(const T& x, BinarySearchNode<T>*& t) {
  if (t == nullptr) {
    t = new BinarySearchNode<T>{x, nullptr, nullptr}; 
  } else if (Less(x, t->_data)) {
    insert(x, t->_left); 
  } else if (Less(t->_data, x)) {
    insert(x, t->_right); 
  } else {} 
}

template<typename T>
void 
BinarySearchTree<T>::
insert(T&& x, BinarySearchNode<T>*& t) {
  if (t == nullptr) {
    t = new BinarySearchNode<T>{std::move(x), nullptr, nullptr}; 
  } else if (Less(x, t->_data)) {
    insert(std::move(x), t->_left); 
  } else if (Less(t->_data, x)) {
    insert(std::move(x), t->_right); 
  } else {} 
}



























template<typename T>
void 
BinarySearchTree<T>::
remove(const T& x, BinarySearchNode<T>*& t) {
  if (t == nullptr) {
    return ; 
  } 
  if (Less(x, t->_data)) {
    remove(x, t->_left); 
  } else if (Less(t->_data, x)) {
    remove(x, t->_right); 
  } else if ((t->_left != nullptr ) && (t->_right != nullptr)) {
    t->_data = findMin(t->_right)->_data; 
    remove(t->_data, t->_right); 
  } else {
    BinarySearchNode<T>* tmp = t; 
    t = (t->_left != nullptr) ? t->_left : t->_right; 
    delete tmp; 
  }
}

template<typename T>
BinarySearchNode<T>* 
BinarySearchTree<T>::
findMin(BinarySearchNode<T>* t) const {
  if ((t == nullptr) || (t->_left == nullptr)) {
    return t; 
  } else {
    return findMin(t->_left); 
  }
}

template<typename T>
BinarySearchNode<T>* 
BinarySearchTree<T>::
findMax(BinarySearchNode<T>* t) const {
  if (t != nullptr) {
    while (t->right != nullptr) {
      t = t->_right; 
    }
  }
  return t; 
}
















template<typename T>
bool 
BinarySearchTree<T>::
contains(const T& x, BinarySearchNode<T>* t) const {
  while (t != nullptr) {
    if (Less(x, t->_data)) {
      t = t->_left; 
    } else if (Less(t->_data, x)) {
      t = t->_right; 
    } else {
      return true; 
    }
  }
  return false; 
}

template<typename T>
void 
BinarySearchTree<T>::
makeEmpty(BinarySearchNode<T>*& t) { 
  if (t != nullptr) {
    makeEmpty(t->_left); 
    makeEmpty(t->_right); 
    delete t; 
  }
  t = nullptr; 
}

template<typename T>
void 
BinarySearchTree<T>::
preorder(std::vector<BinarySearchNode<T>*>& nodes, 
         BinarySearchNode<T>* t) const {
  if (t != nullptr) {
     nodes.push_back(t); 
     preorder(nodes, t->_left); 
     preorder(nodes, t->_right); 
  }
}

template<typename T>
void 
BinarySearchTree<T>::
inorder(std::vector<BinarySearchNode<T>*>& nodes, 
        BinarySearchNode<T>* t) const {
  if (t != nullptr) {
    inorder(nodes, t->_left); 
    nodes.push_back(t); 
    inorder(nodes, t->_right); 
  }
}

template<typename T>
void 
BinarySearchTree<T>::
postorder(std::vector<BinarySearchNode<T>*>& nodes, 
          BinarySearchNode<T>* t) const {
  if (t != nullptr) {
    postorder(nodes, t->_left); 
    postorder(nodes, t->_right); 
    nodes.push_back(t); 
  }
}

template<typename T>
void 
BinarySearchTree<T>::
breadthFirst(std::vector<BinarySearchNode<T>*>& nodes, 
             BinarySearchNode<T>* t) const {
  if (t == nullptr)
    return ; 
  std::deque<BinarySearchNode<T>*> tmp; 
  tmp.push_back(t); 
  while (!tmp.empty()) {
    BinarySearchNode<T>* parent = tmp.front(); 
    tmp.pop_front(); 
    nodes.push_back(parent); 
    if (parent->_left != nullptr)
      tmp.push_back(parent->_left); 
    if (parent->_right != nullptr)
      tmp.push_back(parent->_right); 
  }
}

template<typename T>
void 
BinarySearchTree<T>::
print(BinarySearchNode<T>* t) const { 
  std::vector<BinarySearchNode<T>*> nodes; 
  
  
  
  breadthFirst(nodes, t); 
  typename std::vector<BinarySearchNode<T>*>::const_iterator iter; 
  for (iter = nodes.begin(); iter != nodes.end(); ++iter) {
    std::cout << (*iter)->_data << ' '; 
  }
}

template<typename T>
void 
BinarySearchTree<T>::
convertToList(BinarySearchNode<T>* parent, BinarySearchNode<T>*& tail) {
  if (parent == nullptr) {
    return ; 
  }
  
  if (parent->_left != nullptr) {
    convertToList(parent->_left, tail); 
  }

  parent->_left = tail; 
  if (tail != nullptr) {
    tail->_right = parent; 
  }
  tail = parent; 

  if (parent->_right != nullptr) {
    convertToList(parent->_right, tail); 
  }
}

template<typename T>
void 
BinarySearchTree<T>::
convertToList(BinarySearchNode<T>* parent) {
  if (parent == nullptr)
    return ; 
  if (parent->_left != nullptr) {
    convertToList(parent->_left); 
    while (parent->_left->_right != nullptr) {
      parent->_left = parent->_left->_right; 
    }
  }

  if (parent->_right != nullptr) {
    convertToList(parent->_right); 
    while (parent->_right->_left != nullptr) {
      parent->_right = parent->_right->_left; 
    }
  }

  if (parent->_left != nullptr) {
    parent->_left->_right = parent; 
  }

  if (parent->_right != nullptr) {
    parent->_right->_left = parent; 
  }
}

#endif
