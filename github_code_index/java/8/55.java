package com.anuj.leetcode;

public class EditDistance {

    public static void main(String[] args) {
        System.out.println(editDistance("pneumonoultramicroscopicsilicovolcanoconiosis",
            "ultramicroscopically"));
        System.out.println(editDistance("ab", "a"));
    }

    public static int editDistance(String word1, String word2) {
        if ((word1 == null || word1.isEmpty()) && (word2 == null || word2.isEmpty())) {
            return 0;
        }
        if (word1 == null || word1.isEmpty()) {
            return word2.length();
        }
        if (word2 == null || word2.isEmpty()) {
            return word1.length();
        }

        int[][] editDistance = new int[word1.length()][word2.length()];
        //for the edge cases we will fill it one by one.
        if (word1.charAt(0) == word2.charAt(0)) {
            editDistance[0][0] = 0;
        } else {
            editDistance[0][0] = 1;
        }

        for (int i = 1; i < word2.length(); i++) {
            if (word1.charAt(0) == word2.charAt(i)) {
                editDistance[0][i] = i;
            } else {
                editDistance[0][i] = Math.min(i + 1, editDistance[0][i - 1] + 1);
            }
        }

        for (int i = 1; i < word1.length(); i++) {
            if (word2.charAt(0) == word1.charAt(i)) {
                editDistance[i][0] = i;
            } else {
                editDistance[i][0] = Math.min(i + 1, editDistance[i - 1][0] + 1);
            }
        }

        for (int i = 1; i < word1.length(); i++) {
            for (int j = 1; j < word2.length(); j++) {
                if (word1.charAt(i) == word2.charAt(j)) {
                    editDistance[i][j] = editDistance[i - 1][j - 1];
                } else {
                    editDistance[i][j] = Math.min(Math.min(editDistance[i][j - 1],
                        editDistance[i - 1][j]), editDistance[i - 1][j - 1]) + 1;
                }
            }
        }

        return editDistance[word1.length() - 1][word2.length() - 1];
    }
}
