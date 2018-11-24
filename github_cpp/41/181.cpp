//
//  RedBlackTree
// (1) Every node is either black or red
// (2) The root is black
// (3) Every leaf (NIL) is black
// (4) If a node is red, both its children are black (no two red nodes in a row)
// (5) All the simple paths (root-nil) contain the same number of black nodes
//

#include <iostream>

#define max(a, b) (a > b ? a : b)

enum color_t {RED, BLACK};

class Tree;
Tree *T;

class Node { // could be a struct!
public:
    int data;
    color_t color;
    Node *left;
    Node *right;
    Node *parent;
    Node();
    Node(int d, color_t c);
};

class Tree {
public:
    Node *root;
    Node NIL; // sentinel node
    Tree();
    void print(Node *x);
    int depth(Node *x);
    void insert(int d);
    void insertFixUp(Node *z);
    void leftRotate(Node *x);
    void rightRotate(Node *y);
};


Node::Node() { // default constructor
    left = &T->NIL;
    right = &T->NIL;
    parent = &T->NIL;
}

Node::Node(int d, color_t c) { // if data and color are known
    Node();
    data = d;
    color = c;
}

Tree::Tree() {
    root = &NIL;
    NIL.color = BLACK;
}

int Tree::depth(Node *x) {
    if (x == &T->NIL) { return 0; }
    return 1 + max(depth(x->left), depth(x->right));
}

void Tree::print(Node *x) {
    if (x != &T->NIL) {
        print(x->left);
        printf("%d ", x->data);
        print(x->right);
    }
}

void Tree::leftRotate(Node *x) {

    /* Left Rotate with Example
     x
     /   \
     a     some node (we will let y points to this node)
     / \
     b  c
     */

    Node *y = x->right; // y points to x's right subtree

    // (1) move y's left into x's right (x's right is now node b, y's right is c)
    x->right = y->left;

    if (y->left != &T->NIL) {
        y->left->parent = x; // b's parent should be changed to x
    }

    // (2) now x's parent should be y's new parent
    y->parent = x->parent;
    if (x->parent == &T->NIL) { // if x was the root, y becomes the new root
        T->root = y;
    } else if (x == x->parent->left) { // if x was a left child of p, y is a left child of p
        x->parent->left = y;
    } else { // if x was a right child of p, y is a right child of p
        x->parent->right = y;
    }

    // (3) x should be a left child of y
    y->left = x;
    x->parent = y;

    /*  Final
     y
     / \
     x   c
     /  \
     a    b
     */
}

void Tree::rightRotate(Node *y) {

    /*  Example
     y
     / \
     x   c
     / \
     a   b
     */

    Node *x = y->left; // x points to y's left subtree

    // (1) move x's right into y's left (x's left is now node a, y's left is node b)
    y->left = x->right;

    if (x->right != &T->NIL) {
        x->right->parent = y; // b's parent should be changed to y
    }

    // (2) now y's parent should be x's new parent
    x->parent = y->parent;
    if (y->parent == &T->NIL) { // if y was the root, x becomes the new root
        T->root = x;
    } else if (y == y->parent->left) { // if y was a left child of p, x is a left child of p
        y->parent->left = x;
    } else { // if y was a right child of p, x is a right child of p
        y->parent->right = x;
    }

    // (3) y should be a right child of x
    x->right = y;
    y->parent = x;

    /*  Final
     x
     / \
     a   y
     / \
     b   c
     */
}

void Tree::insert(int d) {
    Node *z = new Node(d, RED); // create a new node
    Node *x = T->root;
    Node *p = &T->NIL;
    while (x != &T->NIL) {
        p = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = p;
    if (p == &NIL) { // tree was empty
        T->root = z;
    } else if (z->data < p->data) { // left child
        p->left = z;
    } else {
        p->right = z;
    }
    z->left = &T->NIL;
    z->right = &T->NIL;
    z->color = RED;
    insertFixUp(z);
}

void Tree::insertFixUp(Node *z) {
    // possible violations are properties:
    // (2) root is black (might be red now)
    // (4) No two reds in a row (we might have two red nodes now)

    // Note here that if there isn't a grandpa then parent must have started as a black node since it's the root,
    // so we won't have violations!
    // if parent is NIL then that's easy, just re-color to black, last line of the function

    while (z->parent != &T->NIL && z->parent->color == RED) { // Parent exists and is RED (TWO REDS in a row)
        // Parent is red implies that the parent is not the root of the tree

        Node *parent = z->parent;
        Node *grandpa = z->parent->parent; // must exist

        // (A) *** PARENT IS A LEFT CHILD *** //
        if (parent == grandpa->left) {

            Node *uncle = grandpa->right; // z's uncle

            // CASE 1: uncle is red
            if (uncle != &T->NIL && uncle->color == RED) { // if the uncle is red, color the parent and the uncle BLACK
                parent->color = BLACK;
                uncle->color = BLACK;
                grandpa->color = RED; // color grandpa RED
                z = grandpa; // z now points to grandpa (because grandpa might now cause violations)
            }

            else {
                // CASE 2: uncle is black && z is a right child
                if (z == parent->right) {

                    // We transform CASE 2 into CASE 3
                    z = parent;
                    leftRotate(z);
                }

                // CASE 3: uncle is black and z is left child
                parent->color = BLACK;
                grandpa->color = RED;
                rightRotate(grandpa);
            }
        }

        // (B) *** PARENT IS A RIGHT CHILD *** // Symmetric
        else {
            Node *uncle = grandpa->left;

            if (uncle != &T->NIL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandpa->color = RED;
                z = grandpa;
            }
            else {
                if (z == parent->left) {
                    z = parent;
                    rightRotate(z);
                }

                parent->color = BLACK;
                grandpa->color = RED;
                leftRotate(grandpa);
            }
        }
    }
    T->root->color = BLACK;
}

int main() {
    T = new Tree();
    T->insert(5);
    printf("root is now %d\n", T->root->data);
    printf("depth of the tree = %d\n\n", T->depth(T->root));

    T->insert(10);
    printf("root is now %d\n", T->root->data);
    printf("%d\n", T->root->left == &T->NIL);
    printf("depth of the tree = %d\n\n", T->depth(T->root));

    T->insert(12);
    printf("root is now %d\n", T->root->data);
    printf("depth of the tree = %d\n\n", T->depth(T->root));

    T->insert(14);
    printf("root is now %d\n", T->root->data);
    printf("depth of the tree = %d\n\n", T->depth(T->root));

    T->insert(16);
    printf("root is now %d\n", T->root->data);
    printf("depth of the tree = %d\n\n", T->depth(T->root));

    T->insert(18);
    printf("root is now %d\n", T->root->data);
    printf("depth of the tree = %d\n\n", T->depth(T->root));

    T->insert(20);
    printf("root is now %d\n", T->root->data);
    printf("depth of the tree = %d\n\n", T->depth(T->root));
    
    T->insert(22);
    printf("root is now %d\n", T->root->data);
    printf("depth of the tree = %d\n\n", T->depth(T->root));
    T->print(T->root);
    return 0;
}
