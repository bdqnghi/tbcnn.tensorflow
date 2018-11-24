#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include "gtest/gtest.h"


// For a B-tree of degree(D), each non-root node contains
// (D-1) to (2D-1) keys, including D-1 and 2D-1:
//   D >= 2

//   Each node can hold up to 2t children.
//   Root has at least 2 children, if it has.

//   All leaves(node that has no children) are on same level.

//   Insert a key into node that contains 2D, will pop its mid
//   to parent, and split node into 2 nodes, each has D keys.

//   Increase height only by split root.

//   Delete key from node of D is ...?
//   https://github.com/algorithm-ninja/cpp-btree/blob/master/btree.h#L1861


struct Node;
using node_p = Node*;

struct Node {
  // Node holds keys/childs as a vector
  // manage by index
  std::vector<int> keys;
  std::vector<node_p> childs;

  // should be equal to keys.size()
  // keep it separate for accounting
  int size;

  // leaf: does not have child
  bool leaf;

  Node() {
    size = 0;
    leaf = true;
  }

  explicit Node(bool l) {
    size = 0;
    leaf = l;
  }

  ~Node() {
    for (auto p : childs) {
      delete p;
    }
  }
};

struct Result {
  node_p node;
  node_p parent;
  int index;

  Result(node_p p, node_p n, int i) {
    parent = p;
    node = n;
    index = i;
  }
};

class BTree {
public:
  // search result, if no result then <nullptr, -1>
  using result_t = std::pair<node_p, int>;

  // by default a 2-3 tree
  BTree() {
    root = new Node();
    degree = 2;
    disk();
  };

  explicit BTree(int _degree) {
    root = new Node();
    degree = std::move(_degree);
    disk();
  }

  ~BTree() {
    delete root;
  };

  auto disk_operation() {
    return count;
  }

  auto search(int val) {
    return search(nullptr, root, val);
  };

  void insert(int val) {
    // root is always initialized in ctor
    auto iter = root;
    if (iter->size < 2 * degree - 1) {
      insert_non_full(iter, val);
      return;
    }

    // else create new root r
    auto r = new Node();
    root = r;
    r->leaf = false;
    r->size = 0;
    r->childs.emplace_back(iter);
    split_child(r, 0);
    insert_non_full(r, val);
  };


  void check() {check(root);};

  bool del(int val) {
    auto search_r = search(val);
    if ((!search_r.node) || search_r.index == -1) {return false;}

    auto node_p = search_r.node;
    auto i = search_r.index;
    assert(*(node_p->keys.begin() + i) == val);

    // LEAF
    if (node_p->leaf) {
      assert(node_p->childs.size() == 0);
      // safest deletion: more than degree-1 keys on this leaf
      if (static_cast<int>(node_p->keys.size()) > degree - 1) {
        node_p->keys.erase(node_p->keys.begin() + i);
        node_p->size -= 1;
        return true;
      }

      // else borrow from sib
      auto parent_p = search_r.parent;
      if (node_p != root) {assert(parent_p);}

      auto iter = std::find(parent_p->childs.begin(),
                            parent_p->childs.end(),
                            node_p);
      auto node_i = iter - parent_p->childs.begin();

      if (node_i == 0) {
        // auto r_sib = parent_p->childs[node_i + 1];
        // borrow_right(node_p, r_sib);
        // del(val);
        return true;
      }

      if (static_cast<uint64_t>(node_i) == parent_p->childs.size() - 1) {
        // auto left_sib = parent_p->childs[node_i - 1];
        // borrow_left(node_p, left_sib);
        // del(val);
        return true;
      }

      // else not edge node, check left and right
      auto left_sib = parent_p->childs[node_i - 1];
      auto r_sib = parent_p->childs[node_i + 1];
      if (static_cast<int>(left_sib->keys.size()) > degree - 1) {
        // borrow_left(node_p, left_sib);
        // del(val);
      } else {
        if (static_cast<int>(r_sib->keys.size()) > degree - 1) {
          // borrow_right(node_p, r_sib);
          // del(val);
        } else {
          // now left/node/right both has t-1 keys
          // check if parent is also t-1, if not
          // FIXME:
        }
      }
      return true;
    }
    // LEAF END

    // INTERNAL
    auto pre_child = node_p->childs[i];
    auto suc_child = node_p->childs[i + 1];
    if (static_cast<int>(pre_child->keys.size()) > degree - 1) {
      // borrow from predecessor in left child
      auto pre_size = pre_child->keys.size();
      auto pre_key = pre_child->keys[pre_size - 1];
      pre_child->keys[pre_size - 1] = val;
      node_p->keys[i] = pre_key;

      // recursively delete it
      del(val);
    } else {
      if (static_cast<int>(suc_child->keys.size()) > degree - 1) {
        // try borrow from successor
        auto suc_key = suc_child->keys[0];
        suc_child->keys[0] = val;
        node_p->keys[i] = suc_key;
        del(val);
      } else {
        // FIXME:
        // move val Node to pre

        // combine pre and suc

        // del val recursively
        // del(val);
      }
    }
    // INTERNAL END

    return true;
  };



private:
  node_p root;
  int degree;

  // records disk operation
  int count = 0;
  void disk() {
    count += 1;
  }

