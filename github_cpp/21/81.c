




#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include "data.cpp"
#include "additionalFuncs.cpp"

using namespace std;

#ifndef SELECTION_CPP_
#define SELECTION_CPP_





void selectionSort(Data list[], int size)
{
	int min, count;
	count = 0;

	Data temp[size];

	
	for (int i = 0; i < size; i++)
		temp[i] = list[i];
      
	
	for (int i = 0; i < size - 1; i++)
	{
		min = i;
	
		for (int j = i + 1; j < size; j++)
		{
			
			if (temp[j].key < temp[min].key)
				min = j;

			count++;
		}
      
		
		if (min != i)
			swapData(temp[i], temp[min]);
	}

	outputData(temp, size, count, 's');
}

#endif 
