/***********************************************
* Given an unsorted integer array, find the first missing positive integer.
* For example, Given [1, 2, 0] return 3, and [3, 4, -1, 1] return 2.
* Your algorithm should run in O(n) time and uses constant space.
***********************************************/
#include <iostream>
#include <vector>
using namespace std;

class Solution {
private:
	void bucketSort(vector<int> &nums) {
		for (int i = 0; i < nums.size(); i++) {
			while (nums[i] != i + 1 && nums[i] > 0 && nums[i] < nums.size() && nums[i] != nums[nums[i]-1]) {
				swap(nums[i], nums[nums[i]-1]);
			}
		} 
	}
public:
	/* Time: O(nlogn), Space: O(1) */
	/* Bucket-Sort: O(n) */
	/* Merge-Sort */
	/* T(n) = n / 2 + 2T(n/2) + n, we get (3n/2)logn */
	int firstMissingPositive(vector<int> nums) {
		bucketSort(nums);
		
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] != i + 1) {
				return i + 1;
			}
		}
		
		return nums.size() + 1;
	}
};

int main(void) {
	Solution* s = new Solution();
	vector<int> arr1 = { 1, 2, 0 };
	vector<int> arr2 = { 3, 4, -1, 1 };
	vector<int> arr3 = { 3, 4, 2, 1, 0 };
	
	cout << "Solution 1: " << s->firstMissingPositive(arr1) << endl;	
	cout << "Solution 1: " << s->firstMissingPositive(arr2) << endl;
	cout << "Solution 1: " << s->firstMissingPositive(arr3) << endl;
	
	delete s;
	return 0;
}