/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			Insertion.cpp
* Date Created:		4/15/2014	
* Modifications:	
*
************************************************************/
#include "Insertion.h"

void InsertionSort(int m_array[], int m_length)
{
	for (int i = 1; i < m_length; i++)
	{
		int temp = m_array[i];
		int j;

		for (j = i; (j > 0) && temp < m_array[j - 1]; j--)
		{
			m_array[j] = m_array[j - 1];
		}

		m_array[j] = temp;
	}
}

void InsertionSort(Array<int> & m_array)
{
	int m_length = m_array.getLength();

	for (int i = 1; i < m_length; i++)
	{
		int temp = m_array[i];
		int j;

		for (j = i; (j > 0) && temp < m_array[j - 1]; j--)
		{
			m_array[j] = m_array[j - 1];
		}

		m_array[j] = temp;
	}
}

void InsertionSort(vector<int> & m_array)
{
	int m_length = m_array.size();

	for (int i = 1; i < m_length; i++)
	{
		int temp = m_array[i];
		int j;

		for (j = i; (j > 0) && temp < m_array[j - 1]; j--)
		{
			m_array[j] = m_array[j - 1];
		}

		m_array[j] = temp;
	}
}