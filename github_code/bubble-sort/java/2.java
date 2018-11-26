package Chapter_07_Single_Dimensional_Arrays;

import java.util.Random;

/**
 * Bubble sort
 * Write a sort method that uses the bubble-sort algorithm. 
 * The bubblesort algorithm makes several passes through the array. 
 * On each pass, successive neighboring pairs are compared. 
 * If a pair is not in order, its values are swapped; otherwise, the values remain unchanged. 
 * The technique is called a bubble sort or sinking sort because the smaller values gradually �bubble� their way to the top 
 * and the larger values �sink� to the bottom. 
 * Write a test program that reads in ten double numbers, invokes the method, and displays the sorted numbers.
 * 
 * 09/21/2016
 * @author kevgu
 *
 */

public class Programming_Exercise_18 
{
	static final int SIZE = 10;
	public static void main(String[] args) 
	{
		double[] bubbleSortArray = new double[SIZE];
		insertNumbers(bubbleSortArray);
		System.out.println("Before bubble sort: ");
		displayArray(bubbleSortArray);
		System.out.println("After bubble sort: ");
		bubbleSort(bubbleSortArray);
		displayArray(bubbleSortArray);
	}
	
	/**
	 * Bubble sort array
	 * 
	 * @param bubbleSortArray
	 */
	public static void bubbleSort(double[] bubbleSortArray)
	{
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE - 1 - i; j++)
				if (bubbleSortArray[j] > bubbleSortArray[j + 1])
					swap(bubbleSortArray, j, j + 1);
	}
	
	/**
	 * Swap two elements in the array
	 * @param bubbleSortArray
	 * @param i
	 * @param j
	 */
	public static void swap(double[] bubbleSortArray, int i, int j)
	{
		double tempNumber = bubbleSortArray[i];
		bubbleSortArray[i] = bubbleSortArray[j];
		bubbleSortArray[j] = tempNumber; 
	}
	
	/**
	 * Display each element in the array
	 * 
	 * @param bubbleSortArray
	 */
	public static void displayArray(double[] bubbleSortArray)
	{
		for (int i = 0; i < SIZE; i++)
			System.out.printf("%-6.2f", bubbleSortArray[i]);
		System.out.println();
	}
	
	/**
	 * Insert random double elements into the array
	 * 
	 * @param bubbleSortArray
	 */
	public static void insertNumbers(double[] bubbleSortArray)
	{
		Random randomNumber = new Random();
		
		for (int i = 0; i < SIZE; i++)
			bubbleSortArray[i] = randomNumber.nextDouble() * 10;
	}
}
