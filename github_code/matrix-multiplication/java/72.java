package com.vignesh.java.module1;

import java.util.Scanner;

public class Matrixmultiplication {

	public static void main(String[] args) {
		int m, n, p, q, sum = 0;
		System.out.println("Enter the row X Column of the first matrix");
		Scanner in = new Scanner(System.in);
		m = in.nextInt();
		n = in.nextInt();
		System.out.println("Enter the Elements of first matrix");
		int a[][] = new int[m][n];
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				a[i][j] = in.nextInt();

		System.out.println("Matrix" + "[" + m + "]" + "[" + n + "]");
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				System.out.println(a[i][j] + "\t");

		System.out.println("Enter the row X Column of the second matrix");
		p = in.nextInt();
		q = in.nextInt();

		if (m != q) {
			System.out.println("Matrices can't be muliplied");
		} else {
			System.out.println("Enter the Elements of first matrix");
			int b[][] = new int[p][q];
			for (int i = 0; i < p; i++)
				for (int j = 0; j < q; j++)
					b[i][j] = in.nextInt();
			System.out.println("Matrix" + "[" + p + "]" + "[" + q + "]");
			for (int i = 0; i < p; i++)
				for (int j = 0; j < q; j++)
					System.out.println(b[i][j] + "\t");
			in.close();
			System.out.println("Multipling...");
			int c[][] = new int[m][q];
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < m; j++) {
					for (int k = 0; k < p; k++) {
						sum = sum + a[i][k] * b[k][j];
					}
					c[i][j] = sum;
					sum = 0;
				}
			}
			System.out.println("The Result Matrix is \n");
			for (int i = 0; i < p; i++)
				for (int j = 0; j < q; j++)
					System.out.println(c[i][j] + "\t");

		}

	}

}