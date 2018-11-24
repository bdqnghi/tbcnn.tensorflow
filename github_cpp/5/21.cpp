#include <fstream>
#include <iostream>
#include <stdlib.h>

#define nullptr 0

struct Vector {
  int data[100];
  int _size;
  Vector() { reset(); }
  void reset() { _size = 0; }
  void push(int d) { data[_size++] = d; }
  void rm(int d) {
    if (_size == 1) {
      if (data[0] == d) {
        --_size;
      }
    } else {
      bool found = false;
      for (int i = 0; i < _size; ++i) {
        if (data[i] == d) {
          for (int j = i; j < _size - 1; ++j) {
            data[j] = data[j + 1];
          }
          found = true;
          break;
        }
      }
      if (found)
        --_size;
    }
  }

  void copy(Vector &rhs) {
    _size = rhs._size;
    for (int i = 0; i < _size; ++i) {
      data[i] = rhs.data[i];
    }
  }
  int size() { return _size; }
  int &operator[](int idx) { return data[idx]; }
};

struct Node {
  int key; // key value
  Vector data;
  Node *left;  // left child
  Node *right; // right child
  int height;  // height of subtree from this node

  Node(Node &rhs) {
    key = rhs.key;
    data.copy(rhs.data);
    left = rhs.left;
    right = rhs.right;
    height = rhs.height;
  }

  Node() {
    key = 0;
    data.reset();
    left = right = nullptr;
    height = -1;
  }
};

class NodePool {
public:
  Node nodes[40000];
  int allocated;

  void reset() { allocated = 0; }
  NodePool() { reset(); }

  Node *alloc() { return &nodes[allocated++]; }
};
NodePool nodePool;

inline int max(int a, int b) { return a < b ? b : a; }

int height(Node *node) {
  if (node == nullptr)
    return -1;
  else
    return node->height;
}

void update_height(Node *node) {
  node->height = max(height(node->right), height(node->left)) + 1;
}

Node *gen_node(int key, int d) {
  Node *fresh = nodePool.alloc();
  fresh->key = key;
  fresh->data.reset();
  fresh->data.push(d);
  fresh->left = fresh->right = nullptr;
  fresh->height = 0;
  return fresh;
}

Node *left_rotate(Node *x) {
  Node *y = x->right;
  Node *B = y->left;

  // rotate to left means root x goes to left
  y->left = x;
  x->right = B;

  // update heights
  update_height(x);
  update_height(y);

  // root of subtree is changed
  return y;
}

Node *right_rotate(Node *y) {
  Node *x = y->left;
  Node *B = x->right;

  // rotate to right means root y goes to right
  y->left = B;
  x->right = y;

  // update heights
  update_height(x);
  update_height(y);

  // root of subtree is changed
  return x;
}

Node *balance(Node *node) {
  static int balancing_factor = 1;
  int hl = height(node->left), hr = height(node->right);

  if (hl > hr + balancing_factor) { // assert(node->left != nullptr)
    Node *l = node->left;
    int hll = height(l->left), hlr = height(l->right);
    if (hll < hlr) {
      node->left = left_rotate(node->left);
    }
    return right_rotate(node);
  } else if (hr > hl + balancing_factor) { // assert(node->right != nullptr)
    Node *r = node->right;
    int hrl = height(r->left), hrr = height(r->right);
    if (hrl > hrr) {
      node->right = right_rotate(node->right);
    }
    return left_rotate(node);
  } else { // no need to balance
    return node;
  }
}

bool less(int a, int b) { return a < b; }

Node *insert(Node *node, int key, int data) {
  if (node == nullptr) // base case -> found right place to insert
    return gen_node(key, data);

  // search right place
  if (less(key, node->key))
    node->left = insert(node->left, key, data);
  else if (less(node->key, key))
    node->right = insert(node->right, key, data);
  else {
    node->data.push(data);
  }

  // 1. update height
  update_height(node);

  // 2. balancing the subtree
  return balance(node);
}

Node *the_very_next_element(Node *node) {
  Node *cur = node;
  while (cur->left != nullptr) {
    cur = cur->left;
  }
  return cur;
}

