//
//  b-tree.cpp
//  Fusion Tree
//

#include "b-tree.hpp"
#include <algorithm>
#include <iostream>
#include "fusiontree.hpp"

using namespace std;

void b_node::print_node() const {
  cout << "---NODE " << this << "--" << endl;
  cout << "Fusion Tree:" << endl;
  cout << "is_leaf = " << is_leaf << endl;
  cout << *(this->key_tree) << endl;
  cout << "Children:" << endl;
  for (int i = 0; i < K + 1; i++) {
    cout << " " << children[i];
  }
  cout << endl << endl;
}

b_node::b_node(vector<big_int> &keys) {
  int num_keys = keys.size();
  vector<big_int> parent_keys;

  if (num_keys <= K) {
    is_leaf = true;
    parent_keys = keys;
    for (int i = 0; i <= K; i++) {
      children[i] = NULL;
    }
  }

  else {
    is_leaf = false;

    int num_children_keys = num_keys - K;
    int q_keys_per_subtree = num_children_keys / (K + 1);
    int r_keys_per_subtree = num_children_keys % (K + 1);

    int cur_key_index = 0;
    int cur_child_index = 0;

    while (cur_key_index < num_keys) {
      int num_keys_subtree = q_keys_per_subtree;
      if (cur_child_index < r_keys_per_subtree) {
        num_keys_subtree++;
      }
      if (num_keys_subtree > 0) {
        vector<big_int> subtree_keys =
            vector<big_int>(keys.begin() + cur_key_index,
                            keys.begin() + cur_key_index + num_keys_subtree);
        children[cur_child_index] = new b_node(subtree_keys);
        cur_key_index += num_keys_subtree;
      } else {
        children[cur_child_index] = NULL;
      }
      cur_child_index++;

      if (cur_key_index < num_keys) {
        parent_keys.push_back(keys[cur_key_index]);
        cur_key_index++;
      }
    }

    while (cur_child_index < K + 1) {
      children[cur_child_index] = NULL;
      cur_child_index++;
    }
  }

  key_tree = new fusiontree(parent_keys);

  print_node();
}

b_tree::b_tree(vector<big_int> &keys) {
  sort(keys.begin(), keys.end());
  root = new b_node(keys);
}

const big_int b_node::get_predecessor(const big_int &x) const {
  // cout << "get_predecessor(" << x << ", " << this << ")" << endl;
  int pred_index = key_tree->find_predecessor(x);
  // cout << "pred_index = " << pred_index << endl;
  if (children[pred_index + 1] == NULL) {
    if (pred_index == -1) {
      return -1;
    } else {
      return key_tree->pos(pred_index);
    }
  } else {
    big_int pred_child = children[pred_index + 1]->get_predecessor(x);
    if (pred_child == -1 && pred_index == -1) {
      return -1;
    } else if (pred_child == -1) {
      return key_tree->pos(pred_index);
    } else {
      return pred_child;
    }
  }
}

const big_int b_tree::get_predecessor(const big_int &x) const {
  return root->get_predecessor(x);
}
