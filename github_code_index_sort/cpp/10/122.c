#include "BucketSort.h"
#include <iostream>
#include <cassert>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

BucketSort::BucketSort()
{

}

BucketSort::BucketSort(float * initArr, int initLen)
{
	len = initLen;
	arr = new(nothrow) float[len];
	assert(arr != nullptr);
	for (int i = 0; i < len; i++)
	{
		*(arr + i) = *(initArr + i);
	}
}

BucketSort::~BucketSort()
{
	delete[] arr;
	arr = nullptr;
}

void BucketSort::sort()
{
	map<int, vector<float> > bucket;
	for (size_t i = 0; i < len; i++)
	{
		int pos = (int)(arr[i] * 10) % 10;
		bucket[pos].push_back(arr[i]);
	}

	int sum = 0;
	map<int, vector<float> >::iterator itr = bucket.begin();
	for (; itr != bucket.end(); itr++)
	{
		std::sort((itr->second).begin(), (itr->second).end());

		int sz = (itr->second).size();
		for (size_t j = 0; j < sz; j++)
		{
			arr[sum + j] = (itr->second)[j];
		}
		sum += sz;
	}

}

void BucketSort::show()
{
	cout << "************************ Show Datas ************************" << endl;
	for (int i = 0; i < len; i++)
	{
		cout << *(arr + i) << " ";
	}
	cout << endl;
	cout << "*************************** End ****************************" << endl;
}

bool BucketSort::isSorted()
{
	bool ret = true;
	for (int i = 1; i < len; i++)
	{
		if (arr[i] < arr[i - 1])
		{
			ret = false;
			break;
		}
	}
	return ret;
}
