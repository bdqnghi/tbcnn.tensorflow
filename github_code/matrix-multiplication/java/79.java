package souvik11.matrix;

import java.io.*;
class matrixmultiplication
{
public static void main()throws IOException
{
BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
int i,n,p,m,j;
System.out.print("Enter matrix elements");
n=Integer.parseInt(br.readLine());
int a[][]=new int[n][n];
for(i=0;i<n;i++)
 {for(j=0;j<n;j++)
   a[i][j]=Integer.parseInt(br.readLine());
}
for(i=0;i<n;i++)
 {for(j=0;j<n;j++)
    System.out.print(a[i][j] );
    System.out.print(" ");
}
int r[][]=new int[n][n];
for(p=0;p<n;p++)
 {for(m=0;m<n;m++)
 r[p][m]*=a[i][j];
 System.out.print(r[p][m]);
}
}
}