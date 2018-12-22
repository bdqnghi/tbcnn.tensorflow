package priorityqueues;

import tools.Tools;

public class Heapsort
{
	public static void sort(Comparable[] a)
	{
		int N = a.length-1;
		// build heap-ordered trees
		for (int k=N/2; k>=0; k--)
		{
			sink(a, k, N);
		}
		// sort array
		while (N>0)
		{
			Tools.exch(a, 0, N--);
			sink(a, 0, N);
		}
	}

	private static void sink(Comparable[] a, int k, int N)
	{	
		while (2*k+1 <= N)
		{
			int j = 2*k+1;
			if ( j<N && Tools.less(a[j], a[j+1]) ) 	j++ ; 	// find bigger of two children
			if ( !Tools.less(a[k], a[j]) ) break;			// k > children, stop sink
			Tools.exch(a, k, j);
			k = j;
		}
	}

	public static void main(String[] args)
	{
		String[] test = {"S", "O", "R", "T", "E", "X", "A", "M", "P", "L", "E"};
		sort(test);
		Tools.show(test);

		Integer[] test2 = {4,3,7,1,8,0,2,5,6};
		sort(test2);
		Tools.show(test2);
	}
}