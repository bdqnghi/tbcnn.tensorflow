



class Solution {
public:
    
    int minDistance(string word1, string word2) {
        const size_t m = word1.size();
        const size_t n = word2.size();

        if (m < n) {
            return minDistance(word2, word1);
        }

        vector<vector<int>> steps(2, vector<int>(n + 1, 0));

        for (int j = 0; j < n + 1; ++j) {
            steps[0][j] = j;
        }

        for (int i = 1; i < m + 1; ++i) {
            steps[i % 2][0] = i;
            for (int j = 1; j < n + 1; ++j) {
                steps[i % 2][j] = word1[i - 1] == word2[j - 1] ?
                steps[(i - 1) % 2][j - 1] :
                1 + min(steps[(i - 1) % 2][j - 1],
                        min(steps[(i - 1) % 2][j], steps[i % 2][j - 1]));
            }
        }

        return steps[m % 2][n];
    }
};




class Solution2 {
public:
    
    int minDistance(string word1, string word2) {
        const size_t m = word1.size();
        const size_t n = word2.size();

        if (m < n) {
            return minDistance(word2, word1);
        }

        vector<vector<int>> steps(m + 1, vector<int>(n + 1, 0));

        for (int j = 0; j < n + 1; ++j) {
            steps[0][j] = j;
        }

        for (int i = 1; i < m + 1; ++i) {
            steps[i][0] = i;
            for (int j = 1; j < n + 1; ++j) {
                steps[i][j] = word1[i - 1] == word2[j - 1] ?
                steps[i - 1][j - 1] :
                1 + min(steps[i - 1][j - 1],
                        min(steps[i - 1][j], steps[i][j - 1]));
            }
        }

        return steps[m][n];
    }
};
