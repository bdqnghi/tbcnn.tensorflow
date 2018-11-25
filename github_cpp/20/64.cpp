








#include <iostream>

#define max(a, b) (a > b ? a : b)

enum color_t {RED, BLACK};

class Tree;
Tree *T;

class Node { 
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
    Node NIL; 
    Tree();
    void print(Node *x);
    int depth(Node *x);
    void insert(int d);
    void insertFixUp(Node *z);
    void leftRotate(Node *x);
    void rightRotate(Node *y);
};


Node::Node() { 
    left = &T->NIL;
    right = &T->NIL;
    parent = &T->NIL;
}

Node::Node(int d, color_t c) { 
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

    

    Node *y = x->right; 

    
    x->right = y->left;

    if (y->left != &T->NIL) {
        y->left->parent = x; 
    }

    
    y->parent = x->parent;
    if (x->parent == &T->NIL) { 
        T->root = y;
    } else if (x == x->parent->left) { 
        x->parent->left = y;
    } else { 
        x->parent->right = y;
    }

    
    y->left = x;
    x->parent = y;

    
}

void Tree::rightRotate(Node *y) {

    

    Node *x = y->left; 

    
    y->left = x->right;

    if (x->right != &T->NIL) {
        x->right->parent = y; 
    }

    
    x->parent = y->parent;
    if (y->parent == &T->NIL) { 
        T->root = x;
    } else if (y == y->parent->left) { 
        y->parent->left = x;
    } else { 
        y->parent->right = x;
    }

    
    x->right = y;
    y->parent = x;

    
}

void Tree::insert(int d) {
    Node *z = new Node(d, RED); 
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
    if (p == &NIL) { 
        T->root = z;
    } else if (z->data < p->data) { 
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
    
    
    

    
    
    

    while (z->parent != &T->NIL && z->parent->color == RED) { 
        

        Node *parent = z->parent;
        Node *grandpa = z->parent->parent; 

        
        if (parent == grandpa->left) {

            Node *uncle = grandpa->right; 

            
            if (uncle != &T->NIL && uncle->color == RED) { 
                parent->color = BLACK;
                uncle->color = BLACK;
                grandpa->color = RED; 
                z = grandpa; 
            }

            else {
                
                if (z == parent->right) {

                    
                    z = parent;
                    leftRotate(z);
                }

                
                parent->color = BLACK;
                grandpa->color = RED;
                rightRotate(grandpa);
            }
        }

        
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
