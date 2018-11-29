package com.cllin.algorithms;

import java.util.Arrays;

import com.cllin.main.Exercise;

/*
 * A k-palindrome is a string which transforms into a palindrome on removing at most k characters. 
 * 
 * Given a string S, and an integer K, print "YES" if S is a k-palindrome; otherwise print "NO".
 * 
 * Sample Case 1:
 *         Input - abxa, 1
 *         Output - YES
 * 
 * Sample Case 2:
 *         Input - abdxa, 1
 *         Output - No
 * 
 * Source: http://www.careercup.com/question?id=6287528252407808
 */

public class KPalindrome extends Exercise {

    private final String[] testSuite = {
        "abba",
        "abxa",
        "abaxbabax"
    };
    
    private boolean isKPalindrome(String string, int K) {
        String reverse = new StringBuilder(string).reverse().toString();
        
        int[][] editDistance = new int[string.length() + 1][string.length() + 1];
        
        for (int i = 0; i <= string.length(); i++) {
            Arrays.fill(editDistance[i], 1000000000);
            editDistance[0][i] = i;
            editDistance[i][0] = i;
        }
        
        for (int i = 1; i <= string.length(); i++) {
            int start = Math.max(1, i - K);
            int end = Math.min(string.length(), i + K);
            
            for (int j = start; j <= end; j++) {
                if (string.charAt(i - 1) == reverse.charAt(j - 1)) {
                    editDistance[i][j] = editDistance[i - 1][j - 1];
                }
                
                int insert = editDistance[i - 1][j] + 1;
                int delete = editDistance[i][j - 1] + 1;
                editDistance[i][j] = Math.min(editDistance[i][j], delete);
                editDistance[i][j] = Math.min(editDistance[i][j], insert);
            }
        }
        
        return editDistance[string.length()][string.length()] / 2 <= K;
    }
    
    private String getKPalindrome(String string, int K) {
        String reverse = new StringBuilder(string).reverse().toString();
        
        int[][] editDistance = new int[string.length() + 1][string.length() + 1];
        
        for (int i = 0; i <= string.length(); i++) {
            Arrays.fill(editDistance[i], 1000000000);
            editDistance[0][i] = i;
            editDistance[i][0] = i;
        }
        
        for (int i = 1; i <= string.length(); i++) {
            int start = Math.max(1, i - K);
            int end = Math.min(string.length(), i + K);
            
            for (int j = start; j <= end; j++) {
                if (string.charAt(i - 1) == reverse.charAt(j - 1)) {
                    editDistance[i][j] = editDistance[i - 1][j - 1];
                }
                
                int insert = editDistance[i - 1][j] + 1;
                int delete = editDistance[i][j - 1] + 1;
                editDistance[i][j] = Math.min(editDistance[i][j], delete);
                editDistance[i][j] = Math.min(editDistance[i][j], insert);
            }
        }
        
        StringBuffer palindrome = new StringBuffer(string);
        for (int i = string.length(); i >= 1; i--) {
            if (editDistance[i][i] != editDistance[i - 1][i - 1]) {
                palindrome.replace(i, i + 1, "");
            }
        }
        
        return palindrome.toString();
    }

    @Override
    protected void initialize() {
        return;
    }

    @Override
    protected void runExercise() {
        for (String string : testSuite) {
            for (int k = 0; k <= string.length(); k++) {
                boolean isKPalindrome = isKPalindrome(string, k);
                System.out.printf("%s %s a %d palindrome%n", string, (isKPalindrome) ? "is" : "is not", k);

                if (isKPalindrome) {
                    System.out.printf("->%s%n", getKPalindrome(string, k));
                }

                System.out.println("------------------");
            }
        }
    }

    @Override
    protected boolean test() {
        return true;
    }
    
}
