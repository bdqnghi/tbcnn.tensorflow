#include <iostream>
#include "catch.hpp"

using namespace std;

struct AvlNode {
  int element;
  AvlNode *left;
  AvlNode *right;
  int height;

  AvlNode(int _element, AvlNode *l, AvlNode *r, int _height = 0) {
    element = _element;
    height = _height;
    left = l;
    right = r;
  }
};

int height (AvlNode *t) {
  return t == nullptr ? -1 : t->height;
}

static const int ALLOWED_IMBALANCE = 1;

void rotateWithLeftChild(AvlNode *&k2) {
  AvlNode *k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  // update heights
  k2->height = max(height(k2->left), height(k2->right)) + 1;
  k1->height = max(height(k1->left), height(k1->right)) + 1;
  // fix original reference
  k2 = k1;
}

void rotateWithRightChild(AvlNode *&k1) {
  AvlNode *k2 = k1->right;
  k1->right = k2->left;
  k2->left = k1;
  // update heights
  k1->height = max(height(k1->left), height(k1->right)) + 1;
  k2->height = max(height(k2->left), height(k2->right)) + 1;
  // fix original reference
  k1 = k2;
}

void doubleWithLeftChild(AvlNode *&k3) {
  rotateWithRightChild(k3->left);
  rotateWithLeftChild(k3);
}

void doubleWithRightChild(AvlNode *&k3) {
  rotateWithLeftChild(k3->right);
  rotateWithRightChild(k3);
}

void balance(AvlNode *&t) {
  if (t == nullptr) return;
  if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
    if (height(t->left->left) >= height(t->left->right)) {
      // left left (single rotation)
      rotateWithLeftChild(t);
    } else {
      // left right (double rotation)
      doubleWithLeftChild(t);
    }
  } else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
    // reflections
    if (height(t->right->right) >= height(t->right->left)) {
      rotateWithRightChild(t);
    } else {
      doubleWithRightChild(t);
    }
  }
  t->height = max(height(t->left), height(t->right)) + 1;
}

void insert (int x, AvlNode *&t) {
  if (t == nullptr) {
    t = new AvlNode(x, nullptr, nullptr);
  } else if (x < t->element) {
    insert(x, t->left);
  } else if (t->element < x) {
    insert(x, t->right);
  }

  // after any insertion operation balance the tree
  balance(t);
}

void print(AvlNode *t, int level = 0) {
  if (t == nullptr) {
    return;
  }
  string spaces(level * 2, ' ');
  cout << spaces << t->element << "\n";
  print(t->right, level + 1);
  print(t->left, level + 1);
}


TEST_CASE("AVL Tree") {
  AvlNode *t = nullptr;
  REQUIRE(t == nullptr);

  SECTION("has an insert method") {
    insert(3, t);
    REQUIRE(t != nullptr);
    REQUIRE(t->element == 3);
  }

  SECTION("autobalance") {
    // 2 level perfect binary tree
    insert(4, t);
    insert(2, t);
    insert(1, t);
    insert(3, t);
    insert(6, t);
    insert(5, t);
    insert(7, t);

    // insert 16,15,14,13,12,11,10
    insert(16, t);
    insert(15, t);
    insert(14, t);
    insert(13, t);
    insert(12, t);
    insert(11, t);
    insert(10, t);

    // print(t);
    REQUIRE(height(t->left) - height(t->right) >= 0);
    REQUIRE(height(t->left) - height(t->right) <= 1);
  }

  SECTION("perfect tree") {
    insert(1, t);
    insert(2, t);
    insert(3, t);
    insert(4, t);
    insert(5, t);
    insert(6, t);
    insert(7, t);
    insert(8, t);
    insert(9, t);
    insert(10, t);
    insert(11, t);
    insert(12, t);
    insert(13, t);
    insert(14, t);
    insert(15, t);

    // print(t);
    REQUIRE(height(t->left) - height(t->right) == 0);
  }
}
