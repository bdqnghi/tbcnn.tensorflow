#include<iostream>
#include<math.h>
#define DEBUG 0
using namespace std;

class AvlTree{
	private:
		struct Node{
			int data;
			int leftHeight;
			int rightHeight;
			Node* parent;
			Node* left;
			Node* right;
		};
		Node* head;
		
	public:
		AvlTree(){
			head = NULL;
		}
		
		void insert(int data){
			if(DEBUG) cout<<"Insert "<<data<<endl;
			Node* node = head;
			Node* temp = NULL;
			while(node){
				temp = node;
				if(data == node->data) return;
				else if(data < node->data) node = node->left;
				else node = node->right;
			}
			Node* new_node = new Node;
			new_node->data = data;
			new_node->leftHeight = 0;
			new_node->rightHeight = 0;
			new_node->parent = temp;
			new_node->left = new_node->right = NULL;
			if(temp){
				if(data < temp->data) temp->left = new_node;
				else temp->right = new_node;
			}
			update(new_node);
		}
		
		void update(Node* node){
			if(!node) return;
			if(DEBUG) cout<<"Update "<<node->data<<endl;
			if(!node->parent){
				head = node;
			}
 			if(!node->left) node->leftHeight = 0;
			else node->leftHeight = max(node->left->leftHeight, node->left->rightHeight) + 1;
			if(!node->right) node->rightHeight = 0;
			else node->rightHeight = max(node->right->leftHeight, node->right->rightHeight) + 1;
			
			if(abs(node->leftHeight - node->rightHeight) > 1){
				balance(node);
				update(node);
			}else{
				update(node->parent);
			}
		}
		
		void balance(Node* node){
			if(DEBUG) cout<<"Balance "<<node->data<<endl;
			Node* child;
			if(node->leftHeight - node->rightHeight >= 2){ //left high
				child = node->left;
				if(child->leftHeight - child->rightHeight >= 0){ //left high
					rRotate(child);
				}else{ //right high
					lrRotate(child->right);
				}
			}else if(node->leftHeight - node->rightHeight <= -2){ //right high
				child = node->right;
				if(child->leftHeight - child->rightHeight <= 0){ //right high
					lRotate(child);
				}else{ //left high
					rlRotate(child->left);
				}
			}
		}
		
		void lrRotate(Node* node){
			if(DEBUG) cout<<"LR "<<node->data<<endl;
			lRotate(node);
			rRotate(node);
		}
		
		void rlRotate(Node* node){
			if(DEBUG) cout<<"RL "<<node->data<<endl;
			rRotate(node);
			lRotate(node);
		}
		
		void rRotate(Node* node){
			if(DEBUG) cout<<"R "<<node->data<<endl;
			Node* right_child = node->right;
			Node* _parent = node->parent;
			Node* grand_parent = _parent->parent;
			
			_parent->left = right_child;
			if(right_child) right_child->parent = _parent;
			_parent->parent = node;
			
			node->right = _parent;
			node->parent = grand_parent;
			
			if(grand_parent){
				if(grand_parent->left == _parent) grand_parent->left = node;
				else grand_parent->right = node;
			}
		}
		
		void lRotate(Node* node){
			if(DEBUG) cout<<"L "<<node->data<<endl;
			Node* left_child = node->left;
			Node* _parent = node->parent;
			Node* grand_parent = _parent->parent;
			
			_parent->right = left_child;
			if(left_child) left_child->parent = _parent;
			_parent->parent = node;
			
			node->left = _parent;
			node->parent = grand_parent;
			
			if(grand_parent){
				if(grand_parent->left == _parent) grand_parent->left = node;
				else grand_parent->right = node;
			}
		}
		
		bool search(int data){
			Node* node = head;
			while(node){
				if(node->data == data) return true;
				else if(data < node->data) node = node->left;
				else node = node->right;
			}
			return false;
		}
		
		/*
		void remove(int data){
			Node* node = head;
			while(node){
				if(node->data == data){
					
				}
				else if(data < node->data) node = node->left;
				else node = node->right;
			}
			return;
		}
		*/
		
		void print_pre_order(){
			print_pre_order(head);
		}
		
		void print_pre_order(Node* node){
			if(!node) return;
			if(node == head) cout<<node->data;
			else cout<<", "<<node->data;
			print_pre_order(node->left);
			print_pre_order(node->right);
		}
};

int main(){
	AvlTree tree;
	tree.insert(10);
	tree.insert(6);
	tree.insert(1);
	tree.insert(17);
	tree.insert(51);
	tree.insert(66);
	tree.insert(3);
	tree.print_pre_order();
}
