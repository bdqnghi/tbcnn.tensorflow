/*
	bucket sort

	g++ -W ./01_bucket_sort.cpp -o unit_test

	range m is limited (0 ~ m-1)
*/

#include <iostream>
#include <string.h>

using std::cout;
using std::endl;

void bucket_sort(int *ar, int size, int m)
{
	int *bucket = new int[m];
	memset(bucket, 0, m*sizeof(int));

	for(int i=0; i < size; ++i)
	{
		++bucket[ar[i]];
	}

	/*
		O(mn) ? O(m+n)
	*/
	int j = 0;
	for(int i=0; i<m; ++i)
	{
		while(bucket[i] != 0)
		{
			ar[j] = i;
			bucket[i] -= 1;
			++j;
		}
	}

	delete bucket;
}

void print(int *ar, int size)
{
	for(int i=0; i<size; ++i)
	{
		cout << ar[i] << " ";
	}

	cout << endl;
}

int main(int argc, char const *argv[])
{
	int m = 32;
	int array[10] = {1,2,3,21,4,12,31,2,7,29};

	print(array, 10);

	bucket_sort(array, 10, m);

	print(array, 10);

	return 0;
}


