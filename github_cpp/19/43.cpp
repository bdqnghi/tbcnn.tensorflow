#include "QuickSort.h"

QuickSort::QuickSort()
{
}

QuickSort::~QuickSort()
{

}

void QuickSort::sort(int nums[], int len)
{
	quickSort(nums, 0, len - 1);
}

void QuickSort::quickSort(int nums[], int low, int high)
{

	if(low > high) return;

	int first = low;
	int last = high;
	int key = nums[first];

	while(first < last) {

		while(first < last && nums[last] >= key) {
			last--;
		}

		nums[first] = nums[last];

		while(first < last && nums[first] <= key) {
			first++;
		}

		nums[last] = nums[first];
		nums[first] = key;

		quickSort(nums, low, first - 1);
		quickSort(nums, first + 1, high);
	}
}

char* QuickSort::printName() const
{
	char* name = "QuickSort";
	return name;
}