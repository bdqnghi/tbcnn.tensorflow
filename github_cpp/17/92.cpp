

#include "btree.h"
#include <iostream>
using namespace std;


bTree::bTree(bool canMerge)
{
   this->root = NULL; 
   this->canMerge = canMerge;
}


bTree::~bTree()
{
   this->root = NULL;
}


bTreeCell* bTree::getRoot()
{
   return(this->root);
}


bTreeCell* bTree::insert(bTreeCell* cell)
{
   bTreeCell* pos = this->root; 
   int cmpValue;                
   bool inserted = false;       

   if(this->root == NULL)
   {
      
      this->root = cell;
      return(cell);
   }

   while(!inserted)
   {
      
      cmpValue = cell->compare(pos);

      if( (cmpValue == 0) && (this->canMerge) )
      {
         
         pos->merge(cell);

          
         freeCell(cell);

         inserted = true;
         return(pos);
      }
      else if(cmpValue < 0)
      {
         
         if(!pos->getLeft())
         {
            
            pos->setLeft(cell);
            inserted = true;
         }

         
         pos = pos->getLeft();
      }
      else 
      {
         
         if(!pos->getRight())
         {
            
            pos->setRight(cell);
            inserted = true;
         }

         
         pos = pos->getRight();
      }
   }

   return(cell);
}


void bTree::remove(bTreeCell* cell)
{
   int cmpValue;
   bTreeCell* father = NULL; 
   bTreeCell* pos = NULL; 

   if(cell)
   {
      
      if(cell == this->root)
      {
         if(cell->getLeft())
         {
            
            this->root = cell->getLeft();
         }
         else
         {
            
            this->root = cell->getRight();
         }

         
         father = NULL;
      }
      else
      {
         
         pos = this->root;
         father = NULL;
         while(pos != cell)
         {
            father = pos;
            cmpValue = cell->compare(pos);

             
            if(cmpValue <= 0)
            {
               pos = pos->getLeft();
            }
            else
            {
               pos = pos->getRight();
            }

            
            if(!pos)
            {
               cerr << "Error: No cell " << cell 
                    << " at tree to remove!" << endl;
               
               freeCell(cell);
               return;
            }
         }
      }

      
      if(cell->getLeft())
      {
         
         if(father)
         {
            cmpValue = cell->compare(father);
            if(cmpValue <= 0)
            {
               father->setLeft(cell->getLeft());
            }
            else
            {
               father->setRight(cell->getLeft());
            }
         }

         
         if(cell->getRight())
         {
            pos = cell->getLeft();
            while(pos->getRight() != NULL)
            {
               pos = pos->getRight();
            }

            
            pos->setRight(cell->getRight());
         }
      }
      else if(cell->getRight())
      {
         
         if(father)
         {
            cmpValue = cell->compare(father);
            if(cmpValue <= 0)
            {
               father->setLeft(cell->getRight());
            }
            else
            {
               father->setRight(cell->getRight());
            }
         }

         
      }
  
      
      freeCell(cell);
   }
}


bTreeCell* bTree::search(bTreeCell* cell)
{
   bTreeCell* pos = this->root;
   int res;

   while(pos != NULL) 
   {
      res = cell->compare(pos);

      if(res == 0)
      {
         
         return(pos);
      }
      else if(res < 0)
      {
         
         pos = pos->getLeft();
      }
      else
      {
         
         pos = pos->getRight();
      }
   }

   return(NULL);
}


void bTree::clearSubTree(bTreeCell* subRoot)
{
   if(subRoot)
   {
      
      this->clearSubTree(subRoot->getLeft());

      
      this->clearSubTree(subRoot->getRight());

      
      freeCell(subRoot);
   }
}


void bTree::mergeTree(bTreeCell* treeRoot)
{
   
   if(treeRoot)
   {
      
      bTreeCell* cell = dupplicateCell(treeRoot);

      
      this->insert(cell);

      
      this->mergeTree(treeRoot->getLeft());

      
      this->mergeTree(treeRoot->getRight());
   }
}

