/*******************************************************************
*   File: RadixSort.cpp											   *
*   Name: James Walker (Ethan)									   *
*   Project: Programming Assignment 4: Sorting					   *
*   Creation Date: 12/06/2013									   *
*   Purpose: CPP file to define radix sort						   *
*   															   *
*******************************************************************/
#include "RadixSort.h"
#include <cmath>

RadixSort::RadixSort()
{

}

RadixSort::~RadixSort()
{

}

void RadixSort::printName()
{
	std::cout << "\n--------------------------------------------------------" << std::endl;
	std::cout << "------------------------RADIX SORT----------------------" << std::endl;
	std::cout << "--------------------------------------------------------" << std::endl;
}

void RadixSort::sort()
{

	
	int index = 1;
	for (int i = 0; i < 5; i++)
	{
		populateHitList(index);
		populateProxArray();
		populateLocalArray(index);

		index *= 10;
	}
}

void RadixSort::populateHitList(int powerOf10)
{
	for (int i = 0; i < 10; i++)
	{
		hitList[i] = 0;
	}

	int digit;
	int powerOf10times10 = 10 * powerOf10;
	for (int i = 0; i < size; i++)
	{
		digit = dataArray[i].key%powerOf10times10 / powerOf10;
		hitList[digit]++;
	}

}

void RadixSort::populateProxArray()
{
	proxArray[0] = 0;

	for (int i = 1; i < RADIX; i++)
	{
		proxArray[i] = proxArray[i - 1] + hitList[i - 1];
	}
}

void RadixSort::populateLocalArray(int powerOf10)
{
	int digit;
	int powerOf10times10 = 10 * powerOf10;
	for (int i = 0; i < size; i++)
	{
		int digit = dataArray[i].key%powerOf10times10 / powerOf10;
		localArray[proxArray[digit]] = dataArray[i];
		proxArray[digit]++;
	}

	for (int i = 0; i < size; i++)
	{
		dataArray[i] = localArray[i];
	}
		
}