/*
 * avl.cpp
 * Copyright (C) 2017 zhangyuehua <zhangyuehua@zhangyuehuadeMacBook-Pro.local>
 *
 * Distributed under terms of the MIT license.
 * compile: g++ -std=c++11 -g avl.cpp -o avl
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

struct avl_node {
        int data;
        avl_node* lchild;
        avl_node* rchild;
        avl_node* parent;
        int hight;
        
};

class AvlTree {
    private:
        avl_node* root;

    public:
        AvlTree(avl_node* node) {
            root = node;
        };

        AvlTree() {
            root = NULL;
        }

        ~AvlTree() {
        };

        avl_node* create_node(int i) {
            avl_node* node = (avl_node*)malloc(sizeof(avl_node));
            node->data = i;
            node->lchild = NULL;
            node->rchild = NULL;
            node->parent = NULL;
            node->hight = 0;
            return node;
        }

        avl_node* insert(avl_node* node) {
            return add_node(root, node);
        }
        avl_node* add_node(avl_node* root, avl_node* node) {
            if (root == NULL) {
                root = node;
                return root;
            } else {
                if (node->data > root->data) {
                    root->rchild = add_node(root->rchild, node);
                    root->rchild->parent = root;    
                    int balance_factor = this->get_hight(root->rchild) - this->get_hight(root->lchild);
                    if (balance_factor == 2) {
                        if (node->data > root->rchild->data) {
                            root = this->left_rotate(root);                    
                        } else {
                            root = this->right_left_rotate(root);
                        }
                    }
                } else if (node->data < root->data) {
                    root->lchild = add_node(root->lchild, node);
                    root->lchild->parent = root;
                    int balance_factor = this->get_hight(root->lchild) - this->get_hight(root->rchild);
                    if (balance_factor == 2) {
                        if (node->data < root->lchild->data) {
                            root = this->right_rotate(root);
                        } else {
                            root = this->left_right_rotate(root);
                        }
                    }
                } else if (node->data == root->data) {
                    // do nothing
                }
            }
            // update hight
            root->hight = max(this->get_hight(root->lchild), this->get_hight(root->rchild)) + 1;
            return root;
        }

        void mid_traverse(const avl_node* root) {
            if (root == NULL) return;
            if (root->lchild != NULL) {
                mid_traverse(root->lchild);
            }
            cout << root->data << '\t';
            if (root->rchild != NULL) {
                mid_traverse(root->rchild);
            }
        }

        void pre_traverse(const avl_node* root) {
            if (root == NULL ) return;
            cout << root->data << "\t";
            if (root->lchild != NULL) {
                pre_traverse(root->lchild);
            }
            if (root->rchild != NULL) {
                pre_traverse(root->rchild);
            }
        }


        avl_node* get_root() {
            return root;
        }

        void set_root(avl_node* node) {
            this->root = node;
        }

        int get_hight(avl_node* root) {
            if (root == NULL) {
                return 0;
            } else if (root->lchild == NULL && root->rchild == NULL) {
                root->hight = 1;
                return 1;
            }
            else  {
                return root->hight; 
            }
        }

        void set_hight(avl_node* root) {
            if (root == NULL) {
            } else if (root->lchild == NULL && root->rchild == NULL) {
                root->hight = 1;
            }
            else  {
                root->hight = 1 + max(this->get_hight(root->lchild), this->get_hight(root->rchild));
            }
        }


        avl_node* right_rotate(avl_node* root) {
            avl_node* new_root = root->lchild;
            root->lchild = new_root->rchild;
            new_root->rchild = root;

            // update parent
            if (root->lchild != NULL) {
                root->lchild->parent = root;
            }
            root->parent = new_root;
            new_root->parent = NULL;
            this->set_hight(root);
            return new_root;
        }

        avl_node* left_rotate(avl_node* root) {
            avl_node* new_root = root->rchild;
            root->rchild = new_root->lchild;
            new_root->lchild = root;

            // update parent
            if (root->rchild != NULL) {
                root->rchild->parent = root;
            }
            root->parent = new_root;
            new_root->parent = NULL;
            this->set_hight(root);
            return new_root;
        }

        avl_node* left_right_rotate(avl_node* root) {
            avl_node* new_root = left_rotate(root->lchild);
            root->lchild = new_root;
            new_root->parent = root;
            return  right_rotate(root);
        }

        avl_node* right_left_rotate(avl_node* root) {
            avl_node* new_root = right_rotate(root->rchild);
            root->rchild = new_root;
            new_root->parent = root;
            return left_rotate(root);
        }

};

int main(int argc, char* argv[]) {
    for (int i = 0 ; i< argc; ++i) {
        // arg 0 is the app itself
        std::cout<<"arg[" << i << "]" << argv[i] << std::endl;
    }
    /*
     * add your code here
     */


    AvlTree avl;

    if (avl.get_root() == NULL) {
        cout << "this is an empty avl tree" << endl;
    }

    avl.set_root(avl.create_node(6));
    vector<int> a  = {4,12,10,14,8};
    avl_node* node = NULL;
    for (size_t i = 0; i < a.size(); ++i) {
        node = avl.create_node(a[i]);
        avl.set_root(avl.insert(node));
    }

    avl.mid_traverse(avl.get_root());
    cout<< endl;
    avl.pre_traverse(avl.get_root());
    cout<< endl;
    cout<< avl.get_hight(avl.get_root()) << endl;
    cout<< avl.get_hight(avl.get_root()->lchild) << endl;
    cout<< avl.get_hight(avl.get_root()->rchild) << endl;
    cout<< endl;
    return 0;
}


