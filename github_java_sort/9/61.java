/**
 * 
 */
package algorithm.sort.unstable;

import algorithm.sort.ISortAlgorithm;
import algorithm.sort.SortUtil;

/**
 * @author aaaajl
 *
 */
public class Selection_SelectionSort{
	/**
	 * Worst case performance	O(n2)
	 * Best case performance	O(n2)
	 * Average case performance	O(n2)
	 * Worst case space complexity	O(n) total, O(1) auxiliary
	 * */
	public static void sort(Comparable[] data) throws Exception {
		long start = System.nanoTime();
		int len = data.length;
		int minIndex = 0;
		for(int i=0;i<len;i++)
		{
			minIndex=i;
			for(int j=i;j<len;j++)
			{
				if(data[minIndex].compareTo(data[j])>0)
				{
					minIndex = j;
				}
			}
			SortUtil.swap(data, i, minIndex);
		}
		long end = System.nanoTime();
		System.out.println("\nSelectionSort Execute time:"+(end-start));
	}

}
