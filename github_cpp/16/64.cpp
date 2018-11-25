/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			Shell.h
* Date Created:		4/10/2014	
* Modifications:	4/19/2014 - moved implementation to 
*								Shell.cpp
*					4/20/2014 - added documentation
*
************************************************************/
#ifndef SHELLSORT_H_
#define SHELLSORT_H_

#include <vector>
#include "Array.h"

/**********************************************************************	
* Purpose: Calculates the gap to be used within the insertion sort
*
* Entry: int i is the current gap number which is used to find the 
*			size of the gap
*
* Exit: int h is returned, the size of the current gap
*
************************************************************************/
int Increments (int i);
/**********************************************************************	
* Purpose: Performs the shell sort on the given c-array
*
* Entry: m_array is the array to be sorted, m_length is the size of 
*			the array
*
* Exit: No values are returned, m_array is sorted
*
************************************************************************/
void ShellSort(int m_array[], int m_length);
/**********************************************************************	
* Purpose: Performs the selection sort on the given Array
*
* Entry: m_array is the array to be sorted, m_length is the size of 
*			the array
*
* Exit: No values are returned, m_array is sorted
*
************************************************************************/
void ShellSort(Array<int> & m_array, int m_length);
/**********************************************************************	
* Purpose: Performs the selection sort on the given vector
*
* Entry: m_array is the vector to be sorted, m_length is the size of 
*			the array
*
* Exit: No values are returned, m_array is sorted
*
************************************************************************/
void ShellSort(vector<int> & m_array, int m_length);

#endif