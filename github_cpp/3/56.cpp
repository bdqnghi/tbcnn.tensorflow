#include <bits/stdc++.h>
using namespace std;

struct Node {
	int key;
	struct Node* left;
	struct Node* right;
	int height;
};
typedef struct Node Node;

int height(Node *N) {
	if(N == NULL) return 0;
	return N->height;
}

Node* newNode(int key) {
	Node* node = (Node*) malloc(sizeof(Node));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	
	return node;
}

Node* leftRotate(Node *x) {
	Node* y = x->right;
	Node* T2 = y->left;

	y->left = x;
	x->right = T2;

	y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

	return y;
}

Node* rightRotate(Node *y) {
	Node *x = y->left;
	Node *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

int getBalance(Node *x) {
	
	if(x == NULL) return 0;
	return height(x->left) - height(x->right);
}

Node* insert(Node* node, int key) {
	if(node == NULL) return newNode(key);

	if(key < node->key) node->left = insert(node->left, key);
	else if(key > node->key) node->right = insert(node->right, key);
	else return node;

	

	node->height = max(height(node->left), height(node->right)) + 1;
	
	int balance = getBalance(node);

	

	
	if(balance < -1 && key > node->right->key)
		return leftRotate(node);

	
	if(balance < -1 && key < node->right->key) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	
	if(balance > 1 && key < node->left->key) {
		return rightRotate(node);
	}

	
	if(balance > 1 && key > node->left->key) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	return node;
}

void preOrder(Node *root) {
    if(root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node *root) {
	if(root != NULL) {
		inOrder(root->left);
		cout << root->key << " ";
		inOrder(root->right);
	}
}

int main() {
	Node *root = NULL;

	for(int i=10; i<100; i+=5) {
		
		root = insert(root, i);
	}

	inOrder(root);

	return 0;
}
