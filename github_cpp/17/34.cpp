
#include "TreeException.h"
#include "TreeNode.h"

typedef void (*FunctionType)(TreeItemType& anItem, TreeItemCount& aCount, int freq);


class BinarySearchTree
{
public:

   BinarySearchTree();

   BinarySearchTree(const BinarySearchTree& tree)
      throw(TreeException);
   virtual ~BinarySearchTree();





   
   virtual bool isEmpty() const;


   
   virtual void setFreq(int num);

   
   virtual void searchTreeInsert(const TreeItemType& newItem)
      throw(TreeException);

   
   virtual void searchTreeDelete(KeyType searchKey)
      throw(TreeException);

   
   virtual void searchTreeRetrieve(KeyType searchKey, TreeItemType& treeItem) const
      throw(TreeException);

    virtual void searchTreeRetrieveCount(KeyType searchKey, TreeItemCount& treeItemCount) const
      throw(TreeException);

   
   virtual void preorderTraverse(FunctionType visit);

   
   virtual void inorderTraverse(FunctionType visit);

   
   virtual void postorderTraverse(FunctionType visit);


   virtual BinarySearchTree& operator=(const BinarySearchTree& rhs)
      throw(TreeException);

   virtual bool searchTreeIsItemInTree(KeyType searchKey);

protected:
   
   void insertItem(TreeNode *& treePtr, const TreeItemType& newItem)
      throw(TreeException);

   
   void deleteItem(TreeNode *& treePtr, KeyType searchKey)
      throw(TreeException);

   
   void deleteNodeItem(TreeNode *& nodePtr);

   
   void processLeftmost(TreeNode *& nodePtr,
                        TreeItemType& treeItem);

   
   void retrieveItem(TreeNode *treePtr, KeyType searchKey, TreeItemType& treeItem) const
      throw(TreeException);
   void retrieveItemCount(TreeNode *treePtr, KeyType searchKey, TreeItemCount& treeItemCount) const
      throw(TreeException);


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
   
   TreeNode *root;
   int freq;
}; 

