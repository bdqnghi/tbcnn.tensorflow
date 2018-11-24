#include <iostream>
using namespace std;

template <class T> class Node;
template <class T> class RedBlackTree;

const char RED = 'r';
const char BLACK = 'b';

template <class T>
class Node {

  friend class RedBlackTree<T>;

private:
  T data;
  Node<T>* parent;
  Node<T>* left;
  Node<T>* right;
  char color;

public:
  Node(T d = T(), Node<T>* p = nullptr, Node<T>* l = nullptr, Node<T>* r = nullptr, char c = RED);

};

template <class T>
class RedBlackTree {

private:
  Node<T>* root;
  int size;
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
  RedBlackTree();
  RedBlackTree(const RedBlackTree<T>& rhs);
  ~RedBlackTree();
  RedBlackTree<T>& operator =(const RedBlackTree<T>& rhs);

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

}