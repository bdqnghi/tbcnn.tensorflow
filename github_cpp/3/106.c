#include <iostream>
#include <stdio.h>
#include <string.h>
#include<sstream>
#include <fstream>
#include <iomanip>
using namespace std;

template <class T>
class AVLTreeNode{
    public:
        T key;                
        int height;         
        AVLTreeNode *left;    
        AVLTreeNode *right;    

        AVLTreeNode(T value, AVLTreeNode *l, AVLTreeNode *r):
            key(value), height(0),left(l),right(r) {}
};

template <class T>
class AVLTree {
    private:
        AVLTreeNode<T> *mRoot;    

    public:
        AVLTree();
        ~AVLTree();

        
        int height();
        
        int max(int a, int b);

        
        void preOrder();
        
        void inOrder();
        
        void postOrder();

        
        AVLTreeNode<T>* search(T key);

        
        T minimum();
        
        T maximum();

        
        void insert(T key);

        
        void remove(T key);

        
        void destroy();

    private:
        
        int height(AVLTreeNode<T>* tree) ;

        
        void preOrder(AVLTreeNode<T>* tree) const;
        
        void inOrder(AVLTreeNode<T>* tree) const;
        
        void postOrder(AVLTreeNode<T>* tree) const;

        
        AVLTreeNode<T>* search(AVLTreeNode<T>* x, T key) const;

        
        AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);
        
        AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);

        
        AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* k2);

        
        AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* k1);

        
        AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* k3);

        
        AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* k1);

        
        AVLTreeNode<T>* insert(AVLTreeNode<T>* &tree, T key);

        
        AVLTreeNode<T>* remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z);

        
        void destroy(AVLTreeNode<T>* &tree);

};


template <class T>
AVLTree<T>::AVLTree():mRoot(NULL)
{
}


template <class T>
AVLTree<T>::~AVLTree()
{
    destroy(mRoot);
}


template <class T>
int AVLTree<T>::height(AVLTreeNode<T>* tree)
{
    if (tree != NULL)
        return tree->height;

    return 0;
}

template <class T>
int AVLTree<T>::height()
{
    return height(mRoot);
}

template <class T>
int AVLTree<T>::max(int a, int b)
{
    return a>b ? a : b;
}


template <class T>
void AVLTree<T>::preOrder(AVLTreeNode<T>* tree) const
{
    if(tree != NULL)
    {
        cout<< tree->key << " " ;
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

template <class T>
void AVLTree<T>::preOrder()
{
    preOrder(mRoot);
}


template <class T>
void AVLTree<T>::inOrder(AVLTreeNode<T>* tree) const
{
    if(tree != NULL)
    {
        inOrder(tree->left);
        cout<< tree->key << " " ;
        inOrder(tree->right);
    }
}

template <class T>
void AVLTree<T>::inOrder()
{
    inOrder(mRoot);
}


template <class T>
void AVLTree<T>::postOrder(AVLTreeNode<T>* tree) const
{
    if(tree != NULL)
    {
        postOrder(tree->left);
        postOrder(tree->right);
        cout<< tree->key << " " ;
    }
}

template <class T>
void AVLTree<T>::postOrder()
{
    postOrder(mRoot);
}


template <class T>
AVLTreeNode<T>* AVLTree<T>::search(AVLTreeNode<T>* x, T key) const
{
    if (x==NULL || x->key==key)
        return x;

    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::search(T key)
{
    return search(mRoot, key);
}


template <class T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->left != NULL)
        tree = tree->left;
    return tree;
}

template <class T>
T AVLTree<T>::minimum()
{
    AVLTreeNode<T> *p = minimum(mRoot);
    if (p != NULL)
        return p->key;

    return (T)NULL;
}


template <class T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->right != NULL)
        tree = tree->right;
    return tree;
}

template <class T>
T AVLTree<T>::maximum()
{
    AVLTreeNode<T> *p = maximum(mRoot);
    if (p != NULL)
        return p->key;

    return (T)NULL;
}


template <class T>
AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T>* k2)
{
    AVLTreeNode<T>* k1;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max( height(k2->left), height(k2->right)) + 1;
    k1->height = max( height(k1->left), k2->height) + 1;

    return k1;
}


template <class T>
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>* k1)
{
    AVLTreeNode<T>* k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max( height(k1->left), height(k1->right)) + 1;
    k2->height = max( height(k2->right), k1->height) + 1;

    return k2;
}


