#include <cstdio>
#include <iostream>

using namespace std;

class Node {
public:
	Node(int);
	int data;
	Node *left;
	Node *right;
};
Node::Node(int ele) {
	data = ele;
	left = right = NULL;
}

class AVLTree {
public:
	Node *root;
	int height(Node*);
	int diff(Node *);
    Node *rr_rotation(Node *);
    Node *ll_rotation(Node *);
    Node *lr_rotation(Node *);
    Node *rl_rotation(Node *);
    Node* balance(Node *);
    void insert(Node *, int);
    void preorder(Node *);
    void postorder(Node *);
    void inorder(Node *);
    void insertit(Node *, int);
	AVLTree() {
		root = NULL;
	}

};

int AVLTree::height(Node *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height(temp->left);
        int r_height = height(temp->right);
        int max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

int AVLTree::diff(Node *temp)
{
    int l_height = height(temp->left);
    int r_height = height(temp->right);
    int bnum = l_height - r_height;
    return bnum;
}

// right-right rotation
Node *AVLTree::rr_rotation(Node *parent)
{
    Node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

//left-left rotation
Node *AVLTree::ll_rotation(Node *parent)
{
    Node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}
 

//left-right rotation
Node *AVLTree::lr_rotation(Node *parent)
{
    Node *temp;
    temp = parent->left;
    parent->left = rr_rotation(temp);
    return ll_rotation(parent);
}
 

// right-left rotation
Node *AVLTree::rl_rotation(Node *parent)
{
    Node *temp;
    temp = parent->right;
    parent->right = ll_rotation(temp);
    return rr_rotation(parent);
}

// balancing tree
Node *AVLTree::balance(Node *temp)
{
    int bnum = diff(temp);
    if (bnum > 1)
    {
        if (diff(temp->left) > 0)
            temp = ll_rotation(temp);
        else
            temp = lr_rotation(temp);
    }
    else if(bnum < -1)
    {
        if (diff(temp->right) > 0)
            temp = rl_rotation(temp);
        else
            temp = rr_rotation(temp);
    }
    return temp;
}

void AVLTree::insertit(Node *node, int value) {
	if(root!=NULL) insert(root, value);
	else root = new Node(value);
}

void AVLTree::insert(Node *node, int value)
{
    	if(value < node->data)
    	{
        	if((node->left)!=NULL) insert(node->left, value);
        	else node->left = new Node(value);
        	node = balance(node);
    	}
    	else
    	{
        	if((node->right)!=NULL) insert(node->right, value);
        	else node->right = new Node(value);
        	node = balance(node);
    	}      
}

void AVLTree::postorder(Node *node) {
	if(node!=NULL) {
		postorder(node->left);
		postorder(node->right);
		cout<<node->data<<" ";
	}
}

void AVLTree::inorder(Node *node) {
	if(node!=NULL) {
		inorder(node->left);
		cout<<node->data<<" ";
		inorder(node->right);
	}
}

void AVLTree::preorder(Node *node) {
	if(node!=NULL) {
		cout<<node->data<<" ";
		preorder(node->left);
		preorder(node->right);
	}
}

int main() {
	AVLTree tree;
	int n, ele;
	cout<<"Enter no. of elements: ";
	cin>>n;
	cout<<"Enter the "<<n<<" elements"<<endl;
	for(int i=0; i<n; i++) {
		cin>>ele;
		tree.insertit(tree.root, ele);
	}
	if(tree.root!=NULL) {
	cout<<"Postorder: ";
	tree.postorder(tree.root);
	cout<<endl; 
	cout<<"Inorder: ";
	tree.inorder(tree.root);
	cout<<endl;
	cout<<"Preorder: ";
	tree.preorder(tree.root);
	cout<<endl;
	cout<<"Height of the tree: "<<tree.height(tree.root)-1<<endl;
	}
	else cout<<"Empty tree"<<endl;
	return 0;
}
