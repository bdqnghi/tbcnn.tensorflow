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

//function that implements the bubble sort algorithm
void bubbleSort(sort_data sortAry[], int n)
{
   int iter = 0;
   sort_data swap;

   //i is the furthest out number that is not known to be the biggest
   //once the biggest value is found from 0 to i it resets and i moves down 1
   for (int i = n ; i > 1; i--)
   {
      //bubbles the bigger values to the top where i is
      for (int j = 0; j < (i - 1); j++)
      {
         if (sortAry[j].key > sortAry[j + 1].key)
         {
            swap = sortAry[j + 1];
            sortAry[j + 1] = sortAry[j];
            sortAry[j] = swap;
         }
         iter++;
      }
   }

   cout << "Bubble Sort Iterations: " << iter << endl;
}