#include <iostream>
#include <vector>
using namespace std;
vector<int> mergeSort(vector<int> &nums, int length);
vector<int> merge_array(vector<int> &nums, vector<int> left, int leftCount, 
			vector<int> right, int rightCount);
int main()
{
	vector <int> nums;
	nums.push_back(2);
	nums.push_back(4);
	nums.push_back(1);
	nums.push_back(6);
	nums.push_back(8);
	nums.push_back(5);
	nums.push_back(3);
	nums.push_back(7);
	int length = nums.size();
	cout<<"Elements before merge sort: "<<endl;
	for(int j = 0; j<nums.size(); j++)
	{
		cout<<nums[j]<<" ";
	}
	cout<<endl;
	mergeSort(nums, length);
	cout<<"Elements after merge sort: "<<endl;
	for(int j = 0; j<nums.size(); j++)
	{
		cout<<nums[j]<<" ";
	}
	cout<<endl;
}

vector<int> mergeSort(vector<int> &nums, int length)
{
	int n, mid, i;
	vector<int>left;
	vector<int>right;
	if(length < 2)
		return nums;
	mid = length/2;

	/* Creating left sub array */
	for(i = 0; i < mid; i++)
	{
		left.push_back(nums[i]);
	}
	

	/*Creating right sub array */
	for(i = mid; i < length; i++)
	{
		right.push_back(nums[i]);
	}
	//cout<<"Hi"<<endl;

	/* Sorting left sub array */
	mergeSort(left, mid);

	/*Sorting right sub array */
	mergeSort(right, length-mid);
	
	/* Merging left and right sub array in to a sorted list */
	merge_array(nums, left, mid, right, length-mid);
	
	return nums;

}

/* Merging left and right sub arrays into a single array */
vector<int> merge_array(vector<int> &nums, vector<int> left, int leftCount, 
			vector<int> right, int rightCount)
{
	/* To mark indices of left, right and merged subarrays */
	int i = 0, j = 0, k = 0; 
	while((i < leftCount) && (j < rightCount))
	{
		if(left[i] < right[j])
		{
			nums[k] = left[i];
			i = i + 1;
		}
		else
		{
			nums[k] = right[j];
			j = j+1;
		}
		k = k + 1;
	}
	while(i < leftCount)
	{
		nums[k] = left[i];
		i = i + 1;
		k = k + 1;
	}
	while(j < rightCount)
	{
		nums[k] = right[j];
		j = j + 1;
		k = k + 1;
	}
	
	return nums;

}

