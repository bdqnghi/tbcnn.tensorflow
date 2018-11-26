/*****************************************************************************
Taylor Hoss
X432Z869
Program #10

This is a program that implements four sorting algoritms and a binary search
tree. It will generate data sets of 100, 500, and 1000 via arrays using a
datatype that holds a key to be sorted by and a value that acts as a
placeholder for data. As each sort goes through each data set it tells how
many iterations it went through to get to the sorted list. Also when
the data is added to the binary search tree and later transversed in-order
it gives iteration counts as well. All of these iteration counts can be
compared to the Big-O worst-case calculations.

*****************************************************************************/

#ifndef IOSTREAM
#define IOSTREAM

#include <iostream>

#endif //IOSTREAM

#ifndef SORT_DATA_CPP
#define SORT_DATA_CPP

#include "sort_data.cpp"

#endif //SORT_DATA_CPP

#ifndef FSTREAM
#define FSTREAM

#include <fstream>

#endif //FSTREAM

#ifndef STRING
#define STRING

#include <string>

#endif //STRING

#ifndef NAMESPACE_STD
#define NAMESPACE_STD

using namespace std;

#endif //NAMESPACE_STD

//function that implements the quick sort algorithm
int quickSort(sort_data sortAry[], int left, int right, int iter)
{
   int i = left, j = right, mid = ( ( left + right ) / 2 );
   sort_data swap;
   
   //finding pivot
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

   //partioning set
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

   //recursively calling for partitions of partitions
   if (left < j)
      iter = quickSort(sortAry, left, j, iter);
   if (i < right)
      iter = quickSort(sortAry, i, right, iter);

   return iter;
}