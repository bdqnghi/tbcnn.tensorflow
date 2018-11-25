#include <iostream>
#include <vector>
#include "DblBinaryTree.h"

using namespace std;





void DblBinaryTree::insert(TreeNode *&tree, double num) {
    
    if(!tree) {
        tree = new TreeNode(num);
        return;
    }
    
    if(tree->value == num) {
        return;
    }
    
    if(num < tree->value) {
        insert(tree->left, num);
    } else {
        insert(tree->right, num);
    }
}

void DblBinaryTree::destroySubtree(TreeNode *tree) {
    
    if(!tree) return;
    destroySubtree(tree->left);
    destroySubtree(tree->right);
    
    delete tree;
}

bool DblBinaryTree::search(double num) const {
    
    TreeNode *tree = root;
    
    while(tree) {
        
        if(tree->value == num)
            return true;
        else if (num < tree->value)
            tree = tree->left;
        else
            tree = tree->right;
    }
    return false;
}

void DblBinaryTree::remove(TreeNode *&tree, double num) {
    
    if(tree == NULL) return;
    if(num < tree->value)
        remove(tree->left, num);
    else if (num > tree->value)
        remove(tree->right, num);
    else
        makeDeletion(tree);
}

void DblBinaryTree::makeDeletion(TreeNode *&tree) {
    
    
    TreeNode *nodeToDelete = tree;
    
    
    
    TreeNode *attachPoint;
    
    if(tree->right == NULL) {
        
        
        tree = tree->left;
    } else if (tree->left == NULL) {
        
        
        tree = tree->right;
    } else { 
        
        
        attachPoint = tree->right;
        
        
        while(attachPoint->left != NULL)
            attachPoint = attachPoint->left;
        
        
        attachPoint->left = tree->left;
        
        
        tree = tree->right;
    }
    
    
    delete nodeToDelete;
}

void DblBinaryTree::displayInOrder(TreeNode *tree) const {
    
    if(tree) {
        
        displayInOrder(tree->left);
        cout << tree->value << "  ";
        displayInOrder(tree->right);
    }
}

void DblBinaryTree::displayPreOrder(TreeNode *tree) const {
    
    if(tree) {
        
        cout << tree->value << "  ";
        displayPreOrder(tree->left);
        displayPreOrder(tree->right);
    }
}

void DblBinaryTree::displayPostOrder(TreeNode *tree) const {
    
    if(tree) {
        
        displayPostOrder(tree->left);
        displayPostOrder(tree->right);
        cout << tree->value << "  ";
    }
}




int main() {

    DblBinaryTree tree;
    

	
    cout << "Inserting numbers. ";
    tree.insert(5.5);
    tree.insert(8.1);
    tree.insert(3.76);
    tree.insert(12.3);
    tree.insert(9.99);
	cout << "\n\n";


	
	vector<double> dblVector;

	cout << "Printing the contents of the vector:\n";
	
	tree.inorder(dblVector);

	
	
	for (int i = 0; i < dblVector.size(); i++) {
	
		cout << dblVector[i] << endl;
	}


    return 0;
}

