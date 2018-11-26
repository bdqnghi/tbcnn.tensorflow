#include <iostream>
using namespace std;

//make use of this: http://en.wikipedia.org/wiki/Red%E2%80%93black_tree
//and this: http://www.sanfoundry.com/cpp-program-implement-red-black-tree/
class Node{
public:
	int data;
	string color;
	Node* left;
	Node* right;
	Node* parent;
	int key;
	Node(int datum, string coloring,Node* lefty,Node* righty){
		data = datum;
		color = coloring;
		left = lefty;
		right = righty;
	}
};



class RedBlackTree{
public:
	Node* root;
	RedBlackTree(){}
	bool exists(int data){
		if(root!=NULL){
			if(root->data==data){
				return true;
			}else{
				return exists(data,root);
			}
		}else{
			return false;
		}
	}

	void insert(int data){
		if(root==NULL){
			root = new Node(data,"red",NULL,NULL);
		}else{

			insert(data,root);
		}
	}
	void remove(int data);
	
private:
	bool exists(int data,Node* cur){
		if(cur==NULL){
			return false;
		}
		if(cur-> data == data){
			return true;
		}
		if(cur->data < data){
			exists(data,cur->left);
		}else{
			exists(data,cur->right);
		}
	}

	void insert(int data, Node* leaf){

	}
	void rotate_left(Node* ){

	}
	void remove(int data, Node* leaf);
};

int main(){
	cout << "Hello";
	return 0;
}
