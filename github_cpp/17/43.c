

#include "TableB.h"  

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

void Table::tableRetrieve(KeyType searchKey,
                          TableItemType& tableItem) const
   throw(TableException)
{
   try
   {  bst.searchTreeRetrieve(searchKey, tableItem);
   }  
   catch (TreeException e)
   {  throw TableException("TableException: Item not found on retrieve");
   }  
}  

void Table::traverseTable(FunctionType visit)
{
   bst.inorderTraverse(visit);
}  