Node *remove(Node *node, int key, int data) {
  if (node == nullptr) // base case -> empty, then return
    return nullptr;

  if (less(key, node->key)) {
    node->left = remove(node->left, key, data);
  } else if (less(node->key, key)) {
    node->right = remove(node->right, key, data);
  } else {
    // key found. actual remove.
    if (data == 0) {
      // remove all
      if (node->left == nullptr || node->right == nullptr) {
        // zero or one child only
        Node *child = node->left == nullptr ? node->right : node->left;
        if (child == nullptr) { // no child
          node = nullptr;
        } else { // one child
          *node = *child;
        }
      } else {
        // two children
        // get the very next element <-> the left most child of right sub tree
        Node *very_next = the_very_next_element(node->right);
        node->key = very_next->key; // swap only key
        node->data.copy(very_next->data);
        // remove the very next from right subtree
        node->right = remove(node->right, very_next->key, 0);
      }
    } else {
      node->data.rm(data);
      if (node->data.size() == 0) {
        if (node->left == nullptr || node->right == nullptr) {
          // zero or one child only
          Node *child = node->left == nullptr ? node->right : node->left;
          if (child == nullptr) { // no child
            node = nullptr;
          } else { // one child
            *node = *child;
          }
        } else {
          // two children
          // get the very next element <-> the left most child of right sub tree
          Node *very_next = the_very_next_element(node->right);
          node->key = very_next->key; // swap only key
          node->data.copy(very_next->data);
          // remove the very next from right subtree
          node->right = remove(node->right, very_next->key, 0);
        }
      }
    }
  }

  // after remove, tree can be empty
  if (node == nullptr)
    return nullptr;

  // 1. update heights
  update_height(node);

  // 2. balancing the subtree
  return balance(node);
}

void in_order(Node *root) {
  if (root != nullptr) {
    in_order(root->left);
    printf("%3d -> {", root->key);
    for (int i = 0; i < root->data.size(); ++i) {
      printf("%2d", root->data[i]);
      if (i != root->data.size() - 1)
        printf(", ");
    }
    printf("}\n");
    in_order(root->right);
  }
}

void pre_order(Node *root) {
  if (root != nullptr) {
    printf("{%d (%d)} ", root->key, root->height);
    pre_order(root->left);
    pre_order(root->right);
  }
}

void aux_null(int key, std::ofstream &out) {
  static int null_id = 0;
  out << "null" << null_id << " [shape=point];\n";
  out << key << " -> "
      << "null" << null_id << ";\n";

  ++null_id;
}

void aux_dot(Node *node, std::ofstream &out) {
  if (node->left != nullptr) {
    out << node->key << " -> " << node->left->key << ";\n";
    aux_dot(node->left, out);
  } else
    aux_null(node->key, out);

  if (node->right != nullptr) {
    out << node->key << " -> " << node->right->key << ";\n";
    aux_dot(node->right, out);
  } else
    aux_null(node->key, out);
}

void print_dot(Node *root, char *filename) {
  std::ofstream dot_output(filename);
  if (dot_output.is_open()) {
    dot_output << "digraph avltree{\nnode [shape=ellipse];\n";
    aux_dot(root, dot_output);
    dot_output << "}";

    dot_output.close();
  } else {
    printf("Unable to open file %s\n", filename);
  }
}

int main() {

  Node *root = nullptr; // initial root of avl tree is nullptr
  char filename[128] = {
      0,
  };

  const int Max = 10;
  for (int i = 0; i < Max; ++i) {
    int data_num = rand() % 10;
    for (int d = 1; d <= data_num; ++d)
      root = insert(root, i, d);
  }

  printf("===initial\n");
  in_order(root);

  // sprintf(filename, "initial.dot");
  // print_dot(root, filename);

  for (int i = 0; i < Max; ++i) {
    int data_rm = rand() % 10;
    if (data_rm != 5) {
      for (int d = 1; d <= data_rm; ++d) {
        if (rand() % 100 < 50) {
          printf("remove %d -> %d\n", i, d);
          root = remove(root, i, d);
          // in_order(root);
        }
      }
    } else
      root = remove(root, i, 0);

    in_order(root);
  }

  return 0;
}
