#include <iostream>
#include <vector>
#include "DblBinaryTree.h"

using namespace std;

//*******************************//
// header define                 //
//*******************************//

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
    
    //Used to hold the node that will be deleted
    TreeNode *nodeToDelete = tree;
    
    //Used to locate the point where the
    //left subtree is attached
    TreeNode *attachPoint;
    
    if(tree->right == NULL) {
        
        //replace tree with its left subtree
        tree = tree->left;
    } else if (tree->left == NULL) {
        
        //replace tree with its right subtree
        tree = tree->right;
    } else { //the node has two children
        
        //move to right subtree
        attachPoint = tree->right;
        
        /*locate the smallest node in the right subtree
         by moving as far to the left as possible */
        while(attachPoint->left != NULL)
            attachPoint = attachPoint->left;
        
        /*attach the left subtree of the original tree
         as the left subtree of the smallest node in the
         right subtree */
        attachPoint->left = tree->left;
        
        //replace the original tree with its right subtree
        tree = tree->right;
    }
    
    //delete root of original tree
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
//*******************************//
// end header define             //
//*******************************//

int main() {

    DblBinaryTree tree;
    

	//insert numbers into the tree
    cout << "Inserting numbers. ";
    tree.insert(5.5);
    tree.insert(8.1);
    tree.insert(3.76);
    tree.insert(12.3);
    tree.insert(9.99);
	cout << "\n\n";


	//create a vector for the inorder function
	vector<double> dblVector;

	cout << "Printing the contents of the vector:\n";
	//pass dblVector by reference
	tree.inorder(dblVector);

	
	//loop through dblVector to print out the values now stored in it
	for (int i = 0; i < dblVector.size(); i++) {
	
		cout << dblVector[i] << endl;
	}


    return 0;
}

