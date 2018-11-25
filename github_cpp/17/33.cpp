
#include <cstddef>   
#include <new>       
#include <cstring>
#include "BST.h"     

using namespace std;

BinarySearchTree::BinarySearchTree() : root(NULL)
{
}  

BinarySearchTree::BinarySearchTree(const BinarySearchTree& tree)
   throw(TreeException)
{
   copyTree(tree.root, root);
}  

BinarySearchTree::~BinarySearchTree()
{
   destroyTree(root);
}  

bool BinarySearchTree::isEmpty() const
{
   return (root == NULL);
}  




void BinarySearchTree::setFreq(int num)
{
	if(num > 0)
		freq = num;
	else
		freq = 1;
}

void BinarySearchTree::searchTreeInsert(const TreeItemType& newItem)
   throw(TreeException)
{
   insertItem(root, newItem);
}  

void BinarySearchTree::searchTreeDelete(KeyType searchKey)
   throw(TreeException)
{
   deleteItem(root, searchKey);
}  

void BinarySearchTree::searchTreeRetrieve(KeyType searchKey, TreeItemType& treeItem) const
   throw(TreeException)
{
   
   
   
   retrieveItem(root, searchKey, treeItem);
}  

void BinarySearchTree::searchTreeRetrieveCount(KeyType searchKey, TreeItemCount& treeItemCount) const
   throw(TreeException)
{
   
   
   
   retrieveItemCount(root, searchKey, treeItemCount);
}  

bool BinarySearchTree::searchTreeIsItemInTree(KeyType searchKey) 
{
	return(isItemInTree(root, searchKey));
}


void BinarySearchTree::preorderTraverse(FunctionType visit)
{
   preorder(root, freq, visit);
}  

void BinarySearchTree::inorderTraverse(FunctionType visit)
{
   inorder(root, freq, visit);
}  

void BinarySearchTree::postorderTraverse(FunctionType visit)
{
   postorder(root, freq, visit);
}  


void BinarySearchTree::insertItem(TreeNode *& treePtr, const TreeItemType& newItem)
   throw(TreeException)
{
   if (treePtr == NULL)
   {  

      
      try
      {
		 treePtr = new TreeNode(newItem, 1, NULL, NULL);
      }
      catch (bad_alloc e)
      {
	 throw TreeException("TreeException: insertItem cannot allocate memory");
      }  
   }
   else if(treePtr->item.getKey() == newItem.getKey()) 
   {
	   treePtr->count = treePtr->count.getKeyCount() + 1;
	   
   }
   
   else if (newItem.getKey() < treePtr->item.getKey()) 
      
      insertItem(treePtr->leftChildPtr, newItem);

   else  
      insertItem(treePtr->rightChildPtr, newItem);
}  

void BinarySearchTree::deleteItem(TreeNode *& treePtr, KeyType searchKey)
   throw(TreeException)

{
   if (treePtr == NULL)
      throw TreeException("TreeException: delete failed");  

   else if (searchKey == treePtr->item.getKey())
      
      deleteNodeItem(treePtr);  

   
   else if (searchKey < treePtr->item.getKey()) 
      
      deleteItem(treePtr->leftChildPtr, searchKey);

   else  
      deleteItem(treePtr->rightChildPtr, searchKey);
}  

void BinarySearchTree::deleteNodeItem(TreeNode *& nodePtr)






{
   TreeNode     *delPtr;
   TreeItemType replacementItem;

   
   if ( (nodePtr->leftChildPtr == NULL) &&
        (nodePtr->rightChildPtr == NULL) )
   {  delete nodePtr;
      nodePtr = NULL;
   }  
   
   else if (nodePtr->leftChildPtr == NULL)
   {  delPtr = nodePtr;
      nodePtr = nodePtr->rightChildPtr;
      delPtr->rightChildPtr = NULL;
      delete delPtr;
   }  

   
   else if (nodePtr->rightChildPtr == NULL)
   {  delPtr = nodePtr;
      nodePtr = nodePtr->leftChildPtr;
      delPtr->leftChildPtr = NULL;
      delete delPtr;
   }  

   
   
   else
   {  processLeftmost(nodePtr->rightChildPtr, replacementItem);
      nodePtr->item = replacementItem;
   }  
}  

void BinarySearchTree::processLeftmost(TreeNode *& nodePtr, TreeItemType& treeItem)
{
   if (nodePtr->leftChildPtr == NULL)
   {  treeItem = nodePtr->item;
      TreeNode *delPtr = nodePtr;
      nodePtr = nodePtr->rightChildPtr;
      delPtr->rightChildPtr = NULL;  
      delete delPtr;
   }

   else
      processLeftmost(nodePtr->leftChildPtr, treeItem);
}  

