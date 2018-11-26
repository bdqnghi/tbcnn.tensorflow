/**
 * Copyright (C) 2007 Stefan Buettcher. All rights reserved.
 * This is free software with ABSOLUTELY NO WARRANTY.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA
 **/

/**
 * Implementation of an AVL tree (balanced binary search tree). This
 * implementation has been adapted from an earlier version used for
 * the document-based indexer from spring 2004.
 *
 * author: Stefan Buettcher
 * created: 2004-09-18
 * changed: 2004-10-15
 **/


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"
#include "alloc.h"


AVLTree::AVLTree(Lexicon *lexicon) {
	owner = lexicon;
	nodes = (AVLTreeNode*)malloc((MAX_NODE_COUNT + 1) * sizeof(AVLTreeNode));
	nodeCount = 0;
	root = EMPTY_NODE;
	freeNodeCount = MAX_NODE_COUNT;
	freeNodes = (uint16_t*)malloc((MAX_NODE_COUNT + 1) * sizeof(uint16_t));
	for (int i = 0; i < freeNodeCount; i++)
		freeNodes[i] = i;
	nodes[EMPTY_NODE].parent = EMPTY_NODE;
	nodes[EMPTY_NODE].leftChild = nodes[EMPTY_NODE].rightChild = EMPTY_NODE;
	nodes[EMPTY_NODE].height = 0;
} // end of AVLTree(Lexicon*)


AVLTree::~AVLTree() {
	free(freeNodes);
	free(nodes);
} // end of ~AVLTree()


int AVLTree::getNodeCount() {
	return nodeCount;
} // end of getNodeCount()


AVLTreeNode * AVLTree::findNode(char *key) {
	int node = root;
	while (node != EMPTY_NODE) {
		char *nodeKey = owner->getTermString(nodes[node].value);
		int comparison = strcmp(nodeKey, key);
		if (comparison == 0)
			return &nodes[node];
		else if (comparison < 0)
			node = nodes[node].rightChild;
		else
			node = nodes[node].leftChild;
	}
	return NULL;
} // end of findNode(char*)


int AVLTree::getNodeNumber(char *key) {
	int node = root;
	while (node != EMPTY_NODE) {
		char *nodeKey = owner->getTermString(nodes[node].value);
		int comparison = strcmp(nodeKey, key);
		if (comparison == 0)
			return node;
		else if (comparison < 0)
			node = nodes[node].rightChild;
		else
			node = nodes[node].leftChild;
	}
	return -1;
} // end of getNodeNumber(char*)


int AVLTree::getSizeOfSubtree(int node) {
	if (node == EMPTY_NODE)
		return 0;
	else
		return 1 + getSizeOfSubtree(nodes[node].leftChild) +
		           getSizeOfSubtree(nodes[node].rightChild);
} // end of getSizeOfSubtree(int)


int32_t * AVLTree::storeSortedList(int node, int32_t *array) {
	if (node == EMPTY_NODE)
		return array;
	else {
		if (nodes[node].leftChild != EMPTY_NODE)
			array = storeSortedList(nodes[node].leftChild, array);
		array[0] = nodes[node].value;
		array++;
		if (nodes[node].rightChild != EMPTY_NODE)
			array = storeSortedList(nodes[node].rightChild, array);
		return array;
	}
} // end of storeSortedList(int, int32_t*)


int32_t * AVLTree::createSortedList() {
	if (nodeCount == 0)
		return (int32_t*)malloc(sizeof(int32_t));
	else {
		int32_t *result = (int32_t*)malloc((nodeCount + 1) * sizeof(int32_t));
		storeSortedList(root, result);
		return result;
	}
} // end of createSortedList()


int32_t * AVLTree::createSortedList(int node) {
	int treeSize = getSizeOfSubtree(node);
	int32_t *result = (int32_t*)malloc((treeSize + 1) * sizeof(int32_t));
	storeSortedList(node, result);
	return result;
} // end of createSortedList(int)


