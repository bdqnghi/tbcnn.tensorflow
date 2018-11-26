#ifndef REDBLACKTREE_H_INCLUDED
#define REDBLACKTREE_H_INCLUDED

typedef int T;                  /* type of item to be stored */

typedef enum { BLACK, RED } nodeColor; /* Red-Black tree description */

struct Node
{
    struct Node *left;         /* left child */
    struct Node *right;        /* right child */
    struct Node *parent;       /* parent */
    nodeColor color;            /* node color (BLACK, RED) */
    T data;                     /* data stored in node */
};

class RedBlackTree
{
public:
    RedBlackTree();
    ~RedBlackTree();
    RedBlackTree(const RedBlackTree &original);
    RedBlackTree &operator=(const RedBlackTree &right);
    RedBlackTree operator+(const RedBlackTree &right) const;    /* sum of sets */
    RedBlackTree operator-(const RedBlackTree &right) const;    /* diference of sets */
    RedBlackTree operator^(const RedBlackTree &right);          /* intersection of sets */

    Node* findNode(T data);
    void insertNode(T data);
    void deleteNode(Node *z);
    void show();                    /* primitive show-function */
    void clear();

<<<<<<< HEAD
private:
=======
private:                    /*эти функции вообще нужно выкинуть из класса, по-хорошему, и реализовывать только в .cpp */
>>>>>>> 7ca7db9168afd7699d340e3d5e1df8b6997ca39a
    void insertFixup(Node *x);
    void deleteFixup(Node *x);
    void rotateLeft(Node *x);
    void rotateRight(Node *x);
    Node *root;                 /* root of Red-Black tree */
};

#endif // REDBLACKTREE_H_INCLUDED
