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
		/* if the btree is full */
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
		/*
		   case 1:
		   if found the key and the node is a leaf then delete it
		   directly
		*/
		memmove(&btree->key[index], &btree->key[index + 1],
			sizeof(type_t) * (btree->num - index - 1));
		--btree->num;
		return btree;
	} else if (btree->leaf && ret) {
		/* not found */
		return btree;
	}

	if (!ret) /* btree includes key */
	{
		/*
		   case 2:
		   If the key k is in node x and x is an internal node, do the
		   following:
		 */
		preceding = btree->child[index];
		successor = btree->child[index + 1];

		if (preceding->num >= M) /* case 2a */
		{
			/*
			   case 2a:
			   If the child y that precedes k in node x has at least
			   t keys,
			   then find the predecessor k′ of k in the subtree
			   rooted at y.
			   Recursively delete k′, and replace k by k′ in x.
			   (Finding k′ and deleting it can be performed in a
			   single downward pass.)
			 */
			replace = preceding->key[preceding->num - 1];
			btree->child[index] = btree_delete(preceding, replace);
			btree->key[index] = replace;
			return btree;
		}
		if (successor->num >= M) /* case 2b */
		{
			/*
			   case 2b:
			   Symmetrically, if the child z that follows k in node
			   x
			   has at least t keys, then find the successor k′ of k
			   in the subtree rooted at z. Recursively delete k′,
			   and
			   replace k by k′ in x. (Finding k′ and deleting it can
			   be performed in a single downward pass.)
			 */
			replace = successor->key[0];
			btree->child[index + 1] =
			    btree_delete(successor, replace);
			btree->key[index] = replace;
			return btree;
		}
		if ((preceding->num == M - 1) &&
		    (successor->num == M - 1)) /* case 2c */
		{
			/*
			   case 2c:
			   Otherwise, if both y and z have only t - 1 keys,
			   merge k
			   and all of z into y, so that x loses both k and the
			   pointer
			   to z, and y now contains 2t - 1 keys. Then, free z
			   and
			   recursively delete k from y.
			 */
			/* merge key and successor into preceding */
			preceding->key[preceding->num++] = key;
			memmove(&preceding->key[preceding->num],
				&successor->key[0],
				sizeof(type_t) * (successor->num));
			memmove(&preceding->child[preceding->num],
				&successor->child[0],
				sizeof(btree_t *) * (successor->num + 1));
			preceding->num += successor->num;

			/* delete key from btree */
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
				/* if the parent node contain no more child,
				 * free it */
				free(btree);
				btree = preceding;
			}

			/* free successor */
			free(successor);

			/* delete key from preceding */
			btree_delete(preceding, key);

			return btree;
		}
	}

	/* btree not includes key */
	if ((child = btree->child[index]) && child->num == M - 1) {
		/*
		   case 3:
		   If the key k is not present in internal node x, determine
		   the root ci[x] of the appropriate subtree that must contain
		   k,
		   if k is in the tree at all. If ci[x] has only t - 1 keys,
		   execute step 3a or 3b as necessary to guarantee that we
		   descend
		   to a node containing at least t keys. Then, finish by
		   recursing
		   on the appropriate child of x.
		 */
		/*
		   case 3a:
		   If ci[x] has only t - 1 keys but has an immediate sibling
		   with at least t keys, give ci[x] an extra key by moving a
		   key from x down into ci[x], moving a key from ci[x]'s
		   immediate
		   left or right sibling up into x, and moving the appropriate
		   child pointer from the sibling into ci[x].
		 */
		if ((index < btree->num) &&
		    (sibling = btree->child[index + 1]) &&
		    (sibling->num >= M)) {
			/* the right sibling has at least M keys */
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
			/* the left sibling has at least M keys */
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
		/*
		   case 3b:
		   If ci[x] and both of ci[x]'s immediate siblings have t - 1
		   keys,
		   merge ci[x] with one sibling, which involves moving a key
		   from x
		   down into the new merged node to become the median key for
		   that node.
		 */
		else if ((index < btree->num) &&
			 (sibling = btree->child[index + 1]) &&
			 (sibling->num == M - 1)) {
			/*
			   the child and its right sibling both have M - 1 keys,
			   so merge child with its right sibling
			 */
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
			/*
			   the child and its left sibling both have M - 1 keys,
			   so merge child with its left sibling
			 */
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

/*
 * child is the posth child of parent
 */
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

	/* copy the last M keys of child into z */
	for (i = 0; i < M - 1; ++i) {
		z->key[i] = child->key[i + M];
	}

	if (!child->leaf) {
		/* copy the last M children of child into z */
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
	/*
	 * when out of the loop, three conditions may happens:
	 * ret == 0 means find the key,
	 * or ret > 0 && i < num means not find the key,
	 * or ret < 0 && i == num means not find the key and out of the key
	 * array range
	 */

	return i;
}

/*
 * btree is not full
 */
btree_t *btree_insert_nonfull(btree_t *btree, type_t key)
{
	int i;

	i = btree->num - 1;

	if (btree->leaf) {
		/* find the position to insert the key */
		while (i >= 0 && key < btree->key[i]) {
			btree->key[i + 1] = btree->key[i];
			--i;
		}

		btree->key[i + 1] = key;

		btree->num++;
	} else {
		/* find the child to insert the key */
		while (i >= 0 && key < btree->key[i]) {
			--i;
		}

		++i;
		if (btree->child[i]->num == KEY_NUM) {
			/* if the child is full, then split it */
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
