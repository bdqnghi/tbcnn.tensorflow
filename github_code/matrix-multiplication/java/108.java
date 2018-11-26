package Arrays;

import java.util.Scanner;

/**
 * Created by Anand on 3/12/2016.
 */
public class MatrixMultiplication {

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        System.out.print("Enter number of rows in A: ");
        int rowsInA = s.nextInt();
        System.out.print("Enter number of columns in A / rows in B: ");
        int columnsInA = s.nextInt();
        System.out.print("Enter number of columns in B: ");
        int columnsInB = s.nextInt();
        int[][] a = new int[rowsInA][columnsInA];
        int[][] b = new int[columnsInA][columnsInB];
        System.out.println("Enter matrix A");
        for (int i = 0; i < a.length; i++) {
            for (int j = 0; j < a[0].length; j++) {
                a[i][j] = s.nextInt();
            }
        }
        System.out.println("Enter matrix B");
        for (int i = 0; i < b.length; i++) {
            for (int j = 0; j < b[0].length; j++) {
                b[i][j] = s.nextInt();
            }
        }
        int[][] c = multiply(a, b);
        System.out.println("Product of A and B is");
        for (int i = 0; i < c.length; i++) {
            for (int j = 0; j < c[0].length; j++) {
                System.out.print(c[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static int[][] multiply(int[][] a, int[][] b) {
        int rowsInA = a.length;
        int columnsInA = a[0].length; // same as rows in B
        int columnsInB = b[0].length;
        int[][] c = new int[rowsInA][columnsInB];
        for (int i = 0; i < rowsInA; i++) {
            for (int j = 0; j < columnsInB; j++) {
                for (int k = 0; k < columnsInA; k++) {
                    c[i][j] = c[i][j] + a[i][k] * b[k][j];
                }
            }
        }
        return c;
    }
}
