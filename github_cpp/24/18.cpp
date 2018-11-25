

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <cmath>
#include <numeric>
#include <string>
#include<stdio.h>
using namespace std;


class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0, high = nums.size()-1;
        while (low <= high) {
            int mid = (low+high)/2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > target) {
                high = mid-1;
            } else {
                low = mid+1;
            }
        }
        return -1;
    }
};

int main() {
    Solution s;
    vector<vector<int>> grid;
    vector<int> v = {-1, 3, 5, 6, 10};
    cout << s.search(v, -1) << endl;
    cout << s.search(v, 2) << endl;
    cout << s.search(v, 3) << endl;
    cout << s.search(v, 10) << endl;

    vector<int> v2 = {9};
    cout << s.search(v2, 10) << endl;
    cout << s.search(v2, 9) << endl;

    return 0;
}


