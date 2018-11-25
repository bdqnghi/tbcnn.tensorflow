

#ifndef IOSTREAM
#define IOSTREAM

#include <iostream>

#endif 

#ifndef SORT_DATA_CPP
#define SORT_DATA_CPP

#include "sort_data.cpp"

#endif 

#ifndef FSTREAM
#define FSTREAM

#include <fstream>

#endif 

#ifndef STRING
#define STRING

#include <string>

#endif 

#ifndef NAMESPACE_STD
#define NAMESPACE_STD

using namespace std;

#endif 


int quickSort(sort_data sortAry[], int left, int right, int iter)
{
   int i = left, j = right, mid = ( ( left + right ) / 2 );
   sort_data swap;
   
   
   if (sortAry[left].key > sortAry[mid].key)
   {
      swap = sortAry[mid];
      sortAry[mid] = sortAry[left];
      sortAry[left] = swap;
   }

   if (sortAry[left].key > sortAry[right].key)
   {
      swap = sortAry[right];
      sortAry[right] = sortAry[left];
      sortAry[left] = swap;
   }

   if (sortAry[mid].key > sortAry[right].key)
   {
      swap = sortAry[right];
      sortAry[right] = sortAry[mid];
      sortAry[mid] = swap;
   }

   int pivot = sortAry[mid].key;

   
   while (i <= j)
   {
      while (sortAry[i].key < pivot)
      {
         i++;
      }
      while (sortAry[j].key > pivot)
      {
         j--;
      }
    
      if (i <= j)
      {
         swap = sortAry[i];
         sortAry[i] = sortAry[j];
         sortAry[j] = swap;

         i++;
         j--;
      }

      iter++;
   }

   
   if (left < j)
      iter = quickSort(sortAry, left, j, iter);
   if (i < right)
      iter = quickSort(sortAry, i, right, iter);

   return iter;
}