#ifndef MyAVL_h
#define MyAVL_h



#include <iomanip>
#include <iostream>
#include "MyString.h"
#include "MyDocuList.h"
using namespace std;

template <class T>
class MyAVLTreeNode{
    public:
        T key;                
        int height;         
		int DF;      
		int occur;   
		int current_docID; 
        MyAVLTreeNode *left;    
        MyAVLTreeNode *right;    
		MyDoculist<T>* html_docuList;  

        MyAVLTreeNode(T value, MyAVLTreeNode *l, MyAVLTreeNode *r):
			key(value), height(0),DF(0),occur(0),left(l),right(r),html_docuList(nullptr),current_docID(-1) {}
};

template <class T>
class MyAVLTree
{
    private:
        MyAVLTreeNode<T> *mRoot;    

    public:
        MyAVLTree();
        ~MyAVLTree();

        
        int height();
        
        int max(int a, int b);

        
        MyAVLTreeNode<T>* search(T key);
        
        MyAVLTreeNode<T>* iterativeSearch(T key);

        
        T minimum();
        
        T maximum();

		
		
		
		
		void adjust(MyAVLTreeNode<T>* &tree, T key);

        
        void insert(T key);

        
        void remove(T key);

        
        void destroy();

        
        void print();
		 
        void preOrder();
        
        void inOrder();
        
        void postOrder();

    private:
        
        int height(MyAVLTreeNode<T>* tree) ;

        
        void preOrder(MyAVLTreeNode<T>* tree) const;
        
        void inOrder(MyAVLTreeNode<T>* tree) const;
        
        void postOrder(MyAVLTreeNode<T>* tree) const;

        
        MyAVLTreeNode<T>* search(MyAVLTreeNode<T>* x, T key) const;
        
        MyAVLTreeNode<T>* iterativeSearch(MyAVLTreeNode<T>* x, T key) const;

        
        MyAVLTreeNode<T>* minimum(MyAVLTreeNode<T>* tree);
        
        MyAVLTreeNode<T>* maximum(MyAVLTreeNode<T>* tree);

        
        MyAVLTreeNode<T>* leftLeftRotation(MyAVLTreeNode<T>* k2);

        
        MyAVLTreeNode<T>* rightRightRotation(MyAVLTreeNode<T>* k1);

        
        MyAVLTreeNode<T>* leftRightRotation(MyAVLTreeNode<T>* k3);

        
        MyAVLTreeNode<T>* rightLeftRotation(MyAVLTreeNode<T>* k1);	

        
        MyAVLTreeNode<T>* insert(MyAVLTreeNode<T>* &tree, T key);

        
        MyAVLTreeNode<T>* remove(MyAVLTreeNode<T>* &tree, MyAVLTreeNode<T>* z);

        
        void destroy(MyAVLTreeNode<T>* &tree);

        
        void print(MyAVLTreeNode<T>* tree, T key, int direction);

};


template <class T>
MyAVLTree<T>::MyAVLTree():mRoot(NULL)
{
}


template <class T>
MyAVLTree<T>::~MyAVLTree() 
{
    destroy(mRoot);
}


template <class T>
int MyAVLTree<T>::height(MyAVLTreeNode<T>* tree) 
{
    if (tree != NULL)
        return tree->height;

    return 0;
}

template <class T>
int MyAVLTree<T>::height() 
{
    return height(mRoot);
}


template <class T>
int MyAVLTree<T>::max(int a, int b) 
{
    return a>b ? a : b;
}



template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::search(MyAVLTreeNode<T>* x, T key) const
{
    if (x == NULL || x->key == key)
        return x;

    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}

template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::search(T key) 
{
    return search(mRoot, key);
}


template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::iterativeSearch(MyAVLTreeNode<T>* x, T key) const
{
    while ((x!=NULL) && (x->key!=key))
    {
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    return x;
}

template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::iterativeSearch(T key)
{
    return iterativeSearch(mRoot, key);
}


template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::minimum(MyAVLTreeNode<T>* tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->left != NULL)
        tree = tree->left;
    return tree;
}

template <class T>
T MyAVLTree<T>::minimum()
{
    MyAVLTreeNode<T> *p = minimum(mRoot);
    if (p != NULL)
        return p->key;

    return (T)NULL;
}
 

template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::maximum(MyAVLTreeNode<T>* tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->right != NULL)
        tree = tree->right;
    return tree;
}

template <class T>
T MyAVLTree<T>::maximum()
{
    MyAVLTreeNode<T> *p = maximum(mRoot);
    if (p != NULL)
        return p->key;

    return (T)NULL;
}


template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::leftLeftRotation(MyAVLTreeNode<T>* k2)
{
    MyAVLTreeNode<T>* k1;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max( height(k2->left), height(k2->right)) + 1;
    k1->height = max( height(k1->left), k2->height) + 1;

    return k1;
}


