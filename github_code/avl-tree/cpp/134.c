/*
* Title : Heaps and AVL Trees
* Author : Abdullah Se�kin �zdil
* ID: 21201929
* Section : 1
* Assignment : 3
* Description : AVL Tree
*/
#include "AVLTree.h"
#include<iostream>

using namespace std;

AVLTree::AVLTree()
{
    root = NULL;
}

AVLTree::~AVLTree()
{

}
Node* AVLTree::insert(Node* &root, int key)
{
    if(root == NULL)
    {
        root = new Node();
        root->key = key;
        root->left = NULL;
        root->right = NULL;
        //return root;
    }
    else if(key < root->key)

        root->left = insert(root->left, key);

    else if(key > root->key)

        root->right = insert(root->right, key);

    else
        return root;


    int checkBalance = isBalanced(root);

    if(checkBalance > 1){
        if(key < root->left->key){
            return singleRR(root);
        }

        else{
            root->left = singleLR(root->left);
            return singleRR(root);
        }
    }
    if(checkBalance < -1){
        if(key > root->right->key){
            return singleLR(root);
        }

        else{
            root->right = singleRR(root->right);
            return singleLR(root);
        }
    }

    return root;
}

Node* AVLTree::singleRR(Node* &n)
{
    Node* temp = n->left;
    n->left = temp->right;
    temp->right = n;
    return temp;
}

Node* AVLTree::singleLR(Node* &n)
{
    Node* temp = n->right;
    n->right= temp->left;
    temp->left = n;
    return temp;
}

void AVLTree::insert(int val)
{
    insert(root, val);
}

int AVLTree::findHeight(Node* n)
{
    if(n == NULL)
    {
        return 0;
    }
    else{
        return max(findHeight(n->left), findHeight(n->right)) + 1;
    }
}

int AVLTree::getHeight()
{
    if(root == NULL){
        return 0;
    }else{
        return findHeight(root);
    }
}

int AVLTree::isBalanced(Node* n)
{
    if(n == NULL)
        return 0;

    return findHeight(n->left) - findHeight(n->right);
}

void AVLTree::displayIn()
{
    inOrderTODisplay(root);
    cout<<endl;
}

void AVLTree::displayPre()
{
    preOrdertoDisplay(root);
    cout<<endl;
}

void AVLTree::inOrderTODisplay(Node* n)
{
    if(n == NULL)
        return;
    inOrderTODisplay(n->left);
    cout << n->key << " ";
    inOrderTODisplay(n->right);
}

void AVLTree::preOrdertoDisplay(Node* n)
{
    if(n == NULL)
        return;
    cout << n->key << " ";
    preOrdertoDisplay(n->left);
    preOrdertoDisplay(n->right);
}

void insertionSort(int* arr, int size)
{
    int unsorted, loc, nextItem;

	for(unsorted = 1; unsorted < size; unsorted++){
		nextItem = arr[unsorted];
		loc = unsorted;

		while((loc > 0) && ( arr[loc-1] > nextItem)){
			arr[loc] = arr[loc-1];
			loc--;
		}
		arr[loc] = nextItem;
	}
}

void revArr(int *arr, int size)
{
    int *temp = new int[size];

	for(int i=0; i<size; i++){
		temp[i] = arr[size-1-i];
	}
	arr = temp;
}
