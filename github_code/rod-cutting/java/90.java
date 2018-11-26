package DynamicProgramming;

public class RodCutting {

	public static void main(String[] args) {

		int n=4;
		int profit[] = new int[n+1];
		profit[0]=0;
		profit[1]=5;
		profit[2]=1;
		profit[3]=27;
		profit[4]=9;
		int x = RodCuttingRecursive(n , profit);
		System.out.println(x);
		x = RodCuttingMemoizedVersion(n , profit);
		System.out.println(x);	
		x =RodCuttingBottomUp(n , profit);
		System.out.println(x);
	}

	public static int RodCuttingRecursive(int n, int[] profit)
	{
		if(n==0)
			return 0;
		int q= Integer.MIN_VALUE;
		for (int i=1;i<=n;i++)
		{
			q=max(q, profit[i]+RodCuttingRecursive(n-i,profit));
		}
		return q;
	}
	
	public static int max(int a , int b)
	{
		if(a>b)
			return a;
		return b;
	}
	//Top Down approach
	public static int RodCuttingMemoizedVersion(int n, int profit[])
	{
		int revenue[] = new int[n+1];
		
		for(int i=0;i<=n;i++)
			revenue[i]=Integer.MIN_VALUE;
		
		int result = RodCuttingMemoizedVersionAux(profit, n, revenue);
		return result;
	}
	
	public static int RodCuttingMemoizedVersionAux(int prize[], int n, int revenue[])
	{
		if(revenue[n]>=0)
			return revenue[n];
		int q;
		if(n==0)
			q=0;
		else
			{
				q=Integer.MIN_VALUE;
				for(int i=1;i<=n;i++)
				{
					q = max(q, prize[i]+RodCuttingMemoizedVersionAux(prize, n-i, revenue));
				}
			}
		
		revenue[n]=q;
		return revenue[n];
	}
	
	//Bootom Up approach
	public static int RodCuttingBottomUp(int n, int profit[])
	{
		int revenue[] = new int[n+1];
		revenue[0]=0;
		int q;
		for(int i=1;i<=n;i++)
		{
			q = Integer.MIN_VALUE;
			for(int j=1;j<=i;j++)
			{
				q = max(q,profit[j]+revenue[i-j]);
			}
			
			revenue[i] = q;
		}
		
		return revenue[n];
	}
	
}
