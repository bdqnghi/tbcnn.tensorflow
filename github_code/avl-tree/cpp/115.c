
#include <iostream>

using namespace std;

struct node{
	node(int _val):val(_val),ht(0),left(NULL), right(NULL){}
	int val, ht;
	node *left, *right;
};

node* rightRotate(node* root){
	node *rootL = root->left;
	root->left = rootL->right;
	rootL->right = root;
	root->ht -=2;
	return rootL;
}

node* leftRotate(node* root){
	node *rootR = root->right;
	root->right = rootR->left;
	rootR->left = root;
	root->ht -=2;
	return rootR;
}

node* insert(node* root, int k){
	if(k < root->val){
		if(root->left)
			root->left = insert(root->left, k);
		else
			root->left = new node(k);
		if(root->right)
			root->ht = max(root->left->ht, root->right->ht) + 1;
		else
			root->ht = root->left->ht+1;
	}else{
		if(root->right)
			root->right = insert(root->right, k);
		else
			root->right = new node(k);
		if(root->left)
			root->ht = max(root->left->ht, root->right->ht) + 1;
		else
			root->ht = root->right->ht+1;
	}

	int lh = -1, rh = -1;
	if(root->left) lh = root->left->ht;
	if(root->right) rh = root->right->ht;
	int lrdiff = lh-rh;
	if( lrdiff > 1){
		if(k > root->left->val)
			root->left = leftRotate(root->left);
		return	rightRotate(root);
	}else if( lrdiff < -1){
		if(k < root->right->val)
			root->right = rightRotate(root->right);
		return 	leftRotate(root);
	}
	return root;
}

void preOrderTraversal(node* root){
	if(root){
		cout <<root->val<<"\t"<<root->ht<<endl;
		preOrderTraversal(root->left);
		preOrderTraversal(root->right);
	}
}

int main() {
	node *root = new node(5);
	root = insert(root, 4);
	root = insert(root, 3);
	root = insert(root, 2);
	root = insert(root, 1);

	cout<<"balanced tree is \n";
	preOrderTraversal(root);
	return 0;
} 
