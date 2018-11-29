/**
 * Created by liuxiongcheng on 2017/4/10.
 */
public class Editdistance {

 static int min(int x,int y,int z)
  {
    if(x<y&&x<z)
        return x;
    else if(y<x&&y<z)
        return y;
    else
        return x;
}
//递归函数解决
     static int editDist(String str1,String str2,int m,int n)/*把第一个字符串变成第二字符串*/ {
         if (m == 0) return n;
         if (n == 0) return m;
         if (str1.charAt(m - 1) == str2.charAt(n - 1))
             return editDist(str1, str2, m - 1, n - 1);
        /*无论如何都要操作一次，三种操作中选出最小的数字,分别对应插入，替换，删除*/
             return 1 + min(editDist(str1, str2, m, n - 1), editDist(str1, str2, m - 1, n - 1), editDist(str1, str2, m - 1, n));

     }
     //采用动态规划的思想解决
     static  int editDsitDP(String str1,String str2,int m,int n)
     {
         int dp[][]=new int [m+1][n+1];
         for(int i=0;i<=m;i++)
         {
             for(int j=0;j<=n;j++)
             {
                 if(i==0)
                 {
                     dp[i][j]=j;
                 }
               else  if (j==0)
                 {
                     dp[i][j]=i;
                 }
               else  if(str1.charAt(i-1)==str2.charAt(j-1))
                     dp[i][j]=dp[i-1][j-1];
                 else
                     dp[i][j]=1+min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1]);

             }
         }
         return dp[m][n];
     }
     public static void main(String[] args) {
        String a="saturday";
        String b="sunday";
        int m=a.length();
        int n=b.length();
        System.out.println(editDist(b,a,n,m));
    }

}
