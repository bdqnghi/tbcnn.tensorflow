package ca.ualberta.cmput681.assignment1;

public class SequentialMatrixMultiplication extends MatrixMultiplication {

	static SequentialMatrixMultiplication matrixMultiplication;

	public static void main(String[] args) {
		int size = 0;
		int seed = 0;
		InitType initTypeA;
		InitType initTypeB;

		if (args.length != 4) {
			System.out
					.println("Usage: SequentialMatrixMultiplication <matrix_size> <random_seed> <type_matrix_A> <type_matrix_B>");
			System.exit(0);
		}

		size = Integer.parseInt(args[0]);
		seed = Integer.parseInt(args[1]);
		initTypeA = fromStringToInitType(args[2]);
		initTypeB = fromStringToInitType(args[3]);

		matrixMultiplication = new SequentialMatrixMultiplication();

		matrixMultiplication.init(size, seed, initTypeA, initTypeB);

		int n = matrixMultiplication.matrixA.length;
		int m = matrixMultiplication.matrixB.length;
		int p = matrixMultiplication.matrixB[0].length;

		long start = System.currentTimeMillis();

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < p; j++) {
				for (int k = 0; k < m; k++) {
					matrixMultiplication.matrixC[i][j] += matrixMultiplication.matrixA[i][k]
							* matrixMultiplication.matrixB[k][j];
				}
			}
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

}
