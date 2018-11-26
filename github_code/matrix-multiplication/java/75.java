/**
 * @brief Write a Java program to perform matrix multiplication.
 * @note Practical No. 005
 */
import java.util.Scanner;
import java.util.Arrays;

public class MatrixMultiplication {
    public static void main(String[] args) {
        int rowsA, colsA, rowsB, colsB;
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter rows and columns of first matrix:");
        rowsA = sc.nextInt();
        colsA = sc.nextInt();
        System.out.println("Enter rows and columns of second matrix:");
        rowsB = sc.nextInt();
        colsB = sc.nextInt();

        if (colsA != rowsB) {
            System.out.println("Matrix Multiplication not possible!");
            System.exit(1);
        }

        int[][] matA = new int[rowsA][colsA];
        int[][] matB = new int[rowsB][colsA];
        int[][] matProduct = new int[rowsA][colsB];

        System.out.println("Enter the elements of first martix");
        for (int i = 0; i < rowsA; i++) {
            for (int j = 0; j < colsA; j++) {
                matA[i][j] = sc.nextInt();
            }
        }
        System.out.println("Enter the elements of second martix");
        for (int i = 0; i < rowsB; i++) {
            for (int j = 0; j < colsB; j++) {
                matB[i][j] = sc.nextInt();
            }
        }
        multiplyMatrices(matA, matB);
    }

    public static void multiplyMatrices(int[][] matA, int[][] matB) {
        int[][] matProduct = new int[matA.length][matB[0].length];

        for (int i = 0; i < matA.length; i++) {
            for (int j = 0; j < matB[0].length; j++) {
                for (int k = 0; k < matA[0].length; k++) {
                    matProduct[i][j] += matA[i][k] * matB[k][j];
                }
            }
        }
        displayMatrix(matProduct);
    }

    public static void displayMatrix(int[][] matrix) {
        for (int[] x : matrix) {
            System.out.printf("%s\n", Arrays.toString(x));
        }
    }
}
