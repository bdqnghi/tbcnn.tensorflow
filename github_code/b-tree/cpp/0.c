//===-- SplayTree.h - Splay Tree Implementation -----------------*- C++ -*-===//
// 
//                         Automatic Pool Allocation
//
// This file was developed by the LLVM research group and is distributed under
// the University of Illinois Open Source License. See LICENSE.TXT for details.
// 
//===----------------------------------------------------------------------===//
//
// This file implements several splay tree classes.
//
//===----------------------------------------------------------------------===//

#include <memory>
#include <vector>

#ifndef SUPPORT_SPLAYTREE_H
#define SUPPORT_SPLAYTREE_H

template<typename dataTy>
struct range_tree_node {
  range_tree_node(void* s, void* e) : left(0), right(0), start(s), end(e) {}
  range_tree_node() : left(0), right(0), start(0), end(0) {}
  template<class O>
  void do_act(O& act) { act(start, end, data); }
  range_tree_node* left;
  range_tree_node* right;
  void* start;
  void* end;
  dataTy data;
};

template<>
struct range_tree_node <void>{
  range_tree_node(void* s, void* e) : left(0), right(0), start(s), end(e) {}
  range_tree_node() : left(0), right(0), start(0), end(0) {}
  template<class O>
  void do_act(O& act) { act(start, end); }
  range_tree_node* left;
  range_tree_node* right;
  void* start;
  void* end;
};

template<typename T, class _Alloc>
class RangeSplayTree {
 public:
  typedef range_tree_node<T> tree_node;
 private:
  typename _Alloc::template rebind<tree_node >::other __node_alloc;
  
  tree_node* Tree;
    
  tree_node* rotate_right(tree_node* p) {
    tree_node* x = p->left;
    p->left = x->right;
    x->right = p;
    return x;
  }

  tree_node* rotate_left(tree_node* p) {
    tree_node* x = p->right;
    p->right = x->left;
    x->left = p;
    return x;
  }

  bool key_lt(void* _key, tree_node* _t) { return _key < _t->start; };

  bool key_gt(void* _key, tree_node* _t) { return _key > _t->end; };

  /* This function by D. Sleator <sleator@cs.cmu.edu> */
  tree_node* splay (tree_node * t, void* key) {
    tree_node N, *l, *r, *y;
    if (t == 0) return t;
    N.left = N.right = 0;
    l = r = &N;
    
    while(1) {
      if (key_lt(key, t)) {
        if (t->left == 0) break;
        if (key_lt(key, t->left)) {
          y = t->left;                           /* rotate right */
          t->left = y->right;
          y->right = t;
          t = y;
          if (t->left == 0) break;
        }
        r->left = t;                               /* link right */
        r = t;
        t = t->left;
      } else if (key_gt(key, t)) {
        if (t->right == 0) break;
        if (key_gt(key, t->right)) {
          y = t->right;                          /* rotate left */
          t->right = y->left;
          y->left = t;
          t = y;
          if (t->right == 0) break;
        }
        l->right = t;                              /* link left */
        l = t;
        t = t->right;
      } else {
        break;
      }
    }
    l->right = t->left;                                /* assemble */
    r->left = t->right;
    t->left = N.right;
    t->right = N.left;
    return t;
  }

  unsigned count_internal(tree_node* t) {
    if (t)
      return 1 + count_internal(t->left) + count_internal(t->right);
    return 0;
  }

  void __clear_internal(tree_node* tree) {
    //
    // If there is no node, then simply return.
    //
    if (!tree) return;

    // The set of elements yet to process
    std::vector<tree_node *> stack;
    stack.push_back (tree);

    //
    // Begin deleting elements.
    //
    while (stack.size()) {
      //
      // Remove the last node of the tree.
      //
      tree_node * t = stack.back();
      stack.pop_back();

      //
      // Push on to the stack for later processing the children.
      //
      if (t->left)  stack.push_back (t->left);
      if (t->right) stack.push_back (t->right);

      //
      // Delete the element.
      //
      __node_alloc.destroy(t);
      __node_alloc.deallocate(t, 1);
    }
  }

  template<class O>
  void __clear_internal(tree_node* t, O& act) {
    if (!t) return;
    __clear_internal(t->left);
    __clear_internal(t->right);
    t->do_act(act);
    __node_alloc.destroy(t);
    __node_alloc.deallocate(t, 1);
  }

