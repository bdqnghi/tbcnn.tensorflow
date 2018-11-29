//Program to multiply two matrices...

import java.util.Scanner;

class matrixmultiplication
{
  public static void main(String args[])
  {
    Scanner in = new Scanner(System.in);
    int p, q, m, n;   //matrix sizes
    int i, j, k;      //Looping variables
    int[][] a, b, c;      //Matrices

    System.out.print("\nEnter the size of the first matrix : ");
    p = in.nextInt();
    q = in.nextInt();

    System.out.print("\nEnter the size of the Second matrix : ");
    m = in.nextInt();
    n = in.nextInt();

    if(q == m)
    {
      a = new int[p][q];
      b = new int[m][n];
      c = new int[p][n];

      System.out.println("\n\nEnter the values of first matrix :\n");
      for(i = 0 ; i < p ; i++)
      {
        for(j = 0 ; j < q ; j++)
        {
          a[i][j] = in.nextInt();
        }
      }
      System.out.println("\n\nEnter the values of Second matrix :\n");
      for(i = 0 ; i < m ; i++)
      {
        for(j = 0 ; j < n ; j++)
        {
          b[i][j] = in.nextInt();
        }
      }

      for(i = 0 ; i < p ; i++)
      {
        for(j = 0 ; j < m ; j++)
        {
          c[i][j] = 0;
          for(k = 0 ; k < q ; k++)
          {
            c[i][j] += a[i][k] * b[k][j];
          }
        }
      }

      System.out.println("\nThe Resultant Matrix will be : \n");
      for(i = 0 ; i < p ; i++)
      {
        for(j = 0 ; j < n ; j++)
        {
          System.out.print("\t" + c[i][j]);
        }
        System.out.print("\n\n");
      }
    }
  }
}
