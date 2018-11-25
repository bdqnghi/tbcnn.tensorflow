




#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include "data.cpp"
#include "additionalFuncs.cpp"

using namespace std;

#ifndef INSERTION_CPP_
#define INSERTION_CPP_





void insertionSort(Data list[], int size)
{

	int walker;
	int count = 0;
	Data temp[size];

	
	for(int i = 0; i < size; i ++)
		temp[i] = list[i];

	for(int i = 1; i < size; i++)
	{
		walker = i;
		while((walker > 0) && (temp[walker - 1].key > temp[walker].key))
		{
         count++;

         	
			swapData(temp[walker], temp[walker - 1]);
         
			walker--;
		}
	}

	outputData(temp, size, count, 'i');

}

#endif 
