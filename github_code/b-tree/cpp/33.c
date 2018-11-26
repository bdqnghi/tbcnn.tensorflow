/** @file BST.cpp. */
#include <cstddef>   // definition of NULL
#include <new>       // for bad_alloc
#include <cstring>
#include "BST.h"     // header file

using namespace std;

BinarySearchTree::BinarySearchTree() : root(NULL)
{
}  // end default constructor

BinarySearchTree::BinarySearchTree(const BinarySearchTree& tree)
   throw(TreeException)
{
   copyTree(tree.root, root);
}  // end copy constructor

BinarySearchTree::~BinarySearchTree()
{
   destroyTree(root);
}  // end destructor

bool BinarySearchTree::isEmpty() const
{
   return (root == NULL);
}  // end searchTreeIsEmpty


//Sets the frequency, which is used with the print functions and visit function (created in main) to determine how the 
//BST is printed out and whether or not all words make the print.
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
}  // end searchTreeInsert

void BinarySearchTree::searchTreeDelete(KeyType searchKey)
   throw(TreeException)
{
   deleteItem(root, searchKey);
}  // end searchTreeDelete

void BinarySearchTree::searchTreeRetrieve(KeyType searchKey, TreeItemType& treeItem) const
   throw(TreeException)
{
   // if retrieveItem throws a TreeException, it is
   // ignored here and passed on to the point in the code
   // where searchTreeRetrieve was called
   retrieveItem(root, searchKey, treeItem);
}  // end searchTreeRetrieve

void BinarySearchTree::searchTreeRetrieveCount(KeyType searchKey, TreeItemCount& treeItemCount) const
   throw(TreeException)
{
   // if retrieveItem throws a TreeException, it is
   // ignored here and passed on to the point in the code
   // where searchTreeRetrieve was called
   retrieveItemCount(root, searchKey, treeItemCount);
}  // end searchTreeRetrieve

bool BinarySearchTree::searchTreeIsItemInTree(KeyType searchKey) 
{
	return(isItemInTree(root, searchKey));
}
//Added in 'freq' to determine the minimum number of times a word
//can appear in order to be printed to the screen.
void BinarySearchTree::preorderTraverse(FunctionType visit)
{
   preorder(root, freq, visit);
}  // end preorderTraverse

void BinarySearchTree::inorderTraverse(FunctionType visit)
{
   inorder(root, freq, visit);
}  // end inorderTraverse

void BinarySearchTree::postorderTraverse(FunctionType visit)
{
   postorder(root, freq, visit);
}  // end postorderTraverse

//This is my insertElement fucntion that needed to be altered from the book to work with a char array
void BinarySearchTree::insertItem(TreeNode *& treePtr, const TreeItemType& newItem)
   throw(TreeException)
{
   if (treePtr == NULL)
   {  // position of insertion found; insert after leaf

      // create a new node
      try
      {
		 treePtr = new TreeNode(newItem, 1, NULL, NULL);
      }
      catch (bad_alloc e)
      {
	 throw TreeException("TreeException: insertItem cannot allocate memory");
      }  // end try
   }
   else if(treePtr->item.getKey() == newItem.getKey()) 
   {
	   treePtr->count = treePtr->count.getKeyCount() + 1;
	   //treePtr = new TreeNode(newItem, treePtr->count.getKeyCount() + 1, NULL, NULL);
   }
   // else search for the insertion position
   else if (newItem.getKey() < treePtr->item.getKey()) // newItem < TreePtr item
      // search the left subtree
      insertItem(treePtr->leftChildPtr, newItem);

   else  // search the right subtree
      insertItem(treePtr->rightChildPtr, newItem);
}  // end insertItem

void BinarySearchTree::deleteItem(TreeNode *& treePtr, KeyType searchKey)
   throw(TreeException)