static inline int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
} // end of max(int, int)


void AVLTree::rotate(int parent, int child) {

	uint16_t parentParent = nodes[parent].parent;

	if (child == nodes[parent].leftChild) {
		nodes[parent].leftChild = nodes[child].rightChild;
		if (nodes[child].rightChild != EMPTY_NODE)
			nodes[nodes[child].rightChild].parent = parent;
		nodes[child].parent = parentParent;
		nodes[child].rightChild = parent;
		nodes[parent].parent = child;
		if (parentParent == EMPTY_NODE)
			root = child;
		else if (nodes[parentParent].leftChild == parent)
			nodes[parentParent].leftChild = child;
		else
			nodes[parentParent].rightChild = child;
		nodes[parent].height = 1 +
				max(nodes[nodes[parent].leftChild].height,
				    nodes[nodes[parent].rightChild].height);
		nodes[child].height = 1 +
				max(nodes[nodes[child].leftChild].height,
				    nodes[nodes[child].rightChild].height);
		return;
	} // end if (child == nodes[parent].leftChild)
	else if (child == nodes[parent].rightChild) {
		nodes[parent].rightChild = nodes[child].leftChild;
		if (nodes[child].leftChild != EMPTY_NODE)
			nodes[nodes[child].leftChild].parent = parent;
		nodes[child].parent = parentParent;
		nodes[parent].parent = child;
		nodes[child].leftChild = parent;
		if (parentParent == EMPTY_NODE)
			root = child;
		else if (nodes[parentParent].leftChild == parent)
			nodes[parentParent].leftChild = child;
		else
			nodes[parentParent].rightChild = child;
		nodes[parent].height = 1 +
				max(nodes[nodes[parent].leftChild].height,
				    nodes[nodes[parent].rightChild].height);
		nodes[child].height = 1 +
				max(nodes[nodes[child].leftChild].height,
				    nodes[nodes[child].rightChild].height);
		return;
	} // end if (child == nodes[parent].rightChild)
	else
		assert("Illegal rotation!" == NULL);

} // end of rotate(int, int)


void AVLTree::rebalanceHereOrAbove(int node) {
	while (node != EMPTY_NODE) {
		int left = nodes[nodes[node].leftChild].height;
		int right = nodes[nodes[node].rightChild].height;
		nodes[node].height = 1 + max(left, right);
		if (left > right + 1) {
			// violation type 1 detected
			int leftNode = nodes[node].leftChild;
			if (nodes[nodes[leftNode].leftChild].height >= nodes[nodes[leftNode].rightChild].height) {
				// easy case: single rotation
				rotate(node, leftNode);
			}
			else {
				// difficult case: double rotation
				int newLeftNode = nodes[leftNode].rightChild;
				rotate(leftNode, newLeftNode);
				rotate(node, newLeftNode);
			}
		}
		else if (right > left + 1) {
			// violation type 2 detected
			int rightNode = nodes[node].rightChild;
			if (nodes[nodes[rightNode].rightChild].height >= nodes[nodes[rightNode].leftChild].height) {
				// easy case: single rotation
				rotate(node, rightNode);
			}
			else {
				// difficult case: double rotation
				int newRightNode = nodes[rightNode].leftChild;
				rotate(rightNode, newRightNode);
				rotate(node, newRightNode);
			}
		}
		node = nodes[node].parent;
	}
} // end of rebalanceHereOrAbove(int node)


int AVLTree::createNode(int32_t value) {
	assert(freeNodeCount > 0);
	int node = freeNodes[--freeNodeCount];
	nodes[node].value = value;
	return node;
} // end of createNode(int32_t)


