#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include "gtest/gtest.h"




















struct Node;
using node_p = Node*;

struct Node {
  
  
  std::vector<int> keys;
  std::vector<node_p> childs;

  
  
  int size;

  
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
  
  using result_t = std::pair<node_p, int>;

  
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
    
    auto iter = root;
    if (iter->size < 2 * degree - 1) {
      insert_non_full(iter, val);
      return;
    }

    
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

    
    if (node_p->leaf) {
      assert(node_p->childs.size() == 0);
      
      if (static_cast<int>(node_p->keys.size()) > degree - 1) {
        node_p->keys.erase(node_p->keys.begin() + i);
        node_p->size -= 1;
        return true;
      }

      
      auto parent_p = search_r.parent;
      if (node_p != root) {assert(parent_p);}

      auto iter = std::find(parent_p->childs.begin(),
                            parent_p->childs.end(),
                            node_p);
      auto node_i = iter - parent_p->childs.begin();

      if (node_i == 0) {
        
        
        
        return true;
      }

      if (static_cast<uint64_t>(node_i) == parent_p->childs.size() - 1) {
        
        
        
        return true;
      }

      
      auto left_sib = parent_p->childs[node_i - 1];
      auto r_sib = parent_p->childs[node_i + 1];
      if (static_cast<int>(left_sib->keys.size()) > degree - 1) {
        
        
      } else {
        if (static_cast<int>(r_sib->keys.size()) > degree - 1) {
          
          
        } else {
          
          
          
        }
      }
      return true;
    }
    

    
    auto pre_child = node_p->childs[i];
    auto suc_child = node_p->childs[i + 1];
    if (static_cast<int>(pre_child->keys.size()) > degree - 1) {
      
      auto pre_size = pre_child->keys.size();
      auto pre_key = pre_child->keys[pre_size - 1];
      pre_child->keys[pre_size - 1] = val;
      node_p->keys[i] = pre_key;

      
      del(val);
    } else {
      if (static_cast<int>(suc_child->keys.size()) > degree - 1) {
        
        auto suc_key = suc_child->keys[0];
        suc_child->keys[0] = val;
        node_p->keys[i] = suc_key;
        del(val);
      } else {
        
        

        

        
        
      }
    }
    

    return true;
  };



private:
  node_p root;
  int degree;

  
  int count = 0;
  void disk() {
    count += 1;
  }

  void insert_non_full(node_p node, int val) {
    
    auto i = node->size - 1;
    if (node->leaf) {
      
      node->keys.emplace_back(-1);
      while (i >= 0 && val < node->keys[i]) {
        node->keys[i + 1] = node->keys[i];
        --i;
      }
      node->keys[i + 1] = val;
      node->size += 1;
      return;
    }

    
    while (i >= 0 && val < node->keys[i]) {
      --i;
    }
    ++i;

    
    if (node->childs[i] && node->childs[i]->size == 2 * degree - 1) {
      split_child(node, i);

      
      if (node->keys[i] < val) {++i;}
    }
    insert_non_full(node->childs[i], val);
  }

  Result search(node_p parent, node_p node, int val) {
    
    int index = 0;
    while (index <= node->size && index < static_cast<int>(node->keys.size()) && val > node->keys[index]) {
      index += 1;
    }

    
    if (index <= node->size && val == node->keys[index]) {
      
      return Result(parent, node, index);
    } else if (node->leaf) {
      
      return Result(parent, nullptr, -1);
    }

    
    disk();
    return search(node, node->childs[index], val);
  }


  void split_child(node_p node, int i) {
    
    

    auto sib = new Node();
    auto child = node->childs[i];

    
    
    
    sib->leaf = child->leaf;
    sib->size = degree - 1;

    
    sib->keys = {std::make_move_iterator(child->keys.begin() + degree),
                 std::make_move_iterator(child->keys.end())};
    child->keys.erase(child->keys.begin() + degree - 1, child->keys.end());

    
    
    if (!child->leaf) {
      sib->childs = {std::make_move_iterator(child->childs.begin() + degree),
                     std::make_move_iterator(child->childs.end())};
      child->childs.erase(child->childs.begin() + degree, child->childs.end());
    }
    child->size = degree - 1;

    
    
    
    node->childs.insert(node->childs.begin() + i + 1, sib);
    node->keys.insert(node->keys.begin() + i, child->keys[degree - 1]);
    node->size += 1;

    
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

    
    check_keys(node->keys);

    
    if (node != root) {
      assert(static_cast<uint64_t>(degree - 1) <= node->keys.size());
      assert(static_cast<uint64_t>(2 * degree - 1) >= node->keys.size());
    }

    assert(node->size == static_cast<int>(node->keys.size()));

    
    if (node->leaf) {
      assert(node->childs.size() == 0);
    } else {
      
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
