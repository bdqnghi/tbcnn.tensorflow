//avl tree 
#include <iostream>
using namespace std;

struct node {
	int info,height;
	node *left,*right;
};

node *getnode (int data) {
	node *newnode = new node;
	newnode->info = data;
	newnode->height = 0;
	newnode->left = newnode->right = NULL;
	return newnode;
}

int height (node *curr) {
	if (curr == NULL)
		return 0;
	return curr->height; 
}

int getBalance (node *curr) {
	if (curr == NULL)
		return 0;
	return (height(curr->left) - height(curr->right));
}

node *leftleft (node *y) {
	node *x = y->left;
	node *subx = x->right;
	x->right = y;
	y->left = subx;
	
	y->height = 1 + max(height(y->left),height(y->right));
	x->height = 1 + max(height(x->left),height(x->right));
	
	return x;
}

node *rightright (node *y) {
	node *x = y->right;
	node *subx = x->left;
	x->left = y;
	y->right = subx;
	
	y->height = 1 + max(height(y->left),height(y->right));
	x->height = 1 + max(height(x->left),height(x->right));
	
	return x;
}

node *insert (node *root,int data) {
	if (root == NULL) 
		root = getnode(data);		
	else if (root->info > data)
		root->left = insert(root->left,data);
	else if (root->info < data)
		root->right = insert(root->right,data);
	else 
		return root;
		
	root->height = 1 + max(height(root->left),height(root->right));
	int balance = getBalance(root);
	
	if (balance == 2 && data < root->left->info) {//LL
		return leftleft(root);
	}
	else if (balance == 2 && data > root->left->info) {//LR
		root->left = rightright(root->left);
		return leftleft(root);
	}
	else if (balance == -2 && data > root->right->info) {//RR
		return rightright(root);
	}
	else if (balance == -2 && data < root->right->info) {//RL
		root->right = leftleft(root->right);
		return rightright(root);
	}
	
	return root;
}

void inorder (node *root) {
	if (root == NULL)
		return;
	inorder(root->left);
	cout<<root->info<<" ";
	inorder(root->right);
}

int main () {
	node *root = NULL;
	root = insert(root,25);
	root = insert(root,20);
	root = insert(root,35);
	root = insert(root,30);
	root = insert(root,24);
	inorder(root);
	cout<<"\n";
}
