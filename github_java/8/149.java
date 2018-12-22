package com.anuj;

public class EditDistance {
    public static void main(String[] args) {
        System.out.println(editDistance("sold", "sales"));
    }

    public static int editDistance(String a, String b) {
        int[][] editDistance = new int[a.length() + 1][b.length() + 1];
        for (int i = 0; i < a.length() + 1; i++) {
            editDistance[i][0] = i;
        }
        for (int i = 0; i < b.length() + 1; i++) {
            editDistance[0][i] = i;
        }

        for (int i = 1; i < a.length() + 1; i++) {
            for (int j = 1; j < b.length() + 1; j++) {
                if (a.charAt(i - 1) == b.charAt(j - 1)) {
                    editDistance[i][j] = editDistance[i - 1][j - 1];
                } else {
                    //if it is not equal.. find the minimum
                    //of all the values that are surrounding it
                    // add 1 to it.
                    int minimum = editDistance[i - 1][j - 1] < editDistance[i - 1][j] ? editDistance[i - 1][j - 1] : editDistance[i - 1][j];
                    minimum = minimum < editDistance[i][j - 1] ? minimum : editDistance[i][j - 1];
                    editDistance[i][j] = minimum + 1;
                }
            }
        }

        return editDistance[a.length()][b.length()];
    }
}
