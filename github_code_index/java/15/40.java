import java.util.*;

public class RodCutting
{
	public static void main(String[] args)
	{
		int[] prices = {1, 5, 8, 9, 10, 17, 17, 20};
		rodCutting(prices, 8);

		int[] prices2 = {3, 5, 8, 9, 10, 17, 17, 20};
		rodCutting(prices2, 8);

	}

	public static void rodCutting(int[] prices, int rodLength)
	{
		int[] optimalSolution = new int[prices.length];
		optimalSolution[0] = prices[0];		

		for (int i = 1; i < prices.length; i++)
		{
			optimalSolution[i] = findMaximumProfit(prices, optimalSolution, i);
		}

		//System.out.println(Arrays.toString(optimalSolution));
		System.out.println("The maximum profit is " + optimalSolution[rodLength-1] + ".");
	}

	public static int findMaximumProfit(int[] prices, int[] solutions, int length)
	{
		int max = Integer.MIN_VALUE;

		for (int i = 0; i < length; i++)
		{
			int value = prices[i] + solutions[length-i-1];
			if (value > max) {
				max = value;
			}
		}

		if (prices[length] > max) {
			max = prices[length];
		}

		return max;
	}
}
