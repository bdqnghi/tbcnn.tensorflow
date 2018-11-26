package com.company;
import java.util.Scanner;

/**
 * Created by Lenovo on 01-10-2015.
 * Multiplication performed on square matrices
 *
 * INCOMPLETE
 */
public class Matrixmultiplication {
    public static void main(String args[]) {
        Scanner input = new Scanner(System.in);

        //ENTERING THE FIRST MATRIX
        System.out.println("Enter The base of the first matrix");
        int m = input.nextInt();

        System.out.println("Enter the elements of the first matrix row wise");
        int[][] a = new int[m][m];
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= m; j++)
                a[m][m] = input.nextInt();

        for (int k = 1; k <= m; k++) {
            for (int l = 1; l <= m; l++) {
                System.out.println(a[m][m]);
            }
        }


    }
}