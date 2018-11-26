package oj311SparseMatrixMultiplication;

/**
 * Given two sparse matrices A and B, return the result of AB.
 *
 * You may assume that A's column number is equal to B's row number.
 *
 * Example:
 *
 * Input:
 *
 * A = [
 *   [ 1, 0, 0],
 *   [-1, 0, 3]
 * ]
 *
 * B = [
 *   [ 7, 0, 0 ],
 *   [ 0, 0, 0 ],
 *   [ 0, 0, 1 ]
 * ]
 *
 * Output:
 *
 *      |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
 * AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
 *                   | 0 0 1 |
 */

public class SparseMatrixMultiplication {
    public int[][] multiply(int[][] A, int[][] B) {
        int row_A = A.length, col_A = A[0].length, col_B = B[0].length;
        int[][] C = new int[row_A][col_B];
        for(int i = 0; i < row_A; i++) {
            for(int j = 0; j < col_A; j++) {
                if(A[i][j] != 0) {
                    for(int k = 0; k < col_B; k++) {
                        if(B[j][k] != 0) {
                            C[i][k] += A[i][j] * B[j][k];
                        }
                    }
                }
            }
        }
        return C;
    }
}
