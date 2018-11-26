package de.lab4inf.wrb.matrix;

import java.util.ArrayList;

public class DivideNConquerMultiplier {
	
	public static Matrix multiply(Matrix A, Matrix B) throws IllegalArgumentException, RuntimeException {
		/*
		 * Fehlerbehandlung
		 */
		
		if(A.getM() == null || B.getM() == null)
			throw new IllegalArgumentException("Matrizen können nicht null sein");
		
		if(A.getCols() != B.getRows())
			throw new IllegalArgumentException("Matrizen sind nicht kompatibel für Matrix-Multiplication");
		
		/**
		 * Setup
		 */
		
		// Matrizen zunächst quadratisch machen, damit wir uns nicht mit ungeraden Größen rumschlagen müssen
		
		int n = Math.max(A.getRows(), B.getRows());
		int m;
		if(n%2 == 0)
			m = n;
		else
			m = n+1;
		
		Matrix APrep = new Matrix(m, m);
		Matrix BPrep = new Matrix(m, m);
		
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < m; j++) {
				APrep.set(i, j, A.get(i, j));
				BPrep.set(i, j, B.get(i, j));
			}
		}
		
		Matrix C = new Matrix(m, m);
		
		// Dann splitten
		
		Matrix[][] splitA = split(APrep);
		Matrix[][] splitB = split(BPrep);
		Matrix[][] splitC = split(C);
		Matrix[][][] temp = new Matrix[2][2][2];
		for(int i = 0; i < 2; i++)
			for(int j = 0; j < 2; j++)
				for(int k = 0; k < 2; k++)
					temp[i][j][k] = new Matrix(splitA[i][j].getRows(), splitB[i][j].getCols());
		
		ArrayList<MultiplyThread> mulThreads = new ArrayList<>();
		
		/**
		 * Paralleler 1. Teil 
		 */
		
		for(int j = 0; j < 2; j++) {
			for(int k = 0; k < 2; k++) {
				MultiplyThread thread1 = new MultiplyThread(splitA[j][0], splitB[0][k], temp[j][k][0]);
				MultiplyThread thread2 = new MultiplyThread(splitA[j][1], splitB[1][k], temp[j][k][1]);
				mulThreads.add(thread1);
				mulThreads.add(thread2);
				thread1.start();
				thread2.start();
			}
		}
		
		/**
		 * Zusammenführen 1. Teil
		 */
		
		for(MultiplyThread thread : mulThreads) {
			try {
				thread.join();
			} catch (InterruptedException e) {
				throw new RuntimeException("MultiplyThread got interrupted!");
			}
		}
		
		/**
		 * Paralleler 2. Teil
		 */
		
		ArrayList<AddThread> addThreads = new ArrayList<>();
		for(int j = 0; j < 2; j++) {
			for(int k = 0; k < 2; k++) {
				AddThread thread = new AddThread(temp[j][k][0], temp[j][k][1], splitC[j][k]);
				addThreads.add(thread);
				thread.start();
			}
		}
		
		/**
		 * Merge 2. Teil
		 */
		
		for(AddThread thread : addThreads) {
			try {
				thread.join();
			} catch (InterruptedException e) {
				throw new RuntimeException("AddThread got Interrupted");
			}
		}
		
		return merge(splitC);
	}
	
	/**
	 * Adds two matrices with the same dimensions
	 * @param A
	 * @param B
	 * @return
	 */
	@SuppressWarnings("unused")
	private static Matrix add(Matrix A, Matrix B) throws IllegalArgumentException {
		if(!(A.getRows() == B.getRows() && A.getCols() == B.getCols()))
			throw new IllegalArgumentException("Matrizen haben nicht die gleiche Größe!");
		
		Matrix res = new Matrix(A.getRows(), A.getCols());
		
		for(int i = 0; i < A.getCols(); i++) {
			for(int j = 0; j < A.getRows(); j++) {
				res.set(i, j, A.get(i, j) + B.get(i, j));
			}
		}
		
		return res;
	}
	
	/**
	 * Splits the Matrix A into 4 
	 * @param A
	 * @return
	 */
	public static Matrix[][] split(Matrix A) {
		Matrix[][] res = new Matrix[2][2];
		
		double[][] a = A.getM();
		
		int splitLength1 = a.length / 2 + (a.length % 2);
		int splitLength2 = a.length - splitLength1;
		
		double[][] a11 = new double[splitLength1][splitLength1];
		double[][] a12 = new double[splitLength1][splitLength2];
		double[][] a21 = new double[splitLength2][splitLength1];
		double[][] a22 = new double[splitLength2][splitLength2];
		
		for(int i = 0; i < a.length; i++) {
			for(int j = 0; j < a[0].length; j++) {
				if(i < splitLength1) 
					if(j < splitLength1)
						a11[i][j] = a[i][j];
					else
						a12[i][j - splitLength1] = a[i][j];
				else
					if(j < splitLength1)
						a21[i - splitLength1][j] = a[i][j];
					else
						a22[i - splitLength1][j - splitLength1] = a[i][j];
			}
		}
		res[0][0] = new Matrix(a11);
		res[0][1] = new Matrix(a12);
		res[1][0] = new Matrix(a21);
		res[1][1] = new Matrix(a22);
		
		return res;
	}
	
	/**
	 * Merges 4 to 1 matrix
	 * @param mat
	 * @return
	 */
	public static Matrix merge(Matrix[][] mat) {
		int rows = mat[0][0].getRows() + mat[1][0].getRows();
		int cols = mat[0][0].getCols() + mat[0][1].getCols();
		
		int splitLength1 = rows / 2;
		int splitLength2 = rows - splitLength1;
		
		double[][] res = new double[rows][cols];
		
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				if(i < splitLength1) 
					if(j < splitLength1)
						res[i][j] = mat[0][0].getM()[i][j];
					else
						res[i][j] = mat[0][1].getM()[i][j - splitLength1];
				else
					if(j < splitLength1)
						res[i][j] = mat[1][0].getM()[i - splitLength1][j];
					else
						res[i][j] = mat[1][1].getM()[i - splitLength1][j - splitLength1];
			}
		}
		
		return new Matrix(res);
	}
	
	/**
	 * Gibt für die gegebene Zahl die nächste Zweierpotenz
	 * @param n
	 * @return
	 */
	private static int nextPowerOfTwo(int n) {
		int log2 = (int) Math.ceil(Math.log(n) / Math.log(2));
		return (int) Math.pow(2, log2);
	}
	
	/**
	 * Thread für die 8 Multiplikationen
	 * @author Till Kobbe
	 *
	 */
	private static class MultiplyThread extends Thread {
		private final Matrix A;
		private final Matrix B;
		private Matrix C;
		
		public MultiplyThread(Matrix A, Matrix B, Matrix C) {
			this.A = A;
			this.B = B;
			this.C = C;
		}
		
		@Override
		public void run() {	
			if(C == null) {
				C = new Matrix(A.getRows(), B.getCols());
			}
			
			/*
			 * Code aus Serieller Multiplikation
			 */
			for(int rowA = 0; rowA < A.getRows(); rowA++) {
				for(int colB = 0; colB < B.getCols(); colB++) {
					double sum = .0;
					for(int colA = 0; colA < A.getCols(); colA++) {
						sum += A.get(rowA, colA) * B.get(colA, colB);
					}
					C.set(rowA, colB, sum);
				}
			}			
		}
	}
	
	/**
	 * Thread für das addieren der Matrizen
	 * @author Till Kobbe
	 *
	 */
	private static class AddThread extends Thread {
		private final Matrix A;
		private final Matrix B;
		private Matrix C;
		
		public AddThread(Matrix A, Matrix B, Matrix C) {
			this.A = A;
			this.B = B;
			this.C = C;
		}
		
		@Override
		public void run() {
			for(int i = 0; i < A.getCols(); i++) {
				for(int j = 0; j < A.getRows(); j++) {
					C.set(i, j, A.get(i, j) + B.get(i, j));
				}
			}
		}
	}
}