 public:

  explicit RangeSplayTree(const _Alloc& a) :__node_alloc(a), Tree(0) {}
  ~RangeSplayTree() { __clear(); }
  
  tree_node* __insert(void* start, void* end) {
    Tree = splay(Tree, start);
    //If the key is already in, fail the insert
    if (Tree && !key_lt(start, Tree) && !key_gt(start, Tree))
      return 0;
    
    tree_node* n = __node_alloc.allocate(1);
    __node_alloc.construct(n, tree_node(start,end));
    if (Tree) {
      if (key_lt(start, Tree)) {
        n->left = Tree->left;
        n->right = Tree;
        Tree->left = 0;
      } else {
        n->right = Tree->right;
        n->left = Tree;
        Tree->right = 0;
      }
    }
    Tree = n;
    return Tree;
  }

  bool __remove(void* key) {
    if (!Tree) return false;
    Tree = splay(Tree, key);
    if (!key_lt(key, Tree) && !key_gt(key, Tree)) {
      tree_node* x = 0;
      if (!Tree->left)
        x = Tree->right;
      else {
        x = splay(Tree->left, key);
        x->right = Tree->right;
      }
      tree_node* y = Tree;
      Tree = x;
      __node_alloc.destroy(y);
      __node_alloc.deallocate(y, 1);
      return true;
    }
    return false; /* not there */
  }

  unsigned __count() {
    return count_internal(Tree);
  }

  void __clear() {
    __clear_internal(Tree);
    Tree = 0;
  }

  template <class O>
  void __clear(O& act) { 
    __clear_internal(Tree, act);
    Tree = 0;
  }

  tree_node* __find(void* key) {
    if (!Tree) return 0;
    Tree = splay(Tree, key);
    if (!key_lt(key, Tree) && !key_gt(key, Tree)) {
      return Tree;
    }
    return 0;
  }
};

template<class Allocator = std::allocator<void> >
class RangeSplaySet 
{
  RangeSplayTree<void, Allocator> Tree;

 public:
  explicit RangeSplaySet(const Allocator& A = Allocator() )
  : Tree(A) {}
  
  //
  // Method: insert()
  //
  // Description:
  //  Insert an element into the splay set.
  //
  // Inputs:
  //  start - The first valid address of the object.
  //  end   - The last valid address of the object.
  //
  // Return value:
  //  true  - The insert succeeded.
  //  false - The insert failed.
  //
  bool insert(void* start, void* end) {
    return 0 != Tree.__insert(start,end);
  }
  
  bool remove(void* key) {
    return Tree.__remove(key);
  }

  unsigned count() { return Tree.__count(); }

  void clear() { Tree.__clear(); }

  template <class O>
  void clear(O& act) { Tree.__clear(act); }

  bool find(void* key, void*& start, void*& end) {
    range_tree_node<void>* t = Tree.__find(key);
    if (!t) return false;
    start = t->start;
    end = t->end;
    return true;
  }
  bool find(void* key) {
    range_tree_node<void>* t = Tree.__find(key);
    if (!t) return false;
    return true;
  }
};

template<typename T, class Allocator = std::allocator<T> >
class RangeSplayMap {
  RangeSplayTree<T, Allocator> Tree;
  
  public:
  explicit RangeSplayMap(const Allocator& A= Allocator() ) 
  : Tree(A) {}
  
  bool insert(void* start, void* end, const T& d) {
    range_tree_node<T>* t = Tree.__insert(start,end);
    if (t == 0) return false;
    t->data = d;
    return true;
  }
  
  bool remove(void* key) {
    return Tree.__remove(key);
  }
  
  unsigned count() { return Tree.__count(); }
  
  void clear() { Tree.__clear(); }
  
  template <class O>
  void clear(O& act) { Tree.__clear(act); }
  
  bool find(void* key, void*& start, void*& end, T& d) {
    range_tree_node<T>* t = Tree.__find(key);
    if (!t) return false;
    start = t->start;
    end = t->end;
    d = t->data;
    return true;
  }
  bool find(void* key) {
    range_tree_node<T>* t = Tree.__find(key);
    if (!t) return false;
    return true;
  }
};

#endif
