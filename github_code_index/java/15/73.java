package com.functional.DP;

/**
 * Rod cutting problem using dynamic programming.
 * @author daebenez
 */
public class RodCutting {
	
	public int maximumProfit(int[] prices,int length)
	{
		int[][] tabulation = new int[prices.length][prices.length];
		
		for(int i=0;i<prices.length;i++)
		{
			tabulation[0][i] = 0;
		}
		for(int i=0;i<prices.length;i++)
		{
			tabulation[1][i] = i;
		}
		
		for(int j=0;j<prices.length;j++)
		{
			tabulation[j][0] = 0; 
		}
		
		for(int i=2;i<prices.length;i++)
		{
			for(int j=1;j<prices.length;j++)
			{
				//If the length is less than cut size
				if(i==j)
				{	
				  if(prices[i-1]>tabulation[i-1][j])
				  {
					  tabulation[i][j]=prices[i-1];
				  }
				  else
				  {
					  tabulation[i][j] = tabulation[i-1][j];
				  }
				}
				else if(i>j)
				{
					tabulation[i][j] = tabulation[i-1][j];
				}
				else
				{
					if(tabulation[i-1][j]>(tabulation[i][j-i]+prices[i-1]))
					{
						tabulation[i][j] = tabulation[i-1][j];
					}
					else
					{
						tabulation[i][j] = tabulation[i][j-i]+prices[i-1];
					}
				}
			}
		}
		
		return tabulation[prices.length-1][prices.length-1];
	}
	/*
	public static void main(String[] args)
	{
		RodCutting obj = new RodCutting();
		int[] prices = {1,5,8,9,10};
		System.out.println(obj.maximumProfit(prices, 4));
	} */
}
