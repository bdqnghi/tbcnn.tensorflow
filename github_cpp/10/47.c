







#include <iostream>
#include <vector>
using namespace std;

class Solution {
    
public:
    
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
