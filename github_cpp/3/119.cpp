

#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

typedef char elemType;	


struct nodeType {
	elemType data;		
	nodeType* left;		
	nodeType* right;	
	int balanceFactor;	
};


class binaryTree {
protected:
	nodeType* root; 
	int nodecount(nodeType*) const;                        
	int height(nodeType*) const;                           

	void inorder(nodeType*) const;                         
	void preorder(nodeType*) const;                        
	void postorder(nodeType*) const;                       

	void display(nodeType*) const;                         
public: 
	
	binaryTree() { root = NULL; }; 

	
	int treeNodeCount() const { return nodecount(root); }; 
	int treeHeight() const { return height(root); };       
		  
	
	void postorderTraversal() const { postorder(root); };  
	void inorderTraversal() const { inorder(root); };      
	void preorderTraversal() const { preorder(root); };    

	
	void treeDisplay() const { cout << endl; display( root ); }; 
};



class binarySearchTree : public binaryTree {
protected:
	bool search(const elemType, const nodeType*) const;    
	void insert(const elemType, nodeType*&);               
public:
	bool searchItem(const elemType key) const { return search(key, root); };  
	void insertItem(const elemType key) { insert(key, root); }; 
};



class balancedBST : public binarySearchTree {
protected:
	void rotateLeft(nodeType*&);                           
	void rotateRight(nodeType*&);                          

	void rotateSubtree(nodeType*&);                        

	void insert(const elemType, nodeType*&);               

	void bFactors(const nodeType*) const;                  
	int calcBalanceFactor(nodeType*) const;                
public:
	balancedBST() {};                                      

	
	void insertItem(const elemType key) { insert(key, root); }; 
	void balanceFactors() const { bFactors(root); };       
};
