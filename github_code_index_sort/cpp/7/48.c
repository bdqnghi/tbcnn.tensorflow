/************************************************
 *
 *  Program: shell.cpp
 *
 *  Author: Brother Cameron
 *
 *  Purpose: Implements the shell sort.
 *
 ************************************************/
#include <iostream.h>

void shellsort(int x[], int n)
{
  int span = 1;
  int temp = 0;
  int counter = 0;
  int i,j;

  //--- compute first increment
  while (span < n)
    span = 3*span + 1;
  // --- do shell sort
  do
  {
    span = span/3;
    cout << span << endl;
    for (i = span-1; i < n; ++i)
    {
      // --- insertion sort on span
      temp = x[i];
      for (j = i; j >= span && x[j-span] > temp; j -= span)
	x[j] = x[j-span];
      x[j] = temp;
    }
  } while(span > 0);
}
