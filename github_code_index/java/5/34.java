package com.hackerrank.interview;

import java.util.*;

public class DFS {

    private static boolean isValid(int[][] matrix, int row, int column) {

        if (row < 0 || column < 0 || row >= matrix.length || column >= matrix[row].length ||
                matrix[row][column] < 1) {
            return false;
        } else {
            return true;
        }
    }

    private static int dfs(int[][] matrix, int row, int column) {

        if (!isValid(matrix, row, column)) {
            return 0;
        }

        int count = 1;
        int newX = row;
        int newY = column;
        matrix[row][column] = -1;

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                newX = row + i;
                newY = column + j;

                count = count + dfs(matrix, newX, newY);
            }
        }
        return count;
    }

    public static int solve(int[][] matrix) {

        int maxValue = 0;
        int tempValue = 0;

        for (int r = 0; r < matrix.length; r++) {
            for (int c = 0; c < matrix[r].length; c++) {
                tempValue = dfs(matrix, r, c);

                if (tempValue > maxValue) {
                    maxValue = tempValue;
                }
            }
        }

        return maxValue;
    }

    public static void main(String[] args) {

//        int[][] matrix = new int[][] {{1,1,0,0}, {0,1,1,0}, {0,0,1,0}, {1,0,0,0,}};
//        System.out.println(solve(matrix));

        Scanner inner = new Scanner(System.in);
        int r = inner.nextInt();
        int c = inner.nextInt();
        int[][] matrix = new int[r][c];

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                matrix[i][j] = inner.nextInt();
            }
        }
        System.out.println(solve(matrix));
        inner.close();
    }

}
