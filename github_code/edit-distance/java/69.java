package leetcode;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;


public class Solution {
    public int minDistance(String word1, String word2) {
    	if (word1.isEmpty())
    		return word2.length();
    	else if (word2.isEmpty())
    		return word1.length();
    	int[][] dp = new int[word1.length() + 1][word2.length() + 1];
    	for (int i = 0; i <= word1.length(); i++)
    		dp[i][word2.length()] = word1.length() - i;
    	for (int i = 0; i <= word2.length(); i++)
    		dp[word1.length()][i] = word2.length() - i;
    	for (int i = word1.length() - 1; i >= 0; i--) {
    		for (int j = word2.length() - 1; j >= 0; j--) {
    			if (word1.charAt(i) == word2.charAt(j))
    				dp[i][j] = dp[i+1][j+1];
    			else {
    				int s = 1 + dp[i+1][j+1];
    				if (1 + dp[i+1][j] < s)
    					s = 1 + dp[i+1][j];
    				if (1 + dp[i][j+1] < s)
    					s = 1 + dp[i][j+1];
    				dp[i][j] = s;
    			}
    		}
    	}
    	return dp[0][0];
    }
}
