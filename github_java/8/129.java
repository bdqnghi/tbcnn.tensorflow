/*

72. Edit Distance
https://leetcode.com/problems/edit-distance/description/

Given two words word1 and word2, find the minimum number of operations required
to convert word1 to word2.

You have the following 3 operations permitted on a word:

Insert a character
Delete a character
Replace a character

Example 1:
Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')

Example 2:
Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')

*/



// dp
class Solution {
    public int minDistance(String word1, String word2) {
        final int n = word1.length();
        final int m = word2.length();
        
        int[] cur = new int[m + 1]; // i
        int[] pre = new int[m + 1]; // i + 1
        
        for (int i = n; i >= 0; i--) {
            for (int j = m; j >= 0; j--) {
                if (i == n && j == m) {
                    cur[j] = 0;
                } else if (i == n) {
                    cur[j] = 1 + cur[j + 1];
                } else if (j == m) {
                    cur[j] = 1 + pre[j];
                } else {
                    if (word1.charAt(i) == word2.charAt(j)) {
                        cur[j] = pre[j + 1];
                    } else {
                        cur[j] = 1 + Math.min(cur[j + 1], 
                            Math.min(pre[j], pre[j + 1]));
                    }
                }
            }
            int[] tmp = cur;
            cur = pre;
            pre = tmp;
        }
        
        return pre[0];
    }
}
// 1146 / 1146 test cases passed.
// Runtime: 4 ms


