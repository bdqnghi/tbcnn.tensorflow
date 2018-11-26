/*
Damon Cestaro
dmc7by
2/28/18
AVLTree.cpp
*/
#include "AVLTree.h"
#include <string>
#include <iostream>

using namespace std;
//variables from node .h
/*
string value;
AVLNode* left;
AVLNode* right;
int height;
    from tree .h
AVLNode* root;
*/

//initializing node
AVLNode::AVLNode() {

  value = "";
  left = NULL;
  right = NULL;
  height = 1;

}

AVLNode& AVLNode::operator=(AVLNode& equivalent) {

  value = equivalent.value;
  left = equivalent.left;
  right = equivalent.right;
  height = equivalent.height;
  return *this;
  
}

//initializing tree
AVLTree::AVLTree() {
  root = NULL;
}

AVLTree::~AVLTree() {

  while(root != NULL) {
    remove(root->value);
  }
  
}

void AVLTree::insert(const string& x) {
  
  //if root dosen't exist insert there.  Else go to helper.
  if (root == NULL) {
    root = new AVLNode();
    root->value = x;

  } else if (find(x) == false) {
    insertHelper(root, x);
    
  }
  
}

//this program will only run if no node with value=x exists
void AVLTree::insertHelper(AVLNode *current, const string& x) {

  string cval = current->value;
  
  if (x.compare(cval) < 0) {
    //head left if possible
    if (current->left == NULL) {
      current->left = new AVLNode();
      current->left->value = x;
      
    } else {
      insertHelper(current->left, x);
      
    }
    
  } else if (x.compare(cval) > 0) {
    //head right if possible
    if (current->right == NULL) {
      current->right = new AVLNode();
      current->right->value = x;
      
    } else {
      insertHelper(current->right, x);
      
    }
    
  }

  //find the new height of this node
  current->height = heightCalculator(current);
  //does this node need balancing?
  balance(current);
  
}

//this code is copied verbatim from the BinarySearchTree.pathTo() method
string AVLTree::pathTo(const string& x) const {

  string path = x;
  
  bool doCont = true;
  AVLNode *current = root;
  
  while (doCont) {

    string cval = current->value;

    if (x.compare(cval) == 0) {
      //we've reached the end
      doCont = false;
      
    } else if (x.compare(cval) < 0) {
      //head left
      current = current->left;
      path += " " + current->value;
      
    } else if (x.compare(cval) > 0) {
      //head right
      current = current->right;
      path += " " + current->value;
      
    }

  }

  return path;

}

//this code is copied verbatim from the BinarySearchTree.find() method
bool AVLTree::find(const string& x) const {

  bool doCont = true;
  AVLNode *current = root;
  
  while (doCont) {

    string cval = current->value;

    if (x.compare(cval) == 0) {
      //found x
      return true;
      doCont = false;
      
    } else if (x.compare(cval) < 0) {
      //head left if possible
      if (current->left == NULL) {
	return false;
      } else {
	current = current->left;
      }
      
    } else if (x.compare(cval) > 0) {
      //head right if possible
      if (current->right == NULL) {
	return false;
      } else {
	current = current->right;
      }
      
    }

  }

  return false; //should never run, but is here to avoid warning

}

//this code is copied verbatim from the BinarySearchTree.numNodes() method
int AVLTree::numNodes() const {

  cout << "root->value: " << root->value << endl;
  return numNodesHelper(root);

}

//this code is copied verbatim from the BinarySearchTree.numNodesHelper() method
int AVLTree::numNodesHelper(AVLNode *current) const {

  int count = 0;
  
  if (current->left != NULL) {
    count += numNodesHelper(current->left);
  }
  
  if (current->right != NULL) {
    count += numNodesHelper(current->right);
  }

  return count+1;

}

