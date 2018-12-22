/* Victor Mao (vtm160030)
 * CS 2336.003 HW 3 Problem 1
 * #8.6, pg. 307
 * Multiply two 3x3 matrices together and display the result.
 */

import java.util.Scanner;
import java.text.DecimalFormat;

public class MatrixMultiplication
{
	public static void main(String[] args)
	{
		// Initialize Scanner and matrices
		Scanner scan = new Scanner(System.in);
		double[][] matrix1 = new double[3][3];
		double[][] matrix2 = new double[3][3];
		
		// Read user input
		System.out.print("Enter matrix 1: ");
		for (int i=0; i<3; i++)
		{
			for (int j=0; j<3; j++)
				matrix1[i][j] = scan.nextDouble();
		}
		System.out.print("Enter matrix 2: ");
		for (int i=0; i<3; i++)
		{
			for (int j=0; j<3; j++)
				matrix2[i][j] = scan.nextDouble();
		}
		
		double[][] answer = multiplyMatrix(matrix1, matrix2);
		
		// Print answer
		System.out.println("The multiplication of the matrices is ");
		printAnswer(matrix1, matrix2, answer);
		
		// Close scanner
		scan.close();	
	}
	
	// Return the matrix multiplication of two 3x3 matrices
	public static double[][] multiplyMatrix(double[][] a, double[][] b)
	{
		double[][] answer = new double[3][3];
		for (int i=0; i<3; i++)
		{
			for (int j=0; j<3; j++)
				answer[i][j] = (a[i][0]*b[0][j])+(a[i][1]*b[1][j])+(a[i][2]*b[2][j]); // matrix multiplication
		}
		return answer;
	}
	
	// Print a formatted equation
	public static void printAnswer(double[][] m1, double[][] m2, double[][] a)
	{
		DecimalFormat df = new DecimalFormat("0.##");		
		
		// Print first row
		System.out.print(df.format(m1[0][0]) + "\t" + df.format(m1[0][1]) + "\t" + df.format(m1[0][2]));
		System.out.print("\t\t");
		System.out.print(df.format(m2[0][0]) + "\t" + df.format(m2[0][1]) + "\t" + df.format(m2[0][2]));
		System.out.print("\t\t");
		System.out.println(df.format(a[0][0]) + "\t" + df.format(a[0][1]) + "\t" + df.format(a[0][2]));
		
		// Print second row		
		System.out.print(df.format(m1[1][0]) + "\t" + df.format(m1[1][1]) + "\t" + df.format(m1[1][2]));
		System.out.print("\t*\t");
		System.out.print(df.format(m2[1][0]) + "\t" + df.format(m2[1][1]) + "\t" + df.format(m2[1][2]));
		System.out.print("\t=\t");
		System.out.println(df.format(a[1][0]) + "\t" + df.format(a[1][1]) + "\t" + df.format(a[1][2]));
		
		// Print third row
		System.out.print(df.format(m1[2][0]) + "\t" + df.format(m1[2][1]) + "\t" + df.format(m1[2][2]));
		System.out.print("\t\t");
		System.out.print(df.format(m2[2][0]) + "\t" + df.format(m2[2][1]) + "\t" + df.format(m2[2][2]));
		System.out.print("\t\t");
		System.out.println(df.format(a[2][0]) + "\t" + df.format(a[2][1]) + "\t" + df.format(a[2][2]));
	}
}