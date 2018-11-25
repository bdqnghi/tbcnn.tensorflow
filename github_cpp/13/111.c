

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


void bubbleSort(sort_data sortAry[], int n)
{
   int iter = 0;
   sort_data swap;

   
   
   for (int i = n ; i > 1; i--)
   {
      
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