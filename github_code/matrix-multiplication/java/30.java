import java.util.Scanner;

class D
{
	public static void main(String args[])
	{
		Scanner ip=new Scanner(System.in);
		
		System.out.println("enter no:");
		int n=ip.nextInt();

		int a[][]=new int[n][n];
		int b[][]=new int[n][n];
		int c[][]=new int[n][n];

		System.out.println("For first Matrix:");

		for (int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				a[i][j]=ip.nextInt();
			}	
		}

		System.out.println("For Second Matrix");

		for (int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				b[i][j]=ip.nextInt();
			}	
		}


		for (int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				for(int k=0;k<n;k++)
				{
					c[i][j]=c[i][j]+a[i][k]*b[k][j];
				}
			}	
		}

		System.out.println("Answer Is: ");

		for (int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				System.out.print(c[i][j]+" ");
			}	
		}

		System.out.println(" ");
	}

}