/*************************************************************************
	> File Name: 072_EditDistance.cpp
	> Author: Sheng Qin
	> Mail: sheng.qin@yale.edu
	> Created Time: Tue Sep  6 19:06:48 2016
 ************************************************************************/

#include<iostream>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length(), n = word2.length();
        int f[m + 1][n + 1];
        
        f[0][0] = 0;
        for(int i = 1; i <= m; i++)
            f[i][0] = i;
        for(int j = 1; j <= n; j++)
            f[0][j] = j;

        for(int i = 1; i <= m; i++)
            for(int j = 1; j <= n; j++){
                if(word1[i - 1] == word2[j - 1])
                    f[i][j] = f[i - 1][j - 1];
                else
                    f[i][j] = f[i - 1][j - 1] + 1;

                if(f[i - 1][j] + 1 < f[i][j])
                    f[i][j] = f[i - 1][j] + 1;
                
                if(f[i][j - 1] + 1 < f[i][j])
                    f[i][j] = f[i][j - 1] + 1;
            }

        return f[m][n];    
    }
};

int main() {
    Solution newSolution;
    cout << newSolution.minDistance("abcde","abc") << endl;
    return 0;
}
