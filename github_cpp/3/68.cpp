
#include "AVLTree.h"
#include <string>
#include <iostream>

using namespace std;




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


AVLTree::AVLTree() {
  root = NULL;
}

AVLTree::~AVLTree() {

  while(root != NULL) {
    remove(root->value);
  }
  
}

void AVLTree::insert(const string& x) {
  
  
  if (root == NULL) {
    root = new AVLNode();
    root->value = x;

  } else if (find(x) == false) {
    insertHelper(root, x);
    
  }
  
}


void AVLTree::insertHelper(AVLNode *current, const string& x) {

  string cval = current->value;
  
  if (x.compare(cval) < 0) {
    
    if (current->left == NULL) {
      current->left = new AVLNode();
      current->left->value = x;
      
    } else {
      insertHelper(current->left, x);
      
    }
    
  } else if (x.compare(cval) > 0) {
    
    if (current->right == NULL) {
      current->right = new AVLNode();
      current->right->value = x;
      
    } else {
      insertHelper(current->right, x);
      
    }
    
  }

  
  current->height = heightCalculator(current);
  
  balance(current);
  
}


string AVLTree::pathTo(const string& x) const {

  string path = x;
  
  bool doCont = true;
  AVLNode *current = root;
  
  while (doCont) {

    string cval = current->value;

    if (x.compare(cval) == 0) {
      
      doCont = false;
      
    } else if (x.compare(cval) < 0) {
      
      current = current->left;
      path += " " + current->value;
      
    } else if (x.compare(cval) > 0) {
      
      current = current->right;
      path += " " + current->value;
      
    }

  }

  return path;

}


bool AVLTree::find(const string& x) const {

  bool doCont = true;
  AVLNode *current = root;
  
  while (doCont) {

    string cval = current->value;

    if (x.compare(cval) == 0) {
      
      return true;
      doCont = false;
      
    } else if (x.compare(cval) < 0) {
      
      if (current->left == NULL) {
	return false;
      } else {
	current = current->left;
      }
      
    } else if (x.compare(cval) > 0) {
      
      if (current->right == NULL) {
	return false;
      } else {
	current = current->right;
      }
      
    }

  }

  return false; 

}


int AVLTree::numNodes() const {

  cout << "root->value: " << root->value << endl;
  return numNodesHelper(root);

}


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


void AVLTree::balance(AVLNode*& n) {

  int lHeight = 0;
  int rHeight = 0;

  
  if (n->left != NULL) {
    lHeight = n->left->height;
  }
  if (n->right != NULL) {
    rHeight = n->right->height;
  }
  
  if (lHeight - rHeight == 2 || lHeight - rHeight == -2) {
    

    cout << "initiating a balance" << endl;
    
    
    if(n->left != NULL) {

      if(n->left->left != NULL) {
	
	n = rotateRight(n);
	
      } else { 
	
        n = rotateLeft(n);
        n = rotateRight(n);
      
      }
      
    } else { 

      if(n->right->left != NULL) {
	
        n = rotateRight(n);
	n = rotateLeft(n);
      
      } else { 
	
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






void AVLTree::remove(const string& x) { root = remove(root, x); }



AVLNode* AVLTree::remove(AVLNode*& n, const string& x) {
  if (n == NULL) {
    return NULL;
  }
  
  if (x == n->value) {
    
    
    if (n->left == NULL && n->right == NULL) {
      delete n;
      return NULL;
    }
    
    if (n->left == NULL) {
      return n->right;
    }
    if (n->right == NULL) {
      return n->left;
    }
    
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


int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}


string AVLTree::min(AVLNode* node) const {
  
  if (node->left == NULL) {
    return node->value;
  }
  return min(node->left);
}



int AVLTree::height(AVLNode* node) const {
  if (node == NULL) {
    return -1;
  }
  return node->height;
}