void BinarySearchTree::retrieveItem(TreeNode *treePtr,KeyType searchKey, TreeItemType& treeItem) const
   throw(TreeException)
{
   if (treePtr == NULL)
      throw TreeException("TreeException: searchKey not found");

   else if (searchKey == treePtr->item.getKey())
      
      treeItem = treePtr->item;

   else if (searchKey < treePtr->item.getKey()) 
      
      retrieveItem(treePtr->leftChildPtr, searchKey, treeItem);

   else  
      retrieveItem(treePtr->rightChildPtr, searchKey, treeItem);
}  

void BinarySearchTree::retrieveItemCount(TreeNode *treePtr, KeyType searchKey, TreeItemCount& treeItemCount) const
   throw(TreeException)
{
   if (treePtr == NULL)
      throw TreeException("TreeException: searchKey not found");

   else if (searchKey == treePtr->item.getKey())
      treeItemCount = treePtr->count.getKeyCount();

   else if (searchKey < treePtr->item.getKey()) 
      
      retrieveItemCount(treePtr->leftChildPtr, searchKey, treeItemCount);

   else  
      retrieveItemCount(treePtr->rightChildPtr, searchKey, treeItemCount);
}  

void BinarySearchTree::copyTree(TreeNode *treePtr, TreeNode *& newTreePtr) const
	throw(TreeException)
{
	if(treePtr != NULL) {
		try {
			newTreePtr = new TreeNode(treePtr->item, treePtr->count, NULL, NULL);
			copyTree(treePtr->leftChildPtr, newTreePtr->leftChildPtr);
			copyTree(treePtr->rightChildPtr, newTreePtr->rightChildPtr);
		}
		catch (bad_alloc e)
		{
			throw TreeException("TreeException: copyTree cannot allocate memory");
		}
	}
	else
		newTreePtr = NULL;
}

void BinarySearchTree::destroyTree(TreeNode *& treePtr)
{
	if(treePtr != NULL) {
		destroyTree(treePtr->leftChildPtr);
		destroyTree(treePtr->rightChildPtr);
		delete treePtr;
	}
}

void BinarySearchTree::preorder(TreeNode *treePtr, int freq, FunctionType visit)
{
	if(treePtr != NULL) {
		visit(treePtr->item, treePtr->count, freq);
		preorder(treePtr->leftChildPtr, freq, visit);
		preorder(treePtr->rightChildPtr, freq, visit);
	}
}

void BinarySearchTree::inorder(TreeNode *treePtr, int freq, FunctionType visit)
{
	if(treePtr != NULL) {
		inorder(treePtr->leftChildPtr, freq, visit);
		visit(treePtr->item, treePtr->count, freq);
		inorder(treePtr->rightChildPtr, freq, visit);
	}
}

void BinarySearchTree::postorder(TreeNode *treePtr, int freq, FunctionType visit)
{
	if(treePtr != NULL) {
		postorder(treePtr->leftChildPtr, freq, visit);
		postorder(treePtr->rightChildPtr, freq, visit);
		visit(treePtr->item, treePtr->count, freq);
	}
}

void BinarySearchTree::setRootPtr(TreeNode *newRoot)
{
	root = newRoot;
}

TreeNode *BinarySearchTree::rootPtr() const
{
	return root;
}

void BinarySearchTree::getChildPtrs(TreeNode *nodePtr, TreeNode *& leftPtr, TreeNode *& rightPtr) const
{
	nodePtr->leftChildPtr = leftPtr;
	nodePtr->rightChildPtr = rightPtr;
}

void BinarySearchTree::setChildPtrs(TreeNode *nodePtr, TreeNode *leftPtr, TreeNode *rightPtr)
{
	nodePtr->leftChildPtr = leftPtr;
	nodePtr->rightChildPtr = rightPtr;
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& rhs)
	throw(TreeException)
{
	if(this != &rhs) {
		destroyTree(root);
		copyTree(rhs.root, root);
	}
	return *this;
}
bool BinarySearchTree::isItemInTree(TreeNode *treePtr, KeyType searchKey)
{
	if (treePtr == NULL)
		return false;
	else if(searchKey == treePtr->item.getKey())
		return true;
	else if(searchKey < treePtr->item.getKey())
		isItemInTree(treePtr->leftChildPtr, searchKey);
	else
		isItemInTree(treePtr->rightChildPtr, searchKey);
}





