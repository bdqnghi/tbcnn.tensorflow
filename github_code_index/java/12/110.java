package edu.seecs.lab1;

import java.util.*;
import java.lang.*;
import java.io.*;

/**
 * @author Manzar Ali
 *
 */

public class Matrix {

	private static int taA[][];
	private static int taB[][];
	
	
	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
		int input;
		System.out.println("***MATRIX COMPUTER***\nMenu:-\nPress 1 for Addition. 2 for Multiplication. 3 for Addition "
				+ "and multiplication");
		Scanner in = new Scanner(System.in);
		
		input = in.nextInt();
		System.out.println("You selected the option " +input +"\nSo performing the particular operation:");
		
		switch (input)
		{
		case 1:
			Addition(taA,taB);
			break;
		
		case 2:
			Multiplication(taA,taB);
			break;
			
		case 3:
			dualOperation(taA,taB);
			break;
		
		}
			

	}
	
	
	
public static void Addition(int[][] a, int[][] b) throws IOException

{
	String fileName = "sample.txt";
	readFile(fileName);
	
	int tms = a.length;
	int tmsB = b.length;
	if (tms != tmsB) {
		System.out.println("Matrix Size Mismatch");
	}

	float matrix[][] = new float[tms][tms];

	for (int i = 0; i < tms; i++)
		for (int j = 0; j < tms; j++) {
			matrix[i][j] = a[i][j] + b[i][j];
		}

	System.out.println("Result is of Addition is: "+ matrix);

}
	
public static  void Multiplication(int [][]a, int[][]b) throws Exception
	
{
	String fileName = "sample.txt";
	readFile(fileName);
	
	if(a[0].length != b.length)
		throw new Exception("Matrices incompatible for multiplication");
	float matrix[][] = new float[a.length][b[0].length];

	for (int i = 0; i < a.length; i++)
		for (int j = 0; j < b[i].length; j++)
			matrix[i][j] = 0;

	//cycle through answer matrix
	for(int i = 0; i < matrix.length; i++){
		for(int j = 0; j < matrix[i].length; j++){
			matrix[i][j] =calculateRowColumnProduct(a,i,b,j);
		}
		
	}
	System.out.println("Result of Multiplication is: "+matrix);
	
}

public static int calculateRowColumnProduct(int[][] A, int row, int[][] B, int col){
	float product = 0;
	for(int i = 0; i < A[row].length; i++)
		product +=A[row][i]*B[i][col];
	return (int) product;
}


public static void dualOperation(int [][]a, int [][]b) throws IOException

{
	String fileName = "sample.txt";
	readFile(fileName);
	int[][] matrix = {};
	//matrix = Addition(taA,taB) + Multiplication(taA,taB);
	System.out.println("Result of dual operations is:" +matrix);
}
	
public static void readFile(String fileName) throws IOException
{
    String line = "";

    FileInputStream inputStream = new FileInputStream(fileName);
    Scanner scanner = new Scanner(inputStream);
    DataInputStream in = new DataInputStream(inputStream);
    BufferedReader bf = new BufferedReader(new InputStreamReader(in));

    int lineCount = 0;
    String[] numbers;
 
    while ((line = bf.readLine()) != null)
    {
        numbers = line.split(" ");
        for (int i = 0; i < 3; i++)
        {
        double[][] matrix = {};
		matrix[lineCount][i] = Double.parseDouble(numbers[i]);
        }

        lineCount++;
    }
    bf.close();

}
	

}