  void insert_non_full(node_p node, int val) {
    // backwardly compare
    auto i = node->size - 1;
    if (node->leaf) {
      // insert a immediately-replaced-value for new key
      node->keys.emplace_back(-1);
      while (i >= 0 && val < node->keys[i]) {
        node->keys[i + 1] = node->keys[i];
        --i;
      }
      node->keys[i + 1] = val;
      node->size += 1;
      return;
    }

    // else not leaf
    while (i >= 0 && val < node->keys[i]) {
      --i;
    }
    ++i;

    // see if child full, needs split
    if (node->childs[i] && node->childs[i]->size == 2 * degree - 1) {
      split_child(node, i);

      // after split, check which i have mid key
      if (node->keys[i] < val) {++i;}
    }
    insert_non_full(node->childs[i], val);
  }

  Result search(node_p parent, node_p node, int val) {
    // search for child(might have val)
    int index = 0;
    while (index <= node->size && index < static_cast<int>(node->keys.size()) && val > node->keys[index]) {
      index += 1;
    }

    // in case key->value == val, or reach leaf but no result
    if (index <= node->size && val == node->keys[index]) {
      // return std::make_pair(node, index);
      return Result(parent, node, index);
    } else if (node->leaf) {
      // return std::make_pair(nullptr, -1);
      return Result(parent, nullptr, -1);
    }

    // else dive in next level
    disk();
    return search(node, node->childs[index], val);
  }


  void split_child(node_p node, int i) {
    // child[i] is full: child[i]->size == 2d - 1
    // pop its median to node

    auto sib = new Node();
    auto child = node->childs[i];

    // child[i]'s neighbor will be on same level
    // of it, and own's right half of values.
    // it's child cound after split = (2d - 1 - 1) / 2
    sib->leaf = child->leaf;
    sib->size = degree - 1;

    // move keys to sib
    sib->keys = {std::make_move_iterator(child->keys.begin() + degree),
                 std::make_move_iterator(child->keys.end())};
    child->keys.erase(child->keys.begin() + degree - 1, child->keys.end());

    // if child is not leaf, it has childs, copy
    // right half(d-1) to new node, set left half's size.
    if (!child->leaf) {
      sib->childs = {std::make_move_iterator(child->childs.begin() + degree),
                     std::make_move_iterator(child->childs.end())};
      child->childs.erase(child->childs.begin() + degree, child->childs.end());
    }
    child->size = degree - 1;

    // sib will be node's childs[i+1]
    // child[d] will be node->keys[i]
    // child->keys will shrink to size of degree-1
    node->childs.insert(node->childs.begin() + i + 1, sib);
    node->keys.insert(node->keys.begin() + i, child->keys[degree - 1]);
    node->size += 1;

    // disk write for node, child and sib
    disk();
    disk();
    disk();
  }

  void borrow_left(node_p node, node_p left_sib) {
    auto left_size = left_sib->keys.size();
    auto left_key = left_sib->keys[left_size - 1];
    left_sib->keys.erase(left_sib->keys.begin() + left_size - 1);
    left_sib->size -= 1;
    node->keys.insert(node->keys.begin(), left_key);
    node->size += 1;
  }

  void borrow_right(node_p node, node_p r_sib) {
    auto r_key = r_sib->keys[0];
    r_sib->keys.erase(r_sib->keys.begin());
    r_sib->size -= 1;
    node->keys.emplace_back(r_key);
    node->size += 1;
  };




  void check_keys(std::vector<int> keys) {
    if (keys.size() <= 1) {return;}

    auto tmp = keys[0];
    int len = keys.size();
    for (int i = 1; i < len; ++i) {
      assert(tmp <= keys[i]);
      tmp = keys[i];
    }
  }

  void check(node_p node) {
    if (!node) {return ;}

    // keys should be ordered, note that non-null nodes have at least 1 key
    check_keys(node->keys);

    // all non-root node follow degree: d-1 <= size(key.size()) <= 2d -1
    if (node != root) {
      assert(static_cast<uint64_t>(degree - 1) <= node->keys.size());
      assert(static_cast<uint64_t>(2 * degree - 1) >= node->keys.size());
    }

    assert(node->size == static_cast<int>(node->keys.size()));

    // leaf node has no childs,
    if (node->leaf) {
      assert(node->childs.size() == 0);
    } else {
      // childs 1 more than keys(left/right child), if not leaf
      assert(node->keys.size() + 1 == node->childs.size());
      for (auto c : node->childs) {check(c);}
    }
  }

};


void test_insert(BTree &tree) {
  for (int i = 0; i < 1000; ++i) {
    tree.insert(i);
    tree.check();
  }
}

void test_delete(BTree &tree) {
  for (int i = 0; i < 400; ++i) {
    tree.del(i * 2);
    tree.check();
  }
}


TEST(BTreeTest, SomeTest) {
  auto tree = BTree(5);
  test_insert(tree);
  std::cout << tree.disk_operation() << std::endl;

  test_delete(tree);
  std::cout << tree.disk_operation() << std::endl;

  auto r = tree.search(-10);
  EXPECT_FALSE(r.node);
  EXPECT_EQ(r.index, -1);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
