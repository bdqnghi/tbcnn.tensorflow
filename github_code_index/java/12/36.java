package lab06;



/*
 * Benjamin Michalowicz (SBU ID: 110982339)
 * Lab 6: Part 4: Matrix Multiplication
 */
import java.util.Scanner;

public class MatrixMultiplication {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the dimensions of the first matrix: ");
        int height = sc.nextInt(), width = sc.nextInt();

        double[][] arr1 = new double[height][width];

        System.out.print("Enter the dimensions of the second matrix: ");
        height = sc.nextInt();
        width = sc.nextInt();

        double[][] arr2 = new double[height][width];

        System.out.println("Fill the first matrix: ");
        for (int i = 0; i < arr1.length; i++) {
            for (int j = 0; j < arr1[i].length; j++) {
                arr1[i][j] = sc.nextDouble();
            }
        }

        System.out.println("Fill the second matrix: ");
        for (int i = 0; i < arr2.length; i++) {
            for (int j = 0; j < arr2[i].length; j++) {
                arr2[i][j] = sc.nextDouble();
            }
        }

        double[][] arr3 = multiplyMatrix(arr1, arr2);

        if (arr3 != null) {
            System.out.println("The resulting array is as follows: ");
            for (int i = 0; i < arr3.length; i++) {
                for (int j = 0; j < arr3[i].length; j++) {
                    System.out.print(arr3[i][j] + "\t");
                }
                System.out.println();

            }
        }

        sc.close();
    }

    public static double[][] multiplyMatrix(double[][] a, double[][] b) {
        int aRow = a.length;
        int aCol = a[0].length;
        int bRow = b.length;
        int bCol = b[0].length;

        if (aCol != bRow) {
            System.out.println("Array a's columns (" + aCol + ") did not match B's rows (" + bRow + ")");
            return null;
        }

        double[][] c = new double[aRow][bCol];

        for (int i = 0; i < aRow; i++) {
            for (int j = 0; j < bCol; j++) {
                for (int k = 0; k < aCol; k++) {
                    c[i][j] += a[i][j] * b[k][j];
                }
            }
        }

        return c;
    }

}
