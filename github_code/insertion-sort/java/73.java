/* *
 * Pseudo-code:
 * 
 * Insertion-Sort(L)
 * 		if L is empty then return L 
 * 		else return Insert(first(L), Insertion-Sort(rest(L)))
 * end Insertion-Sort
 * 
 * Insert(x, L)
 * 		if L is empty then return x
 * 		else if x <= first(L) then return x+L
 * 		else return first(L)+Insert(x, rest(L))
 * end Insert
 * 
 * *******************************************
 * Worst case performance: O(n^2) comparisons and swaps
 * Best case performance: O(n) comparisons and O(1) swaps
 * Average case performance: O(n^2) comparisons and swaps
 * Worst case space complexity: O(n) total, O(1) auxilliary
 * *******************************************
 * */

import java.util.Random;


public class insertion_sort {
	private int[] list;
	
	public insertion_sort(int[] input){
		list = input.clone();
		System.out.print("Original Array: ");
		printResult();
	}
	
	public void ascend_sort()
	{
		list = ascend_sort(list);
		System.out.print("Sorted Array: \t");
		printResult();
	}
	
	private int[] ascend_sort(int[] L)
	{
		if (L.length == 0)
		{
			return L;
		}
		else
		{
			return ascend_insert(L[0], ascend_sort(rest(L)));
		}
	}
	
	private int[] ascend_insert(int x, int[] L)
	{
		if (L.length == 0)
		{
			return new int[]{x};
		}
		else if (x <= L[0])
		{
			int[] result = new int[L.length+1];
			result[0] = x;
			for (int i=0; i<L.length; i++)
			{
				result[i+1] = L[i];
			}
			return result;
		}
		else
		{
			int[] combine = ascend_insert(x, rest(L));
			int[] result = new int[L.length+1];
			result[0] = L[0];
			for (int i=0; i<combine.length; i++)
			{
				result[i+1] = combine[i]; 
			}
			return result;
		}
	}
	
	private int[] rest(int[] L)
	{
		int[] result = new int[L.length-1];
		for (int i=1; i<L.length; i++)
			result[i-1] = L[i];
		return result;
	}
	
	private void printResult()
	{
		for (int i=0; i<list.length; i++)
		{
			System.out.print(list[i]+" ");
		}
		System.out.println();
	}
	

	public static void main(String[] args) {
		int size = 100;
		int[] numbers = new int[size];
		Random rand = new Random();
		for (int i=0; i<size; i++)
		{
			numbers[i] = rand.nextInt(1000);
		}
		insertion_sort is = new insertion_sort(numbers);
		is.ascend_sort();
	}

}
