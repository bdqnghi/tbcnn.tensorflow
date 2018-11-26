#pragma once
#include "AVLtree.hpp"

AVL_node* createTreeAVL(int* array, int start, int end, AVL_node* up) {

	if (start > end)
		return NULL;

	int middle = (start + end + 1) / 2;
	AVL_node* root = new AVL_node(array[middle], up);

	root->left = createTreeAVL(array, middle + 1, end, root);
	root->right = createTreeAVL(array, start, middle - 1, root);
	fixheight(root);
	return root;
}

AVL_node* findMaxAVL(AVL_node* root) {
	if (!root) {
		puts("AVL-tree is empty.");
		return root;
	}

	while (root->right) {
		printf(" %d -->", root->key);
		root = root->right;
	}

	printf(" %d\nMax element: %d\n", root->key, root->key);
	return root;
}

AVL_node* findMinAVL(AVL_node* root) {
	return root->left ? findMinAVL(root->left) : root;
}

AVL_node* deleteNodeAVL(AVL_node* root, int key) {
	if (root == NULL) return root;
	if (root->left == NULL && root->right == NULL) { //jeżeli wierzchołek jest liściem
		if (root->parent) {
			if (root->parent->right == root) {//usunięcie odwołania do wierzchołka w rodzicu
				root->parent->right = NULL;
			}
			else {
				root->parent->left = NULL;
			}
		}
		delete root;
		return NULL;
	}
	else if (root->left == NULL) {//jeżeli wierzchołek ma tylko prawego potomka
		AVL_node* temp = root->right;
		if (root->parent) {//zmiana odwołania w rodzicu wierzchołka
			if (root->parent->right == root) {
				root->parent->right = temp;
			}
			else {
				root->parent->left = temp;
			}
		}
		temp->parent = root->parent;
		delete root;
		return temp;
	}
	else if (root->right == NULL) {//jeżeli wierzchołek ma tylko lewego potomka
		AVL_node* temp = root->left;
		if (root->parent) {
			if (root->parent->right == root) {//zmiana odwołania w rodzicu wierzchołka
				root->parent->right = temp;
			}
			else {
				root->parent->left = temp;
			}
		}
		temp->parent = root->parent;
		delete root;
		return temp;
	}
	else {//jeżeli wierzchołek ma obu potomków

		AVL_node* temp = findMinAVL(root->right);
		root->key = temp->key;
		deleteNodeAVL(temp, temp->key);
		//root->right = deleteNodeAVL(root->right, temp->key); //nie wiem po co to //JB
	}
	return root;
}

void removeNodesAVL(AVL_node* root, int* valueList, int n) {
	for (int i = 0; i < n; i++) {
		AVL_node* beDeleted = searchAVL(root, valueList[i]);
		if (!beDeleted) {
			printf("\nNode with key %d didn\'t found.", valueList[i]);
		}
		else {
			deleteNodeAVL(beDeleted, beDeleted->key);
			printf("\nNode with key %d deleted.", valueList[i]);
		}
	}
}

void printInOrderAVL(AVL_node* root) {
	if (!root) {
		puts("AVL-tree is empty.");
		return;
	}
	if (root->left) printInOrderAVL(root->left);
	printf("%d ", root->key);
	if (root->right) printInOrderAVL(root->right);
}

void printPreOrderAVL(AVL_node* root) {
	if (!root) {
		puts("AVL-tree is empty.");
		return;
	}
	printf("%d ", root->key);
	if (root->left) printPreOrderAVL(root->left);
	if (root->right) printPreOrderAVL(root->right);
}

void deletePostOrderAVL(AVL_node* root) {
	if (!root) {
		puts("AVL-tree is empty.");
		return;
	}

	if (root->left) deletePostOrderAVL(root->left);
	if (root->right) deletePostOrderAVL(root->right);
	delete root;
}

void printSubtreeAVL(AVL_node* root) {
	int key;
	AVL_node* result;
	do {
		printf("\nType root key of subtree:");
		scanf_s("%d", &key);
	} while (!key);

	result = searchAVL(root, key);

	if (!result) {
		puts("No such element.");
	}
	else {
		printf("Printing subtree with root key %d:\n", result->key);
		printAVL("", "", result);
		//printInOrderAVL(result);
	}
}

AVL_node* searchAVL(AVL_node* root, int key) {
	if (!root || root->key == key) {
		return root;
	}

	if (root->key > key)
		return searchAVL(root->left, key);

	return searchAVL(root->right, key);
}

void printAVL(std::string sp, std::string sn, AVL_node* root) {
	std::string s;

	if (root) {
		s = sp;
		if (sn == RIGHT_BRANCH) s[s.length() - 2] = ' ';
		printAVL(s + VERTICAL_BRANCH, RIGHT_BRANCH, root->right);

		s = s.substr(0, sp.length() - 2);
		std::cerr << s << sn << root->key << " " << (int)root->height << std::endl;

		s = sp;
		if (sn == LEFT_BRANCH) s[s.length() - 2] = ' ';
		printAVL(s + VERTICAL_BRANCH, LEFT_BRANCH, root->left);
	}
}

unsigned char height(AVL_node* p) {
	return p ? p->height : 0;
}

int bfactor(AVL_node* p) {
	return height(p->right) - height(p->left);
}

void fixheight(AVL_node* p) {
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr ? hl : hr) + 1;
}

AVL_node* rotateLeftAVL(AVL_node* parent) {
	AVL_node* temp = parent->right;
	parent->right = temp->left;
	temp->left = parent;
	fixheight(parent);
	fixheight(temp);
	return temp;
}

AVL_node* balance(AVL_node* p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2) {
		if (bfactor(p->right) < 0)
			p->right = rotateRightAVL(p->right);
		return rotateLeftAVL(p);
	}
	if (bfactor(p) == -2) {
		if (bfactor(p->left) > 0)
			p->left = rotateLeftAVL(p->left);
		return rotateRightAVL(p);
	}
	return p; // балансировка не нужна
}

AVL_node* rotateRightAVL(AVL_node* parent)
{
	if (!parent) return NULL;
	AVL_node* temp = parent->left;
	parent->left = temp->right;
	temp->right = parent;
	fixheight(parent);
	fixheight(temp);
	return temp;
}

void treeToVineAVL(AVL_node* root) {
	AVL_node *tail, *rest, *temp;
	tail = root;
	rest = tail->right;
	while(rest) {
		if (!(rest->left)) {
			tail = rest;
			rest = rest->right;
		}
		else {
			rest = rotateRightAVL(rest);
			tail->right = rest;
		}
	}
}

void compress(AVL_node* root, int count) {
	AVL_node *scanner, *child;
	scanner = root;
	for (int i = 1; i <= count; i++) {
		child = scanner->right;
		scanner->right = child->right;
		scanner = scanner->right;
		child->right = scanner->left;
		scanner->left = child;
	}
}

unsigned log2(unsigned x) {
	unsigned y = 1;

	while ((x >>= 1) > 0)
		y <<= 1;

	return y;
}

void vineToTreeAVL(AVL_node* root, int size) {
	int leaves = size + 1 - pow(2, log2(size + 1));
	compress(root, leaves);
	size = size - leaves;
	while (size > 1) {
		compress(root, size / 2);
		size = size / 2;
	}
}

AVL_node* balanceAVL(AVL_node* root, int size) {
	AVL_node* pseudoRoot = new AVL_node(0);
	pseudoRoot->right = root;
	treeToVineAVL(pseudoRoot);
	vineToTreeAVL(pseudoRoot, size + 1);
	root = pseudoRoot->right;
	return root;
}
