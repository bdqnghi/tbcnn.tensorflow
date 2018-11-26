/* Example of Verifying Matrix-Multiplication
* May produce incorrect solutions,
* but has a fixed deterministic running time.
*/

import java.util.Random;

public class MatrixMultiplication {
  
  public static void main(String[] args) {

    int[][] matr1 = {{4,8},{0,2},{1,6}};
    int[][] matr2 = {{5,2}, {9,4}};
    int[][] result = multiply(matr1, matr2);
    int[][] expected = {{92,40},{18,8},{59,26}};
    // printMatrix(result);
    // System.out.println(verify(result, expected));
    // System.out.println(randomVerify(matr1, matr2, expected));
    int[][] wrong = {{92,40},{18,8},{59,40}};
    System.out.println(verify(result, wrong));
    System.out.println(randomVerify(matr1, matr2, wrong));
    System.out.println(reduceErrorVerify(matr1, matr2, wrong, 5));

  }

  public static void printMatrix(int[][] matrix) {
    for (int i = 0; i < matrix.length; i++) {
      for (int j = 0; j < matrix[0].length; j++) {
        System.out.print(matrix[i][j] + " ");
      }
      System.out.println();
    }
  }

  public static boolean reduceErrorVerify(int[][] matr1, int[][] matr2, int[][] matr3, int k) {
    boolean isTrue = true;
    for (int i = 0; i < k; i++) {
      isTrue &= randomVerify(matr1, matr2, matr3);
    }
    return isTrue;
  }

  public static boolean randomVerify(int[][] matr1, int[][] matr2, int[][] matr3) {
    int[][] r = new int[matr1[0].length][1];
    Random rand = new Random();
    for (int i = 0; i < r.length; i++) {
      r[i][0] = rand.nextInt(2);
    }
    // printMatrix(r);
    int[][] br = multiply(matr2, r);
    int[][] abr = multiply(matr1, br);
    int[][] cr = multiply(matr3, r);
    return verify(abr, cr);

  }

  public static boolean verify(int[][] matr1, int[][] matr2) {
    if (matr1.length != matr2.length || matr1[0].length != matr2[0].length) {
      return false;
    }

    for (int i = 0; i < matr1.length; i++) {
      for (int j = 0; j < matr1[0].length; j++) {
        if (matr1[i][j] != matr2[i][j]) {
          return false;
        }
      }
    }

    return true;
  }

  public static int[][] multiply(int[][] matr1, int[][] matr2) {
    
    int rowA = matr1[0].length;
    int colA = matr1.length;
    int rowB = matr2[0].length;
    int colB = matr2.length;

    if (rowA != colB) {
      throw new IllegalArgumentException();
    }

    int[][] result = new int[colA][rowB];

    for (int i = 0; i < colA; i++) {
      for (int j = 0; j < rowB; j++) {
        for (int k = 0; k < rowA; k++) {
          result[i][j] += matr1[i][k] * matr2[k][j];
        }
      }
    }

    return result;

  }

}
