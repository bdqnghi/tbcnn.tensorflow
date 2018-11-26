package algo.paradigms.dp.rodcutting;
/**
 * A top down implementation of the rod-cutting problem
 * @author kempa
 *
 */
public class TDRodCutting
{
	int n; // Length of the given rod
	private int p[]; // Price list
	private int r[]; // Table to store maximal revenues
	private String cuts[]; // The cuts which make up the maximal revenue

	public TDRodCutting(int n, int price[])
	{
		this.n = n;
		r = new int[price.length];
		p = price;
		cuts = new String[price.length];
		
		r[0] = 0;
		p[0] = 0;
		cuts[0] = "";
		
		for (int i = 1; i < price.length; i++)
			r[i] = Integer.MIN_VALUE;

		r[n] = cutRod(n);
	}

	private int cutRod(int n)
	{
		if (n == 0) // base case
			return r[n];

		// memoized result
		if (r[n] != Integer.MIN_VALUE)
			return r[n];

		int max = Integer.MIN_VALUE;
		for (int i = 1; i <= n; i++)
		{
			int t = cutRod(n - i);
			if ( p[i] + t > max) {
				max = p[i] + t;
				cuts[n] = new String(i + " " + cuts[n - i]);
			}
		}
		r[n] = max;
		return r[n];
	}

	
	public String toString()
	{
		return("Maximal revenue = " + r[n]);
	}
	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		int p[] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
		TDRodCutting topDown = new TDRodCutting(10, p);
		System.out.println("Read as, Length of Rod : Cuts : Maximal Revenue");
		for ( int i = 1; i <= topDown.n; i++)
			System.out.println(i + " : " + topDown.cuts[i] + " : " + topDown.r[i]);
	}
}