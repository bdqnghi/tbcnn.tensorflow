package sorting;

public class Shellsort {
	/*
	 * Shell sorting algorithm
	 * relies on h-sorting
	 * best h sequence is 3x+1
	 * Best case time not yet proven 
	 * estimate O(N^(3/2))
	 */
	
	@SuppressWarnings("rawtypes")
	public static void sort(Comparable[] list)
	{
		int N = list.length;//set size of list
		int h =	1;//set h 
		
		while(h<N/3)//loop to find highest possible in h sequence by incrementing h by 3x+1 times
		{
			h=(3*h+1);//set h to next in h sequence
		}
		
		while(h>=1) //insertion sort through each sequence of h
		{
			for(int i = h; i<N; i++)//go through the list from h element and increment to the end  
			{
				for(int j=i; j>=h && less(list[j],list[j-h]); j-=h)//find anomalies with the item h indexes back from current i and swap
				{
					exch(list,j,j-h);
				}
			}
			h=h/3;//go to next lower sequence of h in series until h is less than 1
		}
	}
	
	@SuppressWarnings({ "rawtypes", "unchecked" })
	private static boolean less(Comparable x,Comparable y)//function to return true if one item is less than the other
	{
		return x.compareTo(y)==-1;
	}
	
	@SuppressWarnings({ "rawtypes"})
	private static void exch(Comparable[] list,int i,int j)//function that swaps comparable items
	{
		Comparable x = list[i];
		list[i]=list[j];
		list[j]=x;
	}

}
