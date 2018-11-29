#include "stdafx.h"
#include "BucketSort.h"
#include <iostream>

int main2()
{
	std::vector<int> data = { 23, 24, 22, 21, 26, 25, 27, 28, 21, 21 };

	BucketSort *m = new BucketSort(data, 20, 30);
	m->sort();
	for (int i = 0; i < data.size(); i++)
	{
		std::cout << data[i] << " ";
	}
	return 0;
}

BucketSort::BucketSort(std::vector<int> &arr, int lowerRange, int upperRange):
	data(arr)
{
	range = upperRange - lowerRange;
	this->lowerRange = lowerRange;
}

void BucketSort::sort()
{
	int i, j;
	int size = data.size();
	std::vector<int> count(range);

	for (i = 0; i < range; i++)
		count[i] = 0;

	for (i = 0; i < size; i++)
		count[data[i] - lowerRange]++;

	j = 0;

	for (i = 0; i < range; i++)
	{
		for (; count[i] > 0; count[i]--)
			data[j++] = i + lowerRange;
	}
}