/**
 * Project Name: algorithms_java
 * File Name: BubbleSort.java
 * Package Name: com.fanglei.resource.chapter_2.chapter_2_problems_bubble_sort
 * Date: Apr 15, 2017 9:58:59 PM
 * Copyright (c) 2017, fanglei@pku.edu.cn All Rights Reserved.
 * 
 */


package com.fanglei.resource.chapter_2.chapter_2_problems_bubble_sort;


/**
 * ClassName: BubbleSort
 * Description: bubble-sort algorithm
 * 
 * @author Lei Fang
 * @email fanglei@pku.edu.cn
 * @version
 * @date: Apr 15, 2017 9:58:59 PM
 */
public class BubbleSort
{
	/**
	 * Method Name: bubbleSort
	 * Description: bubble-sort algorithm
	 * 
	 * @param A the array to be sorted
	 * 
	 * ALGORITHM-BUBBLE-SORT(A)
	 * for i = 1 to A.length - 1
	 * 		for j = A.length downto i + 1
	 * 			if A[j] < A[j-1]
	 * 				exchange A[j] with A[j-1]
	 *
	 * @author Lei Fang
	 */
	public static void bubbleSort(int[] A)
	{
		for(int i = 0; i < (A.length - 1); i++)
		{
			for (int j = A.length - 1; j >= (i + 1); j--)
			{
				if (A[j] < A[j - 1])
				{
					// Switch with a temp variable
					int temp = A[j];
					A[j] = A[j - 1];
					A[j - 1] = temp;
				}
			}
		}
	}

}
