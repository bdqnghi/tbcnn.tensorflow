/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			Insertion.h
* Date Created:		4/15/2014	
* Modifications:	4/19/2014 - moved implementation to 
*								Insertion.cpp
*					4/20/2014 - added documentation
*
************************************************************/
#ifndef INSERTION_H_
#define INSERTION_H_

#include <vector>
#include "Array.h"

/**********************************************************************	
* Purpose: Performs the insertion sort on the given c-array
*
* Entry: m_array is the array to be sorted, m_length is the size of 
*			the array
*
* Exit: No values are returned, m_array is sorted
*
************************************************************************/
void InsertionSort(int m_array[], int m_length);
/**********************************************************************	
* Purpose: Performs the insertion sort on the given Array
*
* Entry: m_array is the array to be sorted
*
* Exit: No values are returned, m_array is sorted
*
************************************************************************/
void InsertionSort(Array<int> & m_array);
/**********************************************************************	
* Purpose: Performs the insertion sort on the given vector
*
* Entry: m_array is the vector to be sorted
*
* Exit: No values are returned, m_array is sorted
*
************************************************************************/
void InsertionSort(vector<int> & m_array);

#endif