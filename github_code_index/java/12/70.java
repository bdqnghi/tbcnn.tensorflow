package p;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

public class MultithreadingMatrixMultiplication implements MatrixMultiplication {

	public double[][] multiplication(double[][] A, double[][] B) {

		int size = A.length;
		ExecutorService exe = Executors.newFixedThreadPool(4);
		Future<Double>[][] result = new Future[size][size];
		

		double[][] C = new double[size][size];

		double startTime = System.currentTimeMillis();
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {

				result[i][j] = exe.submit(new multi(A[i], B[j]));
			}
		}
		exe.shutdown();
		try {
			exe.awaitTermination(1, TimeUnit.DAYS);

			for (int i = 0; i < size; i++) {
				for (int j = 0; j <size; j++) {
					C[i][j] = result[i][j].get();
					//System.out.println(C[i][j]+" ");
				}
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (ExecutionException e) {
			e.printStackTrace();
		}
		System.out.println(((System.currentTimeMillis() - startTime) / 1000) + " seconds for matrix of size " + size
				+ " multithreaded with algorithm 1.");

		return C;
	}

	public static class multi implements Callable<Double> {

		multi(double[] vec1, double[] vec2) {
			this.vec1 = vec1;
			this.vec2 = vec2;
		}

		double result;
		double[] vec1, vec2;

		@Override
		public Double call() {
			result = 0;
			for (int i = 0; i < vec1.length; i++)
				result += vec1[i] * vec2[i];
			return result;
		}
	}

}
