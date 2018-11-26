package crackingthecoding;

public class matrixmultiplication
{
	public static void main(String[] args)
	{
		mul();
	}

	static void mul()
	{
		int[][] A = { { 4, 3, 1 }, { 2, 1, 1 }, { 4, 3, 1 } };
		int[][] B = { { -1, 1, 1 }, { 1, -2, 1 }, { 4, 3, 1 } };

		int[][] C = new int[3][3];
		int i, j;
		int rowA = A.length;
		int colA = A[0].length;
		int rowB = B.length;
		int colB = B[0].length;

		if (colA != rowB)
		{
			return;
		}
		for (i = 0; i < rowA; i++)
		{
			for (j = 0; j < colB; j++)
			{
				for (int k = 0; k < colA; k++)
					C[i][j] += (A[i][k] * B[k][j]);
				System.out.print(C[i][j] + "\t");
			}
			System.out.println("");
		}

	}
}
