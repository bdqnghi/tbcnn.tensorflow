class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();
        vector<vector<int> > t(m+1, vector<int>(n+1, 0));
        for(int j = 0; j <= n; j++) 
            t[0][j] = j;
        for(int i = 1; i <= m; i++) 
            t[i][0] = i;
        for (int k = 2; k <= m + n; k++){
            for (int j = max(1, k - m); j <= min(n, k - 1); j++){
                int i = k - j;
                t[i][j] = min(min(t[i-1][j], t[i][j-1]) + 1, t[i-1][j-1] + (word1[i-1] == word2[j-1]? 0 : 1) );
            }
        }
        return t[m][n];
    }
};