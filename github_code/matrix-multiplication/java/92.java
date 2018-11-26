package Arrays;

public class MatrixMultiplication {

	public static void main(String[] args)
	{
		int[][] matrix1 = {{1, 2, -2, 0}, {-3, 4, 7, 2}, {6, 0, 3, 1}};
		int[][] matrix2 = {{-1, 3}, {0, 9}, {1, -11}, {4, -5}};
		multiply(matrix1, matrix2);
	}

	private static void multiply(int[][] matrix1, int[][] matrix2) {
		int[][] result = new int[matrix1.length][matrix2[0].length];
		for(int i=0; i<matrix1.length; i++)
		{
			for(int j=0; j<matrix2[0].length; j++)
			{
				for(int k=0; k<matrix1[0].length; k++)
				{
					result[i][j] += matrix1[i][k] * matrix2[k][j]; 
				}
			}
		}
		
		for(int i=0; i<result.length; i++)
		{
			for(int j=0; j<result[0].length; j++)
			{
				System.out.print(result[i][j] + "   ");
			}
			System.out.println();
		}
	}
}
