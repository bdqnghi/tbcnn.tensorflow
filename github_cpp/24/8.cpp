




#include <iostream>
using namespace std;
int binary_search(int arr[], int size, int num)
{
	int start = 0, end = size - 1;
	while (start <= end)
	{
		int mid = (start + end) / 2;
		if (arr[mid] == num)
		{
			return mid;
		}
		else if (num < arr[mid])
		{
			end = mid - 1;
		}
		else
		{
			start = mid + 1;
		}
	}
	return -1;
}
int main()
{
	int arr[10000];
	int size;
	cout << "Enter the size of array:";
	cin >> size;
	int num;
	cout << "Enter the array elements: "<<endl;
	for (int i = 0; i < size; i++)
	{
		cin >> arr[i];
	}
	cout << "Enter number to search? ";
	cin >> num;
	cout << binary_search(arr, size, num);
	return 0;
}
