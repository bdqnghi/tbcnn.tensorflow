/* Bubble Sort of the given array elements */

#include <iostream>
#include <vector>
using namespace std;

void bubble_sort(vector<int>, int);
int main()
{
	vector <int> nums;
	nums.push_back(2);
	nums.push_back(7);
	nums.push_back(4);
	nums.push_back(1);
	nums.push_back(5);
	nums.push_back(3);
	int length = nums.size();
	cout<<"Array before bubble sort: "<<endl;
	for(int i = 0; i < length; i++)
		{
			cout<<nums[i]<<" ";
		}
		cout<<endl;
	bubble_sort(nums,length);	

}

void bubble_sort(vector<int>nums, int length)
{
	int flag, temp;
	
	for(int k = 1; k < length-1; k++)
	{
		flag = 0;
		for(int i = 0; i <= length - k -1; i++)
		{
			if(nums[i] > nums[i+1])
			{
				temp = nums[i];
				nums[i] = nums[i+1];
				nums[i+1] = temp;
				flag = 1;
			}
		}
		if(flag == 0)
				break;
	}
	cout<<"Array after bubble sort: "<<endl;
	for(int i = 0; i < length; i++)
		{
			cout<<nums[i]<<" ";
		}
		cout<<endl;
	
}