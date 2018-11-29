public class Solution {
    /**
     * @param word1 & word2: Two string.
     * @return: The minimum number of steps.
     */
    public int minDistance(String word1, String word2) {
        // write your code here
        if (word1 == null || word1.length() == 0) {
            if (word2 == null || word2.length() == 0) {
                return 0;
            } else {
                return word2.length();
            }
        } else if (word2 == null || word2.length() == 0){
            return word1.length();
        }
        //    k a r m a
        // m  1 2 3 3 4
        // a  2 1 2 3 3
        // r  3 2 1 2 3
        // t  4 3 2 2 3
        int m = word1.length();
        int n = word2.length();
        int[][] result = new int[m + 1][n + 1];
        //初始化第一行和第一列
        for (int j = 0; j <= n; j++) {
            result[0][j] = j;
        }
        for (int i = 0; i <= m; i++) {
            result[i][0] = i;
        }
        //开始计算
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) {//相等，当前元素不需要动，保留word1与word2之前子串的距离即可
                    result[i][j] = result[i - 1][j - 1];
                } else {//不等，需要算个最小值
                    //1. 当前元素做替换，加上word1与word2之前子串的距离
                    //2. 当前元素做插入，加上word1当前子串与word2之前子串的距离
                    //3. 当前元素删除，加上word1之前子串与word2当前子串的距离
                    int min = Math.min(result[i - 1][j - 1], result[i][j - 1]);
                    min = Math.min(min, result[i - 1][j]);
                    result[i][j] = min + 1;
                }
            }
        }
        return result[m][n];
    }
}
