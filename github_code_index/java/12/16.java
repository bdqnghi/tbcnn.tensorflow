


import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.StringTokenizer;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/*
 * Main idea: if we have M multiplications to be performed, and we have N threads, then each thread
 * will perform floor(M/N) multiplications, and we will have M%N threads performing one additional multiplication
 * We need synchronization because according to this scheme more than one thread can be working on the same output cell
 * so we will have a lock associated with each cell.
 * 
 * We could have made it in another way: each thread takes whole number of cells completely devoted 
 * to this thread .So if we have M cells, then again each thread will take floor(M/N) cells and M%N threads will
 * take extra cell, this is less fare than the previous strategy because the unfairness is a whole cell multiplications
 * while in the previous it was just 1 additional multiplication, but this latter strategy is better regarding 
 * synchronization, because each cell is written by only one thread so no locks or synchronization is needed at all.
 * 
 * So this is a trade off between fairness and sync overhead , I chose the first strategy.
 * 
 * One point needed to be say: It is not specified what is the limit of the number of threads. 
 * If this number <= the number of cells , then if we used the first strategy, we will have at most two threads writing
 * to the same cell, and since the writing of each thread occur only once, the overhead due to sync is negligible .
 * However if the number of threads is more than the number of cells, then if we used the second strategy, we will not
 * use more than (the number of cells) many threads, so some threads will just be ignored "not created". But if we
 * used the second strategy, then we can use up to the (total number of multiplications) many threads. Of course the
 * amount of overhead due to sync will increase.
 * 
 * And since it is not clear what is the limit of N, this also encouraged me to use the second strategy as it allowed 
 * a larger number of threads to work.But in normal work I may chose the second strategy and limit the number of threads
 * to be less than the number of cells.Anyway this depends on the requirements and whether the programmer is 
 * allowed to manipulate the parameters given to optimize the task or he has to stick to them.
 */
public class Matrix {

	// Total number of scalar multiplications to be performed
	static int totalMult;
	// floor(totalMult/number of threads)
	static int threadMult;
	// totalMult mod number of threads
	static int rem;
	// lock for each cell in the output matrix
	static Lock locks[][];
	// output matrix
	static int[][] c;
	// First input matrix
	static int[][] a;
	// First output matrix
	static int[][] b;
	// second dimension of the first matrix (and hence the first dimension in
	// the second matrix)
	static int width;

	public static void multiply(int[][] _a, int[][] _b, int N) {
		a = _a;
		b = _b;
		c = new int[a.length][b[0].length];
		locks = new ReentrantLock[a.length][b[0].length];
		for (int i = 0; i < a.length; i++)
			for (int j = 0; j < b[0].length; j++)
				locks[i][j] = new ReentrantLock();
		width = a[0].length;
		totalMult = a.length * a[0].length * b[0].length;
		// If the number of threads is more than the number of scalar
		// multiplications, there is no use/*
		N = Math.min(N, totalMult);
		threadMult = totalMult / N;
		rem = totalMult % N;
		// We will have "rem" threads performing threadMult+1 multiplications,
		// And "(N-rem)" performing threadMult multiplication
		for (int i = 1; i <= N; i++)
			new MatrixThread(i).run();
	}

	/*
	 * Performs the sequential matrix multiplication algorithm, just for
	 * comparison purpose
	 */
	public static int[][] sequentialMultiply(int[][] a, int[][] b) {
		int[][] c = new int[a.length][b[0].length];
		for (int i = 0; i < c.length; i++)
			for (int j = 0; j < c[0].length; j++)
				for (int k = 0; k < a[0].length; k++)
					c[i][j] += a[i][k] * b[k][j];
		return c;
	}

	/*
	 * compares two 2d matrices
	 */
	public static boolean equals(int[][] a, int[][] b) {
		for (int i = 0; i < c.length; i++)
			if (!Arrays.equals(a[i], b[i]))
				return false;
		return true;
	}

	/*
	 * Prints the data in the matrix
	 */
	public static void printMatrix(int[][] a) {
		for (int i = 0; i < a.length; i++)
			for (int j = 0; j < a[0].length; j++)
				System.out.print(a[i][j] + (j == a[0].length - 1 ? "\n" : " "));
	}

	private static int rand() {
		return (int) (60 * (Math.random() + 1));
	}

