package matrix_test;

import java.util.Scanner;

import print_api.r;

public class MatrixMultiplication {
	

	public static double[][] minus(double a[][], double[][] b) {
		int ar = a.length;
		int ac = a[0].length;
		
		int bc = b[0].length;
		int br = b.length;
		
		if (ar == br && ac == bc) {
			
		}
		else {
			System.out.println ("minus Matrix not seem size " + ar + ":" + ac + " .. " + br + ":" + bc);
			return null;
		}
		
		double tmp[][] = new double[ar][ac];
		
		for (int i = 0 ; i < ar ; i ++ ) {
			for (int j = 0 ; j < ac ; j ++ ) {
				tmp[i][j] = a[i][j] - b[i][j];
				
			}
		}
		
		return tmp;
	}
	
	public static double[][] plus(double a[][], double[][] b) {
		int ar = a.length;
		int ac = a[0].length;
		
		int bc = b[0].length;
		int br = b.length;
		
		if (ar == br && ac == bc) {
			
		}
		else {
			System.out.println ("plus Matrix not seem size " + ar + ":" + ac + " .. " + br + ":" + bc);
			return null;
		}
		
		double tmp[][] = new double[ar][ac];
		
		for (int i = 0 ; i < ar ; i ++ ) {
			for (int j = 0 ; j < ac ; j ++ ) {
				tmp[i][j] = a[i][j] + b[i][j];
				
			}
		}
		
		return tmp;
	}

	public static double[][] dot(double a[][], double[][] b) {

		int ar = a.length;
		int bc = b[0].length;
		int br = b.length;

		double[][] multiply = MatrixMultiplication.newMatrix(ar, bc);

		double sum = 0;

		for (int c = 0; c < ar; c++)
			for (int d = 0; d < bc; d++) {
				for (int k = 0; k < br; k++)
					sum = sum + (a[c][k] * b[k][d]);

				multiply[c][d] = sum;
				sum = 0;
			}

		return multiply;
	}

	public static void main(String args[]) {
		MatrixMultiplication.test2();
	}

	public static double[][] newMatrix(int x, int y) {
		double[][] tmp;
		tmp = new double[x][];
		for (int lop = 0; lop < x; lop++)
			tmp[lop] = new double[y];

		return tmp;
	}

	public static void test1() {
		int m, n, p, q, sum = 0, c, d, k;

		Scanner in = new Scanner(System.in);
		System.out.println("Enter the number of rows and columns of first matrix");
		m = in.nextInt();
		n = in.nextInt();

		int first[][] = new int[m][n];

		System.out.println("Enter the elements of first matrix");

		for (c = 0; c < m; c++)
			for (d = 0; d < n; d++)
				first[c][d] = in.nextInt();

		System.out.println("Enter the number of rows and columns of second matrix");
		p = in.nextInt();
		q = in.nextInt();

		if (n != p)
			System.out.println("Matrices with entered orders can't be multiplied with each other.");
		else {
			int second[][] = new int[p][q];
			int multiply[][] = new int[m][q];

			System.out.println("Enter the elements of second matrix");

			for (c = 0; c < p; c++)
				for (d = 0; d < q; d++)
					second[c][d] = in.nextInt();

			for (c = 0; c < m; c++)
				for (d = 0; d < q; d++) {
					for (k = 0; k < p; k++)
						sum = sum + (first[c][k] * second[k][d]);

					multiply[c][d] = sum;
					sum = 0;
				}

			System.out.println("Product of entered matrices:-");

			for (c = 0; c < m; c++) {
				for (d = 0; d < q; d++)
					System.out.print(multiply[c][d] + "\t");

				System.out.print("\n");
			}
		}
	}

	public static void test2() {
		double a[][] = MatrixMultiplication.newMatrix(3, 3);
		double b[][] = MatrixMultiplication.newMatrix(3, 3);

		a[0][0] = 1;
		a[0][1] = 2;
		a[0][2] = 3;

		a[1][0] = 4;
		a[1][1] = 5;
		a[1][2] = 6;
		
		a[2][0] = 7;
		a[2][1] = 8;
		a[2][2] = 9;

		b[0][0] = 9;
		b[0][1] = 8;
		b[0][2] = 7;

		b[1][0] = 6;
		b[1][1] = 5;
		b[1][2] = 4;

		b[2][0] = 3;
		b[2][1] = 2;
		b[2][2] = 1;

		double c[][] = MatrixMultiplication.dot(a, b);

		r.pl("...");

	}
}
