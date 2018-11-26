package kovid123;
import java.util.Scanner;

public class matrixmultiplication {
	public static void main(String []args) {
		Scanner o=new Scanner(System.in);
		int row1,col1,row2,col2;
		
		while(true)
		{
			System.out.println("dimensions of first matrix");
			row1=o.nextInt();
			col1=o.nextInt();
			System.out.println("dimensions of second matrix");
			row2=o.nextInt();
			col2=o.nextInt();
			if(col1!=row2)
			{
				System.out.println("wrong dimensions of matrix chosen\n");
			}
			else
				break;
		}
		
		int a[][]=new int[row1][col1];
		int b[][]=new int[row2][col2];
		int c[][]=new int[row1][col2];
		int i,j,k,y;
		for(i=0;i<row1;i++)
			for(j=0;j<col1;j++)
				a[i][j]=o.nextInt();
		for(i=0;i<row2;i++)
			for(j=0;j<col2;j++)
				b[i][j]=o.nextInt();
		
		for(j=0;j<col2;j++)
		{
			for(k=0;k<row1;k++)
			{
				for(y=0;y<col1;y++)
				{
					c[k][j]=c[k][j]+a[k][y]*b[y][j];
				}
			}
		}
		
		for(i=0;i<row1;i++)
		{
			for(j=0;j<col2;j++)
			{
				System.out.print(c[i][j]+ " ");
			}
			System.out.println();
		}
		
	}

}