// Calls: deleteNodeItem.
{
   if (treePtr == NULL)
      throw TreeException("TreeException: delete failed");  // empty tree

   else if (searchKey == treePtr->item.getKey())
      // item is in the root of some subtree
      deleteNodeItem(treePtr);  // delete the item

   // else search for the item
   else if (searchKey < treePtr->item.getKey()) // searchKey < treePtr->item.getKey()
      // search the left subtree
      deleteItem(treePtr->leftChildPtr, searchKey);

   else  // search the right subtree
      deleteItem(treePtr->rightChildPtr, searchKey);
}  // end deleteItem

void BinarySearchTree::deleteNodeItem(TreeNode *& nodePtr)
// Algorithm note: There are four cases to consider:
//   1. The root is a leaf.
//   2. The root has no left child.
//   3. The root has no right child.
//   4. The root has two children.
// Calls: processLeftmost.
{
   TreeNode     *delPtr;
   TreeItemType replacementItem;

   // test for a leaf
   if ( (nodePtr->leftChildPtr == NULL) &&
        (nodePtr->rightChildPtr == NULL) )
   {  delete nodePtr;
      nodePtr = NULL;
   }  // end if leaf
   // test for no left child
   else if (nodePtr->leftChildPtr == NULL)
   {  delPtr = nodePtr;
      nodePtr = nodePtr->rightChildPtr;
      delPtr->rightChildPtr = NULL;
      delete delPtr;
   }  // end if no left child

   // test for no right child
   else if (nodePtr->rightChildPtr == NULL)
   {  delPtr = nodePtr;
      nodePtr = nodePtr->leftChildPtr;
      delPtr->leftChildPtr = NULL;
      delete delPtr;
   }  // end if no right child

   // there are two children:
   // retrieve and delete the inorder successor
   else
   {  processLeftmost(nodePtr->rightChildPtr, replacementItem);
      nodePtr->item = replacementItem;
   }  // end if two children
}  // end deleteNodeItem

void BinarySearchTree::processLeftmost(TreeNode *& nodePtr, TreeItemType& treeItem)
{
   if (nodePtr->leftChildPtr == NULL)
   {  treeItem = nodePtr->item;
      TreeNode *delPtr = nodePtr;
      nodePtr = nodePtr->rightChildPtr;
      delPtr->rightChildPtr = NULL;  // defense
      delete delPtr;
   }

   else
      processLeftmost(nodePtr->leftChildPtr, treeItem);
}  // end processLeftmost

void BinarySearchTree::retrieveItem(TreeNode *treePtr,KeyType searchKey, TreeItemType& treeItem) const
   throw(TreeException)
{
   if (treePtr == NULL)
      throw TreeException("TreeException: searchKey not found");

   else if (searchKey == treePtr->item.getKey())
      // item is in the root of some subtree
      treeItem = treePtr->item;

   else if (searchKey < treePtr->item.getKey()) //searchKey < treePtr->item.getKey()
      // search the left subtree
      retrieveItem(treePtr->leftChildPtr, searchKey, treeItem);

   else  // search the right subtree
      retrieveItem(treePtr->rightChildPtr, searchKey, treeItem);
}  // end retrieveItem

void BinarySearchTree::retrieveItemCount(TreeNode *treePtr, KeyType searchKey, TreeItemCount& treeItemCount) const
   throw(TreeException)
{
   if (treePtr == NULL)
      throw TreeException("TreeException: searchKey not found");

   else if (searchKey == treePtr->item.getKey())
      treeItemCount = treePtr->count.getKeyCount();

   else if (searchKey < treePtr->item.getKey()) //searchKey < treePtr->item.getKey()
      // search the left subtree
      retrieveItemCount(treePtr->leftChildPtr, searchKey, treeItemCount);

   else  // search the right subtree
      retrieveItemCount(treePtr->rightChildPtr, searchKey, treeItemCount);
}  // end retrieveItem

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

// Implementations of copyTree, destroyTree, preorder,
// inorder, postorder, setRootPtr, rootPtr, getChildPtrs,
// setChildPtrs, and the overloaded assignment operator are
// the same as for the ADT binary tree.
// End of implementation file