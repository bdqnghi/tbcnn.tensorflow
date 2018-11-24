#include <iostream>

int partition(int* int_array, int idx_first, int idx_last)
{
	int idx_left = idx_first;
	int idx_right = idx_last;
	int mid_point = (idx_left + idx_right) / 2;
	int pivot = int_array[mid_point];
	while(idx_left <= idx_right)
	{
		while(int_array[idx_left] < pivot)
		{
			++idx_left;
		}

		while(int_array[idx_right] > pivot)
		{
			--idx_right;
		}

		if(idx_left <= idx_right)
		{
			int temp = int_array[idx_left];
			int_array[idx_left] = int_array[idx_right];
			int_array[idx_right] = temp;
			++idx_left;
			--idx_right;
		}
	}

	return idx_left;
}

void quick_sort(int* int_array, int idx_first, int idx_last)
{
	int pivot_position = partition(int_array, idx_first, idx_last);

	if(idx_first < pivot_position - 1)
	{
		quick_sort(int_array, idx_first, pivot_position - 1);
	}

	if(idx_last > pivot_position)
	{
		quick_sort(int_array, pivot_position, idx_last);
	}
}

int main()
{
	std::cout << "Quick Sort" << std::endl;
	std::cout << "Enter size of array: " << std::endl;
	int array_size = 0;
	std::cin >> array_size;
	if(array_size <= 0)
	{
		std::cout << "Invalid array size. array_size = " << array_size << std::endl;
		return 0;
	}

	int* int_array = new int[array_size];
	std::cout << "Enter unsorted array: " << std::endl;
	for(int arr_idx = 0; arr_idx < array_size; ++arr_idx)
	{
		std::cin >> int_array[arr_idx];
	}

	quick_sort(int_array, 0, array_size - 1);

	std::cout << "Sorted array: " << std::endl;
	for(int arr_idx = 0; arr_idx < array_size; ++arr_idx)
	{
		std::cout << int_array[arr_idx] << " ";
	}

	std::cout << std::endl;

	return 0;
}