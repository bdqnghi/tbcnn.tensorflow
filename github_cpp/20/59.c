#include "red-black-tree.h"
#include "stdafx.h"
using namespace std;


Node* getUncle(Node* curr) {
	if (curr->parent->parent->left == curr->parent) {
		printf("right uncle\n");
		return curr->parent->parent->right;
	}
	else if (curr->parent->parent->right == curr->parent){
		printf("left uncle\n");
		return curr->parent->parent->left;
	}
	else {
		printf("Error, the node cannot be found\n");
		exit(1);
	}
};


void RBT::rebalance(Node* insert) {
	
	if (this->h < 2) {
		return;
	}

	Node* parent = insert->parent;
	Node* uncle = getUncle(insert);

	
	if (uncle == nullptr) {
		uncle = &Node(0);
		uncle->color = black;
	}

	
	if (parent->color == red) {
		
		
		if (uncle->color == red) {
			printf("red\n");
			uncle->color = black;
			parent->color = black;
			parent->parent->color = red;
		}
		
		else {
			Node* rootbranch = nullptr;
			if (parent->parent->left == parent) {
				
				
				
				
				
				
				if (parent->left == insert) {
					printf("left left");
					
					
					
					
					
					rootbranch = parent->parent->parent;
					parent->parent->parent = parent->parent->left;
					parent->parent->left = parent->right;
					parent->right = parent->parent;

					
					parent->parent = rootbranch;

					
					parent->color = black;
					parent->right->color = red;
				} else if (parent->right == insert) {
					printf("left right");
					
					
					insert->left = parent;
					insert->parent = parent->parent;
					parent->right = nullptr;

					
					parent->parent = insert;
					parent = insert;

					
					rootbranch = parent->parent->parent;
					parent->parent->parent = parent->parent->left;
					parent->parent->left = parent->right;
					parent->right = parent->parent;

					
					parent->parent = rootbranch;

					
					parent->color = black;
					parent->right->color = red;
				}
			} else if(parent->parent->right == parent){
				if (parent->right == insert) {
					printf("right right");
					rootbranch = parent->parent->parent;
					parent->parent->parent = parent->parent->right;
					parent->parent->right = parent->left;
					parent->left = parent->parent;

					
					parent->parent = rootbranch;

					
					parent->color = black;
					parent->left->color = red;
				}
				
				else if (parent->left == insert) {
					printf("right left");
					
					
					insert->right = parent;
					insert->parent = parent->parent;
					parent->left = nullptr;

					
					parent->parent = insert;
					parent = insert;

					rootbranch = parent->parent->parent;
					parent->parent->parent = parent->parent->right;
					parent->parent->right = parent->left;
					parent->left = parent->parent;

					
					parent->parent = rootbranch;

					
					parent->color = black;
					parent->left->color = red;
				}
			}
			else {
				printf("huh");
			}
			
			
			if (rootbranch == nullptr) {
				this->tree = parent;
			}

		}
	} 
};

void RBT::trickle(Node* curr, Node* insert, int h) {
	if (insert->val <= curr->val) {
		if (curr->left) {
			this->trickle(curr->left, insert, h+1);
			return;
		}
		else {
			insert->parent = curr;
			curr->left = insert;
		}
	}
	else {
		if (curr->right) {
			this->trickle(curr->right, insert, h+1);
			return;
		}
		else {
			insert->parent = curr;
			curr->right = insert;
		}
	}

	this->h = h + 1;
	this->rebalance(insert);
	printf("%d\n", h + 1);
	return;

};

void RBT::insert(Node* node){
	if (this->tree == nullptr) {
		node->color = black;
		this->tree = node;
		this->bh = 2;
		return;
	}

	this->trickle(this->tree, node, 0);
};


void RBT::printTree(queue<Node*>& discover, int count, Node* curr) {
	if (curr == nullptr) {
		curr = this->tree;
	}

	
	
	
	auto checkNewLine = [=]() {
		int tmp = count;
		while (tmp != 0) {
			if (tmp & 0x1) {
				return (tmp == 1) ? true : false;
			} 
			tmp >>= 1;
		}
		return false;
	};

	if ((bool) checkNewLine()) {
		printf("\n");
	}

	printf("|%d,%d| ", curr->val, curr->color);
	
	if (curr->left) {
		discover.push(curr->left);
	}
	
	if (curr->right) {
		discover.push(curr->right);
	}

	if (discover.empty()) {
		return;
	}
	
	Node* next = discover.front();
	discover.pop();
	this->printTree(discover, count+1, next);
};

int main(){
	RBT& tr = RBT();
	tr.insert(new Node(10));
	tr.insert(new Node(15));
	
	
	tr.insert(new Node(13));
	tr.printTree(queue<Node *>(), 1);
	
	
};