




#include <stddef.h>                 


template <class ItemType>
BinarySearchTree <ItemType>::
   BinarySearchTree(int (*precedes)(const ItemType &one,
                                     const ItemType &two),
                    int (*equals)(const ItemType &one,
                                  const ItemType &two))
   : BinaryTree <ItemType> ()








{
   this -> precedes = precedes;
   this -> equals = equals;
}  


template <class ItemType>
BinarySearchTree <ItemType>::
   BinarySearchTree(BinarySearchTree <ItemType> &source)








{
}  


template <class ItemType>
BinarySearchTree <ItemType>::~BinarySearchTree()





{
}  


template <class ItemType>
void BinarySearchTree <ItemType>::
   operator=(const BinarySearchTree <ItemType> &source)








{
}  


template <class ItemType>
void BinarySearchTree <ItemType>::add(const ItemType &item)






{
   addNode(this->root, item);
}  


template <class ItemType>
void BinarySearchTree <ItemType>::
   addNode(BinaryNode <ItemType> *&start,
           const ItemType &item)
{
   if (start == NULL) 
   {
      start = new BinaryNode <ItemType>;
      start -> info = item;
      start -> left = NULL;
      start -> right = NULL;
   }
   else  
   {
      if (precedes(item, start -> info))
         addNode(start -> left, item);
      else
         addNode(start -> right, item);
   }  
}  


template <class ItemType>
void BinarySearchTree <ItemType>::
   search (ItemType &item, int &found)
{
   searchNode(this->root, item, found);
}  


template <class ItemType>
void BinarySearchTree <ItemType>::
   searchNode(BinaryNode <ItemType> *start,
              ItemType &item,
              int &found)
{
   if (start == NULL)
   {
      found = 0;
   }  
   else if (equals(item, start -> info))
   {
      item = start -> info;
      found = 1;
   }
   else
   {
      if (precedes(item, start -> info))
         searchNode(start -> left, item, found);
      else
         searchNode(start -> right, item, found);
   }
}  


template <class ItemType>
void BinarySearchTree <ItemType>::remove(const ItemType &item)






{
   removeNode(this->root, item);
}  


template <class ItemType>
void BinarySearchTree <ItemType>::
   removeNode(BinaryNode <ItemType> *&start,
              const ItemType &item)
{
   if (start -> info == item)
   {
		BinaryNode<ItemType> 	*temp;
		
		if (start -> left == NULL && start -> right == NULL)	
		{
			temp = start;
			start = NULL;
			delete temp;
		}
      else if (start -> left != NULL && start -> right == NULL)	
		{
			temp = start;
			start = start -> left;
			delete temp;
		}
		else if (start -> left == NULL && start -> right != NULL)	
		{
			temp = start;
			start = start -> right;
			delete temp;
		}
		else	
		{
			BinaryNode<ItemType>		*parent;
			parent = start -> right;
			temp = parent -> left;
	
			if (temp == NULL)
			{
				start -> info = parent -> info;
				start -> right = parent -> right;
				delete parent;
			}
			else
			{				
				while (temp -> left != NULL)
				{
					parent = temp;
					temp = temp -> left;
				}			
			
				start -> info = temp -> info;
				parent -> left = temp -> right;
				delete temp;
			}
		}
   }
   else  
   {
      if (precedes(item, start -> info))
         removeNode(start -> left, item);
      else
         removeNode(start -> right, item);
   }  
}  
