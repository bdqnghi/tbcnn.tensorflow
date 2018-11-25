
#include <iostream>
#include <vector>
#include "rstream.h"
#include "bubble.h"
#include <math.h>
#include <cstdlib>
#include <cstring>
using namespace std;


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
        	 
        	 tmp = arr[x];
        	 arr[x] = arr[x+1];
        	 arr[x+1] = tmp;
         }
      }
   }
   cout<<endl<<"\n\n\n There're "<<count<< " operations on this sort\n\n\n";
   
   return  count;
}
