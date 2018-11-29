package firstjavaprogram;

import java.util.Scanner;

public class matrixmultiplication {
	public static void main(String args[])
	{
		int n,i,j,k,m,x,y;
		System.out.println("enter order of m");
		Scanner s=new Scanner(System.in);
		n=s.nextInt();
		System.out.println("enter order of n");
		m=s.nextInt();
		x=s.nextInt();
		y=s.nextInt();
		int a[][]=new int[m][n];
		int b[][]=new int[m][n];
		int c[][]=new int[m][n];
		System.out.println("enter values for first matrix");
		for(i=0;i<m;i++)
		{
			for(j=0;j<n;j++)
			{
				a[i][j]=s.nextInt();
			}
		}
		System.out.println("enter values for second matrix");
		for(i=0;i<x;i++)
		{
			for(j=0;j<y;j++)
			{
				b[i][j]=s.nextInt();
			}
		}
		for(i=0;i<m;i++)
		{
			for(j=0;j<y;j++)
			{
				for(k=0;k<x;k++)
				{
					c[i][j]=c[i][j]+a[i][k]*b[k][j];
				}
			}
		}
		System.out.println("multiplication of matrix is:");
		for(i=0;i<m;i++)
		{
			for(j=0;j<y;j++)
			{
				System.out.println(c[i][j]);
			}
		}
		
	}
}
