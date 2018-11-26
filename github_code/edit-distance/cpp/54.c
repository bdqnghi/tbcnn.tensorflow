//
//  072_Edit_Distance.cpp
//  leetcode_cpp
//
//  Created by Zhen Li on 10/23/16.
//  Copyright © 2016 zl. All rights reserved.
//

#include "inc.h"

class Solution2 {
    //Using rolling array, reduce space complexity to O(n)
    //T = O(m*n), Space = O(n)
public:
    int minDistance(string word1, string word2) {
        int m = (int)word1.size();
        int n = (int)word2.size();
        int dp[2][n + 1];
        dp[0][0] = 0;
        for(int i = 1; i <= n; ++i){
            dp[0][i] = i;
        }
        for(int i = 1; i <= m; ++i){
            dp[i % 2][0] = i;
            for(int j = 1; j <= n; ++j){
                int addOrRemove = min(dp[i % 2][j - 1], dp[(i - 1) % 2][j]) + 1;
                int replace = dp[(i - 1) % 2][j - 1] + (word1[i - 1] == word2[j - 1] ? 0 : 1);
                dp[i % 2][j] = min(addOrRemove, replace);
            }
        }
        return dp[m % 2][n];
    }
};



class Solution {
    //T = O(m*n), Space = O(m*n)
    //can further reduce space using rolling array, see solution2
public:
    int minDistance(string word1, string word2) {
        int m = (int)word1.size();
        int n = (int)word2.size();
        int dp[m + 1][n + 1];
        dp[0][0] = 0;
        for(int i = 1; i <= m; ++i){
            dp[i][0] = i;
        }
        for(int i = 1; i <= n; ++i){
            dp[0][i] = i;
        }
        //either i or j can be in the out loop. The order doesn't matter.
        for(int i = 1; i <= m; ++i){
            for(int j = 1; j <= n; ++j){
                int addOrRemove = min(dp[i][j - 1], dp[i - 1][j]) + 1;
                int replace = dp[i - 1][j - 1] + (word1[i - 1] == word2[j - 1] ? 0 : 1);
                dp[i][j] = min(addOrRemove, replace);
            }
        }
        return dp[m][n];
    }
};
