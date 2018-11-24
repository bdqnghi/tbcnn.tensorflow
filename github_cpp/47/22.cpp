//
//  binary-search
//  https://leetcode.com/problems/binary-search/
//
//  Created by smilingpoplar on 15/6/7.
//  Copyright (c) 2015年 YangLe. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = -1, u = nums.size();
        while (l + 1 < u) {
            int mid = l + (u - l) / 2;
            if (nums[mid] >= target) {
                u = mid;
            } else {
                l = mid;
            }
        }
        if (u < nums.size() && nums[u] == target) return u;
        return -1;
    }
};

int main(int argc, const char * argv[]) {
    return 0;
}
