#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#ifndef __b_tree__H
#define __b_tree__H

#define t 2


typedef struct btree_node {
    int k[2*t-1];
    struct btree_node *p[2*t];
    int num;
    bool is_leaf;
} btree_node;


btree_node *btree_node_new();

btree_node *btree_create();

int btree_split_child(btree_node *parent, int pos, btree_node *child);

void btree_insert_nonfull(btree_node *node, int target);

btree_node* btree_insert(btree_node *root, int target);

void btree_merge_child(btree_node *root, int pos, btree_node *y, btree_node *z);

btree_node *btree_delete(btree_node *root, int target);

void btree_delete_nonone(btree_node *root, int target);

int btree_search_predecessor(btree_node *root);

int btree_search_successor(btree_node *root);

void btree_shift_to_left_child(btree_node *root, int pos, btree_node *y, btree_node *z);

void btree_shift_to_right_child(btree_node *root, int pos, btree_node *y, btree_node *z);

void btree_inorder_print(btree_node *root);
void btree_visit(btree_node *root);


btree_node *btree_node_new()
{
    btree_node *node = (btree_node *)malloc(sizeof(btree_node));
    if(NULL == node) {
        return NULL;
    }

    for(int i = 0; i < 2 * t -1; i++) {
        node->k[i] = 0;
    }

    for(int i = 0; i < 2 * t; i++) {
        node->p[i] = NULL;
    }

    node->num = 0;
    node->is_leaf = true;
}

btree_node *btree_create()
{
    btree_node *node = btree_node_new();
    if(NULL == node) {
        return NULL;
    }

    return node;
}

int btree_split_child(btree_node *parent, int pos, btree_node *child)
{
    btree_node *new_child = btree_node_new();
    if(NULL == new_child) {
        return -1;
    }

    new_child->is_leaf = child->is_leaf;
    new_child->num = t - 1;
    
    for(int i = 0; i < t - 1; i++) {
        new_child->k[i] = child->k[i+t];
    }

    if(false == new_child->is_leaf) {
        for(int i = 0; i < t; i++) {
            new_child->p[i] = child->p[i+t];
        }
    }
    child->num = t - 1;
    for(int i = parent->num; i > pos; i--) {
        parent->p[i+1] = parent->p[i];
    }
    parent->p[pos+1] = new_child;
    for(int i = parent->num - 1; i >= pos; i--) {
        parent->k[i+1] = parent->k[i];
    }
    parent->k[pos] = child->k[t-1];
    parent->num += 1;
}

void btree_insert_nonfull(btree_node *node, int target)
{
    if(1 == node->is_leaf) {
        int pos = node->num;
        while(pos >= 1 && target < node->k[pos-1]) {
            node->k[pos] = node->k[pos-1];
            pos--;
        }
        node->k[pos] = target;
        node->num += 1;
    } else {
        int pos = node->num;
        while(pos > 0 && target < node->k[pos-1]) {
            pos--;
        }
        if(2 * t -1 == node->p[pos]->num) {
            btree_split_child(node, pos, node->p[pos]);
            if(target > node->k[pos]) {
                pos++;
            }
        }
        btree_insert_nonfull(node->p[pos], target);
    }
}

btree_node* btree_insert(btree_node *root, int target)
{
    if(NULL == root) {
        return NULL;
    }
    if(2 * t - 1 == root->num) {
        btree_node *node = btree_node_new();
        if(NULL == node) {
            return root;
        }
        node->is_leaf = 0;
        node->p[0] = root;
        btree_split_child(node, 0, root);
        btree_insert_nonfull(node, target);
        return node;
    } else {
        btree_insert_nonfull(root, target);    
        return root;
    }
}

void btree_merge_child(btree_node *root, int pos, btree_node *y, btree_node *z)
{
	y->num = 2 * t - 1;
	for(int i = t; i < 2 * t - 1; i++) {
		y->k[i] = z->k[i-t];
	}
	y->k[t-1] = root->k[pos];
	if(false == z->is_leaf) {
		for(int i = t; i < 2 * t; i++) {
			y->p[i] = z->p[i-t];
		}
	}
	for(int j = pos + 1; j < root->num; j++) {
		root->k[j-1] = root->k[j];
		root->p[j] = root->p[j+1];
	}
	root->num -= 1;
	free(z);
}

