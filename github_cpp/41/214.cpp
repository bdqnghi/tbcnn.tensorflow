// #define USE_FILE_IO
#define NDEBUG

#include <cassert>
#include <cstring>
#include <climits>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

#ifndef USE_FILE_IO
#include <iostream>
using std::cin;
using std::cout;
#else
static ifstream cin("tree.in");
static ofstream cout("tree.out");
#endif  // IFNDEF USE_FILE_IO

inline void initialize() {
#ifndef USE_FILE_IO
    ios::sync_with_stdio(false);
#endif
};

#define BLACK false
#define RED true
#define IS_RED(x) (x != nullptr && x->is_red())

struct Node {
    Node() = default;
    Node(int _key = 0, int _value = 0, bool _color = BLACK,
         Node *_left = nullptr, Node *_right = nullptr)
            : key(_key)
            , value(_value)
            , left(_left)
            , right(_right)
            , color(_color) {}

    int key = 0;
    int value = 0;
    Node *left = nullptr;
    Node *right = nullptr;
    bool color = BLACK;

    auto is_red() const -> bool {
        return color;
    }

    std::string print_node() {
        stringstream buffer;

        buffer << key;
        if (color == RED) {
            buffer << "[color=red]";
        }
        buffer << ";";

        if (left != nullptr) {
            buffer << key << ":sw -> " << left->key << ";";
        }

        if (right != nullptr) {
            buffer << key << ":se -> " << right->key << ";";
        }

        return buffer.str();
    }
};  // struct Node

static Node *tree = nullptr;

Node *insert(Node *h, int key, int value);
Node *remove(Node *h, int key);
int query(Node *h, int key);

Node *min_node(Node *h);
Node *remove_min_node(Node *h);

Node *right_rotate(Node *h);
Node *left_rotate(Node *h);
void flip_color(Node *h);
Node *move_red_left(Node *h);
Node *move_red_right(Node *h);
Node *balance(Node *h);

void print_tree(Node *node);
void print_tree(Node *node, std::string &data);

int main() {
    initialize();

    char command;
    int key = INT_MAX, value = INT_MAX;
    while (cin >> command) {
        switch (command) {
            case 'A':
                cin >> key >> value;
                tree = insert(tree, key, value);

                tree->color = BLACK;

                break;
            case 'D':
                cin >> key;

                if (!IS_RED(tree->left) && !IS_RED(tree->right))
                    tree->color = RED;

                tree = remove(tree, key);

                if (tree != nullptr)
                    tree->color = BLACK;

                break;
            case 'Q':
                cin >> key;
                cout << query(tree, key) << "\n";

                break;
        }  // switch to command

#ifndef NDEBUG
        // if (command == 'A') {
        //     cout << "A " << key << " " << value << endl;
        // }
        // if (command == 'D') {
        //     cout << "D " << key << endl;
        // }

        if (command == 'P') {
            print_tree(tree);
        }
#endif  // IFNDEF NDEBUG
    }   // while

    return 0;
}  // function main

void print_tree(Node *node) {
    std::string data;
    data = "digraph{\nnode [shape=circle];";

    print_tree(node, data);

    data += "}";
    ofstream file("/tmp/tree.tmp.dot");
    file << data;
    file.close();
    system("showdot /tmp/tree.tmp.dot");
}

void print_tree(Node *node, std::string &data) {
    if (node == nullptr)
        return;

    data += node->print_node();
    print_tree(node->left, data);
    print_tree(node->right, data);
}

Node *insert(Node *h, int key, int value) {
    if (h == nullptr)
        return new Node(key, value, RED);

    if (key < h->key)
        h->left = insert(h->left, key, value);
    else if (key > h->key)
        h->right = insert(h->right, key, value);
    else
        h->value = value;

    if (IS_RED(h->right) && !IS_RED(h->left))
        h = left_rotate(h);
    if (IS_RED(h->left) && IS_RED(h->left->left))
        h = right_rotate(h);
    if (IS_RED(h->left) && IS_RED(h->right))
        flip_color(h);

    return h;
}

Node *remove(Node *h, int key) {
#ifndef NDEBUG
    print_tree(h);
#endif  // IFNDEF NDEBUG

    if (key < h->key) {
        if (!IS_RED(h->left) && h->left != nullptr && !IS_RED(h->left->left))
            h = move_red_left(h);

        h->left = remove(h->left, key);
    } else {
        if (IS_RED(h->left))
            h = right_rotate(h);

        if (key == h->key && h->right == nullptr) {
            delete h;
            return nullptr;
        }

        if (!IS_RED(h->right) && h->right != nullptr &&
            !IS_RED((h->right->left)))
            h = move_red_right(h);

        if (key == h->key) {
            Node *x = min_node(h->right);
            h->key = x->key;
            h->value = x->value;
            h->right = remove_min_node(h->right);
        } else {
            h->right = remove(h->right, key);
        }
    }

    return balance(h);
}

int query(Node *h, int key) {
    Node *current = h;
    while (current != nullptr and current->key != key) {
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    return current != nullptr ? current->value : -1;
}

Node *min_node(Node *h) {
    if (h == nullptr)
        return nullptr;

    if (h->left != nullptr)
        return min_node(h->left);

    return h;
}

Node *remove_min_node(Node *h) {
#ifndef NDEBUG
    print_tree(h);
#endif  // IFNDEF NDEBUG

    if (h->left == nullptr) {
        delete h;

        return nullptr;
    }

    if (!IS_RED(h->left) && h->left != nullptr && !IS_RED(h->left->left)) {
        h = move_red_left(h);
    }

    h->left = remove_min_node(h->left);

    return balance(h);
}

Node *right_rotate(Node *h) {
    assert(h != nullptr);
    assert(h->left != nullptr);

    Node *x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = x->right->color;
    x->right->color = RED;

    return x;
}

Node *left_rotate(Node *h) {
    assert(h != nullptr);
    assert(h->right != nullptr);

    Node *x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = x->left->color;
    x->left->color = RED;

    return x;
}

void flip_color(Node *h) {
    assert(h != nullptr);
    assert(h->left != nullptr);
    assert(h->right != nullptr);

    h->color = !h->color;
    h->left->color = !h->left->color;
    h->right->color = !h->right->color;
}

Node *move_red_left(Node *h) {
    assert(h != nullptr);
    assert(h->right != nullptr);

    flip_color(h);
    if (IS_RED(h->right->left)) {
        h->right = right_rotate(h->right);
        h = left_rotate(h);
        flip_color(h);
    }

    return h;
}

Node *move_red_right(Node *h) {
    assert(h != nullptr);
    assert(h->left != nullptr);

    flip_color(h);
    if (IS_RED(h->left->left)) {
        h = right_rotate(h);
        flip_color(h);
    }

    return h;
}

Node *balance(Node *h) {
    assert(h != nullptr);

    if (IS_RED(h->right))
        h = left_rotate(h);
    if (IS_RED(h->left) && IS_RED(h->left->left))
        h = right_rotate(h);
    if (IS_RED(h->left) && IS_RED(h->right))
        flip_color(h);

    return h;
}
