




#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include "data.cpp"
#include "additionalFuncs.cpp"

using namespace std;

#ifndef BUBBLE_CPP_
#define BUBBLE_CPP_


void bubbleSort(Data list[], int size)
{

	Data temp[size];
   
	
	for(int i = 0; i < size; i ++)
		temp[i] = list[i];

	int walker, count;
	count = 0;

	
	bool sorted = false;
	
	
	for(int i = 0; (i < size) && (sorted == false); i++)
	{
		sorted = true;

		
		
		for(walker = size - 1; walker > i; walker--)
		{
			if(temp[walker].key < temp[walker - 1].key)
			{
				swapData(temp[walker], temp[walker - 1]);
				sorted = false;
			}

	         count++;
		}
	}	

	outputData(temp, size, count, 'b');
}

#endif 
