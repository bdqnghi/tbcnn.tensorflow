

#include "selectionSort.h"
#include <iostream>

namespace _selectionSort
{

selectionSort::selectionSort(int input_size, int* input) :
		data(new int[input_size]), size(input_size)
{
	for (int i = 0; i < input_size; ++i)
	{
		data[i] = input[i];
	}
}

selectionSort::~selectionSort()
{
	delete[] data;
}

void selectionSort::sort()
{
	
	int i = 0;
	while (i < size) {
		int* the_min = this->find_min(i, size - 1);
		
		swap(data + i, the_min);
		i++;
	}
}

int* selectionSort::find_min(int from, int to)
{
	
	int* this_min = data + from;
	for (int i = from; i <= to; ++i) {
		if (*(data + i) < *this_min)
			this_min = data + i;
	}
	return this_min;
}

void selectionSort::swap(int* origin, int* destiny)
{
	int temp = *origin;
	*origin = *destiny;
	*destiny = temp;
}

bool selectionSort::is_ordered()
{
	bool out = true;

	for (int j = 1; j < size; ++j)
	{
		if(data[j] < data[j-1])
		{
			out = false;
			break;
		}
	}
	return  out;
}


void selectionSort::print_data()
{
	for (int j = 0; j < size; ++j)
	{
		std::cout << data[j] << "\t";
	}
	std::cout << std::endl;
}



} 
