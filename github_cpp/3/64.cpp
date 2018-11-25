#ifndef TREES_AVLTREE_H
#define TREES_AVLTREE_H

#include <iostream>
#include <list>
#include <vector>
#include <functional>

using namespace std;

class AVLTree {

private:
    
    struct Node {
        
        const int key;

        
        Node *previous = nullptr;

        
        Node *left = nullptr;

        
        Node *right = nullptr;

        
        int balance = 0;

        
        AVLTree *tree = nullptr;

        
        Node(const int k, AVLTree *t);

        
        Node(const int k, Node *p, Node *l, Node *r, AVLTree *t);

        
        ~Node();

        
        void upin(bool growedLeft);

        
        void upout(bool leftShrinked);

        
        void rightRotation();

        
        void leftRightRotation();

        
        void rightLeftRotation();

        
        void leftRotation();

        
        bool isRoot();

        
        bool isLeftFollower();

        
        int height();

        
        vector<int> *preorder() const;  

        
        vector<int> *inorder() const;   

        
        vector<int> *postorder() const; 
    };

    
    Node *root = nullptr;

public:
    
    ~AVLTree();

    
    bool search(const int) const;

    
    void insert(const int);

    
    void remove(const int);

    
    vector<int> *preorder() const;  

    
    vector<int> *inorder() const;   

    
    vector<int> *postorder() const; 


    friend ostream &operator<<(ostream &, const AVLTree &);
    friend class treeplotter;
    
    int getBalance(const int);

    
    Node* find(const int);

};

#endif 
