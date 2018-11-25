#include "btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static btree_t *btree_insert_nonfull(btree_t *btree, type_t key);
static btree_t *btree_split_child(btree_t *parent, int pos, btree_t *child);
static int btree_find_index(btree_t *btree, type_t key, int *ret);

btree_t *btree_create()
{
	btree_t *btree;

	if (!(btree = (btree_t *)malloc(sizeof(btree_t)))) {
		printf("[%d]malloc error!\n", __LINE__);
		return NULL;
	}

	btree->num = 0;
	btree->leaf = 1;

	return btree;
}

btree_t *btree_insert(btree_t *btree, type_t key)
{
	if (btree->num == KEY_NUM) {
		
		btree_t *p;
		if (!(p = (btree_t *)malloc(sizeof(btree_t)))) {
			printf("[%d]malloc error!\n", __LINE__);
			return NULL;
		}
		p->num = 0;
		p->child[0] = btree;
		p->leaf = 0;
		btree = btree_split_child(p, 0, btree);
	}

	return btree_insert_nonfull(btree, key);
}

btree_t *btree_delete(btree_t *btree, type_t key)
{
	int index, ret, i;
	btree_t *preceding, *successor;
	btree_t *child, *sibling;
	type_t replace;

	index = btree_find_index(btree, key, &ret);

	if (btree->leaf && !ret) {
		
		memmove(&btree->key[index], &btree->key[index + 1],
			sizeof(type_t) * (btree->num - index - 1));
		--btree->num;
		return btree;
	} else if (btree->leaf && ret) {
		
		return btree;
	}

	if (!ret) 
	{
		
		preceding = btree->child[index];
		successor = btree->child[index + 1];

		if (preceding->num >= M) 
		{
			
			replace = preceding->key[preceding->num - 1];
			btree->child[index] = btree_delete(preceding, replace);
			btree->key[index] = replace;
			return btree;
		}
		if (successor->num >= M) 
		{
			
			replace = successor->key[0];
			btree->child[index + 1] =
			    btree_delete(successor, replace);
			btree->key[index] = replace;
			return btree;
		}
		if ((preceding->num == M - 1) &&
		    (successor->num == M - 1)) 
		{
			
			
			preceding->key[preceding->num++] = key;
			memmove(&preceding->key[preceding->num],
				&successor->key[0],
				sizeof(type_t) * (successor->num));
			memmove(&preceding->child[preceding->num],
				&successor->child[0],
				sizeof(btree_t *) * (successor->num + 1));
			preceding->num += successor->num;

			
			if (btree->num - 1 > 0) {
				memmove(
				    &btree->key[index], &btree->key[index + 1],
				    sizeof(type_t) * (btree->num - index - 1));
				memmove(&btree->child[index + 1],
					&btree->child[index + 2],
					sizeof(btree_t *) *
					    (btree->num - index - 1));
				--btree->num;
			} else {
				
				free(btree);
				btree = preceding;
			}

			
			free(successor);

			
			btree_delete(preceding, key);

			return btree;
		}
	}

	
	if ((child = btree->child[index]) && child->num == M - 1) {
		
		
		if ((index < btree->num) &&
		    (sibling = btree->child[index + 1]) &&
		    (sibling->num >= M)) {
			
			child->key[child->num++] = btree->key[index];
			btree->key[index] = sibling->key[0];

			child->child[child->num] = sibling->child[0];

			sibling->num--;
			memmove(&sibling->key[0], &sibling->key[1],
				sizeof(type_t *) * (sibling->num));
			memmove(&sibling->child[0], &sibling->child[1],
				sizeof(btree_t *) * (sibling->num + 1));
		} else if ((index > 0) && (sibling = btree->child[index - 1]) &&
			   (sibling->num >= M)) {
			
			memmove(&child->key[1], &child->key[0],
				sizeof(type_t) * child->num);
			memmove(&child->child[1], &child->child[0],
				sizeof(btree_t *) * (child->num + 1));
			child->key[0] = btree->key[index - 1];
			btree->key[index - 1] = sibling->key[sibling->num - 1];
			child->child[0] = sibling->child[sibling->num];

			child->num++;
			sibling->num--;
		}
		
		else if ((index < btree->num) &&
			 (sibling = btree->child[index + 1]) &&
			 (sibling->num == M - 1)) {
			
			child->key[child->num++] = btree->key[index];
			memmove(&child->key[child->num], &sibling->key[0],
				sizeof(type_t) * sibling->num);
			memmove(&child->child[child->num], &sibling->child[0],
				sizeof(btree_t *) * (sibling->num + 1));
			child->num += sibling->num;

			if (btree->num - 1 > 0) {
				memmove(
				    &btree->key[index], &btree->key[index + 1],
				    sizeof(type_t) * (btree->num - index - 1));
				memmove(&btree->child[index + 1],
					&btree->child[index + 2],
					sizeof(btree_t *) *
					    (btree->num - index - 1));
				btree->num--;
			} else {
				free(btree);
				btree = child;
			}

			free(sibling);
		} else if ((index > 0) && (sibling = btree->child[index - 1]) &&
			   (sibling->num == M - 1)) {
			
			sibling->key[sibling->num++] = btree->key[index - 1];
			memmove(&sibling->key[sibling->num], &child->key[0],
				sizeof(type_t) * child->num);
			memmove(&sibling->child[sibling->num], &child->child[0],
				sizeof(btree_t *) * (child->num + 1));
			sibling->num += child->num;

			if (btree->num - 1 > 0) {
				memmove(&btree->key[index - 1],
					&btree->key[index],
					sizeof(type_t) * (btree->num - index));
				memmove(&btree->child[index],
					&btree->child[index + 1],
					sizeof(btree_t *) *
					    (btree->num - index));
				btree->num--;
			} else {
				free(btree);
				btree = sibling;
			}

			free(child);

			child = sibling;
		}
	}

	btree_delete(child, key);
	return btree;
}

