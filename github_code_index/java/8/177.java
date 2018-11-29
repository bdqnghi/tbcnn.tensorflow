package org.lilian.util.distance;

import java.util.List;

import org.lilian.util.Functions;

public class LevenshteinDistance<T> implements Distance<List<T>>
{

	@Override
	public double distance(List<T> a, List<T> b)
	{
		if (a.isEmpty()) 
			return b.size();
		
		if (b.isEmpty()) 
			return a.size();		
		
		int d[][]; // matrix
		int n = a.size();
		int m = b.size();
		
		d = new int[n + 1][m + 1];

		for (int i = 0; i <= n; i++) 
			d[i][0] = i;

		for (int j = 0; j <= m; j++) 
			d[0][j] = j;

		for (int i = 1; i <= n; i++) 
			for (int j = 1; j <= m; j++) 
			{
				int cost;
				if ( Functions.equals(a.get(i-1), b.get(j - 1)) ) 
					cost = 0;
				else 
					cost = 1;

				d[i][j] = minimum(
						d[i - 1][j] + 1, 
						d[i][j - 1] + 1,
						d[i - 1][j - 1] + cost);
			}

		return d[n][m];
	}
	

	/** 
	 * Fast minimum over three integers
	 */
	private int minimum(int a, int b, int c) 
	{
		int min = a;

		if (b < min) 
			min = b;

		if (c < min) 
			min = c;
		
		return min;
	}		
}
