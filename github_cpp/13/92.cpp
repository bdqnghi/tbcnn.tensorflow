/*******************************************************************
*   File: BubbleSort.cpp										   *
*   Name: James Walker (Ethan)									   *
*   Project: Programming Assignment 4: Sorting					   *
*   Creation Date: 12/06/2013									   *
*   Purpose: CPP file to define bubble sort						   *
*   															   *
*******************************************************************/
#include "BubbleSort.h"

BubbleSort::BubbleSort()
{

}

BubbleSort::~BubbleSort()
{

}

void BubbleSort::printName()
{
	std::cout << "--------------------------------------------------------" << std::endl;
	std::cout << "----------------------BUBBLE SORT-----------------------" << std::endl;
	std::cout << "--------------------------------------------------------" << std::endl;
}


void BubbleSort::sort()
{


	bool sorted = false;
	
	while(!sorted)
	{
	    sorted = true;
		for(int i = 0; i < (NUMRECS-1); i++)
		{
			if(dataArray[i].key > dataArray[i+1].key )
			{
			    sorted = false;
				temp = dataArray[i];
				dataArray[i] = dataArray[i+1];
				dataArray[i+1] = temp;			}
		}
	}
		
}
