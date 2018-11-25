


#include "stdafx.h"
#include<iostream>
using namespace std;

const int* Sort(int* nums, int size){
	for (int i = 1; i < size; i++){
		if (nums[i-1]> nums[i]){
			int temp = nums[i];	
			for (int j = i - 1; j >= 0; j--){
				if (nums[j] >temp){
					nums[j + 1] = nums[j];
					nums[j] = temp;
				}
				else {
					nums[j+1] = temp;
					break;
				}
			}

		}
	}
	return nums;
}


int _tmain(int argc, _TCHAR* argv[])
{
	int nums[] = { 1, 2, 4, 3, 8, 6, 0 };
	const int* nums_ = Sort(nums, 7);
	for (int i = 0; i < 7; i++)
		cout << nums_[i] << "  ";


	system("pause");
	return 0;


}

