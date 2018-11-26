
#include "stdafx.h"
#include "mergesort.h"
using namespace std;

void
MergeSort::Sort(deque<int> & dInt)
{
	deque<int> dEmpty;
	Merge(dInt, dEmpty);
}
deque<int>  
MergeSort::Merge(deque<int> & dIntLeft, deque<int> & dIntRight)
{
	if (dIntLeft.size() > 1)
	{
		deque<int> dTempLeft;
		deque<int> dTempRight;
		for (int i = 0; i < dIntLeft.size() && dIntLeft.size() > 0; i++)
		{
			if (i < dIntLeft.size() / 2)
				dTempLeft.push_back(dIntLeft[i]);
			else
				dTempRight.push_back(dIntLeft[i]);
		}
		dIntLeft = Merge(dTempLeft, dTempRight);
	}
	if (dIntRight.size() > 1)
	{
		deque<int> dTempLeft;
		deque<int> dTempRight;
		for (int i = 0; i < dIntRight.size() && dIntRight.size() > 0; i++)
		{
			if (i < dIntRight.size() / 2)
				dTempLeft.push_back(dIntRight[i]);
			else
				dTempRight.push_back(dIntRight[i]);
		}
		dIntRight = Merge(dTempLeft, dTempRight);
	}
	deque<int>::iterator itLeft = dIntLeft.begin();
	deque<int>::iterator itRight = dIntRight.begin();

	deque<int> dMerged;
	while (itLeft != dIntLeft.end() || itRight != dIntRight.end())
	{
		if (itLeft != dIntLeft.end() && (itRight == dIntRight.end() || *itLeft <= /*If we get two numbers that are the same*/ *itRight) ) //shortcut here so wwe don't dereference the end()
		{
			dMerged.push_back(*itLeft);
			itLeft++;
		}
		else if (itRight != dIntRight.end() && (itLeft == dIntLeft.end() || *itRight < *itLeft)) //same
		{
			dMerged.push_back(*itRight);
			itRight++;
		}
	}
	return dMerged;

}