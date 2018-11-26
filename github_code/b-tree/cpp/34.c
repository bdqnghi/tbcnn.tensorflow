/** @file BST.h */
#include "TreeException.h"
#include "TreeNode.h"

typedef void (*FunctionType)(TreeItemType& anItem, TreeItemCount& aCount, int freq);

/** @class BinarySearchTree
 * ADT binary search tree.
 * Assumption: A tree contains at most one item with a given
 *             search key at any time. */
class BinarySearchTree
{
public:
// constructors and destructor:
   BinarySearchTree();

   BinarySearchTree(const BinarySearchTree& tree)
      throw(TreeException);
   virtual ~BinarySearchTree();

// binary search tree operations:
// Precondition for all methods: No two items in a binary
// search tree have the same search key.

   /** Determines whether a binary search tree is empty.
    * @return True if the tree is empty; otherwise returns
    *         false. */
   virtual bool isEmpty() const;


   //This function takes in a num set from the main under BST class and sets the 'frequency' value to that.
   virtual void setFreq(int num);

   /** Inserts an item into a binary search tree.
    * @pre The item to be inserted into the tree is newItem.
    * @post newItem is in its proper order in the tree.
    * @throw TreeException  If memory allocation fails. */
   virtual void searchTreeInsert(const TreeItemType& newItem)
      throw(TreeException);

   /** Deletes an item with a given search key from a binary search
    *  tree.
    * @pre searchKey is the search key of the item to be deleted.
    * @post If the item whose search key equals searchKey existed
    *       in the tree, the item is deleted. Otherwise, the tree
    *       is unchanged.
    * @throw TreeException  If searchKey is not found in the
    *        tree. */
   virtual void searchTreeDelete(KeyType searchKey)
      throw(TreeException);

   /** Retrieves an item with a given search key from a binary
    *  search tree.
    * @pre searchKey is the search key of the item to be
    *      retrieved.
    * @post If the retrieval was successful, treeItem contains the
    *       retrieved item.
    * @throw TreeException  If no such item exists. */
   virtual void searchTreeRetrieve(KeyType searchKey, TreeItemType& treeItem) const
      throw(TreeException);

    virtual void searchTreeRetrieveCount(KeyType searchKey, TreeItemCount& treeItemCount) const
      throw(TreeException);

   /** Traverses a binary search tree in preorder, calling function
    *  visit() once for each item.
    * @pre The function represented by visit() exists outside of
    *      the class implementation.
    * @post visit's action occurred once for each item in the
    *       tree.
    * @note visit() can alter the tree. */
   virtual void preorderTraverse(FunctionType visit);

   /** Traverses a binary search tree in sorted order, calling
    *  function visit() once for each item. */
   virtual void inorderTraverse(FunctionType visit);

   /** Traverses a binary search tree in postorder, calling
    *  function visit() once for each item. */
   virtual void postorderTraverse(FunctionType visit);

// overloaded operator:
   virtual BinarySearchTree& operator=(const BinarySearchTree& rhs)
      throw(TreeException);

   virtual bool searchTreeIsItemInTree(KeyType searchKey);

protected:
   /** Recursively inserts an item into a binary search tree.
    * @pre treePtr points to a binary search tree, newItem is the
    *      item to be inserted.
    * @post Same as searchTreeInsert.
    * @throw Same as searchTreeInsert. */
   void insertItem(TreeNode *& treePtr, const TreeItemType& newItem)
      throw(TreeException);

   /** Recursively deletes an item from a binary search tree.
    * @pre treePtr points to a binary search tree, searchKey is the
    *      search key of the item to be deleted.
    * @post Same as searchTreeDelete.
    * @throw Same as searchTreeDelete. */
   void deleteItem(TreeNode *& treePtr, KeyType searchKey)
      throw(TreeException);

   /** Deletes the item in the root of a given tree.
    * @pre nodePtr points to the root of a binary search tree;
    *      nodePtr != NULL.
    * @post The item in the root of the given tree is deleted. */
   void deleteNodeItem(TreeNode *& nodePtr);

   /** Retrieves and deletes the leftmost descendant of a given
    *  node.
    * @pre nodePtr points to a node in a binary search tree;
    *      nodePtr != NULL.
    * @post treeItem contains the item in the leftmost descendant
    *       of the node to which nodePtr points. The leftmost
    *       descendant of nodePtr is deleted. */
   void processLeftmost(TreeNode *& nodePtr,
                        TreeItemType& treeItem);

   /** Recursively retrieves an item from a binary search tree.
    * @pre treePtr points to a binary search tree, searchKey is the
    *      search key of the item to be retrieved.
    * @post Same as searchTreeRetrieve.
    * @throw Same as searchTreeRetrieve. */
   void retrieveItem(TreeNode *treePtr, KeyType searchKey, TreeItemType& treeItem) const
      throw(TreeException);
   void retrieveItemCount(TreeNode *treePtr, KeyType searchKey, TreeItemCount& treeItemCount) const
      throw(TreeException);
// The following 9 methods are the same as for the ADT
// binary tree, and so their specifications are abbreviated.
   void copyTree(TreeNode *treePtr, TreeNode *& newTreePtr) const
      throw(TreeException);
   void destroyTree(TreeNode *& treePtr);
   void preorder(TreeNode *treePtr, int freq, FunctionType visit);
   void inorder(TreeNode *treePtr, int freq, FunctionType visit);
   void postorder(TreeNode *treePtr, int freq, FunctionType visit);
   TreeNode *rootPtr() const;
   void setRootPtr(TreeNode *newRoot);
   void getChildPtrs(TreeNode *nodePtr, TreeNode *& leftChildPtr, TreeNode *& rightChildPtr) const;
   void setChildPtrs(TreeNode *nodePtr, TreeNode *leftChildPtr, TreeNode *rightChildPtr);
   bool isItemInTree(TreeNode *treePtr, KeyType searchKey);

private:
   /** Pointer to root of tree. */
   TreeNode *root;
   int freq;
}; // end BinarySearchTree
// End of header file.
