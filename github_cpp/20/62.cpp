#ifndef REDBLACKTREE_H_INCLUDED
#define REDBLACKTREE_H_INCLUDED

typedef int T;                  

typedef enum { BLACK, RED } nodeColor; 

struct Node
{
    struct Node *left;         
    struct Node *right;        
    struct Node *parent;       
    nodeColor color;            
    T data;                     
};

class RedBlackTree
{
public:
    RedBlackTree();
    ~RedBlackTree();
    RedBlackTree(const RedBlackTree &original);
    RedBlackTree &operator=(const RedBlackTree &right);
    RedBlackTree operator+(const RedBlackTree &right) const;    
    RedBlackTree operator-(const RedBlackTree &right) const;    
    RedBlackTree operator^(const RedBlackTree &right);          

    Node* findNode(T data);
    void insertNode(T data);
    void deleteNode(Node *z);
    void show();                    
    void clear();

<<<<<<< HEAD
private:
=======
private:                    
>>>>>>> 7ca7db9168afd7699d340e3d5e1df8b6997ca39a
    void insertFixup(Node *x);
    void deleteFixup(Node *x);
    void rotateLeft(Node *x);
    void rotateRight(Node *x);
    Node *root;                 
};

#endif 
