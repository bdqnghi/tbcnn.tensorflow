package chapter_7;

import java.util.Arrays;
import java.util.Scanner;



public class Exercise_7_20__SelectionSortRevised
{
	
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

	
	public static void selectionSortLargest(double[] array)
	{
		for (int r = array.length - 1; r > 0; --r)
		{
			int largestElementIndex = r;
			
			for (int l = 0; l < r; ++l)
			{
				if (array[l] > array[largestElementIndex])
					largestElementIndex = l;
			}
			
			
			double temp = array[r];
			array[r] = array[largestElementIndex];
			array[largestElementIndex] = temp;
		}
	}
}
