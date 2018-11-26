#include "BTree.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))

//#define DEBUG_TREE

#ifdef DEBUG_TREE
#define debug_print(fmt,...) printf(fmt, ## __VA_ARGS__)
#else
#define debug_print(fmt,...)
#endif

// ģ�������д��ڵ�
void disk_write(BTNode* node)
{
	printf("�����д��ڵ�\n");
}

// ģ��Ӵ��̶�ȡ�ڵ�
void disk_read(BTNode** node)
{
	printf("�Ӵ��̶�ȡ�ڵ�\n");
}

// ����δ�ӡ B ��
void BTree_print(BTree tree, int her)
{
	int i;
	BTNode* node = tree;

	if (node) {
		printf("�� %d �㣬 %d node : ", her, node->keynum);

		for (i = 0; i < node->keynum; ++i) {
			printf("%c ", node->key[i]);
		}

		printf("\n");

		++her;
		for (i = 0 ; i <= node->keynum; i++) {
			if (node->child[i]) {
				BTree_print(node->child[i], her);
			}
		}
	}
	else {
		printf("��Ϊ�ա�\n");
	}
}

// �������Ľڵ������ index �������ӽڵ�ϲ�
// parent ��һ�������ĸ��ڵ�
// node �� tree ���ӱ����±�Ϊ index �ĺ��ӽڵ㣬��������
void BTree_split_child(BTNode* parent, int index, BTNode* node)
{
	assert(parent && node);

	int i;

	// �����½ڵ㣬�洢 node �к�벿�ֵ�����
	BTNode* newNode = (BTNode*)calloc(sizeof(BTNode), 1);
	if (!newNode) {
		printf("Error! out of memory!\n");
		return;
	}

	newNode->isLeaf = node->isLeaf;
	newNode->keynum = BTree_T - 1;

	// ���� node ��벿�ֹؼ���
	for (i = 0; i < newNode->keynum; ++i){
		newNode->key[i] = node->key[BTree_T + i];
		node->key[BTree_T + i] = 0;
	}

	// ��� node ����Ҷ�ӽڵ㣬���� node ��벿�ֵĺ��ӽڵ�
	if (!node->isLeaf) {
		for (i = 0; i < BTree_T; i++) {
			newNode->child[i] = node->child[BTree_T + i];
			node->child[BTree_T + i] = NULL;
		}
	}

	// �� node ���ѳ� newNode ֮����������ݼ���
	node->keynum = BTree_T - 1;

	// �������ڵ�
	for (i = parent->keynum; i > index; --i) {
		parent->child[i + 1] = parent->child[i];
	}

	parent->child[index + 1] = newNode;

	for (i = parent->keynum - 1; i >= index; --i) {
		parent->key[i + 1] = parent->key[i];
	}

	parent->key[index] = node->key[BTree_T - 1];
	++parent->keynum;

	// ��� node �е��к�����
	// ���Բ���������Ϊ��ͨ�� keynum ���Ʒ��ʵ�
// 	for (i = BTree_T - 1; i < BTree_N; ++i) {
// 		node->key[i] = 0;
// 		node->child[i + 1] = NULL;
// 	}

	// д�����
 	disk_write(parent);
 	disk_write(newNode);
 	disk_write(node);
}

void BTree_insert_nonfull(BTNode* node, int key)
{
	assert(node);

	int i;

	// �ڵ���Ҷ�ӽڵ㣬ֱ�Ӳ���
	if (node->isLeaf) {
		i = node->keynum - 1;
		while (i >= 0 && key < node->key[i]) {
			node->key[i + 1] = node->key[i];
			--i;
		}

		node->key[i + 1] = key;
		++node->keynum;

		// д�����
		disk_write(node);
	}

	// �ڵ����ڲ��ڵ�
	else {
		// ���Ҳ����λ��
		i = node->keynum - 1;
		while (i >= 0 && key < node->key[i]) {
			--i;
		}

		++i;

		// �Ӵ��̶�ȡ���ӽڵ�
		disk_read(&node->child[i]);

		// ����ú��ӽڵ����������ѵ���ֵ
		if (node->child[i]->keynum == BTree_N) {
			BTree_split_child(node, i, node->child[i]);

			if (key > node->key[i]) {
				++i;
			}
		}

		BTree_insert_nonfull(node->child[i], key);
	}
}

