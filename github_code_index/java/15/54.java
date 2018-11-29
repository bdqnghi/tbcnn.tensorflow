import java.util.*;
import java.lang.*;
import java.io.*;
import static java.lang.Integer.parseInt;
//cutting rod problem
class Test {
 
static int rodCuttingByRecursion(int prices[],int length)
{
	if(length<=0)
		return 0;
	int max=Integer.MIN_VALUE;
	for(int i=0;i<length;i++)
	{
		max=Math.max(max, prices[i]+rodCuttingByRecursion(prices,length-(i+1)));
	}
	return max;
}
static int rodCutByBottomUp(int prices[],int n)
{
	int dp[]=new int[n+1];
	for(int i=1;i<=n;i++)
	{
		int max=Integer.MIN_VALUE;
		for(int j=0;j<i;j++)
		{
			max=Math.max(max,prices[j]+dp[i-j-1]);
			dp[i]=max;
		}
	}
	return dp[n];
}
public static void main(String aa[])throws IOException
{
	Scan s=new Scan();
	int t=s.scanInt();
	for(int k=0;k<t;k++)
	{
	   
	    int total=5;
	    int val[]={1, 5, 8, 9, 10, 17, 17, 20};
	    System.out.println(rodCuttingByRecursion(val,val.length));
	    System.out.println(rodCutByBottomUp(val,val.length));
}
}
}
class Scan
	{
	   // BufferedReader br;
	    StringTokenizer st;
	   BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
	    String scanString() throws IOException
	    {
	        while(st==null||!st.hasMoreTokens())
	        {
	            st=new StringTokenizer(br.readLine());
	        }
	        return st.nextToken();
	    }
	    int scanInt() throws IOException
	    {
	        return parseInt(scanString());
	    }
	    
	    
	}
