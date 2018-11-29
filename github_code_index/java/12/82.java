package p;

public class SinglethreadMatrixMultiplication implements MatrixMultiplication{

	public  double[][] multiplication(double[][] A, double[][] B) {
		
		int size = A.length;
	

		double[][] C = new double[size][size];
		
		double startTime = System.currentTimeMillis();
		for (int i = 0; i < size; i++) { // aRow
			for (int j = 0; j < size; j++) { // bColumn
				for (int k = 0; k < size; k++) { // aColumn
					C[i][j] += A[i][k] * B[k][j];
					
				}
			}
		}
//		for (int i = 0; i < size; i++) {
//			for (int j = 0; j <size; j++) {
//				
//				System.out.println(C[i][j]+" ");
//			}
//		}
		System.out.println(((System.currentTimeMillis() - startTime) / 1000) + " seconds for matrix of size " + size
				+ " singlethreaded with algorithm 1.");

		return C;
	}
}
