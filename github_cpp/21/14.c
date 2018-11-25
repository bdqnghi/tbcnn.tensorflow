

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


void selectionSort(sort_data sortAry[], int n)
{
   int iter = 0;
   int smallest = 0;
   sort_data swap;

   
   for (int i = 0; i < n - 1; i++)
   {
      smallest = i;
      
      for (int j = i + 1; j < n; j++)
      {
         if (sortAry[smallest].key > sortAry[j].key)
         {
            smallest = j;
         }

         iter++;
      }
      
      swap = sortAry[smallest];
      sortAry[smallest] = sortAry[i];
      sortAry[i] = swap;
   }

   cout << "Selection Sort Iterations: " << iter << endl;
}