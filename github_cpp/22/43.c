
































#include <iostream>

int _pow(int x, int n)
{
	if (n == 0)
	{
		return 1;
	}
	return x * _pow(x, n - 1);
}
void swap(int & a, int & b)
{
	int temp = a;
	a = b;
	b = temp;
}

int main()
{
	using namespace std;
	int data_array[8] = { 512,111,55,88,91,3,40,5 };

	int temp_data[8];

	int max = 0;
	for (int i = 0; i < 8; ++i)
	{
		if (data_array[i] > max)
		{
			max = data_array[i];
		}
	}
	int curr_max = max;
	int radix_count = 0;
	if (curr_max / 10 == 0) { radix_count = 1; }
	while (curr_max != 1 && curr_max != 0)
	{	
		curr_max /= 10;
		radix_count++;
	}
	
	
	
	

	
	int bucket[10];
	for (int i = 0; i < radix_count; ++i)
	{
		int j, k;
		for (auto & a : bucket)
		{
			a = 0;
		}
		for (j = 0; j < 8; ++j)
		{
			k = (data_array[j] / _pow(10, i)) % 10;
			bucket[k]++;
		}
		for (j = 1; j < 10; ++j)
		{                       
			bucket[j] += bucket[j - 1];
		}
		for (j = 7; j >= 0; --j)
		{
			k = (data_array[j] / _pow(10, i)) % 10;
			temp_data[bucket[k] - 1] = data_array[j];
			bucket[k]--;
		}
		for (j = 0; j < 8; ++j)
		{
			data_array[j] = temp_data[j];
		}
	}

	for (int i = 0; i < 8; ++i)
	{
		cout << data_array[i] << endl;
	}
	return 0;
}

