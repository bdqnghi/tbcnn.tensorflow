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

//function that implements the selection sort algorithm
void selectionSort(sort_data sortAry[], int n)
{
   int iter = 0;
   int smallest = 0;
   sort_data swap;

   //i is at smallest known value and then increments when j is done walking
   for (int i = 0; i < n - 1; i++)
   {
      smallest = i;
      //j walks through all values trying to find smaller than smallest value
      for (int j = i + 1; j < n; j++)
      {
         if (sortAry[smallest].key > sortAry[j].key)
         {
            smallest = j;
         }

         iter++;
      }
      //put smallest element in ith position
      swap = sortAry[smallest];
      sortAry[smallest] = sortAry[i];
      sortAry[i] = swap;
   }

   cout << "Selection Sort Iterations: " << iter << endl;
}