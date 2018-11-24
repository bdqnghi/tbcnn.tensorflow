#include "red-black-tree.h"
#include "stdafx.h"
using namespace std;

/*
* Assuming we only insert above 2 levels
*/
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

/*
* Red and black trees are all about the uncles
* If uncle is red do recoloring
* If uncle is black do rotation
*/
void RBT::rebalance(Node* insert) {
	//Not necessary to rebalance if there are less than 2 levels
	if (this->h < 2) {
		return;
	}

	Node* parent = insert->parent;
	Node* uncle = getUncle(insert);

	//If nullptr uncle, create a black placeholder node on the stack
	if (uncle == nullptr) {
		uncle = &Node(0);
		uncle->color = black;
	}

	//Rebalance
	if (parent->color == red) {
		//If uncle red
		//Recolor upper 2 levels and check depth
		if (uncle->color == red) {
			printf("red\n");
			uncle->color = black;
			parent->color = black;
			parent->parent->color = red;
		}
		//If uncle black
		else {
			Node* rootbranch = nullptr;
			if (parent->parent->left == parent) {
				//Child left:
				//Rotate sub tree starting from grand parent right
				//Dealing with rights:
				//The grandparent used to have a left, but after rotate the 
				//left becomes the parent. So any sibling of current insert
				//goes onto the left of the previous root
				if (parent->left == insert) {
					printf("left left");
					//Relocate right
					//You should always manipulate the top level nodes first
					//Because you do not have direct access to them. If you sever
					//your relative links before you complete all changes to the 
					//indirect nodes then you lose reference to them
					rootbranch = parent->parent->parent;
					parent->parent->parent = parent->parent->left;
					parent->parent->left = parent->right;
					parent->right = parent->parent;

					//Severing link
					parent->parent = rootbranch;

					//Recolor
					parent->color = black;
					parent->right->color = red;
				} else if (parent->right == insert) {
					printf("left right");
					//Rotate into the left left format first
					//Rotate child and parent
					insert->left = parent;
					insert->parent = parent->parent;
					parent->right = nullptr;

					//Severing ties
					parent->parent = insert;
					parent = insert;

					//Perform the standard left-left rotation
					rootbranch = parent->parent->parent;
					parent->parent->parent = parent->parent->left;
					parent->parent->left = parent->right;
					parent->right = parent->parent;

					//Severing link
					parent->parent = rootbranch;

					//Recolor
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

					//Severing link
					parent->parent = rootbranch;

					//Recolor
					parent->color = black;
					parent->left->color = red;
				}
				//Child left
				else if (parent->left == insert) {
					printf("right left");
					//Rotate into the right right format first
					//Rotate child and parent
					insert->right = parent;
					insert->parent = parent->parent;
					parent->left = nullptr;

					//Severing ties
					parent->parent = insert;
					parent = insert;

					rootbranch = parent->parent->parent;
					parent->parent->parent = parent->parent->right;
					parent->parent->right = parent->left;
					parent->left = parent->parent;

					//Severing link
					parent->parent = rootbranch;

					//Recolor
					parent->color = black;
					parent->left->color = red;
				}
			}
			else {
				printf("huh");
			}
			
			//If root has changed, then we need to update root
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

/*
* Print using BFS
* Keep a queue of nodes. When new node 
* discovered, push node onto queue.
*/
void RBT::printTree(queue<Node*>& discover, int count, Node* curr) {
	if (curr == nullptr) {
		curr = this->tree;
	}

	//If there is only one on bit in the number then it is beginning
	//Right shift until first bit is on. 
	//If number is not 1
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
	//tr.insert(new Node(20));
	//tr.insert(new Node(7));
	tr.insert(new Node(13));
	tr.printTree(queue<Node *>(), 1);
	//tr.insert(new Node(3));
	//tr.insert(new Node(1));
};