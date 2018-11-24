class Solution {
public:
    /**
     * @param word1 & word2: Two string.
     * @return: The minimum number of steps.
     */
    int minDistance(string word1, string word2) {
        // write your code here
        int inf = 1000000;
        int len1 = word1.size(), len2 = word2.size();
        vector<vector <int> > vec(len1+1 ,vector<int>(len2+1));
        for (int i = 0; i <= len1; i ++) {
            for (int j = 0; j <= len2; j ++) {
                vec[i][j] = inf;
            }
        }
        vec[0][0] = 0;
        for (int i = 0; i <= len1; i ++) {
            for (int j = 0; j <= len2; j ++) {
                if (i == 0) {
                    vec[i][j] = j;
                } else if (j == 0) {
                    vec[i][j] = i;
                } else if (word1[i-1] != word2[j-1]) {
                    vec[i][j] = min(vec[i-1][j]+1, min(vec[i][j-1]+1, vec[i-1][j-1]+1));
                } else {
                    vec[i][j] = vec[i-1][j-1];
                }
            }
        }
        return vec[len1][len2];
    }
};
