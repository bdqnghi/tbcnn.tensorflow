import java.util.*;
import java.io.*;

public  class MatrixMultiplication{
	public static void main(String[] args){
		int[][]  a = {{1,2,3,4},{4,5,6,7},{7,8,9,10},{11,12,13,14}};
		print(a);
		int[][] b ={{2,3,4,5},{5,6,7,8},{8,9,10,11},{11,12,13,14}};
		print(b);
		int[][]  c = classicalMultiply(a,b);
	}
	public static int[][] classicalAddition(int[][] a, int[][] b){
		int[][] result = new int[a.length][a.length];

		for(int i=0;i<a.length;i++){
			for(int j=0;j<a.length;j++){
				result[i][j] = a[i][j]+b[i][j];
			}
		}
		return result;
	}
	public static int[][] classicalMultiply(int[][] a, int[][] b){
		int[][] result = new int[a.length][b.length];
		for(int i=0;i<a.length;i++){	
			for(int j=0;j<a.length;j++){
				for(int k=0;k<a.length;k++){
					result[i][j]=result[i][j]+a[i][k]*b[k][j];
				}
			}
		}
		print(result);
		return result;
	}
	public static void print(int[][] mat){
		for(int i=0;i<mat.length;i++){
			for(int j=0;j<mat.length;j++){
				System.out.print(mat[i][j]+" ");
			}
			System.out.println();
		}
	}
	public static int[][] strassenMultiplication(int[][] a,int[][] b){
		int[][] result = new int[a.length][b.length];
		if(a.length<=2)
			result = classicalMultiply(a,b);
		else{
			int[][] a11 = new int[a.length/2][b.length/2];
		}
	}
}
