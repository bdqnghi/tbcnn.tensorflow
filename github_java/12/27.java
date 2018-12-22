import java.util.*;
class Matrix
{
public static void main(String args[])
{
int i,j,m,n,o,p;
Scanner sc=new Scanner(System.in);
System.out.println("enter the no of rows of matrix A");
m=sc.nextInt();
System.out.println("enter the no of columns of matrix A");
n=sc.nextInt();
System.out.println("enter the no of rows of matrix B");
o=sc.nextInt();
System.out.println("enter the no of columns of matrix B");
p=sc.nextInt();
int A[][]=new int[m][n];
int B[][]=new int[o][p];
int mul[][]=new int[m][p];

System.out.println("enter the elements of matrix A");
for(i=0;i<m;i++)
{
for(j=0;j<n;j++)
{
A[i][j]=sc.nextInt();
}
}

System.out.println("enter the elements of matrix B");
for(i=0;i<o;i++)
{
for(j=0;j<p;j++)
{
B[i][j]=sc.nextInt();
}
}

System.out.println("matrix A is");
for(i=0;i<m;i++) 
{
for(j=0;j<n;j++)
{
System.out.print(A[i][j]+"\t");
}
System.out.println();
}

System.out.print("matrix B");
for(i=0;i<o;i++)
{
for(j=0;j<p;j++)
{
System.out.print(B[i][j]+"\t");
}
System.out.println();
}

if(m!=p)
{
System.out.println("matrix multiplication not possible");
}
else
{
int k;
for(i=0;i<m;i++)
{
for(j=0;j<p;j++)
{
for(k=0;k<n;k++)
{
mul[i][j]+=A[i][k]*B[k][j];
}
}
}
}
System.out.println("matrix multiplication is");
for(i=0;i<m;i++) 
{
for(j=0;j<p;j++)
{
System.out.print(mul[i][j]+"\t");
}
System.out.println();
}

}
}

OUTPUT:
C:\Users\pranali>d:
D:\>cd JAVA PROGRAMS
D:\JAVA PROGRAMS>javac Matrix.java
D:\JAVA PROGRAMS>java Matrix
enter the no of rows of matrix A
2
enter the no of columns of matrix A
2
enter the no of rows of matrix B
2
enter the no of columns of matrix B
2
enter the elements of matrix A
1
2
3
4
enter the elements of matrix B
1
2
3
4
matrix A is
1       2
3       4
matrix B1       2
3       4
matrix multiplication is
7       10
15      22
