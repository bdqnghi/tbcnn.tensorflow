#include <iostream>
using namespace std;

enum color{RED, BLACK};

struct Node
{
	int data;
	color color;
	Node *left, *right, *parent;
};

Node *root;

void swap(color *c1, color *c2)
{
	color c3 = *c2;
	*c2 = *c1;
	*c1 = c3;
}

void rotateLeft(Node *t)
{
	Node *tRight = t->right;
	t->right = tRight->left;
	if(t->right != NULL)
		t->right->parent = t;
	if(t->parent == NULL)
		root = tRight;
	else if(t == t->parent->left)
		t->parent->left = tRight;
	else
		t->parent->right = tRight;
	tRight->left = t;
	t->parent = tRight;
}

void rotateRight(Node *t)
{
	Node *tLeft = t->left;
	t->left = tLeft->right;
	if(t->left != NULL)
	    t->left->parent = t;
	if(t->parent == NULL)
	    t->parent = tLeft;
	else if(t == t->parent->left)
	    t->parent->left = tLeft;
	else
	    t->parent->right = tLeft;
	tLeft->right = t;
	t->parent = tLeft;	
}

Node *bstInsert(Node *root, Node *t)
{
	if(root == NULL)
		return t;
	else if(t->data > root->data)
	{
		root->right = bstInsert(root->right, t);
		root->right->parent = root;
	}
	else if(t->data < root->data)
	{
		root->left = bstInsert(root->left, t);
		root->left->parent = root;
	}
	return root;
	
}

void *insert(int x)
{
	Node *tmp = new Node;
	tmp->data = x;
	tmp->color = RED;
	tmp->left = NULL;
	tmp->right = NULL;
	root = bstInsert(root, tmp);
}

void fixViolation(Node *t)
{
	Node *parent = NULL, *grandParrent = NULL;
	while(t != root && t->color == RED && t->parent->color == RED)
	{
		parent = t->parent;
		grandParrent = parent->parent;
		if(parent == grandParrent->left)
		{
			Node *uncle = grandParrent->right;
			if(uncle != NULL && uncle->color == RED)
			{
				grandParrent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				t = grandParrent;
			}
			else
			{
				if(t == parent->right)
				{
					rotateLeft(parent);
					t = parent;
					parent = t->parent;
				}
				rotateRight(grandParrent);
				swap(&parent->color, &grandParrent->color);
				t = parent;
			}
		}
		else
		{
			Node *uncle = grandParrent->left;
			if(uncle != NULL && uncle->color == RED)
			{
				grandParrent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				t = grandParrent;
			}
			else
			{
				if(t == parent->left)
				{
					rotateRight(parent);]\
					t = parent;
					parent = t->parent;
				}
				rotateLeft(grandParrent);
				swap(parent->color, grandParrent->color);
				t = parent;
			}
		}
	}
	root->color = BLACK;
}

void inOrder(Node *root)
{
	if(root == NULL)
		return;
	printf("%d\n", root->data);
	inOrder(root->left);
	inOrder(root->right);
}

bool find(int x)
{
	Node *cur = root;
	while(cur != NULL)
	{
		if(x > cur->data)
			cur = cur->right;
		else if(x < cur->data)
			cur = cur->left;
		else
			break;
	}
	if(cur == NULL)
		return 0;
	else
		return 1;
}
int main()
{
	int N, t;
	cin >> N;
	while(N--)
	{
		cin >> t;
		insert(t);
	}
}
	