package chapter_7;

import java.util.Arrays;
import java.util.Scanner;

/**
 * <h1>(Revise selection sort)</h1> In Section 7.11, you used selection sort to
 * sort an array. The selection-sort method repeatedly finds the smallest number
 * in the current array and swaps it with the first. Rewrite this program by
 * finding the largest num- ber and swapping it with the last. Write a test
 * program that reads in ten double numbers, invokes the method, and displays
 * the sorted numbers.
 * 
 * @author William ODieLag Pennington
 * @version 1.0
 * @since 2016-6-7
 *
 */

public class Exercise_7_20__SelectionSortRevised
{
	/*
	 * Write a test program that reads in ten double numbers, invokes the
	 * method, and displays the sorted numbers.
	 */
	public static void main(String[] args)
	{
		Scanner input = new Scanner(System.in);
		double[] array = new double[10];
		System.out.print("Please enter 10 numbers: ");
		for(int i = 0; i < array.length; ++i)
		{
			array[i] = input.nextDouble();
		}
		input.close();
		selectionSortLargest(array);
		System.out.print(Arrays.toString(array));
	}

	/*
	 * The selection-sort method repeatedly finds the smallest number in the
	 * current array and swaps it with the first. Rewrite this program by
	 * finding the largest num- ber and swapping it with the last.
	 */
	public static void selectionSortLargest(double[] array)
	{
		for (int r = array.length - 1; r > 0; --r)
		{
			int largestElementIndex = r;
			// loop to find the largest element lower than r.
			for (int l = 0; l < r; ++l)
			{
				if (array[l] > array[largestElementIndex])
					largestElementIndex = l;
			}
			// once done with loop, replace r element with largestElementIndex
			// element.
			double temp = array[r];
			array[r] = array[largestElementIndex];
			array[largestElementIndex] = temp;
		}
	}
}