void BTree_insert(BTree* tree, int key)
{
	BTNode* node;
	BTNode* root = *tree;

	// ��Ϊ��
	if (NULL == root) {
		root = (BTNode*)calloc(sizeof(BTNode), 1);
		if (!root) {
			printf("Error! out of memory!\n");
			return;
		}
		root->isLeaf = true;
		root->keynum = 1;
		root->key[0] = key;

		*tree = root;

		// д�����
		disk_write(root);

		return;
	}

	// �ڵ���������Ҫ���з��ѵ���
	if (root->keynum == BTree_N) {
		// �����½ڵ㵱����
		node = (BTNode*)calloc(sizeof(BTNode), 1);
		if (!node) {
			printf("Error! out of memory!\n");
			return;
		}

		*tree = node;
		node->isLeaf = false;
		node->keynum = 0;
		node->child[0] = root;

		BTree_split_child(node, 0, root);

		BTree_insert_nonfull(node, key);
	}

	// �ڵ�δ�����ڵ�ǰ�ڵ��в��� key
	else {
		BTree_insert_nonfull(root, key);
	}
}


// �� tree �еĽڵ� node ���кϲ����ӽڵ㴦��
// ע�⣺���ӽڵ�� keynum ������Ѵﵽ���ޣ��������� BTree_T - 1
// �� node ������Ϊ index + 1 �ĺ��ӽڵ�ϲ�������Ϊ index �ĺ��ӽڵ��У�
// ���� tree ������Ϊ index  �� key �½����ýڵ��У�������ص� key ��ָ�롣
//
void BTree_merge_child(BTree* tree, BTNode* node, int index)
{
	assert(tree && node && index >= 0 && index < node->keynum);

	int i;

	int key = node->key[index];
	BTNode* prevChild = node->child[index];
	BTNode* nextChild = node->child[index + 1];

	assert(prevChild && prevChild->keynum == BTree_T - 1
		&& nextChild && nextChild->keynum == BTree_T - 1);

	prevChild->key[prevChild->keynum] = key;
	prevChild->child[prevChild->keynum + 1] = nextChild->child[0];
	++prevChild->keynum;

	// �ϲ�
	for (i = 0; i < nextChild->keynum; ++i) {
		prevChild->key[prevChild->keynum] = nextChild->key[i];
		prevChild->child[prevChild->keynum + 1] = nextChild->child[i + 1];
		++prevChild->keynum;
	}

	// �� node ���Ƴ� key �Լ�ָ���̺��ӽڵ��ָ��
	for (i = index; i < node->keynum - 1; ++i) {
		node->key[i] = node->key[i + 1];
		node->child[i + 1] = node->child[i + 2];
	}

	node->key[node->keynum - 1] = 0;
	node->child[node->keynum] = NULL;
	--node->keynum;

	// ������ڵ�û�� key �ˣ�ɾ֮���������ڵ����Ϊǰ�̺��ӽڵ㡣
	if (node->keynum == 0) {
		if (*tree == node) {
			*tree = prevChild;
		}

		free(node);
		node = NULL;
	}

	free(nextChild);
}

