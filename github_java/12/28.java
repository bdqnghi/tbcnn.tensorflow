package ca.ualberta.cmput681.assignment1;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class CoarserGrainedThreadPoolMatrixMultiplication extends
		MatrixMultiplication {

	static CoarserGrainedThreadPoolMatrixMultiplication matrixMultiplication;

	public static void main(String[] args) {
		int size = 0;
		int seed = 0;
		InitType initTypeA;
		InitType initTypeB;

		if (args.length < 4 || args.length > 5) {
			System.out
					.println("Usage: ThreadPoolHighGranularityMatrixMultiplication <matrix_size> <random_seed> <type_matrix_A> <type_matrix_B> [<num_threads>]");
			System.exit(0);
		}

		size = Integer.parseInt(args[0]);
		seed = Integer.parseInt(args[1]);
		initTypeA = fromStringToInitType(args[2]);
		initTypeB = fromStringToInitType(args[3]);

		int numProcessors = Runtime.getRuntime().availableProcessors();
		if (args.length == 5) {
			numProcessors = Integer.parseInt(args[4]);
		}

		System.out
				.println("Executing coarse grained thread pool matrix multiplication with "
						+ numProcessors + " threads");

		matrixMultiplication = new CoarserGrainedThreadPoolMatrixMultiplication();

		matrixMultiplication.init(size, seed, initTypeA, initTypeB);

		long start = System.currentTimeMillis();

		// create thread pool
		ExecutorService executor = Executors.newFixedThreadPool(numProcessors);

		int chunkSize = (int) Math.floor(size / numProcessors);
		for (int i = 0; i < numProcessors; i++) {
			int startRow = chunkSize * i;
			int endRow = (chunkSize * (i + 1)) - 1;

			if (i == numProcessors-1) {
				endRow = size - 1;
			}

			executor.execute(new MatrixMultiplier(startRow, endRow));
		}
		executor.shutdown();
		try {
			executor.awaitTermination(Long.MAX_VALUE, TimeUnit.SECONDS);
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

		private final int startRow;
		private final int endRow;

		public MatrixMultiplier(int start, int end) {
			this.startRow = start;
			this.endRow = end;
		}

		@Override
		public void run() {
			int result;

			for (int row = startRow; row <= endRow; row++) {
				for (int col = 0; col < matrixMultiplication.matrixB[0].length; col++) {
					result = 0;

					for (int i = 0; i < matrixMultiplication.matrixB.length; i++) {
						result += matrixMultiplication.matrixA[row][i]
								* matrixMultiplication.matrixB[i][col];
					}

					matrixMultiplication.matrixC[row][col] = result;
				}
			}
		}
	}
}
