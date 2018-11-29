/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			Shell.cpp
* Date Created:		4/20/2014	
* Modifications:	
*
************************************************************/

#include "Shell.h"

int Increments (int i)
{
	int h = 1;
	for (; i > 0; i--)
		h = 3 * h + 1;

	return h;
}

void ShellSort(int m_array[], int m_length)
{
	int tmp;
	int k;
	int h = 1;
	int i = 0;

	for (; h < m_length; i++)
	{
		h = 3 * h + 1;
	}
	h = 1;

	for (; i >= 0; i--)
	{
		h = Increments(i);

		for (int hCnt = h; hCnt < 2 * h; hCnt++)
		{
			for (int j = hCnt; j < m_length;)
			{
				tmp = m_array[j];
				k = j;

				while ((k - h >= 0) && (tmp < m_array[k - h]))
				{
					m_array[k] = m_array[k - h];
					k = k - h;
				}

				m_array[k] = tmp;
				j = j + h;
			}
		}
	}
}

void ShellSort(Array<int> & m_array, int m_length)
{
	int tmp;
	int k;
	int h = 1;
	int i = 0;

	for (; h < m_length; i++)
	{
		h = 3 * h + 1;
	}
	h = 1;

	for (; i >= 0; i--)
	{
		h = Increments(i);

		for (int hCnt = h; hCnt < 2 * h; hCnt++)
		{
			for (int j = hCnt; j < m_length;)
			{
				tmp = m_array[j];
				k = j;

				while ((k - h >= 0) && (tmp < m_array[k - h]))
				{
					m_array[k] = m_array[k - h];
					k = k - h;
				}

				m_array[k] = tmp;
				j = j + h;
			}
		}
	}
}

void ShellSort(vector<int> & m_array, int m_length)
{
	int tmp;
	int k;
	int h = 1;
	int i = 0;

	for (; h < m_length; i++)
	{
		h = 3 * h + 1;
	}
	h = 1;

	for (; i >= 0; i--)
	{
		h = Increments(i);

		for (int hCnt = h; hCnt < 2 * h; hCnt++)
		{
			for (int j = hCnt; j < m_length;)
			{
				tmp = m_array[j];
				k = j;

				while ((k - h >= 0) && (tmp < m_array[k - h]))
				{
					m_array[k] = m_array[k - h];
					k = k - h;
				}

				m_array[k] = tmp;
				j = j + h;
			}
		}
	}
}