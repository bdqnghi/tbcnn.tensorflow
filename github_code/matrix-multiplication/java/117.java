/*
 * File Name : Matrix.java
 * Short Description : This java code does all different operations on a matrix
 * Version Number : 1.0
 * Created Date : 04/24/2016
 */


import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;


/**
 * This class has methods which does different operations on matrix
 * 
 * @author Rayyan Mohammed Jaweed
 * @version 1.0
 */
public class Matrix {

	/**
     * This method generates a random matrix of size n by n
     * @param n
     * 		denotes the size of the square matrix
     * @return matrix
     * 		returns the random generated matrix
     */
	public int[][] matrixInit(int n){
		int[][] matrix = new int[n][n];
		for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
              double a=Math.random();
              matrix[i][j] =(int)(a*500);
            }
		}
		return matrix;
	}
	
	/**
     * This method reads a matrix from a file
     * @param file
     * 		the file from where the matrix is to be read
     * @return matrix
     * 		the matrix which is read from the file
     */
	public int[][] matrixReader(File file) throws IOException{
		int size = countLines(file);
		int[][] matrix = new int[size][size];
		try (BufferedReader br = new BufferedReader(new FileReader(file))) {
		    String line;
		    for(int i=0 ; i<size ; i++){
		    	if( (line = br.readLine()) != null){
		    		String temp[] = line.split("\\s+");
			    	for(int j=0 ; j<temp.length ; j++){
			    		matrix[i][j] = Integer.parseInt(temp[j]);
			    	}
		    	}
		    }
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return matrix;
	}
	
	/**
     * This method counts the number of lines inside a file.
     * This method is used only by the method matrixReader() method.
     * @param filename
     * 		the file from the number of lines are to be counted
     * @return count
     * 		the number of lines in the file
     */
	public int countLines(File filename) throws IOException {
	    InputStream is = new BufferedInputStream(new FileInputStream(filename));
	    try {
	        byte[] c = new byte[1024];
	        int count = 0;
	        int readChars = 0;
	        boolean empty = true;
	        while ((readChars = is.read(c)) != -1) {
	            empty = false;
	            for (int i = 0; i < readChars; ++i) {
	                if (c[i] == '\n') {
	                    ++count;
	                }
	            }
	        }
	        return (count == 0 && !empty) ? 1 : count;
	    } finally {
	        is.close();
	    }
	}
	
	/**
     * This method pushes a matrix to a file
     * @param matrix
     * 		the matrix which is to be pushed into the file
     * @param file
     * 		the file where the matrix is to be pushed
     */
	public void pushToFile(int [][] matrix, File file){
		try {
			
			FileWriter fw = new FileWriter(file.getAbsoluteFile());
			BufferedWriter bw = new BufferedWriter(fw);
			int size = matrix.length;
			for(int i = 0 ; i<size ; i++){
				for(int j = 0 ; j<size ; j++){
					bw.write(matrix[i][j] + "\t");
				}
				bw.newLine();
			}
			bw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	/**
     * This method prints a matrix to the output screen
     * @param matrix
     * 		the matrix which is to be printed to the output screen
     */
	public void printMatrix(int[][] matrix){
		int size = matrix.length;
		for(int i=0 ; i<size ; i++){
			for(int j=0 ; j<size ; j++){
				System.out.print(matrix[i][j] + "\t");
			}
			System.out.println();
		}
	}
	
	/**
     * This method compares two matrices and returns true if they are same and false if they are not same.
     * @param A
     * 		the first matrix
     * @param B
     * 		the second matrix
     * @return isSame
     * 		true if the two matrices are same,
     * 		false if the two matrices are not same
     */
	public boolean compareMatrices(int[][] A, int[][] B) {
		boolean isSame = false;
		int size = A.length;
		for(int i=0 ; i<size ; i++){
			for(int j=0 ; j<size ; j++){
				if(A[i][j] == B[i][j]){
					isSame = true;
				}else{
					isSame = false;
					return isSame;
				}
			}
		}
		return isSame;
	}
	
	//Please change the values for size and noOfCores and run the main method
	public static void main(String[] args) {
		int size =2000;
		int noOfCores = 4;
		int [][] A = new int[size][size];
		int [][] B = new int[size][size];
		//Product of Basic Matrix Multiplication Method
		int [][] C = new int[size][size];
		//Product of Static Scheduling Matrix Multiplication Method
		int [][] C2 = new int[size][size];
		//Product of Dynamic Scheduling Matrix Multiplication Method
		int [][] C3 = new int[size][size];
		
		Matrix matrixOperator = new Matrix();
		
		//Create Random A Matrix
		A = matrixOperator.matrixInit(size);
		
		//Create Random B Matrix
		B = matrixOperator.matrixInit(size);
		
		//Basic Multiplication
		MatrixMultiplication basic = new MatrixMultiplication();
		long startTime = System.nanoTime();
		C = basic.multiplication(A, B);
		long timeConsumed = System.nanoTime() -startTime;
        System.out.println("Basic Multiplication Time : "+(timeConsumed/1000000)+ " milliseconds");
		
		//Static Scheduling Multiplication
		StaticScheduling staticSc = new StaticScheduling(A, B, noOfCores);
		try {
			startTime = System.nanoTime();
			C2 = staticSc.multiply();
			timeConsumed = System.nanoTime() -startTime;
			System.out.println("Static Scheduling Multiplication Time : "+(timeConsumed/1000000)+ " milliseconds");
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		//Dynamic Scheduling Multiplication
		DynamicScheduling dynamicSc = new DynamicScheduling(A, B,noOfCores);
		try {
			startTime = System.nanoTime();
			C3 = dynamicSc.multiply();
			timeConsumed = System.nanoTime() -startTime;
			System.out.println("Dynamic Scheduling Multiplication Time : "+(timeConsumed/1000000)+ " milliseconds");
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		boolean isSame = false;
		isSame = matrixOperator.compareMatrices(C, C2);
		System.out.println("C and C2 are same: " + isSame);
		
		isSame = matrixOperator.compareMatrices(C, C3);
		System.out.println("C and C3 are same: " + isSame);
		
	}

}