int AVLTree::insertNode(int32_t value) {
	if (nodeCount >= MAX_NODE_COUNT)
		return -1;
	int node = createNode(value);
	char *nodeKey = owner->getTermString(value);

	if (nodeCount == 0) {
		// if we have an empty tree, we make the new node the root
		nodes[node].height = 1;
		nodes[node].leftChild = nodes[node].rightChild = EMPTY_NODE;
		nodes[node].parent = EMPTY_NODE;
		root = node;
		nodeCount++;
		return 0;
	}
	else {
		// non-empty tree: search for the right position
		int comparison;
		int lastNode = EMPTY_NODE;
		int currentNode = root;
		while (currentNode != EMPTY_NODE) {
			lastNode = currentNode;
			comparison = strcmp(owner->getTermString(nodes[currentNode].value), nodeKey);
			if (comparison == 0) {
				freeNodeCount++;
				return -1;
			}
			else if (comparison < 0)
				currentNode = nodes[currentNode].rightChild;
			else
				currentNode = nodes[currentNode].leftChild;
		}

		// insert the new node at this position in the tree
		currentNode = lastNode;
		if (comparison < 0)
			nodes[currentNode].rightChild = node;
		else
			nodes[currentNode].leftChild = node;

		nodes[node].parent = currentNode;
		nodes[node].leftChild = nodes[node].rightChild = EMPTY_NODE;
		nodes[node].height = 1;
		rebalanceHereOrAbove(node);

		nodeCount++;
		return 0;
	}

} // end of insertNode(int32_t)


int AVLTree::deleteNode(char *key) {
	int node = getNodeNumber(key);
	if (node < 0)
		return -1;
	else
		return deleteNode(node);
} // end of deleteNode(char*)


int AVLTree::deleteNode(int node) {
	int originalNode = node;
	int leftChild = nodes[node].leftChild;
	int rightChild = nodes[node].rightChild;
	int parent = nodes[node].parent;
	
	if (leftChild == EMPTY_NODE) {
		// easy case: no left child, simply replace us by the right child
		if (rightChild != EMPTY_NODE)
			nodes[rightChild].parent = parent;
		if (parent == EMPTY_NODE)
			root = rightChild;
		else if (nodes[parent].leftChild == node)
			nodes[parent].leftChild = rightChild;
		else
			nodes[parent].rightChild = rightChild;
		node = rightChild;
	}
	else if (rightChild == EMPTY_NODE) {
		// easy case: no right child, simply replace us by the left child
		if (leftChild != EMPTY_NODE)
			nodes[leftChild].parent = parent;
		if (parent == EMPTY_NODE)
			root = leftChild;
		else if (nodes[parent].leftChild == node)
			nodes[parent].leftChild = leftChild;
		else
			nodes[parent].rightChild = leftChild;
		node = leftChild;
	}
	else {
		// we take the rightmost node on the left-hand side and put it where the old node is
		int candidate = leftChild;
		while (nodes[candidate].rightChild != EMPTY_NODE)
			candidate = nodes[candidate].rightChild;
		if (nodes[candidate].leftChild != EMPTY_NODE)
			nodes[nodes[candidate].leftChild].parent = nodes[candidate].parent;
		if (nodes[nodes[candidate].parent].leftChild == candidate)
			nodes[nodes[candidate].parent].leftChild = nodes[candidate].leftChild;
		else
			nodes[nodes[candidate].parent].rightChild = nodes[candidate].leftChild;
		int whereToCheckForImbalance = nodes[candidate].parent;
		if (whereToCheckForImbalance == node)
			whereToCheckForImbalance = candidate;

		// the candidate has been removed from its old position; put it into its new place
		nodes[candidate].parent = parent;
		if (parent == EMPTY_NODE)
			root = candidate;
		else if (nodes[parent].leftChild == node)
			nodes[parent].leftChild = candidate;
		else
			nodes[parent].rightChild = candidate;
		nodes[candidate].leftChild = leftChild;
		nodes[candidate].rightChild = rightChild;
		nodes[leftChild].parent = candidate;
		nodes[rightChild].parent = candidate;
		node = whereToCheckForImbalance;
	}

	freeNodes[freeNodeCount++] = originalNode;
	nodeCount--;
	rebalanceHereOrAbove(node);
} // end of removeNode(AVLTree*, AVLTreeNode*)




