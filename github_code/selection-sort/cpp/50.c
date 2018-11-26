#include <iostream>
#include <vector>
using namespace std;
void selection_sort(vector<int>nums, int length);
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
	cout<<"Array before selection sort: "<<endl;
	for(int i = 0; i < length; i++)
		{
			cout<<nums[i]<<" ";
		}
		cout<<endl;
	selection_sort(nums,length);	

}

void selection_sort(vector<int> nums, int length)
{
	int min_pos, temp;
	for(int i = 0; i < length - 1; i++)
	{
		min_pos = i;
		for(int j = i + 1; j < length; j++)
		{
			if(nums[j] < nums[min_pos])
				min_pos = j;
		}		

		temp = nums[i];
		nums[i] = nums[min_pos];
		nums[min_pos] = temp;

	}

	cout<<"Array after selection sort: "<<endl;
	for(int i = 0; i < length; i++)
		{
			cout<<nums[i]<<" ";
		}
	cout<<endl;

}