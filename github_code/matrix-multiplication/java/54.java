import java.util.Scanner;
public class Matrixmultiplication {
	public static void main(String args[])
	{
		Scanner sc=new Scanner(System.in);
		int row1,col1,row2,col2;
		System.out.println("Enter dimensions of first matrix:");
		row1=sc.nextInt();
		col1=sc.nextInt();
		System.out.println("Enter dimensions of second matrix:");
		row2=sc.nextInt();
		col2=sc.nextInt();
		int i,j,k;
		if(col1!=row2)
		{
			System.out.println("Matrix multiplication not possible.");			
		}
		else
		{
			int a[][]=new int[row1][col1];
			int b[][]=new int[row2][col2];
			int res[][]=new int[row1][col2];
			System.out.println("Enter elements of matrix 1:");
			for(i=0;i<row1;i++)
			{
				for(j=0;j<col1;j++)
				{
					a[i][j]=sc.nextInt();
				}
			}
			System.out.println("Enter elements of matrix 2:");
			for(i=0;i<row2;i++)
			{
				for(j=0;j<col2;j++)
				{
					b[i][j]=sc.nextInt();
				}
			}
			for(i=0;i<row1;i++)
			{
				for(j=0;j<col1;j++)
				{
					for(k=0;k<col2;k++)
					{
						res[i][k]+=a[i][j]*b[j][k];
					}
				}
			}
			System.out.println("Resultant matrix is:");
			for(i=0;i<row1;i++)
			{
				for(k=0;k<col2;k++)
				{
					System.out.print(res[i][k]+"  ");
				}
				System.out.println();
			}
		}
	}
}