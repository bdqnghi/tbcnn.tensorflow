//
//  levenshteinDistance.cpp
//  test
//
//  Created by haiyang on 16/7/22.
//  Copyright © 2016年 yingtian corp. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

class Solution {
    
public:
    /**
     设Ai为字符串A(a1a2a3 … am)的前i个字符（即为a1,a2,a3 … ai）
     设Bj为字符串B(b1b2b3 … bn)的前j个字符（即为b1,b2,b3 … bj）
     设 L(i,j)为使两个字符串和Ai和Bj相等的最小操作次数。
     当ai==bj时 显然 L(i,j) = L(i-1,j-1)
     当ai!=bj时
     若将它们修改为相等，则对两个字符串至少还要操作L(i-1,j-1)次
     若删除ai或在bj后添加ai，则对两个字符串至少还要操作L(i-1,j)次
     若删除bj或在ai后添加bj，则对两个字符串至少还要操作L(i,j-1)次
     此时L(i,j) = min( L(i-1,j-1), L(i-1,j), L(i,j-1) ) + 1
     显然，L(i,0)=i，L(0,j)=j, 再利用上述的递推公式，可以直接计算出L(i,j)值
     **/
    int levenshteinDistance(const wstring& l, const wstring& r) {
        vector<vector<int>> dp(l.size() + 1, vector<int>(r.size() + 1));
        
        dp[0][0] = 0;
        for (auto i = 1; i <= l.size(); i++) dp[i][0] = i;
        for (auto i = 1; i <= r.size(); i++) dp[0][i] = i;
        
        for (auto i = 1; i <= l.size(); i++) {
            for (auto j = 1; j <= r.size(); j++) {
                if (l[i - 1] == r[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min(min(dp[i - 1][j - 1], dp[i - 1][j]), dp[i][j - 1]) + 1;
                }
            }
        }
        
        return dp[l.size()][r.size()];
    }
    
};

int main(int argc, const char* argv[]) {
    Solution s;
    
    int distance = s.levenshteinDistance(L"黄海洋", L"黄*洋");
    cout << "levenshteinDistance is: " << distance << endl;
    
    return 0;
}
