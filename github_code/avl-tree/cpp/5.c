#include <iostream>
#include <cmath>

using namespace std;

typedef struct node
{
  int val;
  struct node* left;
  struct node* right;
  int ht;
} node;

node* insert(node * root,int val){
  // Insert val and balance tree
  if(root == null){
    node n;
    n.val = val;
    return &node;
  }

  node *current = root;

  if(root->val > val){
    root->left = insert(root->left, val);
  }else{
    root->right = insert(root->right, val);
  }

  if(abs(height(root->left) - height(root->right)) > 1)
    balance(root);
  return root;
}

void balance(node *root){
  
}
node* rotate_left(node *root){
  node *x = root->right;
  root->right = x->left;
  x->left = root;
  return x;
}
node* rotate_right(node *root){
  node *x = root->left;
  root->left = x->right;
  x->right = root;
  return x;
}
