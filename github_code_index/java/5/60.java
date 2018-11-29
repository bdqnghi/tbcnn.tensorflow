import java.util.*;
public class dfs
{
    Scanner sc=new Scanner(System.in);
    int a,b,ar[][];
    void input()
    {
        int m,n;
        System.out.println("Enter length");
        a=sc.nextInt();
        System.out.println("Enter breadth");
        b=sc.nextInt();
        ar=new int[a][b];
        for(m=0;m<a;m++)
        {
            for(n=0;n<b;n++)
            {
                System.out.println("Enter element");
                ar[m][n]=sc.nextInt();
            }
        }
        row(a-1,b-1);
    }
    void row(int m,int n)
    {
        b=col(m,n,ar[m][n]);
        System.out.println(+b);
        if(m==0)
        {
            return;
        }
        else
        {
            row(m-1,n);
        }
    }
    void display()
    {
        int m,n;
        for(m=0;m<a;m++)
        {
            for(n=0;n<b;n++)
            {
                System.out.print(+ar[m][n]);
            }
            System.out.println();
        }
    }
    int col(int m,int n,int k)
    {
        if(ar[m][n]>k)
        {
            k=ar[m][n];
        }
        if(n==0)
        {
            return k;
        }
        else
        {
            return (col(m,n-1,k));
        }
    }
}