	public static void writeTestData() throws IOException {
		BufferedWriter writer = new BufferedWriter(new FileWriter(
				"MatrixIn.txt"));
		// Number of test cases
		int t = rand();
		writer.write(t + "\n");
		while (t-- > 0) {
			// Generate randomly the dimensions of the matrices
			int n = rand();
			int h = rand();
			int m = rand();
			writer.write(n + " " + h + " " + m + "\n");
			// Generate randomly the values of the first matrix
			for (int i = 0; i < n; i++)
				for (int j = 0; j < h; j++)
					writer.write(rand() + (j == h - 1 ? "\n" : " "));
			// Generate randomly the values of the second matrix
			for (int i = 0; i < h; i++)
				for (int j = 0; j < m; j++)
					writer.write(rand() + (j == m - 1 ? "\n" : " "));
			// Generate randomly the number of threads
			writer.write(Math.max(1, (int) (n * Math.random())) + "\n");
		}
		writer.close();
	}

	public static void main(String[] args) throws IOException {
		// Write test data
		writeTestData();
		BufferedReader st = new BufferedReader(new FileReader("MatrixIn.txt"));
		// Number of test cases
		int t = Integer.parseInt(st.readLine());
		while (t-- > 0) {
			StringTokenizer tok = new StringTokenizer(st.readLine());
			// read the three dimensions
			int s1 = Integer.parseInt(tok.nextToken());
			int s2 = Integer.parseInt(tok.nextToken());
			int s3 = Integer.parseInt(tok.nextToken());
			// Create the input matrices
			int[][] a = new int[s1][s2];
			int[][] b = new int[s2][s3];
			// read first matrix data
			for (int i = 0; i < s1; i++) {
				tok = new StringTokenizer(st.readLine());
				for (int j = 0; j < s2; j++)
					a[i][j] = Integer.parseInt(tok.nextToken());
			}
			// read second matrix data
			for (int i = 0; i < s2; i++) {
				tok = new StringTokenizer(st.readLine());
				for (int j = 0; j < s3; j++)
					b[i][j] = Integer.parseInt(tok.nextToken());
			}
			// read number of threads to use
			int n = Integer.parseInt(st.readLine());
			// Perform multi-threaded multiplication
			multiply(a, b, n);
			// Perform sequential multiplication
			int[][] res = sequentialMultiply(a, b);
			// compare results
			if (!equals(res, c)) {
				// Debug
				System.out.println("NOT Equal");
				System.out.println("Sequential");
				printMatrix(res);
				System.out.println("\n Threaded");
				printMatrix(c);
			} else
				System.out.println("Accepted");
		}

	}
}

class MatrixThread extends Thread {
	// id for each thread
	int id;
	// Number of scalar multiplications this thread will perform
	int numMult;

	public MatrixThread(int id) {
		super();
		this.id = id;
		numMult = Matrix.threadMult;
		if (id <= Matrix.rem)
			numMult++;
	}

	public void run() {
		/*
		 * Given the id, we can calculate where this thread should start
		 */
		// First calculate how many scalar multiplications should be performed
		// by threads from [1,id)
		int multBefore = (id - 1) * Matrix.threadMult + Math.min(id - 1, Matrix.rem);
		// Number of cells processed by threads from [1,id)
		int cellsBefore = multBefore / Matrix.width;
		// current row in the output matrix
		int i = cellsBefore / Matrix.c[0].length;
		// current column in the output matrix
		int j = cellsBefore % Matrix.c[0].length;
		// Where to start multiplication for this cell
		int k = multBefore % Matrix.width;
		int sum = 0;
		// We will perform numMult multiplications
		for (int done = 0; done < numMult; done++) {
			sum += Matrix.a[i][k] * Matrix.b[k][j];
			k++;
			// If this is the last multiplication for this cell, then write
			// the sum to the output matrix, update current row and column
			if (k == Matrix.width) {
				k = 0;
				/*
				 * gain exclusive access to this cell in the output matrix
				 * Note:actually we could have updated the output matrix with
				 * each multiplication, but this will cause a lot of sleep\wake
				 * up to the threads and may be a bottle neck, so it's better to
				 * buffer the sum and write it just in the end
				 */
				Matrix.locks[i][j].lock();
				Matrix.c[i][j] += sum;
				Matrix.locks[i][j].unlock();

				// if we are in the last column in the output matrix, then
				// increment the current row
				i += (j + 1) / Matrix.c[0].length;
				j = (j + 1) % Matrix.c[0].length;
				sum = 0;
			}
		}
		// If the last multiplication performed by this thread wasn't the last
		// one for the last output matrix cell, then the sum wasn't written to
		// the output matrix, so we have to write it
		if ((multBefore + numMult) % Matrix.width != 0) {
			Matrix.locks[i][j].lock();
			Matrix.c[i][j] += sum;
			Matrix.locks[i][j].unlock();
		}
	}
}