void BTree_remove(BTree* tree, int key)
{
	// B-���ı�������֮һ��
	// �Ǹ��ڵ���ڲ��ڵ�Ĺؼ�����Ŀ�������� BTree_T - 1

	int i, j, index;
	BTNode *root = *tree;
	BTNode *node = root;
	BTNode *prevChild, *nextChild, *child;
	int prevKey, nextKey;

	if (!root) {
		printf("Failed to remove %c, it is not in the tree!\n", key);
		return;
	}

	index = 0;
	while (index < node->keynum && key > node->key[index]) {
		++index;
	}

	//
	//  index of key:    i-1  i  i+1
	//	            +---+---+---+---+---+
	//             ...  +   + A +   +  ...
	//	            +---+---+---+---+---+
	//                 /    |    \
	//  index of C: i - 1   i    i + 1
	//               /      |      \
	//	    +---+---+     +---+	  +---+---+
	//     ...  +   +     +   +   +   +  ...
	//	    +---+---+     +---+	  +---+---+
	//      prevChild     child   nextChild

	// Find the key.
	if (index < node->keynum && node->key[index] == key) {
		// 1�����ڽڵ���Ҷ�ӽڵ㣬ֱ��ɾ��
		if (node->isLeaf) {
			for (i = index; i < node->keynum; ++i) {
				node->key[i] = node->key[i + 1];
				node->child[i + 1] = node->child[i + 2];
			}

			--node->keynum;

			if (node->keynum == 0) {
				assert(node == *tree);
				free(node);
				*tree = NULL;
			}

			return;
		}

		// 2a�����λ�� key ǰ���ӽڵ�� key ��Ŀ >= BTree_T��
		// �������� key ��ǰ������ǰ���� key ֵ���� key��
		// Ȼ����ǰ�����ں��ӽڵ��еݹ�ɾ��ǰ����
		else if (node->child[index]->keynum >= BTree_T) {
			prevChild = node->child[index];
			prevKey = prevChild->key[prevChild->keynum - 1];
			node->key[index] = prevKey;

			BTree_remove(&prevChild, prevKey);
		}

		// 2b�����λ�� key ����ӽڵ�� key ��Ŀ >= BTree_T��
		// �������� key �ĺ�̣��ú�̵� key ֵ���� key��
		// Ȼ���ں�����ں��ӽڵ��еݹ�ɾ����̡�
		else if (node->child[index + 1]->keynum >= BTree_T) {
			nextChild = node->child[index + 1];
			nextKey = nextChild->key[0];
			node->key[index] = nextKey;

			BTree_remove(&nextChild, nextKey);
		}

		// 2c��ǰ���ͺ�̶�ֻ���� BTree_T - 1 ���ڵ㣬
		// �� key �½�ǰ�����ӽڵ㣬������̺��ӽڵ�ϲ���ǰ�����ӽڵ㣬
		// ɾ����̺��ӽڵ㣬�� node ���Ƴ� key ��ָ���̺��ӽڵ��ָ�룬
		// Ȼ����ǰ�����ں��ӽڵ��еݹ�ɾ�� key��
		else if (node->child[index]->keynum == BTree_T - 1
			&& node->child[index + 1]->keynum == BTree_T - 1){
			prevChild = node->child[index];

			BTree_merge_child(tree, node, index);

			// ��ǰ�����ӽڵ��еݹ�ɾ�� key
			BTree_remove(&prevChild, key);
		}
	}

	// 3��key �����ڽڵ� node �У���Ӧ����ĳ������ key ���ӽڵ��С�
	//  key < node->key[index], ���� key Ӧ���ں��ӽڵ� node->child[index] ��
	else {
		child = node->child[index];
		if (!child) {
			printf("Failed to remove %c, it is not in the tree!\n", key);
			return;
		}

		if (child->keynum == BTree_T - 1) {
			prevChild = NULL;
			nextChild = NULL;

			if (index - 1 >= 0) {
				prevChild = node->child[index - 1];
			}

			if (index + 1 <= node->keynum) {
				nextChild = node->child[index + 1];
			}

			// 3a��������ں��ӽڵ����ڵ��ֵܽڵ����нڵ����ٰ��� BTree_t ���ؼ���
			// �� node ��һ���ؼ����½��� child �У��������ֵܽڵ���һ���ڵ�������
			// node �У�Ȼ���� child ���ӽڵ��еݹ�ɾ�� key��
			if ((prevChild && prevChild->keynum >= BTree_T)
				|| (nextChild && nextChild->keynum >= BTree_T)) {

				if (nextChild && nextChild->keynum >= BTree_T) {
					child->key[child->keynum] = node->key[index];
					child->child[child->keynum + 1] = nextChild->child[0];
					++child->keynum;

					node->key[index] = nextChild->key[0];

					for (j = 0; j < nextChild->keynum - 1; ++j) {
						nextChild->key[j] = nextChild->key[j + 1];
						nextChild->child[j] = nextChild->child[j + 1];
					}
					--nextChild->keynum;
				}
				else {
					for (j = child->keynum; j > 0; --j) {
						child->key[j] = child->key[j - 1];
						child->child[j + 1] = child->child[j];
					}
					child->child[1] = child->child[0];
					child->child[0] = prevChild->child[prevChild->keynum];
					child->key[0] = node->key[index - 1];
					++child->keynum;

					node->key[index - 1] = prevChild->key[prevChild->keynum - 1];

					--prevChild->keynum;
				}
			}

			// 3b, ������ں��ӽڵ����ڵ��ֵܽڵ㶼ֻ���� BTree_t - 1 ���ؼ��֣�
			// �� child ����һ���ڽڵ�ϲ������� node �е�һ���ؼ����½����ϲ��ڵ��У�
			// ���� node ��ɾ���Ǹ��ؼ��ֺ����ָ�룬�� node �� key Ϊ�գ�ɾ֮������������
			// �������غ��ӽڵ��еݹ�ɾ�� key��
			else if ((!prevChild || (prevChild && prevChild->keynum == BTree_T - 1))
				&& ((!nextChild || nextChild && nextChild->keynum == BTree_T - 1))) {
				if (prevChild && prevChild->keynum == BTree_T - 1) {

					BTree_merge_child(tree, node, index - 1);

					child = prevChild;
				}

				else if (nextChild && nextChild->keynum == BTree_T - 1) {

					BTree_merge_child(tree, node, index);
				}
			}
		}

		BTree_remove(&child, key);
	}
}

