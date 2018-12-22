/**
 * Problem Statement: Edit Distance
 * Link: https://oj.leetcode.com/problems/edit-distance/
 * 
 * Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. 
 * (each operation is counted as 1 step.)
 * 
 * You have the following 3 operations permitted on a word:
 * a) Insert a character
 * b) Delete a character
 * c) Replace a character
 */


public class Solution {
    public int minDistance(String word1, String word2) {
        
        int len1 = word1.length();
        int len2 = word2.length();
        
        //the edit distance of word1[0..i] and word2[0..j]
        int[][] C = new int[len1+1][len2+1];
        
        //initialize
        C[0][0] = 0;
        for(int i=1; i<=len1; i++)
            C[i][0] = i;
        for(int j=1; j<=len2; j++)
            C[0][j] = j;
            
        //dynamic programming find the length of the longest common sequence
        for(int i=1; i<=len1; i++)
            for(int j=1; j<=len2; j++)
            if(word1.charAt(i-1)==word2.charAt(j-1)) C[i][j] = C[i-1][j-1];
            else
            { 
                C[i][j] = Math.min(C[i-1][j], C[i][j-1]) + 1;
                C[i][j] = Math.min(C[i][j], C[i-1][j-1]+1);
             }
        
        return C[len1][len2];
    }
}


////////////////////////////////////////////////////////////////////////
//Round 2: 12/24/2014
public class Solution {
    public int minDistance(String word1, String word2) {
        
        //special case
        if(word1.length()==0) return word2.length();
        if(word2.length()==0) return word1.length();
        
        //define dynamic table
        //len[i+1][j+1] represents the minumum edit distance oc word1(0...i) and word2(0...j)
        int[][] len = new int[word1.length()+1][word2.length()+1];
        len[0][0] = 0;
        
        //intialize the table
        for(int i=0; i<word1.length(); i++)
            len[i+1][0] = i+1;
        for(int i=0; i<word2.length(); i++)
            len[0][i+1] = i+1;
        
        //dynamic build the table
        for(int i=0; i<word1.length(); i++){
            for(int j=0; j<word2.length(); j++){
                if(word1.charAt(i)==word2.charAt(j)){
                    //case 1
                    len[i+1][j+1] = Math.min(len[i][j], len[i+1][j]+1);
                    len[i+1][j+1] = Math.min(len[i+1][j+1], len[i][j+1]+1);
                }
                else{
                    //case 2
                    len[i+1][j+1] = Math.min(len[i+1][j]+1,len[i][j+1]+1);
                    len[i+1][j+1] = Math.min(len[i][j]+1, len[i+1][j+1]);
                }
            }
        }
        
        return len[word1.length()][word2.length()];
        
    }
}


/////////////////////////////////////////////////
// 2015/11/07
// Highlight: DP 2D
public class Solution {
    public int minDistance(String word1, String word2) {
        int len1 = word1.length();
        int len2 = word2.length();
        int[][] count = new int[len1+1][len2+1];
        
        for(int i=0; i<len1+1; i++){
            count[i][0] = i;
        }
        
        for(int j=0; j<len2+1; j++){
            count[0][j] = j;
        }
        
        for(int i=1; i<len1+1; i++){
            for(int j=1; j<len2+1; j++){
                if(word1.charAt(i-1) == word2.charAt(j-1)){
                    count[i][j] = count[i-1][j-1];
                }else{
                    //delete a character, or insert a character
                    count[i][j] = Math.min(count[i-1][j], count[i][j-1])+1;
                    //replace a character
                    count[i][j] = Math.min(count[i-1][j-1]+1, count[i][j]);
                }
            }
        }
        
        return count[len1][len2];
    }
}