btree_node *btree_delete(btree_node *root, int target)
{
	if(1 == root->num) {
		btree_node *y = root->p[0];
		btree_node *z = root->p[1];
		if(NULL != y && NULL != z &&
				t - 1 == y->num && t - 1 == z->num) {
			btree_merge_child(root, 0, y, z);
			free(root);
			btree_delete_nonone(y, target);
			return y;
		} else {
			btree_delete_nonone(root, target);
			return root;
		}
	} else {
		btree_delete_nonone(root, target);	
		return root;
	}
}

void btree_delete_nonone(btree_node *root, int target)
{
	if(true == root->is_leaf) {
		int i = 0;
		while(i < root->num && target > root->k[i]) i++;
		if(target == root->k[i]) {
			for(int j = i + 1; j < 2 * t - 1; j++) {
				root->k[j-1] = root->k[j];
			}
			root->num -= 1;
		} else {
			printf("target not found\n");
		}
	} else {
		int i = 0;
		btree_node *y = NULL, *z = NULL;
		while(i < root->num && target > root->k[i]) i++;
		if(i < root->num && target == root->k[i]) {
			y = root->p[i];
			z = root->p[i+1];
			if(y->num > t - 1) {
				int pre = btree_search_predecessor(y);
				root->k[i] = pre;
				btree_delete_nonone(y, pre);
			} else if(z->num > t - 1) {
				int next = btree_search_successor(z);
				root->k[i] = next;
				btree_delete_nonone(z, next);
			} else {
				btree_merge_child(root, i, y, z);
				btree_delete(y, target);
			}
		} else {
			y = root->p[i];
			if(i < root->num) {
				z = root->p[i+1];
			}
			btree_node *p = NULL;
			if(i > 0) {
				p = root->p[i-1];
			}
			if(y->num == t - 1) {
				if(i > 0 && p->num > t - 1) {
					btree_shift_to_right_child(root, i-1, p, y);
				} else if(i < root->num && z->num > t - 1) {
					btree_shift_to_left_child(root, i, y, z);
				} else if(i > 0) {
					btree_merge_child(root, i-1, p, y);
					y = p;
				} else {
					btree_merge_child(root, i, y, z);
				}
				btree_delete_nonone(y, target);
			} else {
				btree_delete_nonone(y, target);
			}
		}
	}
}

int btree_search_predecessor(btree_node *root)
{
	btree_node *y = root;
	while(false == y->is_leaf) {
		y = y->p[y->num];
	}
	return y->k[y->num-1];
}

int btree_search_successor(btree_node *root) 
{
	btree_node *z = root;
	while(false == z->is_leaf) {
		z = z->p[0];
	}
	return z->k[0];
}


void btree_shift_to_right_child(btree_node *root, int pos, 
		btree_node *y, btree_node *z)
{
	z->num += 1;
	for(int i = z->num -1; i > 0; i--) {
		z->k[i] = z->k[i-1];
	}
	z->k[0]= root->k[pos];
	root->k[pos] = y->k[y->num-1];

	if(false == z->is_leaf) {
		for(int i = z->num; i > 0; i--) {
			z->p[i] = z->p[i-1];
		}
		z->p[0] = y->p[y->num];
	}
	y->num -= 1;
}

void btree_shift_to_left_child(btree_node *root, int pos,
		btree_node *y, btree_node *z)
{
	y->num += 1;
	y->k[y->num-1] = root->k[pos];
	root->k[pos] = z->k[0];
	for(int j = 1; j < z->num; j++) {
		z->k[j-1] = z->k[j];
	}
	if(false == z->is_leaf) {
		y->p[y->num] = z->p[0];
		for(int j = 1; j <= z->num; j++) {
			z->p[j-1] = z->p[j];
		}
	} 
	z->num -= 1;
}

void btree_inorder_print(btree_node *root) 
{
    if(NULL != root) {
        btree_inorder_print(root->p[0]);
        for(int i = 0; i < root->num; i++) {
            
            btree_inorder_print(root->p[i+1]);
        }
    }
}

#endif
