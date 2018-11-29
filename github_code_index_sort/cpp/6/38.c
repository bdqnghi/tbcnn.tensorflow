/************************************************************************
 * Author: Abdelrahman Elogeel                                         
 * Date: 4/9/2015
 * Verification: https://leetcode.com/problems/maximum-gap/
************************************************************************/

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <algorithm>

int getDigits(vector<int> &nums) {
    int max = 0;
    for (int n : nums) {
        int cmax = 0;
        while (n) {
            n /= 10;
            ++cmax;
        }
        max = std::max(max, cmax);
    }

    return max;
}

void radixSort(vector<int> &nums) {
    unordered_map<int, vector<int>> hash;
    char x = 0;
    int cdigit = 1;
    int digits = getDigits(nums);

    while (digits--) {
        for (int n : nums) {
            int temp = n;
            n /= cdigit;
            x = n % 10;
            hash[x].push_back(temp);
        }

        nums.clear();

        for (int i = 0; i < 10; ++i) {
            nums.insert(nums.end(), hash[i].begin(), hash[i].end());
        }

        hash.clear();
        cdigit *= 10;
    }
}