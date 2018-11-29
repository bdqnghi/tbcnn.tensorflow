#pragma once
#include "stdafx.h"
#include <vector>
#include <iterator>
using namespace std;
 
//post: the two elements are swapped
//for use with the bubbleSort function :D
//modified from code from https://www.geeksforgeeks.org/bubble-sort/
void swap(double *xp, double *yp)
{
	double temp = *xp;
	*xp = *yp;
	*yp = temp;
}

//pre: vector is unsorted
//post: vector is sorted
//code from https://www.geeksforgeeks.org/bubble-sort/ used and modified for this part
void bubbleSort(vector<double> & number)
{ 
	vector<double>::iterator i, j;
	for (i = number.begin(); i != number.end(); i++)
	{
		for (j = number.begin(); j != number.end(); j++)
		{
			if (next(j, 1) != number.end())
			{ 
				if (*j > *next(j, 1))
				{
					swap(*j, *next(j, 1));
				}
			}
		}
	}
}

/*
// A function to implement bubble sort 
void bubbleSort(int arr[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
  
       // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
} 
  */