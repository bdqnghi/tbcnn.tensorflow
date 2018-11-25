#ifndef E_REDBLACK_TREE
#define E_REDBLACK_TREE


#include"misc.h"
#include"TemplateStack.H"
#include<math.h>
#include<limits.h>
#include<iostream>















#ifndef MAX_INT
#define MAX_INT INT_MAX 
#endif











class RedBlackEntry {
public:
  RedBlackEntry();
  virtual ~RedBlackEntry();
  virtual int GetKey() const = 0;
  virtual void Print() const;
};

class RedBlackTreeNode {
  friend class RedBlackTree;
public:
  void Print(RedBlackTreeNode*,
	     RedBlackTreeNode*) const;
  RedBlackTreeNode();
  RedBlackTreeNode(RedBlackEntry *);
  RedBlackEntry * GetEntry() const;
  ~RedBlackTreeNode();
protected:
  RedBlackEntry * storedEntry;
  int key;
  int red; 
  RedBlackTreeNode * left;
  RedBlackTreeNode * right;
  RedBlackTreeNode * parent;
};

class RedBlackTree {
public:
  RedBlackTree();
  ~RedBlackTree();
  void Print() const;
  RedBlackEntry * DeleteNode(RedBlackTreeNode *);
  RedBlackTreeNode * Insert(RedBlackEntry *);
  RedBlackTreeNode * GetPredecessorOf(RedBlackTreeNode *) const;
  RedBlackTreeNode * GetSuccessorOf(RedBlackTreeNode *) const;
  RedBlackTreeNode * Search(int key);
  TemplateStack<RedBlackTreeNode *> * Enumerate(int low, int high) ;
  void CheckAssumptions() const;
protected:
  
  
  
  
  
  
  RedBlackTreeNode * root;
  RedBlackTreeNode * nil;
  void LeftRotate(RedBlackTreeNode *);
  void RightRotate(RedBlackTreeNode *);
  void TreeInsertHelp(RedBlackTreeNode *);
  void TreePrintHelper(RedBlackTreeNode *) const;
  void FixUpMaxHigh(RedBlackTreeNode *);
  void DeleteFixUp(RedBlackTreeNode *);
};

#endif
