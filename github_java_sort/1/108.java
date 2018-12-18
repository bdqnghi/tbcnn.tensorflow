package com.algo.sorting;

public class InsertionSortJava {

	public static void print(int numbers[]) {
		for (int i = 0; i < numbers.length - 1; i++) {
			System.out.print(numbers[i] + " ");
		}
	}

	public static int[] swap(int numbers[], int i, int j) {
		int temp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = temp;
		return numbers;
	}

	public static int[] sort(int array[]) {
		for (int index = 1; index < array.length; index++) {
			for (int indexj = 0; indexj < index-1; indexj++)
				if (array[indexj] > array[index]) {
					array = swap(array, indexj, index);
				}
		}
		return array;
	}

	public static void main(String[] args) {
		int numbers[] = new int[] { 24, 67, 89, 24, 5, 7, 456, 789, 34, 98, -1 };
		int num[] = sort(numbers);
		print(num);
	}

}
