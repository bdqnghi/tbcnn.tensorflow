// package whatever; // don't place package name!

import java.io.*;
import java.util.*;

// Execute with: javac EditDistance.java && java EditDistance
class EditDistance {

    public Integer distance(String left, String right) {
        int[][] matrix = new int[left.length()][];
        for (int i = 0; i < left.length(); i++) {
            matrix[i] = new int[right.length()];
        }

        for (int i = 0; i < left.length(); i++) {
            for (int j = 0; j < right.length(); j++) {
                if (i == 0) {
                    matrix[i][j] = j;
                } else if (j == 0) {
                    matrix[i][j] = i;
                } else if (left.charAt(i) == right.charAt(j)) {
                    matrix[i][j] = matrix[i - 1][j - 1];
                } else {
                    matrix[i][j] = 1 + min(min(matrix[i - 1][j], matrix[i][j - 1]), matrix[i - 1][j - 1]);
                }
            }
        }
        return matrix[left.length() - 1][right.length() - 1];
    }

    private Integer min(Integer left, Integer right) {
        return (left > right) ? right : left;
    }

    public static void main (String[] args) {
        EditDistance arr = new EditDistance();
        Integer result = arr.distance("geek", "gesek");
        System.out.println(result);

        result = arr.distance("cat", "cut");
        System.out.println(result);

        result = arr.distance("saturday", "sunday");
        System.out.println(result);
    }
}
