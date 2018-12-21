package Chapter_07_Single_Dimensional_Arrays;

import java.util.Random;



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
	
	
	public static void bubbleSort(double[] bubbleSortArray)
	{
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE - 1 - i; j++)
				if (bubbleSortArray[j] > bubbleSortArray[j + 1])
					swap(bubbleSortArray, j, j + 1);
	}
	
	
	public static void swap(double[] bubbleSortArray, int i, int j)
	{
		double tempNumber = bubbleSortArray[i];
		bubbleSortArray[i] = bubbleSortArray[j];
		bubbleSortArray[j] = tempNumber; 
	}
	
	
	public static void displayArray(double[] bubbleSortArray)
	{
		for (int i = 0; i < SIZE; i++)
			System.out.printf("%-6.2f", bubbleSortArray[i]);
		System.out.println();
	}
	
	
	public static void insertNumbers(double[] bubbleSortArray)
	{
		Random randomNumber = new Random();
		
		for (int i = 0; i < SIZE; i++)
			bubbleSortArray[i] = randomNumber.nextDouble() * 10;
	}
}