template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::rightRightRotation(MyAVLTreeNode<T>* k1)
{
    MyAVLTreeNode<T>* k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max( height(k1->left), height(k1->right)) + 1;
    k2->height = max( height(k2->right), k1->height) + 1;

    return k2;
}


template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::leftRightRotation(MyAVLTreeNode<T>* k3)
{
    k3->left = rightRightRotation(k3->left);

    return leftLeftRotation(k3);
}


template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::rightLeftRotation(MyAVLTreeNode<T>* k1)
{
    k1->right = leftLeftRotation(k1->right);

    return rightRightRotation(k1);
}


template <class T>
void MyAVLTree<T>::adjust(MyAVLTreeNode<T>* &tree, T key)
{
	 if (height(tree->left) - height(tree->right) == 2)
     {
        if (key < tree->left->key)
		{
            tree = leftLeftRotation(tree);
		}
        else
		{
            tree = leftRightRotation(tree);
		}
     }
	 else if (height(tree->right) - height(tree->left) == 2)
	 {
        if (key > tree->right->key)
		{
            tree = rightRightRotation(tree);
		}
        else
		{
            tree = rightLeftRotation(tree);
		}
     }
	 else
	 {}
}




template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::insert(MyAVLTreeNode<T>* &tree, T key)
{
    if (tree == NULL) 
    {
        
        tree = new MyAVLTreeNode<T>(key, NULL, NULL);
        if (tree==NULL)
        {
            cout << "ERROR: create MyAVLTree node failed!" << endl;
            return NULL;
        }
    }
    else if ( key < tree->key ) 
    {
		
        tree->left = insert(tree->left, key);
		
		adjust(tree,key);
		
    }
    else if ( key > tree->key ) 
    {
		
        tree->right = insert(tree->right, key);
        
		adjust(tree,key);
       
    }
    else 
    {
       
    }

    tree->height = max( height(tree->left), height(tree->right)) + 1;

    return tree;
}

template <class T>
void MyAVLTree<T>::insert(T key)
{
    insert(mRoot, key);
}


template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::remove(MyAVLTreeNode<T>* &tree, MyAVLTreeNode<T>* z)
{
    
    if (tree==NULL || z==NULL)
        return NULL;

    if (z->key < tree->key)        
    {
        tree->left = remove(tree->left, z);
        
        if (height(tree->right) - height(tree->left) == 2)
        {
            MyAVLTreeNode<T> *r =  tree->right;
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
            MyAVLTreeNode<T> *l =  tree->left;
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
                
                
                
                
                MyAVLTreeNode<T>* max = maximum(tree->left);
                tree->key = max->key;
                tree->left = remove(tree->left, max);
            }
            else
            {
                
                
                
                
                MyAVLTreeNode<T>* min = maximum(tree->right);
                tree->key = min->key;
                tree->right = remove(tree->right, min);
            }
        }
        else
        {
            MyAVLTreeNode<T>* tmp = tree;
            tree = (tree->left!=NULL) ? tree->left : tree->right;
            delete tmp;
        }
    }

    return tree;
}

template <class T>
void MyAVLTree<T>::remove(T key)
{
    MyAVLTreeNode<T>* z; 

    if ((z = search(mRoot, key)) != NULL)
        mRoot = remove(mRoot, z);
}


template <class T>
void MyAVLTree<T>::destroy(MyAVLTreeNode<T>* &tree)
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
void MyAVLTree<T>::destroy()
{
    destroy(mRoot);
}


template <class T>
void MyAVLTree<T>::print(MyAVLTreeNode<T>* tree, T key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    
            wcout << setw(2) << tree->key << " is root" << endl;
        else                
            wcout << setw(2) << tree->key << " is " << setw(2) << key << "'s "  << setw(12) << (direction==1?"right child" : "left child") << endl;

        print(tree->left, tree->key, -1);
        print(tree->right,tree->key,  1);
    }
}

template <class T>
void MyAVLTree<T>::print()
{
    if (mRoot != NULL)
        print(mRoot, mRoot->key, 0);
}


template <class T>
void MyAVLTree<T>::preOrder(MyAVLTreeNode<T>* tree) const
{
    if(tree != NULL)
    {
        wcout<< tree->key << " " ;
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

template <class T>
void MyAVLTree<T>::preOrder() 
{
    preOrder(mRoot);
}


template <class T>
void MyAVLTree<T>::inOrder(MyAVLTreeNode<T>* tree) const
{
    if(tree != NULL)
    {
        inOrder(tree->left);
        wcout<< tree->key << " " ;
        inOrder(tree->right);
    }
}

template <class T>
void MyAVLTree<T>::inOrder() 
{
    inOrder(mRoot);
}


template <class T>
void MyAVLTree<T>::postOrder(MyAVLTreeNode<T>* tree) const
{
    if(tree != NULL)
    {
        postOrder(tree->left);
        postOrder(tree->right);
        wcout<< tree->key << " " ;
    }
}

template <class T>
void MyAVLTree<T>::postOrder() 
{
    postOrder(mRoot);
}



void MyAVLTree_Test1();

#endif


