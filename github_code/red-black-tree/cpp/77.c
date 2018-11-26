#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

#define RED 1
#define BLACK 2


Node makenode(Item item) {
	Node newnode = (Node )malloc(sizeof(node));
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->p = NULL;
	newnode->data = item;
	newnode->color = RED;
	return newnode;
}

void leftrotate(Node head, Node root) {
	Node p = root->p;
	Node y = root->right;
	Node b = y->left;

	if (p == NULL) {
		head = y;
	}
	else if (p->right == root) {
		p->right = y;
	}
	else {
		p->left = y;
	}

	y->left = root;
	y->p = root->p;
	root->p = y;
	root->right = b;
	if (b != NULL) {
		b->p = root;
	}
	
}

void rightrotate(Node head, Node root) {
	Node parent = root->p;
	Node x = root->left;
	Node b = x->right;

	if (parent == NULL) {
		head = root;
	}
	else if (parent->left == root) {
		parent->left = x;
	}
	else {
		parent->right = x;
	}
	x->p = parent;
	if (b != NULL) {
		b->p = root;
	}
	root->left = b;
	x->right = root;
	root->p = x;


}

void rb_insert_fixup(Node head, Node root) {
	if (head == root) {
		root->color = BLACK;
		return;
	}

	while (root->p->color == RED && root->p!=NULL) {
		if (root->p == root->p->p->left) { //case 1,2,3
			if (root->p->p->right->color == RED) { //case 1
				root->p->color = BLACK;
				root->p->p->right->color == BLACK;
				root->p->p->color = RED;

				rb_insert_fixup(head, root->p->p);
			}
			else {//case 2, 3
				if (root->p->right == root) {//case 2
					leftrotate(head, root->p);
					root = root->p;
				}
				//case 3
				root->p->color = BLACK;
				root->p->p->color = RED;
				rightrotate(head, root->p->p);
				return;
			}
		}
		else {//case 4,5,6
			if (root->p->p->left->color == RED) { //case 4
				root->p->color = BLACK;
				root->p->p->left->color == BLACK;
				root->p->p->color = RED;

				rb_insert_fixup(head, root->p->p);
			}
			else {//case 5, 6
				if (root->p->left== root) {//case 6
					rightrotate(head, root->p);
					root = root->p;
				}
				//case 6
				root->p->color = BLACK;
				root->p->p->color = RED;
				leftrotate(head, root->p->p);
				return;
			}
		}
	}
}

void rb_insert(Node head, Node root) {
	//Normal BST Insert
	if (head == NULL) {
		head = root;
		return;
	}
	Node temp = head;
	while (1) {
		if (temp->data>root->data) {
			Node thead = temp;
			temp = temp->left;
			if ( temp == NULL) {
				thead->left = root;
				root->p = thead;
				break;
			}
		}
		else if (temp->data < root->data) {
			Node thead = temp;
			temp = temp->right;
			if (temp == NULL) {
				thead->right = root;
				root->p = thead;
				break;
			}
		}
		else {
			printf("Error\n");
			return;
		}
	}

	//For RED-BLACK TREE
	rb_insert_fixup(head, root);
}

void rb_delete_fixup(Node head, Node root) {
	while (root->color == BLACK && root != head) {
		Node parent = root->p;
		if (root == parent->left) { //CASE 1, 2, 3, 4
			Node w = parent->right;
			if (w->color == RED) {//CASE 1
				w->color = BLACK;
				parent->color = RED;
				leftrotate(head, parent);
			}
			else { //CASE 2,3,4 w->color == BLACK
				if (w->left->color == BLACK && w->right->color == BLACK) { //CASE 2
					w->color = RED;
					root = parent;
				}
				else if (w->left->color == RED) { //CASE 3
					w->color = RED;
					w->left->color = BLACK;
					rightrotate(head, w);
				}
				else if (w->right->color == RED) { //CASE 4
					w->color = parent->color;
					parent->color = BLACK;
					w->right->color = BLACK;
					leftrotate(head, parent);
					break;
				}
				else {
					printf("Error: there is an error on case 1,2,3,4 if statement\n");
				}
			}
		}
		else {//CASE 5, 6, 7, 8
			Node w = parent->left;
			if (w->color == RED) {//CASE 5
				w->color = BLACK;
				parent->color = RED;
				rightrotate(head, parent);
			}
			else { //CASE 6,7,8 w->color == BLACK
				if (w->right->color == BLACK && w->left->color == BLACK) { //CASE 6
					w->color = RED;
					root = parent;
				}
				else if (w->right->color == RED) { //CASE 7
					w->color = RED;
					w->right->color = BLACK;
					leftrotate(head, w);
				}
				else if (w->left->color == RED) { //CASE 8
					w->color = parent->color;
					parent->color = BLACK;
					w->left->color = BLACK;
					rightrotate(head, parent);
					break;
				}
				else {
					printf("Error: there is an error on case 5,6,7,8 if statement\n");
				}
			}
		}
	}
	root->color = BLACK;
	return;
}

void rb_delete(Node head, Node root) {
	int color;
	Node x;
	//normal BST delete
	if (root->left == NULL && root->right == NULL) { //leaf node
		if (root->p->left == root) {
			root->p->left = NULL;
		}
		else {
			root->p->right = NULL;
		}
		color = root->color;
		x = NULL;
		free(root);
	}
	else if (root->right == NULL) {
		x = root->left;
		if (root->p->left == root) {
			root->p->left = root->left;
			root->left->p = root->p;
		}
		else {
			root->p->right = root->left;
			root->left->p = root->p;
		}
		color = root->color;
		free(root);
	}
	else if (root->left == NULL) {
		x = root->right;
		if (root->p->left == root) {
			root->p->left = root->right;
			root->right->p = root->p;
		}
		else {
			root->p->right = root->right;
			root->right->p = root->p;
		}
		color = root->color;
		free(root);
	}
	else {
		Node successor = bst_successor(root);
		x = successor->right;
		root->data = successor->data;
		color = successor->color;
		bst_delete(successor);
	}

	//FOR RED-BLACK TREE
	if (color == BLACK) {
		rb_delete_fixup(head, x);
	}
	return;
}

int main() {
	Node p = makenode(6);
	Node x = makenode(1);
	p->left = x;
	x->p = p;
	Node a = makenode(2);
	x->left = a;
	a->p = x;
	Node y = makenode(3);
	x->right = y;
	y->p = x;
	Node b = makenode(4);
	b->p = y;
	y->left = b;
	Node r = makenode(5);
	r->p = y;
	y->right = r;


	leftrotate(p, x);

	rightrotate(p, y);
	
}