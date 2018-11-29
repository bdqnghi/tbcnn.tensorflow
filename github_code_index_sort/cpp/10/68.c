// BucketSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <assert.h>

using namespace std;

int FindMostDigits(const vector<unsigned int>& numbers)
{
	int most = 0;
	for (unsigned int num : numbers)
	{
		int digits = 0;
		while (num > 0)
		{
			num >>= 1;
			++digits;
		}
		if (digits > most) most = digits;
	}

	return most;
}

vector<unsigned int> BucketSortInternal(const vector<unsigned int>& numbers, int digits)
{
	vector<unsigned int> buckets[10];

	assert(digits > 0);

	unsigned int mod = 1 << (digits - 1);
	for (unsigned int number : numbers)
	{
		int bucket = number % mod;
		buckets[bucket].push_back(number);
	}

	for (int i = 0; i <= 9; ++i)
	{
		buckets[i] = BucketSortInternal(buckets[i], digits - 1);
	}

	vector<unsigned int> merged;
	for (int i = 9; i >= 0; --i)
	{
		merged.insert(merged.end(), buckets[i].begin(), buckets[i].end());
	}

	return merged;
}

// from most significant to least significant
vector<unsigned int> BucketSort(const vector<unsigned int>& numbers)
{
	vector<unsigned int> result;
	vector<unsigned int> buckets[10];

	int n = FindMostDigits(numbers);

	return BucketSortInternal(numbers, n);
}

int main()
{
    return 0;
}

