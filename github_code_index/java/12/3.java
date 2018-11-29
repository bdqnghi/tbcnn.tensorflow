/**
 * Created by udingji on 5/11/17.
 */
public class SparseMatrixMultiplication {

    // Question: Given two sparse matrices A and B, return the result of AB.
    // You may assume that A's column number is equal to B's row number.

    // Example:
    // A = [
    // [ 1, 0, 0],
    // [-1, 0, 3]
    //]

    // B = [
    //   [ 7, 0, 0 ],
    //   [ 0, 0, 0 ],
    //   [ 0, 0, 1 ]
    // ]

    //        |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
    //   AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
    //                     | 0 0 1 |


    // Idea: https://en.wikipedia.org/wiki/Matrix_multiplication
    // Number of rows of B should be equal to number of columns in A
    // As we scan A horizontally, we scan B vertically
    public int[][] multiply(int[][] A, int[][] B) {

        int rowA = A.length, columnA = A[0].length, rowB = columnA, columnB = B[0].length;
        int[][] result = new int[rowA][columnB];

        for (int i = 0; i < rowA; i++){
            for (int j = 0; j < columnA; j++){
                if (A[i][j] != 0){
                    for (int k = 0; k < columnB; k++){
                        if (B[j][k] != 0){
                            result[i][k] += A[i][j] * B[j][k];
                        }
                    }
                }
            }
        }
        return result;
    }
}
