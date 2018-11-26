#include <bits/stdc++.h>

using namespace std;

struct Node {
	enum Color { RED, BLACK } color;
	int value;
	Node *left, *right, *father;
	Node(enum Color color = BLACK, int value = 0, Node *left = 0, Node *right = 0, Node *father = 0):
		color(color),
		value(value),
		left(left),
		right(right),
		father(father) {
	}
} *Root, *nil;

void LeftRotate(Node **root, Node *node) {
	if (node == nil || node->right == nil)
		return;
	Node *A = node;
	Node *C = node->right;
	Node *D = node->right->left;
	A->right = D;
	if (D != nil)
		D->father = A;
	C->left = A;
	C->father = A->father;
	A->father = C;
	if (C->father != nil) {
		if (C->father->left == A)
			C->father->left = C;
		else
			C->father->right = C;
	} else
		*root = C;
}

void RightRotate(Node **root, Node *node) {
	if (node == nil || node->left == nil)
		return;
	Node *A = node;
	Node *C = node->left;
	Node *D = node->left->right;
	A->left = D;
	if (D != nil)
		D->father = A;
	C->right = A;
	C->father = A->father;
	A->father = C;
	if (C->father != nil) {
		if (C->father->left == A)
			C->father->left = C;
		else
			C->father->right = C;
	} else
		*root = C;
}

void InsertFixup(Node **root, Node *node) {
	while (node->father->color == Node::RED) {
		if (node->father == node->father->father->left) {
			Node *uncle = node->father->father->right;
			if (uncle->color == Node::RED) {
				node->father->color = uncle->color = Node::BLACK;
				node->father->father->color = Node::RED;
				node = node->father->father;
			} else {
				if (node == node->father->right) {
					node = node->father;
					LeftRotate(root, node);
				}
				node->father->color = Node::BLACK;
				node->father->father->color = Node::RED;
				RightRotate(root, node->father->father);
			}
		} else {
			Node *uncle = node->father->father->left;
			if (uncle->color == Node::RED) {
				node->father->color = uncle->color = Node::BLACK;
				node->father->father->color = Node::RED;
				node = node->father->father;
			} else {
				if (node == node->father->left) {
					node = node->father;
					RightRotate(root, node);
				}
				node->father->color = Node::BLACK;
				node->father->father->color = Node::RED;
				LeftRotate(root, node->father->father);
			}
		}
	}
	(*root)->color = Node::BLACK;
}

void Insert(Node **root, Node *node, int value) {
	Node *father = nil;
	while (node != nil) {
		father = node;
		if (value <= node->value)
			node = node->left;
		else
			node = node->right;
	}
	Node *temp = new Node(Node::RED, value, nil, nil, father);
	if (father != nil) {
		if (value <= temp->father->value)
			temp->father->left = temp;
		else
			temp->father->right = temp;
	} else
		*root = temp;
	InsertFixup(root, temp);
}

void Transplant(Node **root, Node *where, Node *with) {
	if (where->father == nil)
		*root = with;
	else if (where->father->left == where)
		where->father->left = with;
	else
		where->father->right = with;
	with->father = where->father;
}

Node *Minimum(Node *node) {
	while (node->left != nil)
		node = node->left;
	return node;
}

void DeleteFixup(Node **root, Node *node) {
	Node *sibling;
	while (node != *root && node->color == Node::BLACK) {
		if (node == node->father->left) {
			sibling = node->father->right;
			if (sibling->color == Node::RED) {
				sibling->color = Node::BLACK;
				node->father->color = Node::RED;
				LeftRotate(root, node->father);
				sibling = node->father->right;
			}
			if (sibling->left->color == Node::BLACK && sibling->right->color == Node::RED) {
				sibling->color = Node::RED;
				node = node->father;
			} else {
				if (sibling->left->color == Node::RED && sibling->right->color == Node::BLACK) {
					sibling->left->color = Node::BLACK;
					sibling->color = Node::RED;
					RightRotate(root, sibling);
					sibling = node->father->right;
				}
				sibling->color = node->father->color;
				node->father->color = Node::BLACK;
				sibling->right->color = Node::BLACK;
				LeftRotate(root, node->father);
				node = *root;
			}
		} else {
			sibling = node->father->left;
			if (sibling->color == Node::RED) {
				sibling->color = Node::BLACK;
				node->father->color = Node::RED;
				RightRotate(root, node->father);
				sibling = node->father->left;
			}
			if (sibling->right->color == Node::BLACK && sibling->left->color == Node::RED) {
				sibling->color = Node::RED;
				node = node->father;
			} else {
				if (sibling->right->color == Node::RED && sibling->left->color == Node::BLACK) {
					sibling->right->color = Node::BLACK;
					sibling->color = Node::RED;
					LeftRotate(root, sibling);
					sibling = node->father->left;
				}
				sibling->color = node->father->color;
				node->father->color = Node::BLACK;
				sibling->left->color = Node::BLACK;
				RightRotate(root, node->father);
				node = *root;
			}
		}
	}
	node->color = Node::BLACK;
}

void Delete(Node **root, Node *node) {
	Node::Color color = node->color;
	Node *temp1, *temp2;
	if (node->left == nil) {
		temp2 = node->right;
		Transplant(root, node, node->right);
	} else if (node->right == nil) {
		temp2 = node->left;
		Transplant(root, node, node->left);
	} else {
		temp1 = Minimum(node->right);
		color = temp1->color;
		temp2 = temp1->right;
		if (temp1->father == node)
			temp2->father = temp1;
		else {
			Transplant(root, temp1, temp2);
			temp1->right = node->right;
			temp1->right->father = temp1;
		}
		Transplant(root, node, temp1);
		temp1->left = node->left;
		temp1->left->father = temp1;
		temp1->color = node->color;
	}
	delete node;
	if (color == Node::BLACK)
		DeleteFixup(root, temp2);
}

Node *Find(Node *node, int value) {
	while (node != nil) {
		if (value == node->value)
			return node;
		if (value < node->value)
			node = node->left;
		else
			node = node->right;
	}
	return nil;
}

int main() {
	assert(freopen("hashuri.in", "r", stdin));
	assert(freopen("hashuri.out", "w", stdout));

	Root = nil = new Node();
	nil->left = nil->right = nil->father = nil;

	int N, op, value;
	scanf("%d", &N);
	while (N--) {
		scanf("%d %d", &op, &value);
		Node *where = Find(Root, value);
		if (op == 1) {
			if (where == nil)
				Insert(&Root, Root, value);
		} else if (op == 2) {
			if (where != nil)
				Delete(&Root, where);
		} else {
			cout << (where == nil ? 0 : 1) << '\n';
		}
	}

	return 0;
}