BTNode* BTree_search(const BTree tree, int key, int* pos)
{
	if (!tree) {
		return NULL;
	}

	int i = 0;

	while (i < tree->keynum && key > tree->key[i]) {
		++i;
	}

	// Find the key.
	if (i < tree->keynum && tree->key[i] == key) {
		if (pos) {
			*pos = i;
		}

		return tree;
	}

	// tree ΪҶ�ӽڵ㣬�Ҳ��� key������ʧ�ܷ���
	if (tree->isLeaf) {
		return NULL;
	}

	// �ڵ��ڲ���ʧ�ܣ��� tree->key[i - 1]< key < tree->key[i]��
	// ��һ�����ҵĽ��ӦΪ child[i]

	// �Ӵ��̶�ȡ�� i �����ӵ�����
	disk_read(&tree->child[i]);

	// �ݹ�ؼ����������� tree->child[i]
	return BTree_search(tree->child[i], key, pos);
}

void BTree_create(BTree* tree, const int* data, int length)
{
	assert(tree);

	int i;

#ifdef DEBUG_TREE
	debug_print("\n ��ʼ���� B- �����ؼ���Ϊ:\n");
	for (i = 0; i < length; i++) {
		printf(" %c ", data[i]);
	}
	debug_print("\n");
#endif


	for (i = 0; i < length; i++) {
#ifdef DEBUG_TREE
		debug_print("\n����ؼ��� %c:\n", data[i]);
#endif
		BTree_insert(tree, data[i]);

#ifdef DEBUG_TREE
		BTree_print(*tree);
#endif
	}

	debug_print("\n");
}

void BTree_destory(BTree* tree)
{
	int i;
	BTNode* node = *tree;

	if (node) {
		for (i = 0; i <= node->keynum; i++) {
			BTree_destory(&node->child[i]);
		}

		free(node);
	}

	*tree = NULL;
}

