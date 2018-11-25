





#include <iostream>
#include <queue>
#include <vector>

using namespace std;

enum NodeColor{
  RED, BLACK
};

class RedBlackTree{
public:
  RedBlackTree(){
    p = nullptr;
    left = nullptr;
    right = nullptr;
    color = BLACK;
  }  
  RedBlackTree(int key);
private:
  void leftRotate(RedBlackTree** root);
  void rightRotate(RedBlackTree** root);
  
  int key;
  NodeColor color;
  RedBlackTree* p;
  RedBlackTree* left;
  RedBlackTree* right;

  friend void rbInsert(RedBlackTree** root, RedBlackTree* z);
  friend void rbInsertFixup(RedBlackTree** root, RedBlackTree* z);
  friend ostream& operator<<(ostream& stream, const RedBlackTree& t);
};

ostream& operator<<(ostream& stream, const RedBlackTree& t);
void rbInsert(RedBlackTree** root, RedBlackTree* z);
void rbInsertFixup(RedBlackTree** root, RedBlackTree* z);

RedBlackTree Nil;

RedBlackTree::RedBlackTree(int key){
  this -> key = key;
  color = RED;
  p = &Nil;
  left = &Nil;
  right = &Nil;
}



ostream& operator<<(ostream& stream, const RedBlackTree& t){
  queue<const RedBlackTree*> s;
  s.push(&t);
  while(!s.empty()){
    auto e = s.front();
    cout << e -> key << " " << e -> color << endl;
    if(e -> left != &Nil){
      s.push(e -> left);
    }

    if(e -> right != &Nil){
      s.push(e -> right);
    }
    s.pop();
  }
  return stream;
}

void rbInsert(RedBlackTree** root, RedBlackTree* z){
  if(*root == &Nil){
    *root = z;
    (*root) -> color = BLACK;
    return;
  }

  auto y = &Nil;
  auto x = *root;
  
  while(x != &Nil){
    y = x;
    if(z -> key < x -> key){
      x = x -> left;
    }else{
      x = x -> right;
    }
  }

  z -> p = y;
  if(z -> key < y -> key){
    y -> left = z;
  }else{
    y -> right = z;
  }

  z -> color = RED;
  rbInsertFixup(root, z);
}

void rbInsertFixup(RedBlackTree** root, RedBlackTree* z){
  
  
  
  while(z -> p != &Nil && (z -> p) -> color == RED){
    auto y = z -> p;
    auto x = y -> p;
    if(y == x -> left){ 
      if(x -> right -> color == RED){
	x -> right -> color = BLACK;
	y -> color = BLACK;
	x -> color = RED;
	z = x;
      }else{
	if(z == y -> right){
	  z = z -> p;
	  z -> leftRotate(root);
	}
	z -> p -> color = BLACK;
	x -> color = RED;
	x -> rightRotate(root);
      }      
    } else {
      if(x -> left -> color == RED){
	x -> left -> color = BLACK;
	y -> color = BLACK;
	x -> color = RED;
	z = x;
      }else{
	if(z == y -> left){
	  z = z -> p;
	  z -> rightRotate(root);
	}
	z -> p -> color = BLACK;
	x -> color = RED;
	x -> leftRotate(root);
      }      
    }
  }

  (*root)->color = BLACK;
}

void RedBlackTree::leftRotate(RedBlackTree** root){
  auto y = this -> right;
  this -> right = y -> left;
  y -> left -> p = this;
  y -> p = this -> p;

  if(this -> p != &Nil){
    if(this == this -> p -> left){
      this -> p -> left = y;
    }else{
      this -> p -> right = y;
    }
  }else{
    *root = y;  
  }
  
  y -> left = this;
  this -> p = y;
}

void RedBlackTree::rightRotate(RedBlackTree** root){
  auto y = this -> left;
  this -> left = y -> right;
  y -> right -> p = this;
  y -> p = this -> p;

  if(this -> p != &Nil){
    if(this == this -> p -> left){
      this -> p -> left = y;
    }else{
      this -> p -> right = y;
    }
  }else{
    *root = y;
  }
  
  y -> right = this;
  this -> p = y;
}


int main(){
  vector<RedBlackTree> nodes{41, 38, 31, 12, 19, 8, 6, 4};
  RedBlackTree* root = &Nil;
  
  for(int i = 0; i < nodes.size(); i ++){
    rbInsert(&root, &nodes[i]);
  }
  
  cout << *root << endl;
  return 0;
}