template <class T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* k3)
{
    k3->left = rightRightRotation(k3->left);

    return leftLeftRotation(k3);
}


template <class T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* k1)
{
    k1->right = leftLeftRotation(k1->right);

    return rightRightRotation(k1);
}


template <class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &tree, T key)
{
    if (tree == NULL)
    {
        
        tree = new AVLTreeNode<T>(key, NULL, NULL);
        if (tree==NULL)
        {
            return NULL;
        }
    }
    else if (key < tree->key) 
    {
        tree->left = insert(tree->left, key);
        
        if (height(tree->left) - height(tree->right) == 2)
        {
            if (key < tree->left->key)
                tree = leftLeftRotation(tree);
            else
                tree = leftRightRotation(tree);
        }
    }
    else if (key > tree->key) 
    {
        tree->right = insert(tree->right, key);
        
        if (height(tree->right) - height(tree->left) == 2)
        {
            if (key > tree->right->key)
                tree = rightRightRotation(tree);
            else
                tree = rightLeftRotation(tree);
        }
    }
    tree->height = max( height(tree->left), height(tree->right)) + 1;

    return tree;
}

template <class T>
void AVLTree<T>::insert(T key)
{
    insert(mRoot, key);
}


template <class T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z)
{
    
    if (tree==NULL || z==NULL)
        return NULL;

    if (z->key < tree->key)        
    {
        tree->left = remove(tree->left, z);
        
        if (height(tree->right) - height(tree->left) == 2)
        {
            AVLTreeNode<T> *r =  tree->right;
            if (height(r->left) > height(r->right))
                tree = rightLeftRotation(tree);
            else
                tree = rightRightRotation(tree);
        }
    }
    else if (z->key > tree->key)
    {
        tree->right = remove(tree->right, z);
        
        if (height(tree->left) - height(tree->right) == 2)
        {
            AVLTreeNode<T> *l =  tree->left;
            if (height(l->right) > height(l->left))
                tree = leftRightRotation(tree);
            else
                tree = leftLeftRotation(tree);
        }
    }
    else    
    {
        
        if ((tree->left!=NULL) && (tree->right!=NULL))
        {
            if (height(tree->left) > height(tree->right))
            {
                
                
                
                
                
                
                AVLTreeNode<T>* max = maximum(tree->left);
                tree->key = max->key;
                tree->left = remove(tree->left, max);
            }
            else
            {
                
                
                
                
                
                
                AVLTreeNode<T>* min = minimum(tree->right);
                tree->key = min->key;
                tree->right = remove(tree->right, min);
            }
        }
        else
        {
            AVLTreeNode<T>* tmp = tree;
            tree = (tree->left!=NULL) ? tree->left : tree->right;
            delete tmp;
        }
    }

    return tree;
}

template <class T>
void AVLTree<T>::remove(T key)
{
    AVLTreeNode<T>* z;

    if ((z = search(mRoot, key)) != NULL)
        mRoot = remove(mRoot, z);
}


template <class T>
void AVLTree<T>::destroy(AVLTreeNode<T>* &tree)
{
    if (tree==NULL)
        return ;

    if (tree->left != NULL)
        destroy(tree->left);
    if (tree->right != NULL)
        destroy(tree->right);

    delete tree;
}

template <class T>
void AVLTree<T>::destroy()
{
    destroy(mRoot);
}

void input() {
    ifstream infile("test.txt");
    string line;

    while(getline(infile, line)) {

        stringstream ss(line);
        
        AVLTree<int>* tree=new AVLTree<int>();

        string data;
        while(data != "IN" && data != "POST" && data != "PRE") {

            getline(ss, data, ' ');

            
            if (data == "IN" || data == "POST" || data == "PRE") {

                
                if (!tree->height()) {
                    cout << "EMPTY";
                } else if (data == "IN") {
                    tree->inOrder();
                } else if (data == "POST") {
                    tree->postOrder();
                } else if (data == "PRE"){
                    tree->preOrder();
                } else {
                    break;
                }
                tree->destroy();

                break;

            } else {
                string operation = data.substr(0, 1);
                int value = stoi(data.substr(1, data.length() - 1));

                if (operation == "A") {
                    tree->insert(value);
                } else if (operation == "D") {
                    tree->remove(value);
                }
            }

            data = "";
        } 
    } 
}

int main()
{

    input();
    return 0;
}