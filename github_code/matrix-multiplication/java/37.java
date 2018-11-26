package ca.ualberta.cmput681.assignment1;

public class ParallelMatrixMultiplication extends MatrixMultiplication {

	private static ParallelMatrixMultiplication matrixMultiplication;
	private static Thread[] threads;

	public static void main(String[] args) {
		int size = 0;
		int seed = 0;
		InitType initTypeA;
		InitType initTypeB;

		if (args.length != 4) {
			System.out
					.println("Usage: ParallelMatrixMultiplication <matrix_size> <random_seed> <type_matrix_A> <type_matrix_B>");
			System.exit(0);
		}

		size = Integer.parseInt(args[0]);
		seed = Integer.parseInt(args[1]);
		initTypeA = fromStringToInitType(args[2]);
		initTypeB = fromStringToInitType(args[3]);

		matrixMultiplication = new ParallelMatrixMultiplication();

		matrixMultiplication.init(size, seed, initTypeA, initTypeB);

		int n = matrixMultiplication.matrixA.length;
		int p = matrixMultiplication.matrixB[0].length;

		threads = new Thread[n * p];

		long start = System.currentTimeMillis();

		// create threads
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < p; j++) {
				MatrixMultiplier mm = new MatrixMultiplier(i, j);
				threads[(i * n) + j] = new Thread(mm);
			}
		}

		// run threads
		for (int i = 0; i < threads.length; i++) {
			threads[i].start();
		}

		// join threads
		try {
			for (int i = 0; i < threads.length; i++) {
				threads[i].join();
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		long end = System.currentTimeMillis();

		if (matrixMultiplication.matrixC.length < 10) {
			matrixMultiplication.printMatrix("C", matrixMultiplication.matrixC);
		}

		System.out.println("Total time: " + (end - start) + " ms.");

	}

	public static int[][] getResult() {
		return matrixMultiplication.matrixC;
	}

	public static int[][] getMatrixA() {
		return matrixMultiplication.matrixA;
	}

	public static int[][] getMatrixB() {
		return matrixMultiplication.matrixB;
	}

	static class MatrixMultiplier implements Runnable {

		private final int row;
		private final int col;

		public MatrixMultiplier(int i, int j) {
			this.row = i;
			this.col = j;
		}

		@Override
		public void run() {
			int result = 0;

			for (int i = 0; i < matrixMultiplication.matrixB.length; i++) {
				result += matrixMultiplication.matrixA[row][i]
						* matrixMultiplication.matrixB[i][col];
			}

			matrixMultiplication.matrixC[row][col] = result;
		}
	}
}
