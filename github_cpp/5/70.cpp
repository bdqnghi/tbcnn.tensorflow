#include <iostream>
#include <cstdio>
#include <string>
#include "avl-tree.h"


namespace ads {

	AVLNode::AVLNode() {
		this->left = NULL;
		this->right = NULL;
		this->height = 1;
	}


	int update_height_tree(AVLNode * tree) {
		return tree ? (tree->height = max(update_height_tree(tree->left), update_height_tree(tree->right)) + 1) : 0;
	}


	void update_height_node(AVLNode * node) {
		if(node) {
			node->height = max(get_height(node->left), get_height(node->right)) + 1;
		}
	}


	int get_height(AVLNode * node) {
		return node ? node->height : 0;
	}


	signed char get_balance_factor(AVLNode * node) {
		return node ? get_height(node->right) - get_height(node->left) : 0;
	}


	AVLNode * build_avltree(int * arr, int n, int lo, int hi) {
		if(lo <= hi) {
			AVLNode * new_node = new AVLNode();
			new_node->value = arr[(lo + hi) / 2];
			new_node->left  = build_avltree(arr, n, lo, (lo + hi) / 2 - 1);
			new_node->right = build_avltree(arr, n, (lo + hi) / 2 + 1, hi);
			return new_node;
		}
		return NULL;
	}


	AVLNode * make_avltree(int * arr, int n, bool was_sorted) {
		if(!was_sorted) {
			sort_quick<int>(arr, n);
		}
		AVLNode * tree = build_avltree(arr, n, 0, n - 1);
		update_height_tree(tree);
		return tree;
	}


	void inorder_tree_print(AVLNode * tree) {
		if(tree != NULL) {
			inorder_tree_print(tree->left);
			printf("%d ", tree->value);
			inorder_tree_print(tree->right);
		}
	}


	void tree_print(AVLNode * tree, std::string (*node_out)(AVLNode*)) {
		if(tree) {
			deque<AVLNode*> * v = make_deque<AVLNode*>();
			deque<AVLNode*> * t;
			push_back_deque<AVLNode*>(v, tree);

			do {
				t = make_deque<AVLNode*>();
				while(!is_deque_empty<AVLNode*>(v)) {
					if(top_deque<AVLNode*>(v) && top_deque<AVLNode*>(v)->left) {
						push_back_deque<AVLNode*>(t, top_deque<AVLNode*>(v)->left);
					}
					if(top_deque<AVLNode*>(v) && top_deque<AVLNode*>(v)->right) {
						push_back_deque<AVLNode*>(t, top_deque<AVLNode*>(v)->right);
					}
					std::cout << node_out(pop_front_deque(v)) << " ";
				}
				std::cout << std::endl;
				delete v;
				v = t;
			} while(!is_deque_empty<AVLNode*>(t));
		}
	}


	void right_rotate(AVLNode *& node) {
		AVLNode* temp = node->left;
		node->left = temp->right;
		temp->right = node;
		node = temp;					// ����� ������
		update_height_node(temp);		// ��� �� ��� ����� ������� �������� - ������� ������� ���� �� ��������
		update_height_node(node);
	}


	void left_rotate(AVLNode *& node) {
		AVLNode* temp = node->right;
		node->right = temp->left;
		temp->left = node;
		node = temp;					// ����� ������
		update_height_node(temp);		// ��� �� ��� ����� ������� �������� - ������� ������� ���� �� ��������
		update_height_node(node);
	}


	void left_big_rotate(AVLNode *& node) {
		right_rotate(node->right);
		left_rotate(node);
	}


	void right_big_rotate(AVLNode *& node) {
		left_rotate(node->left);
		right_rotate(node);
	}


	void balance_node(AVLNode *& node) {
		update_height_node(node);
		// ������ ������ �� ���� ����� ���������� 1 �������� �� ��� ���������� ������ ��� �� 1
		// �� ���� �� 0, 1, -1 �� �� ������, ��� � ���� �� ����������
		// �������������, ������ ������ ������ ����� ���� ���� -2 ���� 2. ����� ����� ������������. ������� ����� ������������
		if(get_balance_factor(node) == -2) {
			if(get_balance_factor(node->left) > 0) {
				right_big_rotate(node);
			} else {
				right_rotate(node);
			}
		} else if(get_balance_factor(node) == 2) {
			if(get_balance_factor(node->right) < 0) {
				left_big_rotate(node);
			} else {
				left_rotate(node);
			}
		}
		// ����� ������������ �� �����
	}



}