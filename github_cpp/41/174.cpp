#include <iostream>

class Node {
public:
    int value;
    bool red = false;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;

    Node(int value_, int red_, Node *left_, Node *right_, Node *parent_) {
        value = value_;
        red = red_;
        left = left_;
        right = right_;
        parent = parent_;
    }

    Node() {}
};

#define leaf &leaf_node
Node leaf_node = {0, false, leaf, leaf, nullptr};

class Tree {
public:
    Node *root = leaf;
    int count = 0;

    void rotate_left(Node *node) {
        Node *y = node->right;
        node->right = y->left;
        if (y->left != leaf) {
            y->left->parent = node;
        }
        if (y != leaf) {
            y->parent = node->parent;
        }
        if (node->parent) {
            if (node == node->parent->left) {
                node->parent->left = y;
            } else {
                node->parent->right = y;
            }
        } else {
            root = y;
        }
        y->left = node;
        if (node != leaf) {
            node->parent = y;
        }
    }

    void rotate_right(Node *node) {
        Node *y = node->left;
        node->left = y->right;
        if (y->right != leaf) {
            y->right->parent = node;
        }
        if (y != leaf) {
            y->parent = node->parent;
        }
        if (node->parent) {
            if (node == node->parent->right) {
                node->parent->right = y;
            } else {
                node->parent->left = y;
            }
        } else {
            root = y;
        }
        y->right = node;
        if (node != leaf) {
            node->parent = y;
        }
    }

    void insert_fix(Node *node) {
        while (node != root && node->parent->red) {
            if (node->parent == node->parent->parent->left) {
                Node *y = node->parent->parent->right;
                if (y->red) {
                    node->parent->red = false;
                    y->red = false;
                    node->parent->parent->red = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotate_left(node);
                    }
                    node->parent->red = false;
                    node->parent->parent->red = true;
                    rotate_right(node->parent->parent);
                }
            } else {
                Node *y = node->parent->parent->left;
                if (y->red) {
                    node->parent->red = false;
                    y->red = false;
                    node->parent->parent->red = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotate_right(node);
                    }
                    node->parent->red = false;
                    node->parent->parent->red = true;
                    rotate_left(node->parent->parent);
                }
            }
        }
        root->red = false;
    }

    void insert_node(int value) {
        Node *current, *parent, *node;
        current = root;
        parent = nullptr;
        while (current != leaf) {
            if (value == current->value) {
                return;
            }
            parent = current;
            if (value < current->value) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        node = new Node;
        node->value = value;
        node->parent = parent;
        node->left = leaf;
        node->right = leaf;
        node->red = true;
        ++count;
        if (parent) {
            if (value < parent->value) {
                parent->left = node;
            } else {
                parent->right = node;
            }
        } else {
            root = node;
        }
        insert_fix(node);
    }

    Node *find_node(int value) {
        Node *current = root;
        while (current != leaf) {
            if (value == current->value) {
                return current;
            } else {
                if (value < current->value) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
        }
        return nullptr;
    }

    void print(Node *node) {
        if (node == leaf) {
            return;
        }
        print(node->left);
        std::cout << node->value << " ";
        if (node->left == leaf) {
            std::cout << "null ";
        } else {
            std::cout << node->left->value << " ";
        }
        if (node->right == leaf) {
            std::cout << "null ";
        } else {
            std::cout << node->right->value << " ";
        }
        if (node->red) {
            std::cout << "R\n";
        } else {
            std::cout << "B\n";
        }
        print(node->right);
    }
};