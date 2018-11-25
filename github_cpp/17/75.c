
#ifndef B_TREE_H
#define B_TREE_H

#if DEBUG
#include <stdio.h>
#endif

#include <stdlib.h>
#include <assert.h>

#include "util.h"
#include "btree_util.h"


typedef struct btree_t {
	int order;
	node_t *root;
} BTree;


BTree* btree_new(int order);

void btree_init(BTree *bt, int order);

void btree_delete_s(BTree *bt);

void btree_delete_h(BTree *bt);


node_position btree_find(BTree *bt, int key);

node_position btree_insert(BTree *bt, int key, void *value);

node_position btree_remove(BTree *bt, int key);


node_position _btree_find_node(node_t *node, int key);

node_position _btree_insert_nonfull(node_t *node, pair_t *pair, int order);

void _btree_split(node_t *x, int pos, int order);

node_position _btree_remove_node(node_t *node, int key, int order);


inline node_position _node_find_max(node_t *node);

inline node_position _node_find_min(node_t *node);

#endif
