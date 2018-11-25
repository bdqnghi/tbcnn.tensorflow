




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
} 


AVLTree::~AVLTree() {
	free(freeNodes);
	free(nodes);
} 


int AVLTree::getNodeCount() {
	return nodeCount;
} 


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
} 


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
} 


int AVLTree::getSizeOfSubtree(int node) {
	if (node == EMPTY_NODE)
		return 0;
	else
		return 1 + getSizeOfSubtree(nodes[node].leftChild) +
		           getSizeOfSubtree(nodes[node].rightChild);
} 


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
} 


int32_t * AVLTree::createSortedList() {
	if (nodeCount == 0)
		return (int32_t*)malloc(sizeof(int32_t));
	else {
		int32_t *result = (int32_t*)malloc((nodeCount + 1) * sizeof(int32_t));
		storeSortedList(root, result);
		return result;
	}
} 


int32_t * AVLTree::createSortedList(int node) {
	int treeSize = getSizeOfSubtree(node);
	int32_t *result = (int32_t*)malloc((treeSize + 1) * sizeof(int32_t));
	storeSortedList(node, result);
	return result;
} 


static inline int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
} 


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
	} 
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
	} 
	else
		assert("Illegal rotation!" == NULL);

} 


void AVLTree::rebalanceHereOrAbove(int node) {
	while (node != EMPTY_NODE) {
		int left = nodes[nodes[node].leftChild].height;
		int right = nodes[nodes[node].rightChild].height;
		nodes[node].height = 1 + max(left, right);
		if (left > right + 1) {
			
			int leftNode = nodes[node].leftChild;
			if (nodes[nodes[leftNode].leftChild].height >= nodes[nodes[leftNode].rightChild].height) {
				
				rotate(node, leftNode);
			}
			else {
				
				int newLeftNode = nodes[leftNode].rightChild;
				rotate(leftNode, newLeftNode);
				rotate(node, newLeftNode);
			}
		}
		else if (right > left + 1) {
			
			int rightNode = nodes[node].rightChild;
			if (nodes[nodes[rightNode].rightChild].height >= nodes[nodes[rightNode].leftChild].height) {
				
				rotate(node, rightNode);
			}
			else {
				
				int newRightNode = nodes[rightNode].leftChild;
				rotate(rightNode, newRightNode);
				rotate(node, newRightNode);
			}
		}
		node = nodes[node].parent;
	}
} 


int AVLTree::createNode(int32_t value) {
	assert(freeNodeCount > 0);
	int node = freeNodes[--freeNodeCount];
	nodes[node].value = value;
	return node;
} 


int AVLTree::insertNode(int32_t value) {
	if (nodeCount >= MAX_NODE_COUNT)
		return -1;
	int node = createNode(value);
	char *nodeKey = owner->getTermString(value);

	if (nodeCount == 0) {
		
		nodes[node].height = 1;
		nodes[node].leftChild = nodes[node].rightChild = EMPTY_NODE;
		nodes[node].parent = EMPTY_NODE;
		root = node;
		nodeCount++;
		return 0;
	}
	else {
		
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

} 


int AVLTree::deleteNode(char *key) {
	int node = getNodeNumber(key);
	if (node < 0)
		return -1;
	else
		return deleteNode(node);
} 


int AVLTree::deleteNode(int node) {
	int originalNode = node;
	int leftChild = nodes[node].leftChild;
	int rightChild = nodes[node].rightChild;
	int parent = nodes[node].parent;
	
	if (leftChild == EMPTY_NODE) {
		
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
} 




