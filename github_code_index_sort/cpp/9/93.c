/*
 * selection.cpp
 *
 *  Created on: Dec 4, 2011
 *      Author: alexzhang
 */
#include <iostream>
#include <vector>
#include "rstream.h"
#include "selection.h"
#include <math.h>
#include <cstdlib>
#include <cstring>
using namespace std;
// SELECTION SORT
int selectionSort(vector <int> &arr)
{
    int tmp;
    int min;
    int count=0;
    for(unsigned int i=0;i<arr.size();i++)
    {
       min = i;
       for(int x=i; x<arr.size(); x++)
       {
		   count++;
    	   if(arr[x] < arr[min])
    	   {
    		   min = x;
    	   }
       }
       count++;
       tmp = arr[i];
       arr[i] = arr[min];
       arr[min] = tmp;
     }
     cout<<endl<<"There're "<<count<< " operations on this sort\n";
     return count;
}

