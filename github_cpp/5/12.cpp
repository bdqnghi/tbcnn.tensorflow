#include <vector>

using namespace std;

/*

Insertion sort:

A list is divided into two parts:
	- Unsorted 	(right of i)
	- Sorted	(left of i)

This algorithm iterates over the list, picking the element and moving it left
if it is more than the element left of it, continuing to swap left until it 
finds it's spot.

Complexity: 
	Worst:		O(n^2)
	Average: 	O(n^2)
	Best: 		O(n)

*/
void insertionSort(vector<int>& arr)
{
	int tmp, j;

	for (unsigned i = 0; i < arr.size(); ++i)
	{
		j = i;
		tmp = arr[i];

		while (j > 0 && tmp < arr[j-1])
		{
			arr[j] = arr[j-1];
			j--;
		}
		arr[j] = tmp;
	}
}