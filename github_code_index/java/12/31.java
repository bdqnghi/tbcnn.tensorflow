/**
 * Multiply two matrix, using Strassen algorithms.
 * 
 * @author QingxiaoDong
 */

import java.io.*;

public class MatrixMultiplication {

	static int[][] multiply(int[][] matrix1, int[][] matrix2) {
		int size = matrix1.length;
		int[][] product = new int[size][size];
		if (size == 1) {
			product[0][0] = matrix1[0][0] * matrix2[0][0];
		} else if (size % 2 == 0) {
			int [][] a = new int[size/2][size/2];
			int [][] b = new int[size/2][size/2];
			int [][] c = new int[size/2][size/2];
			int [][] d = new int[size/2][size/2];
			int [][] e = new int[size/2][size/2];
			int [][] f = new int[size/2][size/2];
			int [][] g = new int[size/2][size/2];
			int [][] h = new int[size/2][size/2];
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (i < size / 2 & j < size / 2) {
						a[i][j] = matrix1[i][j];
						e[i][j] = matrix2[i][j];
					} else if (i < size / 2 && j >= size / 2) {
						b[i][j - size/2] = matrix1[i][j];
						f[i][j - size/2] = matrix2[i][j];
					} else if (i >= size / 2 && j < size / 2) {
						c[i - size/2][j] = matrix1[i][j];
						g[i - size/2][j] = matrix2[i][j];
					} else {
						d[i - size/2][j - size/2] = matrix1[i][j];
						h[i - size/2][j - size/2] = matrix2[i][j];
					}
				}
			}
			int[][] p1 = multiply(a, minus(f, h));
			int[][] p2 = multiply(add(a, b), h);
			int[][] p3 = multiply(add(c, d), e);
			int[][] p4 = multiply(d, minus(g, e));
			int[][] p5 = multiply(add(a, d), add(e, h));
			int[][] p6 = multiply(minus(b, d), add(g, h));
			int[][] p7 = multiply(minus(a, c), add(e, f));
			int[][] c1 = add(minus(add(p5, p4), p2), p6);
			int[][] c2 = add(p1, p2);
			int[][] c3 = add(p3, p4);
			int[][] c4 = minus(add(p1, p5), add(p3, p7));
			for (int i = 0; i < size/2; i++) {
				for (int j = 0; j < size/2; j++) {
					product[i][j] = c1[i][j];
					product[i][j + size/2] = c2[i][j];
					product[i + size/2][j] = c3[i][j];
					product[i + size/2][j + size/2] = c4[i][j];
				}
			}
		} else {
			int[][] copy1 = new int[size + 1][size + 1];
			int[][] copy2 = new int[size + 1][size + 2];
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					copy1[i][j] = matrix1[i][j];
					copy2[i][j] = matrix2[i][j];
				}
			}
			int[][] copy3 = multiply(copy1, copy2);
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					product[i][j] = copy3[i][j];
				}
			}
		}
		return product;
		
	}

	static int[][] add(int[][] matrix1, int[][] matrix2) {
		int size = matrix1.length;
		int[][] sum = new int[size][size]; 
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				sum[i][j] = matrix1[i][j] + matrix2[i][j];
			}
		}
		return sum;
	}
	
	static int[][] minus(int[][] matrix1, int[][] matrix2) {
		int size = matrix1.length;
		int[][] difference = new int[size][size]; 
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				difference[i][j] = matrix1[i][j] - matrix2[i][j];
			}
		}
		return difference;
	}
	
	static void print(int[][] matrix) {
		int size = matrix.length;
		for (int i = 0; i < size; i++) {
    		for (int j = 0; j < size; j++) {
    			System.out.printf("%4d", matrix[i][j]);
    		}
    		System.out.println();
    	}
	}
	
    public static void main(String[] args) throws FileNotFoundException {
    	int[][] first = {
    			{1, 1, 1},
    			{1, 1, 1},
    			{1, 1, 1}
    	};
    	int[][] second = {
    			{1, 2, 3, 4, 5},
    			{1, 1, 1, 1, 1},
    			{1, 1, 1, 1, 1},
    			{5, 4, 3, 2, 1},
    			{1, 1, 1, 1, 1}
    	};
    	int[][] test1 = multiply(first, first);
    	print(test1);
    	print(multiply(second, second));
    }
}