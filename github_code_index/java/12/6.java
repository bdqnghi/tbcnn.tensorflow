package chapter4;

import java.util.Arrays;

public class SimpleMatrixMultiplication {
	public static void main(String[] args){
		int[][] a = {{1,3,2},{1,0,0},{1,2,2}};
		int[][] b = {{0,0,2},{7,5,0},{2,1,1}};
		multiplication(a,b);
		
	}
	private static int[][] multiplication(int[][] a, int[][] b){
		int[][] c = new int[3][3];
		
		if(a[0].length!=a.length||a[0].length!=b[0].length||b[0].length!=b.length){
			return null;
		}
		int n = a[0].length;
		
		for(int i=0; i<n; i++){
			for(int j=0;j<n;j++){
				c[i][j] = 0;
				for(int k=0; k<n;k++){
					c[i][j] += a[i][k] * b[k][j];
				}
				
			}
		}
		for(int i=0; i<n; i++){
			for(int j=0;j<n;j++){
				System.out.print(c[i][j] + " ");				
			}
			System.out.println();
		}
		
		return c;
	}

}
