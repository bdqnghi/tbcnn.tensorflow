

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


void insertionSort(sort_data sortAry[], int n)
{
   int iter = 0;
   int j = 0;
   sort_data swap;

   
   for (int i = 0; i < n; i++)
   {
      j = i;
      
      while (j > 0 && sortAry[j].key < sortAry[j - 1].key)
      {
         swap = sortAry[j - 1];
         sortAry[j - 1] = sortAry[j];
         sortAry[j] = swap;

         j = j - 1;

         iter++;
      }
   }

   cout << "Insertion Sort Iterations: " << iter << endl;
}