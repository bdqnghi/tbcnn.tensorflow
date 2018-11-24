#include <stdio.h>
#define RED 1
#define BLACK 0

struct Node {
  Node * left, * right, *p;
  bool color;
  int key;
  
  void insert( Node * z );
  void insert_fix( Node * z );
};

Node NIL(BLACK,BLACK,BLACK,BLACK,BLACK);

void Node::insert( Node * z ) {
  Node * y = NIL;
  Node * x = this;

  while (x != NIL) {
    y = x;
    if ( x->key > z->key ) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  z->p = y;

  if (z->key < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }

  z->color = RED;
  z->right = z->left = 0;

  insert_fix(z);
}

void Node::insert_fix( Node * z ) {
    
}
