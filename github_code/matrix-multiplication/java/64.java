package caching;

public class MatrixMultiplication implements Runnable {
	
	private static int SIZE;
	int fromRow;
	int toRow;
	private static double[][] A;
	private static double[][] B;
	private static double[][] C;
	
	
	MatrixMultiplication() {
		this.fromRow = 0;
		this.toRow = SIZE;
	}
	
	MatrixMultiplication(int fromRow, int toRow) {
		this.fromRow = fromRow;
		this.toRow = toRow;
	}
	
	public void run() {
		for (int i = fromRow; i<toRow; i++) {
			for (int j = 0; j<SIZE; j++) {
				C[i][j] = 0;
				for (int k = 0; k<SIZE; k++) {
					C[i][j] += A[i][k] * B[k][j];
				}
			}
			
		}
	}
	
	public static void initializeMatrices() {
		for (int i = 0; i<SIZE; i++) {
			for (int j = 0; j<SIZE; j++) {
				A[i][j] = 1;
				B[i][j] = 2;
			}
		}
	}

	public static void printResult() {
		for (int i = 0; i<SIZE; i++) {
			for (int j = 0; j<SIZE; j++) {
				System.out.print(C[i][j] + " ");
			}
			System.out.println();
		}
	}
	
	public static void printResult(int s, int e) {
		for (int i = 0; i<s; i++) {
			for (int j = 0; j<e; j++) {
				System.out.print(C[i][j] + " ");
			}
			System.out.println();
		}
	}
	
	private static void mainx(String[] args) {
		
		if (args.length != 2) {
			System.err.println("Syntax error: java MatrixMultiplication <size> <threads>");
			System.exit(-1);
		}
		
		SIZE = Integer.parseInt(args[0]);
		int threadNum = Integer.parseInt(args[1]);
		
		A = new double[SIZE][SIZE];
		B = new double[SIZE][SIZE];
		C = new double[SIZE][SIZE];
		initializeMatrices();
		
		Thread[] threads = new Thread[threadNum];
		int quanto = SIZE / threadNum;
		for (int i =0 ; i<threadNum; i++) {
			if (i != threadNum-1) {
				threads[i] = new Thread(new MatrixMultiplication(i*quanto, (i+1)*quanto));
			} else {
				threads[i] = new Thread(new MatrixMultiplication(i*quanto, SIZE));
			}
		}
		
		for (int i =0 ; i<threadNum; i++) {
			threads[i].start();
		}
		try {
			for (int i =0 ; i<threadNum; i++) {
				threads[i].join();
			}
		} catch(InterruptedException e) {
			
		}
		
//		printResult();		
	}
	
	public static void main(String[] args) {
		
		long start = System.nanoTime();
		mainx(args);
		long end = System.nanoTime();
		System.out.println((double)( end - start ) / 1000000000.0);

		
		
	}

}
 
