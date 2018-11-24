#include<iostream>
using namespace std;

class SplayTree{
	private:
		struct Node{
			int data;
			Node* parent;
			Node* left;
			Node* right;
		};
		Node* head;
		
	public:
		SplayTree(){
			head = NULL;
		}
		
		void insert(int data){
			Node* node = head;
			Node* temp = NULL;
			while(node){
				if(data == node->data) return;
				temp = node;
				if(data < node->data) node = node->left;
				else node = node->right;
			}
			Node* new_node = new Node;
			new_node->data = data;
			new_node->parent = temp;
			new_node->left = new_node->right = NULL;
			if(temp){
				if(data < temp->data) temp->left = new_node;
				else temp->right = new_node;
			}
			splay(new_node);
			return;	
		}
		
		void splay(Node* splay_node){
			if(!splay_node->parent){
				head = splay_node;
				return;
			}
			if(splay_node->parent->parent){
				Node* grand_parent = splay_node->parent->parent;
				Node* _parent = splay_node->parent;
				if(grand_parent->left == _parent && _parent->left == splay_node) rrRotate(splay_node);
				else if(grand_parent->left == _parent && _parent->right == splay_node) lrRotate(splay_node);
				else if(grand_parent->right == _parent && _parent->left == splay_node) rlRotate(splay_node);
				else llRotate(splay_node);
			}else{
				Node* _parent = splay_node->parent;
				if(_parent->left == splay_node) rRotate(splay_node);
				else lRotate(splay_node);
			}
			splay(splay_node);
		}
		
		void rrRotate(Node* splay_node){
			rRotate(splay_node->parent);
			rRotate(splay_node);
		}
		
		void lrRotate(Node* splay_node){
			lRotate(splay_node);
			rRotate(splay_node);
		}
		
		void rlRotate(Node* splay_node){
			rRotate(splay_node);
			lRotate(splay_node);
		}
		
		void llRotate(Node* splay_node){
			lRotate(splay_node->parent);
			lRotate(splay_node);
		}
		
		void rRotate(Node* splay_node){
			Node* right_child = splay_node->right;
			Node* _parent = splay_node->parent;
			Node* grand_parent = _parent->parent;
			
			_parent->left = right_child;
			if(right_child) right_child->parent = _parent;
			_parent->parent = splay_node;
			
			splay_node->right = _parent;
			splay_node->parent = grand_parent;
			
			if(grand_parent){
				if(grand_parent->left == _parent) grand_parent->left = splay_node;
				else grand_parent->right = splay_node;
			}
		}
		
		void lRotate(Node* splay_node){
			Node* left_child = splay_node->left;
			Node* _parent = splay_node->parent;
			Node* grand_parent = _parent->parent;
			
			_parent->right = left_child;
			if(left_child) left_child->parent = _parent;
			_parent->parent = splay_node;
			
			splay_node->left = _parent;
			splay_node->parent = grand_parent;
			
			if(grand_parent){
				if(grand_parent->left == _parent) grand_parent->left = splay_node;
				else grand_parent->right = splay_node;
			}
		}
		
		void search(int data){
			Node* node = head;
			Node* temp;
			int found = 0;
			while(node){
				temp = node;
				if(data == node->data){
					found = 1;
					break;
				}else if(data < node->data) node = node->left;
				else node = node->right;
			}
			if(found) cout<<"Data Found!"<<endl;
			else cout<<"Not Found!"<<endl;
			splay(temp);
		}
		
		void remove(int data){
			search(data);
			if(head->data != data) return;

			Node* left_child = head->left;
			Node* right_child = head->right;
			if(left_child) left_child->parent = NULL;
			if(right_child) right_child->parent = NULL;
			delete head;
			if(!left_child){
				head = right_child;
				return;
			}
			head = left_child;
			search(INT_MAX);
			head->right = right_child;
			return;
		}
		
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
	SplayTree tree;
	tree.insert(4);
	tree.insert(5);
	tree.insert(3);
	tree.insert(15);
	tree.insert(51);
	tree.insert(1);
	tree.insert(17);
	tree.search(12);
	tree.remove(17);
	tree.print_pre_order();
	return 0;
}