btree_t *btree_search(btree_t *btree, type_t key, int *index)
{
	int i;

	*index = -1;

	for (i = 0; i < btree->num && key > btree->key[i]; ++i)
		;

	if (i < btree->num && key == btree->key[i]) {
		*index = i;
		return btree;
	}

	if (btree->leaf) {
		return NULL;
	} else {
		return btree_search(btree->child[i], key, index);
	}
}


btree_t *btree_split_child(btree_t *parent, int pos, btree_t *child)
{
	btree_t *z;
	int i;

	if (!(z = (btree_t *)malloc(sizeof(btree_t)))) {
		printf("[%d]malloc error!\n", __LINE__);
		return NULL;
	}

	z->leaf = child->leaf;
	z->num = M - 1;

	
	for (i = 0; i < M - 1; ++i) {
		z->key[i] = child->key[i + M];
	}

	if (!child->leaf) {
		
		for (i = 0; i < M; ++i) {
			z->child[i] = child->child[i + M];
		}
	}
	child->num = M - 1;

	for (i = parent->num; i > pos; --i) {
		parent->child[i + 1] = parent->child[i];
	}
	parent->child[pos + 1] = z;

	for (i = parent->num - 1; i >= pos; --i) {
		parent->key[i + 1] = parent->key[i];
	}
	parent->key[pos] = child->key[M - 1];

	parent->num++;

	return parent;
}

int btree_find_index(btree_t *btree, type_t key, int *ret)
{
	int i, num;

	for (i = 0, num = btree->num;
	     i < num && (*ret = btree->key[i] - key) < 0; ++i)
		;
	

	return i;
}


btree_t *btree_insert_nonfull(btree_t *btree, type_t key)
{
	int i;

	i = btree->num - 1;

	if (btree->leaf) {
		
		while (i >= 0 && key < btree->key[i]) {
			btree->key[i + 1] = btree->key[i];
			--i;
		}

		btree->key[i + 1] = key;

		btree->num++;
	} else {
		
		while (i >= 0 && key < btree->key[i]) {
			--i;
		}

		++i;
		if (btree->child[i]->num == KEY_NUM) {
			
			btree_split_child(btree, i, btree->child[i]);
			if (key > btree->key[i]) {
				++i;
			}
		}

		btree_insert_nonfull(btree->child[i], key);
	}

	return btree;
}

#define NUM 20000

int main()
{
	btree_t *btree;
	btnode_t *node;
	int index, i;

	if (!(btree = btree_create())) {
		exit(-1);
	}

	for (i = 1; i < NUM; ++i) {
		btree = btree_insert(btree, i);
	}

	for (i = 1; i < NUM; ++i) {
		node = btree_search(btree, i, &index);

		if (!node || index == -1) {
			printf("insert error!\n");
			return -1;
		}
	}

	for (i = 1; i < NUM; ++i) {
		btree = btree_delete(btree, i);

		btree = btree_insert(btree, i);
	}

	return 0;
}
