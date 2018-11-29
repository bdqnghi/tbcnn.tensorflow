package impDSandALGO;

public class MatrixMultiplication {
	int[][] matrixmultiplication(int[][] A,int[][] B)
	{
		int[][] C = {{0,0},{0,0}};
		//code to calculate the matrix multiplication C=A*B
		C[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0];
		C[0][1] = A[0][0]*B[0][1] + A[0][1]*B[1][1];
		C[1][0] = A[1][0]*B[0][0] + A[1][1]*B[1][0];
		C[1][1] = A[1][0]*B[0][1] + A[1][1]*B[1][1];
		

		return C;
		
	}
	
	void printMatrix(int[][] A)
	{
	     for(int i = 0;i <2 ;i++){
	    	 
		    for(int j = 0; j < 2; j++){
		    	
			   System.out.print(A[i][j] + " ");
			   
		    }
		    System.out.println("\n");
		    
		}
		
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[][] A = {{2,3},{4,5}}, B = {{1,2},{3,4}} , C ={{1,0},{0,1}} , D = {{1,1},{1,0}};
		MatrixMultiplication m = new MatrixMultiplication();
		int n = 3;
		//C = m.matrixmultiplication(A,B,C);
		while(n>=1)
		{
		C = m.matrixmultiplication(C, D);
		n--;
		}
		//System.out.println("the value returned C is :" + C);
		//Code to print the matrix
		m.printMatrix(C);
		
		//int orig =  164;
	  //  int orig_shifted = orig >>> 1;
	  //  System.out.println(orig ^ ~orig);

	}

}
