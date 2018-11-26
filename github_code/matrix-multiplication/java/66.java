package ca.mcgill.ecse420.a1;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MatrixMultiplication {

	private static final int MATRIX_SIZE = 1000;

	public static void main(String[] args) {
		
		// Generate two random matrices, same size
		double[][] a = generateRandomMatrix(MATRIX_SIZE, MATRIX_SIZE);
		double[][] b = generateRandomMatrix(MATRIX_SIZE, MATRIX_SIZE);


		// 1.4 Plot thread performance starting at 1 thread, go to 10
		System.out.println("Times:");
		for(int i = 1; i < 11; i++){
			System.out.println(timeParallelMultiplication(a, b, i));
		}

		// 1.5 Plot matrix sizes and compare sequential and top performing thread count in parallel
		int bestTreads = 3;
		int[] sizes = {100, 200, 500, 1000, 2000};
		for(int i = 0; i < sizes.length; i++){
			double[][] a_i = generateRandomMatrix(sizes[i], sizes[i]);
			double[][] b_i = generateRandomMatrix(sizes[i], sizes[i]);
			System.out.println(timeSequentialMultiplication(a_i, b_i));
			System.out.println(timeParallelMultiplication(a_i, b_i, bestTreads));
		}

	}

	private static double timeParallelMultiplication(double[][]a, double[][]b, int threads){
		// 1. Get the time
		long startTime = System.nanoTime();

		// 2. Multiple in parallel
		parallelMultiplyMatrix(a, b, threads);

		// 3. Get another time
		long endTime = System.nanoTime();

		// 4. Return the difference (divide by 1,000,000,000)
		return (endTime - startTime)/(1000000000.0);
	}

	private static double timeSequentialMultiplication(double[][]a, double[][]b){
		// 1. Get the time
		long startTime = System.nanoTime();

		// 2. Multiple in sequential
		sequentialMultiplyMatrix(a, b);

		// 3. Get another time
		long endTime = System.nanoTime();

		// 4. Return the difference (divide by 1,000,000,000)
		return (endTime - startTime)/(1000000000.0);
	}

	// This method prints a matrix
	public static void printMatrix(double[][] m){
		for(int i = 0; i < m.length; i++){
			for(int j = 0; j < m.length; j++) {
				System.out.print(m[i][j] + " ");
			}
			System.out.println("");
		}
	}
	
	/**
	 * Returns the result of a sequential matrix multiplication
	 * The two matrices are randomly generated
	 * @param a is the first matrix
	 * @param b is the second matrix
	 * @return the result of the multiplication
	 * */
	public static double[][] sequentialMultiplyMatrix(double[][] a, double[][] b) {
		//Define output matrix
		double result[][] = new double[a.length][b.length];         //assuming square !!!

		//iterate through rows of matrix a and columns of matrix b
		for(int row_i = 0; row_i < a.length; row_i++){
			for(int col_i=0; col_i < b.length; col_i++){            //assuming square !!!
				//retrieve the column array for col_i of matrix b
				double[] column = getColumnArray(col_i, b);

				//retrieve the row matrix a we are multiplying
				double[] row = a[row_i];

				result[row_i][col_i] = calculateCell(row, column);
			}
		}

		return result;
	}
	
	/**
	 * Returns the result of a concurrent matrix multiplication
	 * The two matrices are randomly generated
	 * @param a is the first matrix
	 * @param b is the second matrix
	 * @return the result of the multiplication
	 * */
    public static double[][] parallelMultiplyMatrix(double[][] a, double[][] b, int threads) {
		// 1. Define the result and the thread-pool
        double result[][] = new double[a.length][b[0].length];
        ExecutorService executor = Executors.newFixedThreadPool(threads);

        int MATRIX_CELL_COUNT = (a.length)*(b[0].length);

        // 2. Launch all the threads and ___
        for(int i = 0; i < threads; i++){
        	// If you're on the remainder thread, just
        	if(MATRIX_CELL_COUNT % threads != 0 && i == threads - 1){
        		executor.execute(new ParallelMultiplication(result, i*(MATRIX_CELL_COUNT/threads), MATRIX_CELL_COUNT, a, b));
			}else{
				executor.execute(new ParallelMultiplication(result, i*(MATRIX_CELL_COUNT/threads), (i+1)*(MATRIX_CELL_COUNT/threads), a, b));
			}
		}

		// 3. Shutdown each thread from pool
		executor.shutdown();

		// 4. Wait until the pool is down
        while(!executor.isTerminated()){ }

		// 5. Return the result
        return result;
    }

    public static class ParallelMultiplication implements Runnable{
    	private double[][] result;
    	private int startRowA;
		private int endRowA;
		private double[][] a;
		private double[][] b;

		public ParallelMultiplication(double[][] result, int startRowA, int endRowA, double[][] a, double[][] b){
			this.result = result;
			this.startRowA = startRowA;
			this.endRowA = endRowA;
			this.a = a;
			this.b = b;
		}

		// Each thread takes a chunk of cells and calculates their value
		@Override
		public void run() {
			// For each cell
			for(int iter = startRowA; iter < endRowA; iter++){
				// Get the row
				int i = iter / result[0].length; 		// Cell # floor divided by row length gives you row # (row)
				double[] row = a[i]; 					// Set the row #

				// Get the column
				int j = iter % result[0].length;		// Cell # modded by row length gives you column index (col)
				double[] col = getColumnArray(j, b);	// Set col to it's fetched column index

				// Calculate and set the cell
				result[i][j] = calculateCell(row, col);
			}
		}
	}

    /**
     * Populates a matrix of given size with randomly generated integers between 0-10.
     * @param numRows number of rows
     * @param numCols number of cols
     * @return matrix
     */
    private static double[][] generateRandomMatrix (int numRows, int numCols) {
        double matrix[][] = new double[numRows][numCols];
        for (int row = 0 ; row < numRows ; row++ ) {
            for (int col = 0 ; col < numCols ; col++ ) {
                matrix[row][col] = (double) ((int) (Math.random() * 10.0));
            }
        }
        return matrix;
    }

	/* This method takes a column index (j) and matrix then return the column as an array */
	// 1. Define an output array equal to the number of rows
	// 2. Iterate through every row - populating array
	// 3. Return the array
    private static double[] getColumnArray(int j, double[][] matrix){
		// 1. Define an output array equal to the number of rows
		double column[] = new double[matrix.length];

		// 2. Iterate through every row - populating array
		for(int iter = 0; iter < matrix.length; iter++){
			column[iter] = matrix[iter][j];
		}

		// 3. Return the array
        return column;
	}

    /* This method takes a row array and a column array and returns a cell post matrix multiplication */
	// 1. Set a sum to zero
	// 2. Iterate through the length of row/column
	// 3. Return the final answer
    private static double calculateCell (double[] row, double[] column) {
		// 1. Set a sum to zero
		double cell = 0.0;

		// 2. Iterate through the length of row/column
		for(int iter = 0; iter < row.length; iter++){
			cell += row[iter] * column[iter];
		}

		// 3. Return the final answer
		return cell;
	}

}
