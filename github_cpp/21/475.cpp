class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        vector<vector<int>> A(n + 1, vector<int>(m + 1));
        
        for (int col = 0; col < m + 1; col++) {
            A[0][col] = col;
        }
        for (int row = 0; row < n + 1; row++) {
            A[row][0] = row;
        }
        
        for (int row = 1; row < n + 1; row++) {
            for (int col = 1; col < m + 1; col++) {
                if (word1[row - 1] == word2[col - 1]) {
                    A[row][col] = A[row - 1][col - 1];
                } else {
                    A[row][col] = 1 + min(min(A[row - 1][col - 1], A[row - 1][col]), A[row][col - 1]);
                }
            }
        }
        
        return A[n][m];
    }
};