//checks if balancing is needed, and if so does correct sequence
void AVLTree::balance(AVLNode*& n) {

  int lHeight = 0;
  int rHeight = 0;

  //need to make sure n->(direction) exists before calling (direction)->height
  if (n->left != NULL) {
    lHeight = n->left->height;
  }
  if (n->right != NULL) {
    rHeight = n->right->height;
  }
  
  if (lHeight - rHeight == 2 || lHeight - rHeight == -2) {
    //need to make a correction

    cout << "initiating a balance" << endl;
    
    //This node can only have 1 child node
    if(n->left != NULL) {

      if(n->left->left != NULL) {
	//left subtree left child
	n = rotateRight(n);
	
      } else { //n->left->right != NULL)
	//left subtree right child
        n = rotateLeft(n);
        n = rotateRight(n);
      
      }
      
    } else { //n->right != NULL)

      if(n->right->left != NULL) {
	//right subtree left child
        n = rotateRight(n);
	n = rotateLeft(n);
      
      } else { //n->right->right != NULL)
	//right subtree right child
	cout << "n->value 1.0: " << n->value << endl;
	cout << "root->value 1.0: " << root->value << endl;
	n = rotateLeft(n);
	cout << "n->value 2.0: " << n->value << endl;
	cout << "root->value 2.0: " << root->value << endl;
      
      }
      
    }
    
  }

}

AVLNode* AVLTree::rotateLeft(AVLNode*& n) {

  AVLNode *rightNode = n->right;
  n->right = rightNode->left;
  rightNode->left = n;

  n->height = heightCalculator(n);
  rightNode->height = heightCalculator(rightNode);

  cout << "rightNode->value: " << rightNode->value << endl;
  cout << "n->value in rotate: " << n->value << endl;
  n = rightNode;
  cout << "rightNode->value: " << rightNode->value << endl;
  cout << "n->value in rotate: " << n->value << endl;
  
  return rightNode;
  
}

AVLNode* AVLTree::rotateRight(AVLNode*& n) {

  AVLNode *leftNode = n->left;
  n->left = leftNode->right;
  leftNode->right = n;

  n->height = heightCalculator(n);
  leftNode->height = heightCalculator(leftNode);
  
  return leftNode;

}

int AVLTree::heightCalculator(AVLNode* current) {

  int lHeight = 0;
  int rHeight = 0;
  
  if(current->left != NULL) {
    lHeight = current->left->height;
  }

  if(current->right != NULL) {
    rHeight = current->right->height;
  }

  return max(lHeight, rHeight)+1;

}

/*
POINT WHERE MY WORK STOPS
**************************************************
**************************************************
*/

// The following are implemented for you
// remove finds x's position in the tree and removes it, rebalancing as
// necessary.
void AVLTree::remove(const string& x) { root = remove(root, x); }

// private helper for remove to allow recursion over different nodes. returns
// an AVLNode* that is assigned to the original node.
AVLNode* AVLTree::remove(AVLNode*& n, const string& x) {
  if (n == NULL) {
    return NULL;
  }
  // first look for x
  if (x == n->value) {
    // found
    // no children
    if (n->left == NULL && n->right == NULL) {
      delete n;
      return NULL;
    }
    // single child
    if (n->left == NULL) {
      return n->right;
    }
    if (n->right == NULL) {
      return n->left;
    }
    // two children -- tree may become unbalanced after deleting n
    string sr = min(n->right);
    n->value = sr;
    n->right = remove(n->right, sr);
  } else if (x < n->value) {
    n->left = remove(n->left, x);
  } else {
    n->right = remove(n->right, x);
  }
  n->height = 1 + max(height(n->left), height(n->right));
  balance(n);
  return n;
}

// max returns the greater of two integers.
int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

// min finds the string with the smallest value in a subtree.
string AVLTree::min(AVLNode* node) const {
  // go to bottom-left node
  if (node->left == NULL) {
    return node->value;
  }
  return min(node->left);
}

// height returns the value of the height field in a node. If the node is
// null, it returns -1.
int AVLTree::height(AVLNode* node) const {
  if (node == NULL) {
    return -1;
  }
  return node->height;
}
