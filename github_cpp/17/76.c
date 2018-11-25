

#include "TableB.h"  

Table::Table()
{
	BinarySearchTree bst;
}

void Table::tableInsert(const TableItemType& newItem)
   throw(TableException)
{
   try
   {
      bst.searchTreeInsert(newItem);
      ++size;
   }  
   catch (TreeException e)
   {  throw TableException(
      "TableException: tableInsert cannot allocate memory");
   }  
}  

void Table::tableDelete(KeyType searchKey)
   throw(TableException)
{
   try
   {  bst.searchTreeDelete(searchKey);
   }  
   catch (TreeException e)
   {  throw TableException("TableException: Item not found on delete");
   }  
}  

void Table::tableRetrieve(KeyType searchKey, TableItemType& tableItem) const
   throw(TableException)
{
   try
   {  bst.searchTreeRetrieve(searchKey, tableItem);
   }  
   catch (TreeException e)
   {  throw TableException("TableException: Item not found on retrieve");
   }  
}  

void Table::tableRetrieveCount(KeyType searchKey,TableItemCount& tableItemCount) const
   throw(TableException)
{
   try
   {  bst.searchTreeRetrieveCount(searchKey, tableItemCount);
   }  
   catch (TreeException e)
   {  throw TableException("TableException: Item not found on retrieve");
   }  
}  

bool Table::tableIsItemInTable(KeyType searchKey)
{
	return(bst.searchTreeIsItemInTree(searchKey));
}
