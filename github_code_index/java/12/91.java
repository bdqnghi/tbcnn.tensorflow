import java.util.Random;

public class MatrixMultiplication {
	

	 public static Integer[][] makeMatrix(int n) {
		 Integer[][] matrix = new Integer[n][n];
	        for (int i = 0; i < n; i++)
	        {
	        	for(int j = 0; j < n; j++)
	        	{
	        		Random randomGenerator = new Random();
	        		int randomInt = randomGenerator.nextInt(2500);
	        	    matrix[i][j] = randomInt;
	        	}
	        }
	        return matrix;
	 }
	 public static Integer[][] multiply(int n) {
		 Integer[][] firstMatrix = makeMatrix(n);
		 Integer[][] secondMatrix = makeMatrix(n);
		 Integer[][] newMatrix = new Integer[n][n];
		for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
            	newMatrix[i][j] = 0;
            	for (int k = 0; k < n; k++){
                    newMatrix[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            	}
            }
		}
        return newMatrix;
	}	 
}
