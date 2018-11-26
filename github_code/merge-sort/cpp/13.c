/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			MergeSort.cpp
* Date Created:		4/19/2014
* Modifications:	
*
************************************************************/
#include "MergeSort.h"

void Merge(int m_array[], int temp_array[], int left, int right, int l_right)
{
	int l_left = right - 1;
	int temp_left = left;
	int temp_pos = left;
	int num_of_elements = l_right - left + 1;

	while (temp_left <= l_left && right <= l_right)
	{
		if (m_array[temp_left] <= m_array[right])
		{
			temp_array[temp_pos] = m_array[temp_left];
			temp_left++;
		}
		else 
		{
			temp_array[temp_pos] = m_array[right];
			right++;
		}
		temp_pos++;
	}

	if(temp_left > l_left)
    {
        for(; right <= l_right; right++)
        {
            temp_array[temp_pos] = m_array[right];
            temp_pos++;
        }
    }
    else
    {
        for(; temp_left <= l_left; temp_left++)
        {
            temp_array[temp_pos] = m_array[temp_left];
            temp_pos++;
        }
    }
    for(; left <= l_right; left++) 
	{
		m_array[left] = temp_array[left];
	}
}

void MergeSort(int m_array[], int temp_array[], int left, int right)
{
	int mid; 

	if (left < right)
	{
		mid = (left + right) / 2;

		MergeSort(m_array, temp_array, left, mid);
		MergeSort(m_array, temp_array, mid + 1, right);
		Merge(m_array, temp_array, left, mid + 1, right);
	}
}

void MergeSort(int m_array[], int array_size)
{
	int * temp_array = new int[array_size];

	MergeSort(m_array, temp_array, 0, array_size - 1);

	delete [] temp_array;
}

void Merge(Array<int> & m_array, Array<int> & temp_array, int left, int right, int l_right)
{
	int l_left = right - 1;
	int temp_left = left;
	int temp_pos = left;
	int num_of_elements = l_right - left + 1;

	while (temp_left <= l_left && right <= l_right)
	{
		if (m_array[temp_left] <= m_array[right])
		{
			temp_array[temp_pos] = m_array[temp_left];
			temp_left++;
		}
		else 
		{
			temp_array[temp_pos] = m_array[right];
			right++;
		}
		temp_pos++;
	}

	if(temp_left > l_left)
    {
        for(; right <= l_right; right++)
        {
            temp_array[temp_pos] = m_array[right];
            temp_pos++;
        }
    }
    else
    {
        for(; temp_left <= l_left; temp_left++)
        {
            temp_array[temp_pos] = m_array[temp_left];
            temp_pos++;
        }
    }
    for(; left <= l_right; left++) 
	{
		m_array[left] = temp_array[left];
	}
}

void MergeSort(Array<int> & m_array, Array<int> & temp_array, int left, int right)
{
	int mid; 

	if (left < right)
	{
		mid = (left + right) / 2;

		MergeSort(m_array, temp_array, left, mid);
		MergeSort(m_array, temp_array, mid + 1, right);
		Merge(m_array, temp_array, left, mid + 1, right);
	}
}

void MergeSort(Array<int> & m_array, int array_size)
{
	Array<int> temp_array(array_size);

	MergeSort(m_array, temp_array, 0, array_size - 1);
}

void Merge(vector<int> & m_array, vector<int> & temp_array, int left, int right, int l_right)
{
	int l_left = right - 1;
	int temp_left = left;
	int temp_pos = left;
	int num_of_elements = l_right - left + 1;

	while (temp_left <= l_left && right <= l_right)
	{
		if (m_array[temp_left] <= m_array[right])
		{
			temp_array[temp_pos] = m_array[temp_left];
			temp_left++;
		}
		else 
		{
			temp_array[temp_pos] = m_array[right];
			right++;
		}
		temp_pos++;
	}

	if(temp_left > l_left)
    {
        for(; right <= l_right; right++)
        {
            temp_array[temp_pos] = m_array[right];
            temp_pos++;
        }
    }
    else
    {
        for(; temp_left <= l_left; temp_left++)
        {
            temp_array[temp_pos] = m_array[temp_left];
            temp_pos++;
        }
    }
    for(; left <= l_right; left++) 
	{
		m_array[left] = temp_array[left];
	}
}

void MergeSort(vector<int> & m_array, vector<int> & temp_array, int left, int right)
{
	int mid; 

	if (left < right)
	{
		mid = (left + right) / 2;

		MergeSort(m_array, temp_array, left, mid);
		MergeSort(m_array, temp_array, mid + 1, right);
		Merge(m_array, temp_array, left, mid + 1, right);
	}
}

void MergeSort(vector<int> & m_array, int array_size)
{
	vector<int> temp_array(array_size);

	MergeSort(m_array, temp_array, 0, array_size - 1);
}