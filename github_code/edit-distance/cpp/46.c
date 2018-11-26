// https://leetcode.com/problems/edit-distance/description/
//  edit-distance.h
//  CppToySolution
//
//  Created by QZQ on 19/10/2018.
//  Copyright © 2018 QZQ. All rights reserved.
//

#ifndef edit_distance_h
#define edit_distance_h
class Solution {
public:
    const int INF = 2e9;
    int minDistance(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();
        
        int **dp = new int*[n+1];
        for(int i = 0; i <= n; ++i) dp[i] = new int[m+1];
        
        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= m; ++j) dp[i][j] = INF;
        dp[0][0] = 0;
        
        
        for(int i = 0; i <= n; ++i) // i j 指长度
            for(int j = 0; j <= m; ++j)
            {
                if(i+1 <= n && j+1 <= m && word1[i] == word2[j]) dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j]);
                if(i+1 <= n && j+1 <= m) dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j]+1);
                if(i+1 <= n) dp[i+1][j] = min(dp[i+1][j], dp[i][j]+1);
                if(j+1 <= m) dp[i][j+1] = min(dp[i][j+1], dp[i][j]+1);
            }
        
        int ans = dp[n][m];
        for(int i = 0; i < n; ++i) delete [] dp[i];
        delete [] dp;
        return ans;
    }
};

#endif /* edit_distance_h */
