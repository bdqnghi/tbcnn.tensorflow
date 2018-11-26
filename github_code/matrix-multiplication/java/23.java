package com.java.matrix;

public class Matrixmultiplication {

	public static void main(String args[]) {
		int a[][] = { { 1, 2, 3 }, 
				      { 4, 5, 6 } }; // sample 2x3 matrix

		int b[][] = { { 1, 2, -2 }, 
				      { -1, -2, -3 }, 
				      { 5, 6, 9 } }; // sample 3x3
																	// matrix

		multiplymatrices(a, b);

	}

	public static void multiplymatrices(int[][] mat1, int[][] mat2) {
		int column = mat1[0].length;
		int rows = mat2.length;

		if (column != rows) {
			System.out.println("Multiplication is not possible");
			return;
		}

		int mat3[][] = new int[mat1.length][mat2[0].length];

		for (int i = 0; i < mat1.length; i++) {
			for (int j = 0; j < mat2[0].length; j++) {
				for (int k = 0; k < mat2.length; k++) {/*can be mat1[0].length or mat2.lentgh it signifies column for matrix 1
					                                   and row for matrix 2 which is the common value for matrix multiplication*/
					mat3[i][j] += mat1[i][k] * mat2[k][j];
				}
				System.out.print(mat3[i][j] + " "); // printing matrix element
			}
			System.out.println();
		}

	}
}
