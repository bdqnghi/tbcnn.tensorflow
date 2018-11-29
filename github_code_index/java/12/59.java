package exercices;

/**
 * @author amadou
 *
 */
public class MatrixMatrixMultiplication {

	public static void main(String[] args) {
		
		
		char [][] a= new char [2][10];
		
		
		int N=a.length;
		double [][] c= new double[N][N];
		double [] [] b = new double [2][N];
		for (int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				
				
				for(int k=0; k<N; k++){
				c[i][j] += a[i][k]* b[j][k];
				
				
				System.out.println( " c[i][j]:"+ " "+ c[i][j]);
				}
			}
		}

	}

}
