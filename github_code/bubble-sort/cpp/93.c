/*
 * bubble.cpp
 *
 *  Created on: Dec 4, 2011
 *      Author: alexzhang
 */
#include <iostream>
#include <vector>
#include "rstream.h"
#include "bubble.h"
#include <math.h>
#include <cstdlib>
#include <cstring>
using namespace std;

// BUBBLE SORT
int bubbleSort(vector <int> &arr)
{
   int tmp;
   int count=0;
   for(long i=0;i<arr.size();i++)
   {
      for(long x=0; x<arr.size()-1-i; x++)
      {
     	 count++;
         if(arr[x] > arr[x+1])
         {
        	 //r.push_back(rnd);
        	 tmp = arr[x];
        	 arr[x] = arr[x+1];
        	 arr[x+1] = tmp;
         }
      }
   }
   cout<<endl<<"\n\n\n There're "<<count<< " operations on this sort\n\n\n";
   //system("PAUSE");
   return  count;
}
