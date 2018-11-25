
#include <assert.h>
#include <time.h>

#include <algorithm>
#include <iostream>
#include <vector>
void shell_sort(int array[], int len)
{
	for (int span = len / 2; span > 0; span /= 2)
	{
		for (int collection_num = 0; collection_num < span; collection_num ++)
		{
			for (int collection_cursor = collection_num; collection_cursor < len; collection_cursor += span)
			{
				int i = collection_cursor - span;
				for (; i >= 0 && array[i] > array[i + span]; i -= span)
				{
					int key = array[i + span];
					array[i + span] = array[i];
					array[i] = key;
				}
			}
		}
	}
}

int main()
{
	srand(time(NULL));
	const int ARRAY_LEN = 1000;
	const int INT_RANGE = 100000;
	int *array = new int[ARRAY_LEN];
	for (int i = 0; i < ARRAY_LEN; i ++) {
		array[i] = rand() % INT_RANGE;
	}

	
	std::vector<int> v(array, array + ARRAY_LEN);
	std::sort(v.begin(), v.end());

	
	shell_sort(array, ARRAY_LEN);

	
	for (int i = 0; i < ARRAY_LEN; i ++)
	{
		
		assert(v[i] == array[i]);
	}
}
