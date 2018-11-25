#include <iostream>
#include <ctime>

int* generateArray(int n)
{
	int* arr = new int[n];
	srand(time(0));

	for (int i = 0; i < n; i++)
		arr[i] = rand() % 100;

	return arr;
}

void printArray(int* arr, int n)
{
	for (int i = 0; i < n; i++)
		std::cout << arr[i] << "  ";
	std::cout << std::endl;
}

int max(int* arr, int n)
{
	int max = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
}

int main()
{
	int n = 20;
	int* arr = generateArray(n);
	printArray(arr, n);

	int size = max(arr, n);
	int* newArr = new int[size + 1];
	for (int i = 0; i <= size; i++)
		newArr[i] = 0;

	for (int i = 0; i < n; i++)
	{
		int index = arr[i];
		++newArr[index];
	}

	for (int i = 0; i <= size; i++)
	{
		if (newArr[i] > 0)
		{
			for (int j = 0; j < newArr[i]; j++)
				std::cout << i << "  ";
		}
	}

	std::cout << std::endl;

	system("pause");
	return 0;
}